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
	string name;//�������� ������
	int number,kolvo;//������� ����� � ������ �������
	Section* section;//������
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
			cout << "������ �������!" << endl;
			system("pause");
		}
		else {
			cout << "������! ������ �� ����������!" << endl;
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
			cout << "1 - ������� ������ �� ������� ����� \n2 - ������� ������ �� �������� ������" << endl;
			string add = "";
			getline(cin, add);
			if (add == "1") {
				section[number - 1].DeleteCell();
				return;
			}
			else if (add == "2") {
				cout << "������� ����� ������ - " << endl;
				string addsec = "";
				getline(cin, addsec);
				for (int i = 0; i < number; i++) {
					if (section[i].GetName() == addsec) {
						section[i].DeleteCell();
						return;
					}
				}
				cout << "� ��������� ������ � ������ ������� �� �������!" << endl;
				system("pause");
			}
		}
			else {
				cout << "������! ������ �� ����������!" << endl;
				system("pause");
			}
	}
	string Pustclear(string str) {    //������������� ������
		if (str.size() > 5000) {
			cout << "������! �������� ������� �� ������ ���� ������ 1000!" << endl;
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
	void Show() {//������� ������������ � ����� �����
		cout << "                          �������� ������ - " << name << " :" << endl;
		for(int i=number-1;i>=0;i--){
			cout << "             ������ � - " << section[i].GetName()<< " :" << endl;
			section[i].Show();
		}
		system("pause");
	}
	void SaveToFile(string www) { //��������� � ����
			if (www == "2")
			{
				remove("file.txt");
			}
			fstream txt("file.txt", ios::app); if (txt.is_open()) // ����� ������ is_open()
			{
				if (number > 0) {
					for (int i = 0; i < number; i++) {
						txt << "			 ������:" << endl;
						txt << "            " << section[i].GetName() << endl;
						section[i].SaveToFile();
					}
					txt.close();
					cout << "������ ��������� � ����" << endl;
					system("pause");
					return;
				}
			}
			else
			{
				cout << "���� �� ������!\n\n" << endl;
				system("pause");
				return;
			}
	}
	void AddSection() {
		if (number < kolvo) {
			string numbe = "";
			do {
				system("cls");
				cout << "������� ����� ������ : ";
				getline(cin, numbe);
				numbe = Proverka(Pustclear(numbe));
			} while (numbe == "");
			section[number].SetName(numbe);
			number++;
			cout << "������ ���������!" << endl;
			system("pause");
		}
		else {
			cout << "����� ������ �������� ������" << endl;
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
			cout << "����� ������ �������� ������" << endl;
			system("pause");
			return false;
		}
	}
	void AddCell() {
		if (number > 0) {
			cout << "1 - �������� ������ � ������� ����� \n2 - �������� ������ � �������� ������" << endl;
			string add = "";
			getline(cin, add);
			if (add == "1"){
				section[number - 1].AddCell();
				return;
			}
			else if (add == "2") {
				cout << "������� ����� ������ - " << endl;
				string addsec = "";
				getline(cin, addsec);
				for (int i = 0; i < number; i++) {
					if (section[i].GetName() == addsec) {
						section[i].AddCell();
						return;
					}
				}
				cout << "� ��������� ������ � ������ ������� �� �������!" << endl;
				system("pause");
			}
			else { 
				cout << "������! ������� ����� 1 ��� 2" << endl;
				system("pause");
			}
		}
		else {
			cout << "������! �������� ������" << endl;
			system("pause");
		}
	}
	void DownloadFromFile()    //�������� �� �����
	{
		Deleting();//������� ��� ����� ���������
		int find_first_section = 0;//������� ���� ����� ������ ��������� �� ������ �����
		int stop_reding_txt_file = 0;//������� ���� �� ���������� ����
		string stroka = "";
		ifstream txt("file.txt");
		if (txt.is_open()) // ���� ���� ������
		{
			getline(txt, stroka);
			stroka = Pustclear(stroka);
			while (stop_reding_txt_file != 5)//���� �� ������ ����� ����� ��������� ������ �� �����
			{
				if (stroka == "������:") {//���� � ������ ���� ����� ������
					find_first_section = 0;
					if (!txt.eof()) {//�� ����� �����
						getline(txt, stroka);
						stroka = Pustclear(stroka);
					}
					if (!txt.eof()) {//�� ����� �����
						int reading_if_empty = 1;
						if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//���� ������ �����, �� ���������� ����
						while (reading_if_empty != 1)//��������� ������ �� �����, ���� �� ����� ������ ��� �� �������� ����� �����
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
						if (txt.eof()) { stop_reding_txt_file = 5; }//����� �����
						if (stroka != "������:"&& stroka != "������:" && !stroka.empty())//���� ����� ����� ����. ������ �� �������� ������ � �� �����
						{
							stroka = Proverka(stroka);
							if (stroka == "") {
								cout << "������ � ������ ������!" << endl;//���� �� �����
								txt.close(); system("pause"); return;
							}
							find_first_section = 1;
							if (AddForDownloadSection(stroka) == false) {
								stop_reding_txt_file = 5; txt.close(); return;
							}//��������� ������ � ���������� true ���� �� �������� ������
							if (!txt.eof()) {//���� �� ����� �����, �� ��������� ����. ������
								getline(txt, stroka);
								stroka = Pustclear(stroka);
							}
							else { stop_reding_txt_file = 5; }
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }//���� ������ �����, ��� ��� �������, ��
							while (reading_if_empty != 1)//���� ������ �����, ��������� ������ ���� �� ����� ������
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
							if (stroka != "������:" && stroka != "������:" && !stroka.empty())//���� ��������� ������ ����� ������ ������ �� �������� ������ ��� ������, �� ����������� ��� �������
							{
								cout << "������! � ����� ������ ������ ������ ����� ���� �����!" << endl << "������ � ������� " << stroka << " �� ����� ����� �����!" << endl;
								system("pause");
								txt.close();
								return;
							}
						}
					}
					else { stop_reding_txt_file = 5; }//���� ����� �����
				}
				else if (stroka == "������:") {//���� ����� ����� ������
					string busy;
					int do_if_not_find_metka = 0;
					if (find_first_section != 1) { do_if_not_find_metka = 1; stop_reding_txt_file = 5; cout << "�� ������� ������!" << endl; system("pause"); }//���� ����� ������ ����� �� ����� ������
					while (do_if_not_find_metka != 1) {//����������� ���� �� �������� ����� ����� ��� �� ������� �� ���� �����
						if (!txt.eof()) {//�� ������ ����� ����� - ��������� ������
							getline(txt, stroka);
							stroka = Pustclear(stroka);
						}
						if (!txt.eof()) {//�� ������ ����� �����
							int reading_if_empty = 1;
							if (stroka.empty() || stroka == "") { reading_if_empty = 0; }
							while (reading_if_empty != 1)//����������� ���� ������ ����� ��� ��� ������ ������� � ���������, ���������� ���� ��� ������ ��� ����� �����
							{
								if (stroka.empty() || stroka == "") {//������ �����
									if (!txt.eof()) {
										getline(txt, stroka);
										stroka = Pustclear(stroka);
									}
									else reading_if_empty = 1;
								}
								else { reading_if_empty = 1; }//���� ������ �������
								if (txt.eof()) { reading_if_empty = 1; }
							}
							if ((txt.eof()) || stroka == "������:" || stroka == "������:") { do_if_not_find_metka = 1; }//����� �����, ������� �� �����, � ���������� ��� ������ �� �����
							else {//���� �� ����� ����� � �� ����� �����
								if (!txt.eof()) {
									getline(txt, busy);
									busy = Pustclear(busy);
								}
								int reading_if_empty = 1;
								if (busy.empty() || busy == "") { reading_if_empty = 0; }
								while (reading_if_empty != 1)//���� ������ ����� ��� �� ����� �����
								{
									if (txt.eof()) {//����� �����
										reading_if_empty = 1;
										do_if_not_find_metka = 1;
										stop_reding_txt_file = 5;
									}
									if (busy.empty() || busy == "") {//������ �����
										if (!txt.eof()) {
											getline(txt, busy);
											busy = Pustclear(busy);
										}
										else reading_if_empty = 1;//����� �����
									}
									else { reading_if_empty = 1; }//������ �� �����
								}

								if (txt.eof()) { stop_reding_txt_file = 5; do_if_not_find_metka = 1; }//����� �����
								if (busy != "������:" && busy != "������:" && !busy.empty() && !(busy == ""))//���� ��������� ������ ����� ������ ������ h1 (���������) �� �������� ������ 
								{
									string ggg = stroka;
									stroka = Proverka(stroka);
									if (stroka == "") {
										cout << "������ � ������ ������! ---- " << ggg << endl;//���� � ������ ���� ������� - �� �������� ������
										txt.close(); system("pause"); return;
									}
									section[number-1].AddForDownloadCell(stroka, busy);
								}
								else {//���� ������ ��������� - ������ - �������� ������, �.�. ���� ��������
									do_if_not_find_metka = 1;
									cout << "������! ������ ������ ����� ������� ���������!" << endl << "������ � ������� " << stroka << " �� ����� ������� ���������!" << endl;
									system("pause");
									txt.close();
									return;
								}
							}
						}
						else { do_if_not_find_metka = 1; stop_reding_txt_file = 5; }//����� �����
					}
					if (txt.eof()) { stop_reding_txt_file = 5; do_if_not_find_metka = 1; }//����� �����
				}
				if (txt.eof()) { //����� �����, ���� �����������
					stop_reding_txt_file = 5;

					txt.close();
					return;
				}
				if (stroka.empty())//���� ������ �����
				{
					if (!txt.eof()) {
						getline(txt, stroka);
						stroka = Pustclear(stroka);
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
						cout << "������! ������ ��������� �� ������ �����!" << endl;
						system("pause");
						txt.close();
						return;
					}
					else {//������ �����
						if (!txt.eof()) {//�� ������ ����� �����
							getline(txt, stroka);
							stroka = Pustclear(stroka);
						}
					}
				}
			}
			txt.close();
		}
		else//���� �� ������
		{
			cout << "���� �� ������!" << endl;
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
