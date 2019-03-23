#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Section.h"
#pragma once
using namespace std;
class Sklad
{
private:
	string name;//название склада
	int number,kolvo;//вершина стека и размер массива
	Section* section;//массив
public:
	Sklad(string nam, int kolv) {
		name = nam;
		kolvo = kolv;
		section = new Section[kolvo];
		number = 0;
	}
	void DeleteSection() {
		if (number > 0) {
			section[number - 1].DeleteAllCell();
			section[number - 1].SetName("");
			number--;
			cout << "Секция удалена!" << endl;
			system("pause");
		}
		else {
			cout << "Ошибка! Секций не существует!" << endl;
			system("pause");
		}
	}
	void Deleting() {
		if (number > 0) {
			while (number > 0) {
				section[number - 1].DeleteAllCell();
				section[number - 1].SetName("");
				number--;
			}
		}
	}
	void DeleteCell() {
		if (number > 0) {
			cout << "1 - Удалить ячейку из вершины стека \n2 - Удалить ячейку из заданной секции" << endl;
			string add = "";
			getline(cin, add);
			if (add == "1") {
				section[number - 1].DeleteCell();
				return;
			}
			else if (add == "2") {
				cout << "Введите номер секции - " << endl;
				string addsec = "";
				getline(cin, addsec);
				for (int i = 0; i < number; i++) {
					if (section[i].GetName() == addsec) {
						section[i].DeleteCell();
						return;
					}
				}
				cout << "К сожалению секция с данным номером не найдена!" << endl;
				system("pause");
			}
		}
			else {
				cout << "Ошибка! Секций не существует!" << endl;
				system("pause");
			}
	}
	string Pustclear(string str) {    //преобразовать строку
		if (str.size() > 5000) {
			cout << "Ошибка! Вводимые символы не должны быть больше 1000!" << endl;
			system("pause");
			return "Error";
		}
		string endword;
		char chars[5000];
		strcpy_s(chars, str.c_str());
		char *nextword = strtok(chars, " \t");
		while (nextword != NULL)
		{
			endword += nextword;
			nextword = strtok(NULL, " \t");
		}
		return endword;
	}
	string Proverka(string str) {
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
	void Show() {//вершина показывается в самом верху
		cout << "                          Название склада - " << name << " :" << endl;
		for(int i=number-1;i>=0;i--){
			cout << "             Секция № - " << section[i].GetName()<< " :" << endl;
			section[i].Show();
		}
		system("pause");
	}
	void SaveToFile(string www) { //сохранить в файл
			if (www == "2")
			{
				remove("file.txt");
			}
			fstream txt("file.txt", ios::app); if (txt.is_open()) // вызов метода is_open()
			{
				if (number > 0) {
					for (int i = 0; i < number; i++) {
						txt << "			 Секция:" << endl;
						txt << "            " << section[i].GetName() << endl;
						section[i].SaveToFile();
					}
					txt.close();
					cout << "Данные сохранены в файл" << endl;
					system("pause");
					return;
				}
			}
			else
			{
				cout << "Файл не открыт!\n\n" << endl;
				system("pause");
				return;
			}
	}
	void AddSection() {
		if (number < kolvo) {
			string numbe = "";
			do {
				system("cls");
				cout << "Введите номер секции : ";
				getline(cin, numbe);
				numbe = Proverka(Pustclear(numbe));
			} while (numbe == "");
			section[number].SetName(numbe);
			number++;
			cout << "Секция добавлена!" << endl;
			system("pause");
		}
		else {
			cout << "Число секций достигла лимита" << endl;
			system("pause");
		}
	}
	bool AddForDownloadSection(string sec) {
		if (number < kolvo) {
			section[number].SetName(sec);
			number++;
			return true;
		}
		else {
			cout << "Число секций достигла лимита" << endl;
			system("pause");
			return false;
		}
	}
	void AddCell() {
		if (number > 0) {
			cout << "1 - Добавить ячейку в вершину стека \n2 - Добавить ячейку в заданную секцию" << endl;
			string add = "";
			getline(cin, add);
			if (add == "1"){
				section[number - 1].AddCell();
				return;
			}
			else if (add == "2") {
				cout << "Введите номер секции - " << endl;
				string addsec = "";
				getline(cin, addsec);
				for (int i = 0; i < number; i++) {
					if (section[i].GetName() == addsec) {
						section[i].AddCell();
						return;
					}
				}
				cout << "К сожалению секция с данным номером не найдена!" << endl;
				system("pause");
			}
			else { 
				cout << "Ошибка! Введите цифру 1 или 2" << endl;
				system("pause");
			}
		}
		else {
			cout << "Ошибка! Создайте секцию" << endl;
			system("pause");
		}
	}
	void DownloadFromFile()    //загрузка из файла
	{
		Deleting();//удаляем все кроме заголовка
		int find_first_section = 0;//условие если метка ячейки находятся до первой метки
		int stop_reding_txt_file = 0;//условие пока не закончится файл
		string stroka = "";
		ifstream txt("file.txt");
		if (txt.is_open()) // если файл открыт
		{
			getline(txt, stroka);
			stroka = Pustclear(stroka);
			while (stop_reding_txt_file != 5)//пока не достиг конец файла считывает строки из файла
			{
				if (stroka == "Секция:") {//если в строке есть метка Секция
					find_first_section = 0;
					if (!txt.eof()) {//не конец файла
						getline(txt, stroka);
						stroka = Pustclear(stroka);
					}
					if (!txt.eof()) {//не конец файла
						int reading_if_empty = 1;
						if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//если строка пуста, то вызывается цикл
						while (reading_if_empty != 1)//считывает строки из файла, пока не найдёт символ или не наступит конец файла
						{
							if (stroka.empty() || stroka == "") {
								if (!txt.eof()) {
									getline(txt, stroka);
									stroka = Pustclear(stroka);
								}
								else { reading_if_empty = 1; }
							}
							else { reading_if_empty = 1; }
						}
						if (txt.eof()) { stop_reding_txt_file = 5; }//конец файла
						if (stroka != "Секция:"&& stroka != "Ячейки:" && !stroka.empty())//если после метки след. строка не является меткой и не пуста
						{
							stroka = Proverka(stroka);
							if (stroka == "") {
								cout << "Ошибка в номере секции!" << endl;//если не цифра
								txt.close(); system("pause"); return;
							}
							find_first_section = 1;
							if (AddForDownloadSection(stroka) == false) {
								stop_reding_txt_file = 5; txt.close(); return;
							}//добавляет секцию и возвращает true если не заполнен массив
							if (!txt.eof()) {//если не конец файла, то считывает след. строку
								getline(txt, stroka);
								stroka = Pustclear(stroka);
							}
							else { stop_reding_txt_file = 5; }
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//если строка пуста, или там пробелы, то
							while (reading_if_empty != 1)//пока строка пуста, считывает строки пока не найдёт символ
							{
								if (stroka.empty() || stroka == "") {
									if (!txt.eof()) {
										getline(txt, stroka);
										stroka = Pustclear(stroka);
									}
									else { reading_if_empty = 1; }
								}
								else { reading_if_empty = 1; }
							}
							if (txt.eof()) { stop_reding_txt_file = 5; }
							if (stroka != "Секция:" && stroka != "Ячейки:" && !stroka.empty())//если следующая строка после номера секции не является меткой или пустой, то выполняется это условие
							{
								cout << "Ошибка! В файле каждая секция должна иметь свою метку!" << endl << "Секция с номером " << stroka << " не имеет своей метки!" << endl;
								system("pause");
								txt.close();
								return;
							}
						}
					}
					else { stop_reding_txt_file = 5; }//если конец файла
				}
				else if (stroka == "Ячейки:") {//если равен метке Ячейки
					string busy;
					int do_if_not_find_metka = 0;
					if (find_first_section != 1) { do_if_not_find_metka = 1; stop_reding_txt_file = 5; cout << "Не указана секция!" << endl; system("pause"); }//если метка ячейки стоит до метки секция
					while (do_if_not_find_metka != 1) {//выполняется пока не наступит конец файла или не найдётся ни одна метка
						if (!txt.eof()) {//не достиг конца файла - считывает строку
							getline(txt, stroka);
							stroka = Pustclear(stroka);
						}
						if (!txt.eof()) {//не достиг конца файла
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }
							while (reading_if_empty != 1)//выполняется пока строка пуста или там только пробелы и табуляции, закончится если там символ или конец файла
							{
								if (stroka.empty() || stroka == "") {//строка пуста
									if (!txt.eof()) {
										getline(txt, stroka);
										stroka = Pustclear(stroka);
									}
									else reading_if_empty = 1;
								}
								else { reading_if_empty = 1; }//если символ нашёлся
								if (txt.eof()) { reading_if_empty = 1; }
							}
							if ((txt.eof()) || stroka == "Секция:" || stroka == "Ячейки:") { do_if_not_find_metka = 1; }//нашёл метку, выходит из цикла, и сравнивает эту строку на метки
							else {//если не конец файла и не нашёл метку
								if (!txt.eof()) {
									getline(txt, busy);
									busy = Pustclear(busy);
								}
								int reading_if_empty = 1;
								if (busy.empty() || busy == "") { reading_if_empty = 0; }
								while (reading_if_empty != 1)//пока строка пуста или не конец файла
								{
									if (txt.eof()) {//конец файла
										reading_if_empty = 1;
										do_if_not_find_metka = 1;
										stop_reding_txt_file = 5;
									}
									if (busy.empty() || busy == "") {//строка пуста
										if (!txt.eof()) {
											getline(txt, busy);
											busy = Pustclear(busy);
										}
										else reading_if_empty = 1;//конец файла
									}
									else { reading_if_empty = 1; }//строка не пуста
								}

								if (txt.eof()) { stop_reding_txt_file = 5; do_if_not_find_metka = 1; }//конец файла
								if (busy != "Секция:" && busy != "Ячейки:" && !busy.empty() && !(busy == ""))//если следующая строка после номера ячейки h1 (занятость) не является меткой 
								{
									string ggg = stroka;
									stroka = Proverka(stroka);
									if (stroka == "") {
										cout << "Ошибка в номере ячейки! ---- " << ggg << endl;//если в номере есть символы - не является цифрой
										txt.close(); system("pause"); return;
									}
									section[number-1].AddForDownloadCell(stroka, busy);
								}
								else {//если призак занятости - строка - является меткой, т.е. нету признака
									do_if_not_find_metka = 1;
									cout << "Ошибка! ячейка должна иметь признак занятости!" << endl << "Ячейка с номером " << stroka << " не имеет признак занятости!" << endl;
									system("pause");
									txt.close();
									return;
								}
							}
						}
						else { do_if_not_find_metka = 1; stop_reding_txt_file = 5; }//конец файла
					}
					if (txt.eof()) { stop_reding_txt_file = 5; do_if_not_find_metka = 1; }//конец файла
				}
				if (txt.eof()) { //конец файла, цикл завершается
					stop_reding_txt_file = 5;

					txt.close();
					return;
				}
				if (stroka.empty())//если строка пуста
				{
					if (!txt.eof()) {
						getline(txt, stroka);
						stroka = Pustclear(stroka);
					}
				}
				if (stroka != "Секция:" && stroka != "Ячейки:" && !stroka.empty())//если в файле строка не равен меткам и не пуста (до первой метки)
				{
					bool if_empty = false;
					for (int j = 0; j < stroka.length(); j++)//проверка на пустоту
					{
						if (stroka.at(j) != ' ') { if_empty = true; }
					}
					if (if_empty == true) {// ошибку выводит, если не пуста строка до первой метки
						cout << "Ошибка! Данные находятся до первой метки!" << endl;
						system("pause");
						txt.close();
						return;
					}
					else {//строка пуста
						if (!txt.eof()) {//не достиг конца файла
							getline(txt, stroka);
							stroka = Pustclear(stroka);
						}
					}
				}
			}
			txt.close();
		}
		else//файл не открыт
		{
			cout << "Файл не открыт!" << endl;
			system("pause");
			return;
		}
	}
	Sklad() {}
	~Sklad() {
		name = "";
		for (int i = kolvo-1; i >=0; i--) {
			section[i].~Section();
		}
		number = NULL;
		kolvo = NULL;
	}
};
