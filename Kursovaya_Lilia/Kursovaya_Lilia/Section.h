#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Celler.h"
#pragma once
using namespace std;
class Section
{
private:
	Celler *cell = NULL;
	string name;
	int count=0;//���-�� �����
public:
	void DeleteAllCell() {
		if (cell != NULL) {
			while (cell != NULL) {
				Celler *temp = cell;
				cell = cell->GetNext();
				delete temp;
				count--;
			}
		}
	}
	void DeleteCell() {
		if (cell != NULL) {
			Celler *temp = cell;
			cell = cell->GetNext();
			delete temp;
			count--;
			cout << "������ �������!" << endl;
			system("pause");
			return;
		}
		else {
			cout << "������! ����� ���" << endl;
			system("pause");
		}
	}
	void SaveToFile() {
			if (cell != NULL)
			{
				Celler *temp1 = cell;
				Celler *arr = new Celler[count];
				for (int i = 0; i < count; i++)
				{
					arr[i] = *temp1;
					temp1 = temp1->GetNext();
				}//������ ������� ����� ��� ���������� � ����, ������� � ����� � ����� �����
				fstream txt("file.txt", ios::app); 
				if (txt.is_open()) // ����� ������ is_open()
				{
					txt << "           ������:" << endl;
					for (int i = count - 1; i >= 0; i--)
					{
						txt << arr[i].GetNumber() << endl;
						txt << arr[i].GetEmployment() << endl;
					}
					txt.close();
				}
				else
				{
					cout << "���� �� ������!\n\n" << endl;
					system("pause");
					return;
				}
			}
	}
	void Show() {
		if (cell != NULL) {
			Celler *temp = cell;
			while (temp != NULL)
			{
				cout << "   ������ - " << temp->GetNumber() << endl;
				cout << "��������� - " << temp->GetEmployment() << endl<<endl;
				temp = temp->GetNext();
			}
		}
	}
	string Pustclear(string str) {    //������������� ������
		if (str.size() > 5000) {
			cout << "������! �������� ������� �� ������ ���� ������ 5000!" << endl;
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
		return str;
	}
	void AddForDownloadCell(string number, string busy) {
		Celler *temp = new Celler(number, busy);
		if (cell == NULL) {
			temp->SetNext(NULL);
			cell = temp;
			count++;
		}
		else {
			temp->SetNext(cell);
			cell = temp;
			count++;
		}
	}
	void AddCell() {
		string nomer = "";
		do {
			system("cls");
			cout << "����� ������ :";
			getline(cin, nomer);
			nomer = Proverka(Pustclear(nomer));
		} while (nomer=="");
		string busy = "";
		do {
			system("cls");
			cout << "������� ��������� :";
			getline(cin, busy);
			busy = Pustclear(busy);
		} while (busy==""||busy== "������:" ||busy=="������:");
		Celler *temp = new Celler(nomer, busy);
		if (cell == NULL) {
			temp->SetNext(NULL);
			cell = temp;
			count++;
			cout << "������ ���������!" << endl;
			system("pause");
		}
		else {
			temp->SetNext(cell);
			cell = temp;
			count++;
			cout << "������ ���������!" << endl;
			system("pause");
		}
	}
	void SetName(string n) { name = n; }
	string GetName() { return name; }
	Section() {}
	~Section() {
		if (cell != NULL) {
			while (cell != NULL) {
				Celler *temp = cell;
				cell = cell->GetNext();
				temp->~Celler();
				count--;
			}
		}
	}
};

