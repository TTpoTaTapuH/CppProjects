#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <windows.h>
#include "Line.h"
using namespace std;
#pragma once
class Table
{
private:
	string name;
	Line *line;
public:
	Table(string str) {
		name = str;
		line = NULL;
	}
	void Clear() {
		if (line != NULL) {
			while (line != NULL) {
				Line *temp = line;
				line = line->Get_Right();
				delete temp;
			}
		}
	}
	Line *Download_Add_Line(string li, Line *ptr) {
		Line *temp = new Line(li);
		if (line == NULL) {
			line = temp;
			return temp;
		}
		else {
			ptr->Set_Right(temp);
			temp->Set_Left(ptr);
			return temp;
		}
	}
	void Save_To_File(string key) {
		if (key == "2")
		{
			remove("file.txt");
		}
		fstream txt("file.txt", ios::app); if (txt.is_open()) // вызов метода is_open()
		{
			if (line != NULL) {
				Line *temp = line;
				while (temp != NULL) {
					txt << "Строка:" << endl;
					txt << "       " << temp->Get_Nomer() << endl;
					temp->Save_To_File();
					temp = temp->Get_Right();
				}
			}
			cout << "Данные сохранены в файл." << endl;
			txt.close();
			system("pause");
			return;
		}
		else
		{
			cout << "Файл не открыт!\n\n" << endl;
			system("pause");
			return;
		}
	}
	void Download_From_File()    //загрузка из файла
	{
		Clear();//удаляем все
		Line *liner = line;
		int _find_republic = 0;//условие если метка города стоит до республики
		int stop_reding_file = 0;//условие пока не закончится файл
		string stroka = "";//строка
		ifstream file("file.txt");
		if (file.is_open()) // если файл открыт
		{
			getline(file, stroka);
			stroka = Check_Void(stroka);
			while (stop_reding_file != 5)//пока не достиг конец файла считывает строки из файла
			{
				if (stroka == "Строка:") {//если нашёл метку
					_find_republic = 0;
					if (!file.eof()) {//не конец файла
						getline(file, stroka);
						stroka = Check_Void(stroka);
					}
					if (!file.eof()) {//не конец файла
						int reading_if_empty = 1;
						if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//если строка пуста, то вызывается цикл
						while (reading_if_empty != 1)//считывает строки из файла, пока не найдёт символ или не наступит конец файла
						{
							if (stroka.empty() || stroka == "") {
								if (!file.eof()) {
									getline(file, stroka);
									stroka = Check_Void(stroka);
								}
								else { reading_if_empty = 1; }
							}
							else { reading_if_empty = 1; }
						}
						if (file.eof()) { stop_reding_file = 5; }//конец файла
						if (stroka != "Строка:"&& stroka != "Ячейки:" && !stroka.empty())//если после метки след. строка не является меткой и не пуста
						{
							_find_republic = 1;
							stroka = Check_Number(stroka);
							if (stroka == "") {
								cout << "Ошибке в номере строки!" << endl;
								system("pause");
								file.close();
								return;
							}
							liner = Download_Add_Line(stroka, liner);
							if (!file.eof()) {//если не конец файла, то считывает след. строку
								getline(file, stroka);
								stroka = Check_Void(stroka);
							}
							else { stop_reding_file = 5; }
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//если строка пуста, или пробелы
							while (reading_if_empty != 1)//пока строка пуста считает строки
							{
								if (stroka.empty() || stroka == "") {
									if (!file.eof()) {
										getline(file, stroka);
										stroka = Check_Void(stroka);
									}
									else { reading_if_empty = 1; }
								}
								else { reading_if_empty = 1; }
							}
							if (file.eof()) { stop_reding_file = 5; }
							if (stroka != "Строка:" && stroka != "Ячейки:" && !stroka.empty())//если следующая строка после названия республики не является меткой или пустой
							{
								cout << "Ошибка! В файле каждая Республика должна иметь свою метку!" << endl << "Республика " << stroka << " не имеет своей метки!" << endl;
								system("pause");
								file.close();
								return;
							}
						}
					}
					else { stop_reding_file = 5; }//если конец файла
				}
				else if (stroka == "Ячейки:") {//если равен метке
					string text;
					int do_if_not_find_metka = 0;
					if (_find_republic != 1) { //если метка города написана в файле до метки республика
						do_if_not_find_metka = 1;
						stop_reding_file = 5;
						cout << "Не указана Республика!" << endl;
						system("pause");
					}
					while (do_if_not_find_metka != 1) {//выполняется пока не наступит конец файла или не найдётся ни одна метка
						if (!file.eof()) {//не достиг конца файла - считывает строку
							getline(file, stroka);
							stroka = Check_Void(stroka);
						}
						if (!file.eof()) {//не достиг конца файла
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }
							while (reading_if_empty != 1)//выполняется пока строка пуста или там только пробелы и табуляции, закончится если там символ или конец файла
							{
								if (stroka.empty() || stroka == "") {//строка пуста
									if (!file.eof()) {
										getline(file, stroka);
										stroka = Check_Void(stroka);
									}
									else reading_if_empty = 1;
								}
								else { reading_if_empty = 1; }//если символ нашёлся
								if (file.eof()) { reading_if_empty = 1; }
							}
							if ((file.eof()) || stroka == "Строка:" || stroka == "Ячейки:") { do_if_not_find_metka = 1; }//нашёл метку, выходит из цикла line=="Города"
							else {//если не конец файла и не нашёл метку
								if (!file.eof()) {
									getline(file, text);
									text = Check_Void(text);
								}
								int reading_if_empty = 1;
								if (text.empty() || text == "") { reading_if_empty = 0; }
								while (reading_if_empty != 1)//пока строка пуста или не конец файла
								{
									if (file.eof()) {//конец файла
										reading_if_empty = 1;
										do_if_not_find_metka = 1;
										stop_reding_file = 5;
									}
									if (text.empty() || text == "") {//строка пуста
										if (!file.eof()) {
											getline(file, text);
											text = Check_Void(text);
										}
										else reading_if_empty = 1;//конец файла
									}
									else { reading_if_empty = 1; }//строка не пуста
								}

								if (file.eof()) { stop_reding_file = 5; do_if_not_find_metka = 1; }//конец файла
								if (text != "Строка:" && text != "Ячейки:" && !text.empty() && !(text == ""))//если следующая строка после числа жителей не является меткой
								{
									string ggg = stroka;
									stroka = Check_Number(stroka);
									if (text == "") {//если в количестве жителей есть символы - не является цифрой
										cout << "Ошибка в количестве жителей города! ---- " << ggg << endl;
										file.close(); system("pause"); return;
									}
									if (liner->Download_Add_Cell(stroka, text) == false) {
										stop_reding_file = 5; file.close();
										cout << "Ошибка! Число ячеек достигла предела!" << endl;
										system("pause");
										return;
									}
								}
								else {//если у города не указано количество жителей
									do_if_not_find_metka = 1;
									cout << "Ошибка! Город должна иметь жителей!" << endl << "В городе " << line << " не указано количество жителей!" << endl;
									system("pause");
									file.close();
									return;
								}
							}
						}
						else { do_if_not_find_metka = 1; stop_reding_file = 5; }//конец файла
					}
					if (file.eof()) { stop_reding_file = 5; do_if_not_find_metka = 1; }//конец файла
				}
				if (file.eof()) { //конец файла, цикл завершается
					stop_reding_file = 5;

					file.close();
					return;
				}
				if (stroka.empty())//если строка пуста
				{
					if (!file.eof()) {
						getline(file, stroka);
						stroka = Check_Void(stroka);
					}
				}
				if (stroka != "Строка:" && stroka != "Ячейки:" && !stroka.empty())//если в файле строка не равен меткам и не пуста (до первой метки)
				{
					bool if_empty = false;
					for (int j = 0; j < stroka.length(); j++)//проверка на пустоту
					{
						if (stroka.at(j) != ' ') { if_empty = true; }
					}
					if (if_empty == true) {// ошибку выводит, если не пуста строка до первой метки
						cout << "Ошибка! Данные находятся вне метки (в начале файла)!" << endl;
						system("pause");
						file.close();
						return;
					}
					else {//строка пуста
						if (!file.eof()) {//не достиг конца файла
							getline(file, stroka);
							stroka = Check_Void(stroka);
						}
					}
				}
			}
			file.close();
		}
		else//файл не открыт
		{
			cout << "Файл не открыт!" << endl;
			system("pause");
			return;
		}
	}
	string Check_Void(string line_name) {    //преобразовать строку
		if (line_name.size() > 5000) {
			cout << "Ошибка! Вводимые символы не должны быть больше 5000!" << endl;
			system("pause");
			return "Error";
		}
		string word_end;
		char chars[5000];
		strcpy_s(chars, line_name.c_str());
		char *next_word = strtok(chars, " \t");
		while (next_word != NULL)
		{
			word_end += next_word;
			next_word = strtok(NULL, " \t");
		}
		return word_end;
	}
	string Check_Number(string str) {
		if (str.empty() || str == "") { return ""; }
		for (int i = 0; i < str.size(); i++) {
			if (str.at(i) != '1' && str.at(i) != '0' && str.at(i) != '2' && str.at(i) != '3' && str.at(i) != '4' && str.at(i) != '5' && str.at(i) != '6' && str.at(i) != '7' && str.at(i) != '8' && str.at(i) != '9')
			{
				return "";
			}
		}
		if (str.size() > 1) {
			if (str.at(0) == '0' && (str.at(0) == '0' || str.at(0) == '1' || str.at(0) == '2' || str.at(0) == '3' || str.at(0) == '4' || str.at(0) == '5' || str.at(0) == '6' || str.at(0) == '7' || str.at(0) == '8' || str.at(0) == '9')) { return ""; }
		}
		return str;
	}
	void Add_Line() {
		string name_of_line = "";
		if (line == NULL) {
			while (name_of_line == "") {
				system("cls");
				cout << "Номер строки : ";
				getline(cin, name_of_line);
				name_of_line = Check_Number(Check_Void(name_of_line));
			}
			Line *new_line = new Line(name_of_line);
			line = new_line;
			cout << "Строка добавлена" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
				system("cls");
				cout << "1 - Добавить до (прямой поиск)\n2 - Добавить до (обратный поиск) \n3 - Добавить после (прямой поиск) \n4 - Добавить после (обратный поиск) ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				cout << "Введите номер строки для поиска : ";
				getline(cin, line_poisk);
				line_poisk = Check_Number(Check_Void(line_poisk));
			}
			Line *temp = line;
			if (choice == "1" || choice == "3") {
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Right();
				}
			}
			if (choice == "2" || choice == "4") {
				while (temp->Get_Right() != NULL) {
					temp = temp->Get_Right();
				}
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Left();
				}
			}
			if (temp == NULL) {
				cout << "Строка с данным номером не найдена!" << endl;
				system("pause");
				return;
			}
			while (name_of_line == "") {
				system("cls");
				cout << "Номер строки : ";
				getline(cin, name_of_line);
				name_of_line = Check_Number(Check_Void(name_of_line));
			}
			Line *new_line = new Line(name_of_line);
			if (choice == "1" || choice == "2") {
				new_line->Set_Right(temp);
				new_line->Set_Left(temp->Get_Left());
				if (temp->Get_Left() != NULL) {
					temp->Get_Left()->Set_Right(new_line);
				}
				else {
					line = new_line;
				}
				temp->Set_Left(new_line);
			}
			if (choice == "3" || choice == "4") {
				new_line->Set_Right(temp->Get_Right());
				new_line->Set_Left(temp);
				if (temp->Get_Right() != NULL) {
					temp->Get_Right()->Set_Left(new_line);
				}
				temp->Set_Right(new_line);
			}
			cout << "Строка добавлена" << endl;
			system("pause");
			return;
		}
	}
	void Delete_Cell() {
		if (line == NULL) {
			cout << "Ошибка! Строк не существует!" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2") {
				system("cls");
				cout << "Поиск строки для удаления ячейки :\n1 - прямоe направление поиска\n2 - обратное направление поиска : ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				system("cls");
				cout << "Введите номер строки для поиска : ";
				getline(cin, line_poisk);
				line_poisk = Check_Number(line_poisk);
			}
			Line *temp = line;
			if (choice == "1") {
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Right();
				}
			}
			if (choice == "2") {
				while (temp->Get_Right() != NULL) {
					temp = temp->Get_Right();
				}
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Left();
				}
			}
			if (temp == NULL) {
				cout << "Строка с данным номером не найдена!" << endl;
				system("pause");
				return;
			}
			temp->Delete_Cell();
		}
	}
	void Delete_Line() {
		if (line == NULL) {
			cout << "Ошибка! Строк не существует!" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2") {
				system("cls");
				cout << "Поиск строки для удаления строки :\n1 - прямоe направление поиска\n2 - обратное направление поиска : ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				system("cls");
				cout << "Введите номер строки для поиска : ";
				getline(cin, line_poisk);
				line_poisk = Check_Number(line_poisk);
			}
			Line *temp = line;
			if (choice == "1") {
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Right();
				}
			}
			if (choice == "2") {
				while (temp->Get_Right() != NULL) {
					temp = temp->Get_Right();
				}
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Left();
				}
			}
			if (temp == NULL) {
				cout << "Строка с данным номером не найдена!" << endl;
				system("pause");
				return;
			}
			if (temp->Get_Left() != NULL) {
				temp->Get_Left()->Set_Right(temp->Get_Right());
			}
			else {
				line = temp->Get_Right();
			}
			if (temp->Get_Right() != NULL) {
				temp->Get_Right()->Set_Left(temp->Get_Left());
			}
			delete temp;
			cout << "Строка удалена!" << endl;
			system("pause");
			return;
		}
	}
	void Search(int key) {
		if (line != NULL) {
			string ask1 = "";
			while (ask1 != "1" && ask1 != "2") {
				system("cls");
				cout << "Поиск строки : 1 - Прямой обход " << endl << "2 - обратный обход" << endl;
				getline(cin, ask1);
				ask1 = Check_Number(Check_Void(ask1));
			}
			string ask = "";
			while (ask == "") {
				system("cls");
				cout << "Поиск строки (введите номер строки):" << endl;
				getline(cin, ask);
				ask = Check_Number(Check_Void(ask));
			}
			Line *temp = line;
			if (ask1 == "1") {
				while (temp != NULL) {
					if (temp->Get_Nomer() == ask) {
						if (key == 1)
						{
							cout << "Строка с данным номером найдена!" << endl;
							system("pause");
							return;
						}
						if (key == 2) {
							temp->Search_Cell();
							return;
						}
					}
					temp = temp->Get_Right();
				}
				cout << "Строка с данным номером не найдена!" << endl;
				system("pause");
				return;
			}
			if (ask1 == "2") {
				while (temp->Get_Right() != NULL) {
					temp = temp->Get_Right();
				}
				while (temp != NULL) {
					if (temp->Get_Nomer() == ask) {
						if (key == 1)
						{
							cout << "Строка с данным номером найдена!" << endl;
							system("pause");
							return;
						}
						if (key == 2) {
							temp->Search_Cell();
							return;
						}
					}
					temp = temp->Get_Left();
				}
				cout << "Строка с данным номером не найдена!" << endl;
				system("pause");
				return;
			}
		}
	}
	void Add_Cell() {
		if (line == NULL) {
			cout << "Ошибка! Строк не существует!" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2") {
				system("cls");
				cout << "Поиск строки для добавления ячейки :\n1 - прямоe направление поиска\n2 - обратное направление поиска : ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				system("cls");
				cout << "Введите номер строки для поиска : ";
				getline(cin, line_poisk);
				line_poisk = Check_Number(line_poisk);
			}
			Line *temp = line;
			if (choice == "1") {
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Right();
				}
			}
			if (choice == "2") {
				while (temp->Get_Right() != NULL) {
					temp = temp->Get_Right();
				}
				while (temp != NULL) {
					if (temp->Get_Nomer() == line_poisk) {
						break;
					}
					temp = temp->Get_Left();
				}
			}
			if (temp == NULL) {
				cout << "Строка с данным номером не найдена!" << endl;
				system("pause");
				return;
			}
			temp->Add_Cell();
		}
	}
	void Show() {
		cout << "Название абзаца - " << name << endl;
		if (line != NULL) {
			Line *temp = line;
			while (temp != NULL) {
				temp->Show();
				temp = temp->Get_Right();
			}
		}
		system("pause");
	}
	Table() {}
	~Table() {
		name = "";
		if (line != NULL) {
			while (line != NULL) {
				Line *temp = line;
				line = line->Get_Right();
				delete temp;
			}
		}
	}
};

