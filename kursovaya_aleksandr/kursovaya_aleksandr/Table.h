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
		fstream txt("file.txt", ios::app); if (txt.is_open()) // ����� ������ is_open()
		{
			if (line != NULL) {
				Line *temp = line;
				while (temp != NULL) {
					txt << "������:" << endl;
					txt << "       " << temp->Get_Nomer() << endl;
					temp->Save_To_File();
					temp = temp->Get_Right();
				}
			}
			cout << "������ ��������� � ����." << endl;
			txt.close();
			system("pause");
			return;
		}
		else
		{
			cout << "���� �� ������!\n\n" << endl;
			system("pause");
			return;
		}
	}
	void Download_From_File()    //�������� �� �����
	{
		Clear();//������� ���
		Line *liner = line;
		int _find_republic = 0;//������� ���� ����� ������ ����� �� ����������
		int stop_reding_file = 0;//������� ���� �� ���������� ����
		string stroka = "";//������
		ifstream file("file.txt");
		if (file.is_open()) // ���� ���� ������
		{
			getline(file, stroka);
			stroka = Check_Void(stroka);
			while (stop_reding_file != 5)//���� �� ������ ����� ����� ��������� ������ �� �����
			{
				if (stroka == "������:") {//���� ����� �����
					_find_republic = 0;
					if (!file.eof()) {//�� ����� �����
						getline(file, stroka);
						stroka = Check_Void(stroka);
					}
					if (!file.eof()) {//�� ����� �����
						int reading_if_empty = 1;
						if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//���� ������ �����, �� ���������� ����
						while (reading_if_empty != 1)//��������� ������ �� �����, ���� �� ����� ������ ��� �� �������� ����� �����
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
						if (file.eof()) { stop_reding_file = 5; }//����� �����
						if (stroka != "������:"&& stroka != "������:" && !stroka.empty())//���� ����� ����� ����. ������ �� �������� ������ � �� �����
						{
							_find_republic = 1;
							stroka = Check_Number(stroka);
							if (stroka == "") {
								cout << "������ � ������ ������!" << endl;
								system("pause");
								file.close();
								return;
							}
							liner = Download_Add_Line(stroka, liner);
							if (!file.eof()) {//���� �� ����� �����, �� ��������� ����. ������
								getline(file, stroka);
								stroka = Check_Void(stroka);
							}
							else { stop_reding_file = 5; }
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//���� ������ �����, ��� �������
							while (reading_if_empty != 1)//���� ������ ����� ������� ������
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
							if (stroka != "������:" && stroka != "������:" && !stroka.empty())//���� ��������� ������ ����� �������� ���������� �� �������� ������ ��� ������
							{
								cout << "������! � ����� ������ ���������� ������ ����� ���� �����!" << endl << "���������� " << stroka << " �� ����� ����� �����!" << endl;
								system("pause");
								file.close();
								return;
							}
						}
					}
					else { stop_reding_file = 5; }//���� ����� �����
				}
				else if (stroka == "������:") {//���� ����� �����
					string text;
					int do_if_not_find_metka = 0;
					if (_find_republic != 1) { //���� ����� ������ �������� � ����� �� ����� ����������
						do_if_not_find_metka = 1;
						stop_reding_file = 5;
						cout << "�� ������� ����������!" << endl;
						system("pause");
					}
					while (do_if_not_find_metka != 1) {//����������� ���� �� �������� ����� ����� ��� �� ������� �� ���� �����
						if (!file.eof()) {//�� ������ ����� ����� - ��������� ������
							getline(file, stroka);
							stroka = Check_Void(stroka);
						}
						if (!file.eof()) {//�� ������ ����� �����
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }
							while (reading_if_empty != 1)//����������� ���� ������ ����� ��� ��� ������ ������� � ���������, ���������� ���� ��� ������ ��� ����� �����
							{
								if (stroka.empty() || stroka == "") {//������ �����
									if (!file.eof()) {
										getline(file, stroka);
										stroka = Check_Void(stroka);
									}
									else reading_if_empty = 1;
								}
								else { reading_if_empty = 1; }//���� ������ �������
								if (file.eof()) { reading_if_empty = 1; }
							}
							if ((file.eof()) || stroka == "������:" || stroka == "������:") { do_if_not_find_metka = 1; }//����� �����, ������� �� ����� line=="������"
							else {//���� �� ����� ����� � �� ����� �����
								if (!file.eof()) {
									getline(file, text);
									text = Check_Void(text);
								}
								int reading_if_empty = 1;
								if (text.empty() || text == "") { reading_if_empty = 0; }
								while (reading_if_empty != 1)//���� ������ ����� ��� �� ����� �����
								{
									if (file.eof()) {//����� �����
										reading_if_empty = 1;
										do_if_not_find_metka = 1;
										stop_reding_file = 5;
									}
									if (text.empty() || text == "") {//������ �����
										if (!file.eof()) {
											getline(file, text);
											text = Check_Void(text);
										}
										else reading_if_empty = 1;//����� �����
									}
									else { reading_if_empty = 1; }//������ �� �����
								}

								if (file.eof()) { stop_reding_file = 5; do_if_not_find_metka = 1; }//����� �����
								if (text != "������:" && text != "������:" && !text.empty() && !(text == ""))//���� ��������� ������ ����� ����� ������� �� �������� ������
								{
									string ggg = stroka;
									stroka = Check_Number(stroka);
									if (text == "") {//���� � ���������� ������� ���� ������� - �� �������� ������
										cout << "������ � ���������� ������� ������! ---- " << ggg << endl;
										file.close(); system("pause"); return;
									}
									if (liner->Download_Add_Cell(stroka, text) == false) {
										stop_reding_file = 5; file.close();
										cout << "������! ����� ����� �������� �������!" << endl;
										system("pause");
										return;
									}
								}
								else {//���� � ������ �� ������� ���������� �������
									do_if_not_find_metka = 1;
									cout << "������! ����� ������ ����� �������!" << endl << "� ������ " << line << " �� ������� ���������� �������!" << endl;
									system("pause");
									file.close();
									return;
								}
							}
						}
						else { do_if_not_find_metka = 1; stop_reding_file = 5; }//����� �����
					}
					if (file.eof()) { stop_reding_file = 5; do_if_not_find_metka = 1; }//����� �����
				}
				if (file.eof()) { //����� �����, ���� �����������
					stop_reding_file = 5;

					file.close();
					return;
				}
				if (stroka.empty())//���� ������ �����
				{
					if (!file.eof()) {
						getline(file, stroka);
						stroka = Check_Void(stroka);
					}
				}
				if (stroka != "������:" && stroka != "������:" && !stroka.empty())//���� � ����� ������ �� ����� ������ � �� ����� (�� ������ �����)
				{
					bool if_empty = false;
					for (int j = 0; j < stroka.length(); j++)//�������� �� �������
					{
						if (stroka.at(j) != ' ') { if_empty = true; }
					}
					if (if_empty == true) {// ������ �������, ���� �� ����� ������ �� ������ �����
						cout << "������! ������ ��������� ��� ����� (� ������ �����)!" << endl;
						system("pause");
						file.close();
						return;
					}
					else {//������ �����
						if (!file.eof()) {//�� ������ ����� �����
							getline(file, stroka);
							stroka = Check_Void(stroka);
						}
					}
				}
			}
			file.close();
		}
		else//���� �� ������
		{
			cout << "���� �� ������!" << endl;
			system("pause");
			return;
		}
	}
	string Check_Void(string line_name) {    //������������� ������
		if (line_name.size() > 5000) {
			cout << "������! �������� ������� �� ������ ���� ������ 5000!" << endl;
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
				cout << "����� ������ : ";
				getline(cin, name_of_line);
				name_of_line = Check_Number(Check_Void(name_of_line));
			}
			Line *new_line = new Line(name_of_line);
			line = new_line;
			cout << "������ ���������" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
				system("cls");
				cout << "1 - �������� �� (������ �����)\n2 - �������� �� (�������� �����) \n3 - �������� ����� (������ �����) \n4 - �������� ����� (�������� �����) ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				cout << "������� ����� ������ ��� ������ : ";
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
				cout << "������ � ������ ������� �� �������!" << endl;
				system("pause");
				return;
			}
			while (name_of_line == "") {
				system("cls");
				cout << "����� ������ : ";
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
			cout << "������ ���������" << endl;
			system("pause");
			return;
		}
	}
	void Delete_Cell() {
		if (line == NULL) {
			cout << "������! ����� �� ����������!" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2") {
				system("cls");
				cout << "����� ������ ��� �������� ������ :\n1 - �����e ����������� ������\n2 - �������� ����������� ������ : ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				system("cls");
				cout << "������� ����� ������ ��� ������ : ";
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
				cout << "������ � ������ ������� �� �������!" << endl;
				system("pause");
				return;
			}
			temp->Delete_Cell();
		}
	}
	void Delete_Line() {
		if (line == NULL) {
			cout << "������! ����� �� ����������!" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2") {
				system("cls");
				cout << "����� ������ ��� �������� ������ :\n1 - �����e ����������� ������\n2 - �������� ����������� ������ : ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				system("cls");
				cout << "������� ����� ������ ��� ������ : ";
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
				cout << "������ � ������ ������� �� �������!" << endl;
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
			cout << "������ �������!" << endl;
			system("pause");
			return;
		}
	}
	void Search(int key) {
		if (line != NULL) {
			string ask1 = "";
			while (ask1 != "1" && ask1 != "2") {
				system("cls");
				cout << "����� ������ : 1 - ������ ����� " << endl << "2 - �������� �����" << endl;
				getline(cin, ask1);
				ask1 = Check_Number(Check_Void(ask1));
			}
			string ask = "";
			while (ask == "") {
				system("cls");
				cout << "����� ������ (������� ����� ������):" << endl;
				getline(cin, ask);
				ask = Check_Number(Check_Void(ask));
			}
			Line *temp = line;
			if (ask1 == "1") {
				while (temp != NULL) {
					if (temp->Get_Nomer() == ask) {
						if (key == 1)
						{
							cout << "������ � ������ ������� �������!" << endl;
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
				cout << "������ � ������ ������� �� �������!" << endl;
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
							cout << "������ � ������ ������� �������!" << endl;
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
				cout << "������ � ������ ������� �� �������!" << endl;
				system("pause");
				return;
			}
		}
	}
	void Add_Cell() {
		if (line == NULL) {
			cout << "������! ����� �� ����������!" << endl;
			system("pause");
			return;
		}
		else {
			string choice = "";
			while (choice != "1" && choice != "2") {
				system("cls");
				cout << "����� ������ ��� ���������� ������ :\n1 - �����e ����������� ������\n2 - �������� ����������� ������ : ";
				getline(cin, choice);
				choice = Check_Void(choice);
			}
			string line_poisk = "";
			while (line_poisk == "") {
				system("cls");
				cout << "������� ����� ������ ��� ������ : ";
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
				cout << "������ � ������ ������� �� �������!" << endl;
				system("pause");
				return;
			}
			temp->Add_Cell();
		}
	}
	void Show() {
		cout << "�������� ������ - " << name << endl;
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

