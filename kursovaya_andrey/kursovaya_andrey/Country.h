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
			cout << "������ �������� �����! ������� �������� ����������!" << endl;
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
	void Download_From_File()    //�������� �� �����
	{
		Remove_country();//������� ���
		int _find_republic = 0;//������� ���� ����� ������ ����� �� ����������
		int stop_reding_file = 0;//������� ���� �� ���������� ����
		string line = "";//������
		ifstream file("data_base.txt");
		if (file.is_open()) // ���� ���� ������
		{
			getline(file, line);
			line = Check_To_Void(line);
			while (stop_reding_file != 5)//���� �� ������ ����� ����� ��������� ������ �� �����
			{
				if (line == "����������:") {//���� ����� �����
					_find_republic = 0;
					if (!file.eof()) {//�� ����� �����
						getline(file, line);
						line = Check_To_Void(line);
					}
					if (!file.eof()) {//�� ����� �����
						int reading_if_empty = 1;
						if (line.empty() || line == "") { reading_if_empty = 0; }//���� ������ �����, �� ���������� ����
						while (reading_if_empty != 1)//��������� ������ �� �����, ���� �� ����� ������ ��� �� �������� ����� �����
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
						if (file.eof()) { stop_reding_file = 5; }//����� �����
						if (line != "����������:"&& line != "������:" && !line.empty())//���� ����� ����� ����. ������ �� �������� ������ � �� �����
						{
							_find_republic = 1;
							Download_Add_Republic(line);
							if (!file.eof()) {//���� �� ����� �����, �� ��������� ����. ������
								getline(file, line);
								line = Check_To_Void(line);
							}
							else { stop_reding_file = 5; }
							int reading_if_empty = 1;
							if (line.empty() || line == "") { reading_if_empty = 0; }//���� ������ �����, ��� �������
							while (reading_if_empty != 1)//���� ������ ����� ������� ������
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
							if (line != "����������:" && line != "������:" && !line.empty())//���� ��������� ������ ����� �������� ���������� �� �������� ������ ��� ������
							{
								cout << "������! � ����� ������ ���������� ������ ����� ���� �����!" << endl << "���������� " << line << " �� ����� ����� �����!" << endl;
								system("pause");
								file.close();
								return;
							}
						}
					}
					else { stop_reding_file = 5; }//���� ����� �����
				}
				else if (line == "������:") {//���� ����� �����
					string _people_number;
					int do_if_not_find_metka = 0;
					if (_find_republic != 1) { //���� ����� ������ �������� � ����� �� ����� ����������
						do_if_not_find_metka = 1; 
						stop_reding_file = 5; 
						cout << "�� ������� ����������!" << endl; 
						system("pause"); 
					}
					while (do_if_not_find_metka != 1) {//����������� ���� �� �������� ����� ����� ��� �� ������� �� ���� �����
						if (!file.eof()) {//�� ������ ����� ����� - ��������� ������
							getline(file, line);
							line = Check_To_Void(line);
						}
						if (!file.eof()) {//�� ������ ����� �����
							int reading_if_empty = 1;
							if (line.empty() || line == "") { reading_if_empty = 0; }
							while (reading_if_empty != 1)//����������� ���� ������ ����� ��� ��� ������ ������� � ���������, ���������� ���� ��� ������ ��� ����� �����
							{
								if (line.empty() || line == "") {//������ �����
									if (!file.eof()) {
										getline(file, line);
										line = Check_To_Void(line);
									}
									else reading_if_empty = 1;
								}
								else { reading_if_empty = 1; }//���� ������ �������
								if (file.eof()) { reading_if_empty = 1; }
							}
							if ((file.eof()) || line == "����������:" || line == "������:") { do_if_not_find_metka = 1; }//����� �����, ������� �� ����� line=="������"
							else {//���� �� ����� ����� � �� ����� �����
								if (!file.eof()) {
									getline(file, _people_number);
									_people_number = Check_To_Void(_people_number);
								}
								int reading_if_empty = 1;
								if (_people_number.empty() || _people_number == "") { reading_if_empty = 0; }
								while (reading_if_empty != 1)//���� ������ ����� ��� �� ����� �����
								{
									if (file.eof()) {//����� �����
										reading_if_empty = 1;
										do_if_not_find_metka = 1;
										stop_reding_file = 5;
									}
									if (_people_number.empty() || _people_number == "") {//������ �����
										if (!file.eof()) {
											getline(file, _people_number);
											_people_number = Check_To_Void(_people_number);
										}
										else reading_if_empty = 1;//����� �����
									}
									else { reading_if_empty = 1; }//������ �� �����
								}

								if (file.eof()) { stop_reding_file = 5; do_if_not_find_metka = 1; }//����� �����
								if (_people_number != "����������:" && _people_number != "������:" && !_people_number.empty() && !(_people_number == ""))//���� ��������� ������ ����� ����� ������� �� �������� ������
								{
									string ggg = _people_number;
									_people_number = Check_To_Number(_people_number);
									if (_people_number == "") {//���� � ���������� ������� ���� ������� - �� �������� ������
										cout << "������ � ���������� ������� ������! ---- " << ggg << endl;
										file.close(); system("pause"); return;
									}
									if (top_of_stack->Download_Add_City(line, _people_number) == false) {
										stop_reding_file = 5; file.close(); return;
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
				if (line.empty())//���� ������ �����
				{
					if (!file.eof()) {
						getline(file, line);
						line = Check_To_Void(line);
					}
				}
				if (line != "����������:" && line != "������:" && !line.empty())//���� � ����� ������ �� ����� ������ � �� ����� (�� ������ �����)
				{
					bool if_empty = false;
					for (int j = 0; j < line.length(); j++)//�������� �� �������
					{
						if (line.at(j) != ' ') { if_empty = true; }
					}
					if (if_empty == true) {// ������ �������, ���� �� ����� ������ �� ������ �����
						cout << "������! ������ ��������� ��� ����� (� ������ �����)!" << endl;
						system("pause");
						file.close();
						return;
					}
					else {//������ �����
						if (!file.eof()) {//�� ������ ����� �����
							getline(file, line);
							line = Check_To_Void(line);
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
	void Save_to_file(string choice) {
		if (choice == "1" || choice == "2") {
			if (choice == "2")
			{
				remove("data_base.txt");
			}
			fstream txt("data_base.txt", ios::app);
			if (txt.is_open()) // ����� ������ is_open()
			{
				if (top_of_stack != NULL)
				{
					for (int j = 0; j < number_of_republics; j++)
					{
						Republic *temp = top_of_stack;
						for (int i = (number_of_republics - 1 - j); i > 0; i--) {
							temp = temp->Get_Next();
						}
						txt << " ����������:" << endl;
						txt << temp->Get_name_of_republic() << endl;
						temp->Save_to_file();
					}
					txt.close();
					cout << "������ ��������� � ����" << endl;
					system("pause");
					return;
				}
				cout << "������ ��������� � ����" << endl;
				system("pause");
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
		else {
			cout << "������! ������� ����� 1 ��� 2" << endl;
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
			cout << "���������� �������!" << endl;
			system("pause");
		}
		else {
			cout << "������ ������� ����������! ������� �������� ����������!" << endl;
			system("pause");
		}
	}
	string Check_To_Void(string name_of_republic) {    //������������� ������
		if (name_of_republic.size() > 4700) {
			cout << "������! �������� ������� �� ������ ���� ������ 4700!" << endl;
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
			cout << "�������� ����������� :";
			getline(cin, name_of_republic);
			name_of_republic = Check_To_Void(name_of_republic);
		} while (name_of_republic == "" || name_of_republic == "����������:" || name_of_republic == "������:");
		Republic *temp = new Republic(name_of_republic);
			temp->Set_Next(top_of_stack);
			top_of_stack = temp;
			number_of_republics++;
			cout << "���������� ���������!" << endl;
			system("pause");
	}
	void Remove_City() {
		if (top_of_stack != NULL)
			top_of_stack->Remove_City();
		else {
			cout << "������ ������� �����! ������� �������� ����������!" << endl;
			system("pause");
		}
	}
	void Show() {//������� ������������ � ����� �����
		cout << "                       ������ - " << name_of_country << endl;
		if (top_of_stack != NULL) {
			Republic *temp = top_of_stack;
			while (temp != NULL) {
				cout << "���������� - " << temp->Get_name_of_republic() << endl;
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

