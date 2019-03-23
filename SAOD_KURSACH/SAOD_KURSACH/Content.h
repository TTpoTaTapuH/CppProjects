#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <cstdlib>
#include <istream>
#include <conio.h>
#include <io.h>
#include <string>
#include <windows.h>
#include "Section.h"
#pragma once
using namespace std;
class Content 
{
private:
	Section *list[101];
	int N;
public:
	Content(int kolvo, string txt) //��� � ������
	{
		N = kolvo + 1;
		list[0] = new Section(txt);
		Start();
	}
	void DeleteWorker()  //�������� ����������
	{
		if (list[0]->GetNext() == NULL) { cout << "������ �����. �������� �����!" << endl; system("pause"); return; }
		else {
			cout << "����� �� �������� ���� ������� ���������� :";
			string name_of_deleting_list;
			getline(cin, name_of_deleting_list);
			name_of_deleting_list = ClearWords(name_of_deleting_list);
			Section *search_deletting_list = list[0];
			while (search_deletting_list->GetNext() != NULL)
			{
				search_deletting_list = search_deletting_list->GetNext();
				if (search_deletting_list->GetName() == name_of_deleting_list) {
					cout << "����� ������." << endl;
					system("pause");
					search_deletting_list->DeletWorker();
					return;
				}
			}
			cout << "����� �� ������!" << endl;
			system("pause");
		}
	}
	void DelAll() {  //������� ��
		if (list[0]->GetNext() == NULL) { return; }
		else {
			while (list[0]->GetNext() != NULL)//����� ������
			{
				Section *temp = list[0]->GetNext();
					temp->DeletSection();
					list[0]->SetNext(temp->GetNext());
					if (temp->GetPstack() == NULL) {//���� ���������� �������
						temp->SetKey(1);
						temp->Setname("");
						temp->SetNext(NULL);
					}
				}
		}
	}
	void DeleteSection() {  //������� �����
		if (list[0]->GetNext() == NULL) { cout << "������ �����. �������� �����!" << endl; system("pause"); return; }
		else {
			cout << "����� ��� �������� :";
			string name_of_deleting_list;
			getline(cin, name_of_deleting_list);
			name_of_deleting_list = ClearWords(name_of_deleting_list);
			Section *search_deletting_list = list[0];
			Section *search_del = list[0];
			bool h = true;
			while (search_deletting_list->GetNext() != NULL)//����� ������
			{
				search_deletting_list = search_deletting_list->GetNext();//������� � ���� ������
				if (h == false) { search_del = search_del->GetNext(); }//����������
				if (h == true) { h = false; }//�����
				if (search_deletting_list->GetName() == name_of_deleting_list) //���� ����� �����
				{
					search_deletting_list->DeletSection();
					if (search_deletting_list->GetPstack() == NULL) {//���� ���������� �������
						Section *del = search_deletting_list;//��������� �����
						search_del->SetNext(search_deletting_list->GetNext());
						del->SetKey(1);
						del->Setname("");
						del->SetNext(NULL);
						cout << "����� �����!" << endl;
						system("pause");
						return;
					}
				}
			}
			cout << "����� �� ������!" << endl;
			system("pause");
		}

	}
	void Start()//�������� ��� ������
	{
		for (int i = 1; i<N; i++)
		{
			list[i] = new Section();
			list[i]->SetKey(1);
		}
	}
	string ClearWords(string word) {    //������������� ������
		string endword;
		if (word.size() > 10000) {
			cout << "������! �������� ������� �� ������ ���� ������ 1000!" << endl;
			system("pause");
			return "Error";
		}
		char chars[10000];
		strcpy_s(chars, word.c_str());
		char *nextword = strtok(chars, " \t");
		while (nextword != NULL)
		{
			endword += nextword;
			nextword = strtok(NULL, " \t");
			if (nextword != NULL)
				endword += ' ';
		}
		return endword;
	}
	void SearchWorker() { //����� ����������
		string http = "";
		string gg = "";
		Section *dom = list[0]->GetNext();
		while (http == "") {
			system("cls");
			cout << "�������� ������ :" << endl;
			getline(cin, http);
			http = ClearWords(http);
		}
		while (dom != NULL) {
			if (dom->GetName() == http) {
				while (gg == "") {
					system("cls");
					cout << "����� ���������� (�������) :" << endl;
					getline(cin, gg);
					gg = ClearWords(gg);
				}
				dom->SearchWorker(gg);
				return;
			}
			dom = dom->GetNext();
		}
		cout << "����� �� ������!" << endl;
		system("pause");
	}
	void SaveToFile() { //��������� � ����
		fstream txt("file.txt", ios::app);
		Section *temp = list[0];
		if (txt.is_open()) // ����� ������ is_open()
		{
			while (temp->GetNext() != NULL)
			{
				temp = temp->GetNext();
				txt << "						   //�����//" << endl;
				txt << "                           "<<temp->GetName() << endl;
				temp->SaveToFile();
			}
			txt.close();
			cout << "������ ��������� � ����." << endl;
			system("pause");
		}
		else
		{
			cout << "���� �� ������!\n\n" << endl;
			system("pause");
			return;
		}
	}
	int FreeList()    //����� ������� ������ (�����)
	{
		for (int i = 1; i < N; i++)
		{
			if (list[i]->GetKey() == 1)
			{
				list[i]->SetKey(5);
				return i;
			}
		}
		return -5;
	}
	void AddSection()	//���������� �������
	{
		int k = FreeList();
		if (k == -5)//���� ��������
		{
			cout << "����� ��������� �������� ������!" << endl;
			system("pause");
			return;
		}
		else { Section *temp = list[k]; }
		if (list[0]->GetNext() == NULL)
		{
			string ffame;
			do {
				system("cls");
				cout << "�������� ������ :";
				getline(cin, ffame);
				ffame = ClearWords(ffame);
			} while (ffame == ""|| ffame=="//�����//" || ffame == "//����������//" || pust(ffame) == -1);
			list[k]->Setname(ffame);
			list[k]->SetNull();
			list[0]->SetNext(list[k]);
			cout << "����� ��������!" << endl;
			system("pause");
		}
		else//�� ��������
		{
			string choose;//�� ��� �����
			do
			{
				cout << "1 - �������� ����� ����� �������� ������ \n2 - �������� ����� �� ��������� ������" << endl;
				getline(cin, choose);
				choose = ClearWords(choose);
			} while (choose != "1" && choose != "2");
			cout << "����� ������ : " << endl;
			string ask;//�������� ������ ��� ������
			getline(cin, ask);
			ask = ClearWords(ask);
			if (choose == "1") {//�����
				Section *poisk = list[0];
				while (poisk->GetNext() != NULL)//����� ������
				{
					poisk = poisk->GetNext();
					if (poisk->GetName() == ask)//���� �����
					{
						cout << "����� ������\n-------------------------" << endl;
						string fame;
						do {
							system("cls");
							cout << "�������� ������ :" << endl;
							getline(cin, fame);
							fame = ClearWords(fame);
						} while (fame == "" || fame == "//�����//" || fame == "//����������//" || pust(fame) == -1);
						list[k]->Setname(fame);
						list[k]->SetNull();
						list[k]->SetNext(poisk->GetNext());
						poisk->SetNext(list[k]);
						cout << "����� ��������" << endl;
						system("pause");
						return;
					}
				}
				cout << "������� �� ������!" << endl;
				system("pause");
				list[k]->SetKey(1);
				return;
			}
			if (choose == "2") {
				Section *poisk1 = list[0];
				Section *last = list[0];
				while (poisk1->GetNext() != NULL)//����� ������
				{
					poisk1 = poisk1->GetNext();
					if (poisk1->GetName() == ask)//���� �����
					{
						cout << "����� ������\n-------------------------" << endl;
						cout << "�������� ������ :" << endl;
						string fame;
						do {
							system("cls");
							cout << "�������� ������ :" << endl;
							getline(cin, fame);
							fame = ClearWords(fame);
						} while (fame == "" || fame == "//�����//" || fame == "//����������//" || pust(fame) == -1);
						list[k]->Setname(fame);
						list[k]->SetNull();
						if (list[0]->GetNext()->GetName() == ask)
						{
							list[k]->SetNext(poisk1);
							list[0]->SetNext(list[k]);
						}
						else
						{
							list[k]->SetNext(poisk1);
							last->SetNext(list[k]);
						}
						cout << "����� ��������" << endl;
						system("pause");
						return;
					}
					last = last->GetNext();
				}
				cout << "������� �� ������!" << endl;
				system("pause");
				list[k]->SetKey(1);
				return;
			}
		}
	}
	int pust(string h) //�������� �� �������
	{
			bool ad = false;
			for (int j = 0; j < h.length(); j++)
			{
				if (h.at(j) != ' ') { ad = true; }
			}
			if (ad == true) {
				return 1;//1 - ������ ����
			}
			else { return -1; }//-1 - ������� ����
	}
	void DownloadFromFile()    //�������� �� �����
	{
		Section *temp = list[0];
		DelAll();
		int k=0;
		int key = 0;
		string h="";
		ifstream txt("file.txt");
		if (txt.is_open()) // ����� ������ is_open()
		{
			getline(txt, h);
			h = ClearWords(h);
			while (key != 5)
			{
				if (h == "//�����//") {
					getline(txt, h);
					h = ClearWords(h);
					int g1 = 1;
					if (h.empty() || pust(h)==-1) { g1 = 0; }
					while (g1 != 1)
					{
						if (h.empty() || pust(h) == -1) { getline(txt, h); h = ClearWords(h);
						}
						else { g1 = 1; }
					}
					if (txt.eof()) { key = 5; }
					if (h != "//�����//"&&h != "//����������//"&&!h.empty())
					{
						k = FreeList();
						if (k == -5)//���� ��������
						{
							cout << "����� ��������� �������� ������!" << endl;
							system("pause");
							txt.close();
							return;
						}
						list[k]->Setname(h);
						list[k]->SetNull();
						temp->SetNext(list[k]);
						temp = list[k];
						getline(txt, h);
						h = ClearWords(h);
						int g1 = 1;
						if (h.empty() || pust(h) == -1) { g1 = 0; }
						while (g1 != 1)
						{
							if (h.empty() || pust(h) == -1) { getline(txt, h); 
							h = ClearWords(h);
							}
							else { g1 = 1; }
						}
						if (txt.eof()) { key = 5; }
						if (h != "//�����//" && h != "//����������//")
						{
							cout << "������! � ����� ������ ����� ������ ����� ���� �����!"<<endl<<"����� "<<h<<" �� ����� ����� �����!"<<endl;
							system("pause");
							txt.close();
							return;
						}
					}
				}
				else if (h == "//����������//") {
					string h1;
					int a = 0;
					while (a != 1) {
						getline(txt, h);
						h = ClearWords(h);
						int g = 1;
						if (h.empty() || pust(h) == -1) { g = 0; }
						while (g != 1)
						{
							if (h.empty() || pust(h) == -1) { getline(txt, h); 
							h = ClearWords(h);
							}
							else { g = 1; }
							if (txt.eof()) { g = 1; }
						}
						if ((txt.eof()) || h == "//�����//" || h == "//����������//") { a = 1; }
						else {
							getline(txt, h1);
							h1 = ClearWords(h1);
							int g1 = 1;
							if (h1.empty() || pust(h1) == -1) { g1 = 0; }
							while (g1 != 1)
							{
								if (txt.eof()) {
									g1 = 1;
									a = 1;
									key = 5;
								}
								if (h1.empty() || pust(h1) == -1) { getline(txt, h1); 
								h1 = ClearWords(h1);
								}
								else { g1 = 1; }
							}

							if (txt.eof()) { key = 5; a = 1; }
							if (h1 != "//�����//" && h1 != "//����������//" && !h1.empty()&&!(pust(h1) == -1))
							{
								temp->AddWork(h, h1);
							}
							else {
								a = 1;
								cout << "������! ��������� ������ ����� ���������!!!" << endl << "��������� �� ������� " << h << " �� ����� ���������!" << endl;
								system("pause");
								txt.close();
								return;
							}
						}
					}
						if (txt.eof()) { key = 5; a = 1; }
					}
				if (txt.eof()) { key = 5;

				txt.close();
				return;
				}
				if (h.empty()) { getline(txt, h); 
				h = ClearWords(h);
				}
				if (h != "//�����//" && h != "//����������//"&&!h.empty())
				{
					bool ad = false;
					for (int j = 0; j < h.length(); j++)
					{
						if (h.at(j) != ' ') { ad = true; }
					}
					if (ad == true) {
						cout << "������! ������ ��������� �� ������ �����!" << endl;
						system("pause");
						txt.close();
						return;
					}
					else { getline(txt, h); 
					h = ClearWords(h);
					}
				}
			}
			txt.close();
		}
		else
		{
			cout << "���� �� ������!" << endl;
			system("pause");
			return;
		}
	}
	void AddWorker()    //�������� ����������
	{
		if (list[0]->GetNext() == NULL)//������� ���
		{
			cout << "������ �� ���������! �������� �����!" << endl;
			system("pause");
			return;
		}
		else//������ ����
		{
			cout << "�������� ������ ��� ���������� ����������� : " << endl;
			string otdel_poisk;
			getline(cin, otdel_poisk);
			otdel_poisk = ClearWords(otdel_poisk);
			Section *poisk_list = list[0];
			while (poisk_list->GetNext() != NULL)//����� �������
			{
				poisk_list = poisk_list->GetNext();
				if (poisk_list->GetName() == otdel_poisk)//����� ����� �����
				{
					cout << "����� ������." << endl;
					system("pause");
					string name_worker = "";
					string mayor_worker = "";
					if (poisk_list->GetPstack() == NULL)//���� ������ �������
					{
						do {
							system("cls");
							cout << "������� ���������� : " << endl;
							getline(cin, name_worker);
							name_worker = ClearWords(name_worker);
						} while (name_worker == "" || name_worker== "//����������//" || name_worker == "//�����//"||pust(name_worker)==-1);
						do {
							system("cls");
							cout << "��������� ���������� : " << endl;
							getline(cin, mayor_worker);
							mayor_worker = ClearWords(mayor_worker);
						} while (mayor_worker == "" || mayor_worker== "//����������//" || mayor_worker == "//�����//" || pust(mayor_worker) == -1);
						poisk_list->FirstWorker(name_worker, mayor_worker);
						cout << "��������� ��������!" << endl;
						system("pause");
						return;
					}
					else {
						cout << "1 - �������� ���������� ����� ���������� (����� � ������) \n2 - �������� ���������� �� ����������� (� ������)\n3 - �������� ���������� ����� ���������� (����� � �����) \n4 - �������� ���������� �� ����������� (� �����)" << endl;
						string dobav;// 1 ��� 2
						do {
							getline(cin, dobav); 
							dobav = ClearWords(dobav);
						} while (dobav != "1" && dobav != "2"&& dobav != "3"&& dobav != "4");
						string search_work;// ����� ����������
						cout << "������� ���������� ��� ������ : ";
						getline(cin, search_work);
						search_work = ClearWords(search_work);
						poisk_list->AddWorker(dobav, search_work);
						return;
					}
				}
			}
			cout << "����� �� ������." << endl;
			system("pause");
		}
	}
	void SearchSection() {      //����� ������
		string http = "";
		int summer = 0;
		Section *dom = list[0]->GetNext();
		while (http == "") {
			system("cls");
			cout << "����� ������ (��������) :" << endl;
			getline(cin, http);
			http = ClearWords(http);
		}
		while (dom != NULL) {
			if (dom->GetName() == http) { summer++; }
			dom = dom->GetNext();
		}
		cout << "������� " << summer << " �������" << endl;
		system("pause");
	}
	void Show()		//����� �� �������
	{
		Section *temp = list[0];
		cout << "                 ����������� : " + list[0]->GetName() << endl;
		while (temp->GetNext() != NULL)
		{
			temp = temp->GetNext();
			cout << "      ��������� : " + temp->GetName() << endl;
			temp->Show();
		}
		system("pause");
	}
	Content();
	~Content();
};