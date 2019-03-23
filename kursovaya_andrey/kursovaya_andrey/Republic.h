#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "City.h"
#pragma once
using namespace std;
class Republic
{
private:
	const int number = 7;
	string name_of_republic = "";
	Republic *next;
	City *city = NULL;
	int top_of_stack = 0;
public:
	void Remove_City() {
		if (top_of_stack > 0) {
			top_of_stack--;
			city[top_of_stack].Set_name_of_city("");
			city[top_of_stack].Set_number_of_people("");
			cout << "Город удалён" << endl;
			system("pause");
		}
		else {
			cout << "Нельзя удалить город! В данной республике нету городов!" << endl;
			system("pause");
		}
	}
	Republic(string name) {
		name_of_republic = name;
		city = new City[number];
	}
	Republic() {}
	bool Download_Add_City(string name_of_city, string number_of_people) {
		if (top_of_stack < number) {
			city[top_of_stack].Set_name_of_city(name_of_city);
			city[top_of_stack].Set_number_of_people(number_of_people);
			top_of_stack = top_of_stack + 1;
			return true;
		}
		else {
			cout << "Нельзя добавить город! Число городов достигла предела в данной республике!" << endl;
			system("pause");
			return false;
		}
	}
	void Set_Next(Republic *repub) {
		next = repub;
	}
	Republic* Get_Next() {
		return next;
	}
	void Set_name_of_republic(string name) {
		name_of_republic = name;
	}
	string Get_name_of_republic() {
		return name_of_republic;
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
	void Add_City() {
		if (top_of_stack < number) {
			string name_of_city = "";
			do {
				system("cls");
				cout << "Название города :";
				getline(cin, name_of_city);
				name_of_city = Check_To_Void(name_of_city);
			} while (name_of_city == "" || name_of_city == "Республика:" || name_of_city == "Города:");
			string number_of_people = "";
			do {
				system("cls");
				cout << "Численность населения :";
				getline(cin, number_of_people);
				number_of_people = Check_To_Number(Check_To_Void(number_of_people));
			} while (number_of_people == "");
			city[top_of_stack].Set_name_of_city(name_of_city);
			city[top_of_stack].Set_number_of_people(number_of_people);
			top_of_stack = top_of_stack + 1;
			cout << "Город добавлен!" << endl;
			system("pause");
		}
		else {
			cout << "Нельзя добавить город! Число городов достигла предела в данной республике!" << endl;
			system("pause");
		}
	}
	void Save_to_file() {
		fstream txt("data_base.txt", ios::app); 
		if (txt.is_open())
		{
			if (top_of_stack > 0) {
				txt << "        Города:" << endl;
				for (int i = 0; i<top_of_stack; i++) {
					txt << "                 " << city[i].Get_name_of_city() << endl;
					txt << "                 " << city[i].Get_number_of_people() << endl;
				}
				txt.close();
				return;
			}
			txt.close();
		}
		else
		{
			cout << "Файл не открыт!\n\n" << endl;
			system("pause");
		}
	}
	void Show() {
		for (int i = top_of_stack; i > 0; i--) {
			cout << "	         Город - "<< city[i-1].Get_name_of_city() << endl;
			cout << "	     Население - "<< city[i-1].Get_number_of_people() << endl << endl;
		}
	}
	~Republic() {
		for (int i = number - 1; i >= 0; i--) {
			city[i].~City();
		}
		name_of_republic = "";
		next = NULL;
		top_of_stack = NULL;
	}
};

