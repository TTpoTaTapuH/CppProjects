#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
#include "Cell.h"
using namespace std;
#pragma once
class Line
{
private:
	string nomer;
	Line *right = NULL, *left = NULL;
	Cell cell[5];
	int sum = 0;
public:
	Line(string h) {
		nomer = h;
	}
	void Delete_Cell() {
		if (sum > 0) {
			string poisk = "";
			while (poisk == "")
			{
				system("cls");
				cout << "������� ����� ������ ��� ��������" << endl;
				getline(cin, poisk);
			}
			int index = -1;
			for (int i = 0; i < sum; i++) {
				if (cell[i].Get_Number() == poisk) {
					index = i;
					break;
				}
			}
			if (index > -1) {
				for (int i = index; i <sum - 1; i++) {
					cell[i] = cell[i + 1];
				}
				cell[sum - 1].Delete();
				sum--;
				cout << "������ �������!" << endl;
				system("pause");
			}
		}
		else {
			cout << "���� ����� ��� ��������!" << endl;
			system("pause");
			return;
		}
	}
	void Add_Cell() {
		if (sum < 5) {
			if (sum == 0) {
				cell[sum].Add();
				sum++;
			}
			else {
				string ask = "";
				while (ask == "") {
					system("cls");
					cout << "1 - �������� �� 2 - �������� �����" << endl;
					getline(cin, ask);
				}
				if (ask == "1" || ask == "2") {
					string poisk = "";
					while (poisk == "")
					{
						system("cls");
						cout << "������� ����� ������ ��� ������" << endl;
						getline(cin, poisk);
					}
					int index = -1;
					for (int i = 0; i < sum; i++) {
						if (cell[i].Get_Number() == poisk) {
							index = i;
							break;
						}
					}
					if (index > -1) {
						if (ask == "1") {
							for (int i = (sum - 1); i >= index; i--) {
								cell[i + 1] = cell[i];
							}
							cell[index].Add();
							sum++;
						}
						if (ask == "2") {
							for (int i = (sum - 1); i > index; i--) {
								cell[i + 1] = cell[i];
							}
							cell[index + 1].Add();
							sum++;
						}
					}
				}
			}
		}
		else {
			cout << "����� ����� �������� �������!" << endl;
			system("pause");
			return;
		}
	}
	void Show() {
		cout << "      ����� ������ - " << nomer << endl;
		if (sum > 0) {
			for (int i = 0; i < sum; i++) {
				cell[i].Show();
			}
		}
	}
	string Get_Nomer() {
		return nomer;
	}
	Line *Get_Right() {
		return right;
	}
	Line *Get_Left() {
		return left;
	}
	void Set_Left(Line *le) {
		left = le;
	}
	void Set_Right(Line *ri) {
		right = ri;
	}
	void Save_To_File() {
		fstream txt("file.txt", ios::app); if (txt.is_open()) // ����� ������ is_open()
		{
			if (sum > 0) {
				txt << "           ������:" << endl;
				for (int i = 0; i<sum; i++) {
					txt << "                    " << cell[i].Get_Number() << endl;
					txt << "                    " << cell[i].Get_Txt() << endl;
				}
			}
			txt.close();
			return;
		}
		else
		{
			cout << "���� �� ������!\n\n" << endl;
			system("pause");
			return;
		}
	}
	void Search_Cell() {
		if (sum > 0) {
			string poisk = "";
			while (poisk == "")
			{
				system("cls");
				cout << "������� ����� ������ ��� ������" << endl;
				getline(cin, poisk);
			}
			for (int i = 0; i < sum; i++) {
				if (cell[i].Get_Number() == poisk) {
					cout << "����� � ������ ������� �������!" << endl;
					system("pause");
					return;
				}
			}
			cout << "����� � ������ ������� �� �������!" << endl;
			system("pause");
			return;
		}
		else {
			cout << "��� �����!" << endl;
			system("pause");
			return;
		}
	}
	bool Download_Add_Cell(string line, string text) {
		if (sum < 5) {
			cell[sum].Download_Cell(line, text);
			sum++;
			return true;
		}
		else {
			return false;
		}
	}
	Line();
	~Line() {
		nomer = "";
		right = NULL;
		left = NULL;
		for (int i = sum - 1; i >= 0; i--) {
			cell[i].~Cell();
		}
		sum = 0;
	}
};

