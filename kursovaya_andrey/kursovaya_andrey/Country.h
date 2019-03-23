#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Republic.h"
#pragma once
using namespace std;
class Country
{
private:
	Republic *top_of_stack = NULL;
	string name_of_country = "";
	int number_of_republics = 0;
public:
	Country(string name) {
		name_of_country = name;
	}
	void Add_City() {
		if(top_of_stack != NULL)
		top_of_stack->Add_City();
		else {
			cout << "Нельзя добавить город! Сначала добавьте Республику!" << endl;
			system("pause");
		}
	}
	void Download_Add_Republic(string name) {
		Republic *new_republic = new Republic(name);
			new_republic->Set_Next(top_of_stack);
			top_of_stack = new_republic;
			number_of_republics++;
	}
	void Remove_country() {
		if (top_of_stack != NULL) {
			while (top_of_stack != NULL) {
				Republic *temp = top_of_stack;
				top_of_stack = top_of_stack->Get_Next();
				delete temp;
			}
			number_of_republics=0;
		}
	}
	string Check_To_Number(string number) {
		if (number.empty() || number == "") { return ""; }
		for (int i = 0; i < number.size(); i++) {
			if (number.at(i) != '1' && number.at(i) != '0' && number.at(i) != '2' && number.at(i) != '3' && number.at(i) != '4' && number.at(i) != '5' && number.at(i) != '6' && number.at(i) != '7' && number.at(i) != '8' && number.at(i) != '9')
			{
				return "";
			}
		}
		if (number.size() > 1) {
			if (number.at(0) == '0' && (number.at(0) == '0' || number.at(0) == '1' || number.at(0) == '2' || number.at(0) == '3' || number.at(0) == '4' || number.at(0) == '5' || number.at(0) == '6' || number.at(0) == '7' || number.at(0) == '8' || number.at(0) == '9')) { return ""; }
		}
		return number;
	}
	void Download_From_File()    //загрузка из файла
	{
		Remove_country();//удаляем все
		int _find_republic = 0;//условие если метка города стоит до республики
		int stop_reding_file = 0;//условие пока не закончится файл
		string line = "";//строка
		ifstream file("data_base.txt");
		if (file.is_open()) // если файл открыт
		{
			getline(file, line);
			line = Check_To_Void(line);
			while (stop_reding_file != 5)//пока не достиг конец файла считывает строки из файла
			{
				if (line == "Республика:") {//если нашёл метку
					_find_republic = 0;
					if (!file.eof()) {//не конец файла
						getline(file, line);
						line = Check_To_Void(line);
					}
					if (!file.eof()) {//не конец файла
						int reading_if_empty = 1;
						if (line.empty() || line == "") { reading_if_empty = 0; }//если строка пуста, то вызывается цикл
						while (reading_if_empty != 1)//считывает строки из файла, пока не найдёт символ или не наступит конец файла
						{
							if (line.empty() || line == "") {
								if (!file.eof()) {
									getline(file, line);
									line = Check_To_Void(line);
								}
								else { reading_if_empty = 1; }
							}
							else { reading_if_empty = 1; }
						}
						if (file.eof()) { stop_reding_file = 5; }//конец файла
						if (line != "Республика:"&& line != "Города:" && !line.empty())//если после метки след. строка не является меткой и не пуста
						{
							_find_republic = 1;
							Download_Add_Republic(line);
							if (!file.eof()) {//если не конец файла, то считывает след. строку
								getline(file, line);
								line = Check_To_Void(line);
							}
							else { stop_reding_file = 5; }
							int reading_if_empty = 1;
							if (line.empty() || line == "") { reading_if_empty = 0; }//если строка пуста, или пробелы
							while (reading_if_empty != 1)//пока строка пуста считает строки
							{
								if (line.empty() || line == "") {
									if (!file.eof()) {
										getline(file, line);
										line = Check_To_Void(line);
									}
									else { reading_if_empty = 1; }
								}
								else { reading_if_empty = 1; }
							}
							if (file.eof()) { stop_reding_file = 5; }
							if (line != "Республика:" && line != "Города:" && !line.empty())//если следующая строка после названия республики не является меткой или пустой
							{
								cout << "Ошибка! В файле каждая Республика должна иметь свою метку!" << endl << "Республика " << line << " не имеет своей метки!" << endl;
								system("pause");
								file.close();
								return;
							}
						}
					}
					else { stop_reding_file = 5; }//если конец файла
				}
				else if (line == "Города:") {//если равен метке
					string _people_number;
					int do_if_not_find_metka = 0;
					if (_find_republic != 1) { //если метка города написана в файле до метки республика
						do_if_not_find_metka = 1; 
						stop_reding_file = 5; 
						cout << "Не указана Республика!" << endl; 
						system("pause"); 
					}
					while (do_if_not_find_metka != 1) {//выполняется пока не наступит конец файла или не найдётся ни одна метка
						if (!file.eof()) {//не достиг конца файла - считывает строку
							getline(file, line);
							line = Check_To_Void(line);
						}
						if (!file.eof()) {//не достиг конца файла
							int reading_if_empty = 1;
							if (line.empty() || line == "") { reading_if_empty = 0; }
							while (reading_if_empty != 1)//выполняется пока строка пуста или там только пробелы и табуляции, закончится если там символ или конец файла
							{
								if (line.empty() || line == "") {//строка пуста
									if (!file.eof()) {
										getline(file, line);
										line = Check_To_Void(line);
									}
									else reading_if_empty = 1;
								}
								else { reading_if_empty = 1; }//если символ нашёлся
								if (file.eof()) { reading_if_empty = 1; }
							}
							if ((file.eof()) || line == "Республика:" || line == "Города:") { do_if_not_find_metka = 1; }//нашёл метку, выходит из цикла line=="Города"
							else {//если не конец файла и не нашёл метку
								if (!file.eof()) {
									getline(file, _people_number);
									_people_number = Check_To_Void(_people_number);
								}
								int reading_if_empty = 1;
								if (_people_number.empty() || _people_number == "") { reading_if_empty = 0; }
								while (reading_if_empty != 1)//пока строка пуста или не конец файла
								{
									if (file.eof()) {//конец файла
										reading_if_empty = 1;
										do_if_not_find_metka = 1;
										stop_reding_file = 5;
									}
									if (_people_number.empty() || _people_number == "") {//строка пуста
										if (!file.eof()) {
											getline(file, _people_number);
											_people_number = Check_To_Void(_people_number);
										}
										else reading_if_empty = 1;//конец файла
									}
									else { reading_if_empty = 1; }//строка не пуста
								}

								if (file.eof()) { stop_reding_file = 5; do_if_not_find_metka = 1; }//конец файла
								if (_people_number != "Республика:" && _people_number != "Города:" && !_people_number.empty() && !(_people_number == ""))//если следующая строка после числа жителей не является меткой
								{
									string ggg = _people_number;
									_people_number = Check_To_Number(_people_number);
									if (_people_number == "") {//если в количестве жителей есть символы - не является цифрой
										cout << "Ошибка в количестве жителей города! ---- " << ggg << endl;
										file.close(); system("pause"); return;
									}
									if (top_of_stack->Download_Add_City(line, _people_number) == false) {
										stop_reding_file = 5; file.close(); return;
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
				if (line.empty())//если строка пуста
				{
					if (!file.eof()) {
						getline(file, line);
						line = Check_To_Void(line);
					}
				}
				if (line != "Республика:" && line != "Города:" && !line.empty())//если в файле строка не равен меткам и не пуста (до первой метки)
				{
					bool if_empty = false;
					for (int j = 0; j < line.length(); j++)//проверка на пустоту
					{
						if (line.at(j) != ' ') { if_empty = true; }
					}
					if (if_empty == true) {// ошибку выводит, если не пуста строка до первой метки
						cout << "Ошибка! Данные находятся вне метки (в начале файла)!" << endl;
						system("pause");
						file.close();
						return;
					}
					else {//строка пуста
						if (!file.eof()) {//не достиг конца файла
							getline(file, line);
							line = Check_To_Void(line);
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
	void Save_to_file(string choice) {
		if (choice == "1" || choice == "2") {
			if (choice == "2")
			{
				remove("data_base.txt");
			}
			fstream txt("data_base.txt", ios::app);
			if (txt.is_open()) // вызов метода is_open()
			{
				if (top_of_stack != NULL)
				{
					for (int j = 0; j < number_of_republics; j++)
					{
						Republic *temp = top_of_stack;
						for (int i = (number_of_republics - 1 - j); i > 0; i--) {
							temp = temp->Get_Next();
						}
						txt << " Республика:" << endl;
						txt << temp->Get_name_of_republic() << endl;
						temp->Save_to_file();
					}
					txt.close();
					cout << "Данные сохранены в файл" << endl;
					system("pause");
					return;
				}
				cout << "Данные сохранены в файл" << endl;
				system("pause");
				txt.close();
				return;
			}
			else
			{
				cout << "Файл не открыт!\n\n" << endl;
				system("pause");
				return;
			}
		}
		else {
			cout << "Ошибка! Введите цифру 1 или 2" << endl;
			system("pause");
			return;
		}
	}
	void Remove_Republic() {
		if (top_of_stack != NULL) {
			Republic *temp = top_of_stack;
			top_of_stack = top_of_stack->Get_Next();
			delete temp;
			number_of_republics--;
			cout << "Республика удалена!" << endl;
			system("pause");
		}
		else {
			cout << "Нельзя удалить республику! Сначала добавьте Республику!" << endl;
			system("pause");
		}
	}
	string Check_To_Void(string name_of_republic) {    //преобразовать строку
		if (name_of_republic.size() > 4700) {
			cout << "Ошибка! Вводимые символы не должны быть больше 4700!" << endl;
			system("pause");
			return "Error";
		}
		string finished_name;
		char symbols[4700];
		strcpy_s(symbols, name_of_republic.c_str());
		char *words = strtok(symbols, " \t");
		while (words != NULL)
		{
			finished_name += words;
			words = strtok(NULL, " \t");
		}
		return finished_name;
	}
	void Add_Republic() 
	{
		string name_of_republic = "";
		do {
			system("cls");
			cout << "Название Реуспублики :";
			getline(cin, name_of_republic);
			name_of_republic = Check_To_Void(name_of_republic);
		} while (name_of_republic == "" || name_of_republic == "Республика:" || name_of_republic == "Города:");
		Republic *temp = new Republic(name_of_republic);
			temp->Set_Next(top_of_stack);
			top_of_stack = temp;
			number_of_republics++;
			cout << "Республика добавлена!" << endl;
			system("pause");
	}
	void Remove_City() {
		if (top_of_stack != NULL)
			top_of_stack->Remove_City();
		else {
			cout << "Нельзя удалить город! Сначала добавьте Республику!" << endl;
			system("pause");
		}
	}
	void Show() {//вершина показывается в самом верху
		cout << "                       Страна - " << name_of_country << endl;
		if (top_of_stack != NULL) {
			Republic *temp = top_of_stack;
			while (temp != NULL) {
				cout << "Республика - " << temp->Get_name_of_republic() << endl;
				temp->Show();
				temp = temp->Get_Next();
			}
		}
		system("pause");
	}
	Country() {}
	~Country() {
		if (top_of_stack != NULL) {
			while (top_of_stack != NULL) {
				Republic *temp = top_of_stack;
				top_of_stack = top_of_stack->Get_Next();
				temp->~Republic();
			}
			number_of_republics = 0;
			name_of_country = "";
		}
	}
};

