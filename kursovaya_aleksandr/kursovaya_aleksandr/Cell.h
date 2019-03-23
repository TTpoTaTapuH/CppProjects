#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
using namespace std;
#pragma once
class Cell
{
private:
	string number, txt;
public:
	string Get_Number() {
		return number;
	}
	void Delete() {
		number = "";
		txt = "";
	}
	string Check_Void(string line_name, int key) {    //преобразовать строку
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
			if (key == 1) {
				if (next_word != NULL)
					word_end += ' ';
			}
		}
		return word_end;
	}
	string Get_Txt() {
		return txt;
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
	void Add() {
		string nomer = "";
		do {
			system("cls");
			cout << "Номер ячейки : " << endl;
			getline(cin, nomer);
			nomer = Check_Number(Check_Void(nomer, 0));
		} while (nomer == "");
		number = nomer;
		string tx = "";
		do {
			system("cls");
			cout << "Текст : " << endl;
			getline(cin, tx);
			tx = Check_Void(tx, 1);
		} while (tx == "" || tx == "Строка:" || tx == "Ячейки:");
		txt = tx;
		cout << "Ячейка добавлена!" << endl;
		system("pause");
	}
	void Show() {
		cout << "             Строка : " << number << " --- " << txt << endl;
	}
	Cell();
	void Download_Cell(string num, string text) {
		number = num;
		txt = text;
	}
	~Cell() {
		number = "";
		txt = "";
	}
};