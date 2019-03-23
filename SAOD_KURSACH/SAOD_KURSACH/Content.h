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
	Content(int kolvo, string txt) //имя и размер
	{
		N = kolvo + 1;
		list[0] = new Section(txt);
		Start();
	}
	void DeleteWorker()  //удаление сотрудника
	{
		if (list[0]->GetNext() == NULL) { cout << "Отделы пусты. Создайте отдел!" << endl; system("pause"); return; }
		else {
			cout << "Отдел из которого надо удалить сотрудника :";
			string name_of_deleting_list;
			getline(cin, name_of_deleting_list);
			name_of_deleting_list = ClearWords(name_of_deleting_list);
			Section *search_deletting_list = list[0];
			while (search_deletting_list->GetNext() != NULL)
			{
				search_deletting_list = search_deletting_list->GetNext();
				if (search_deletting_list->GetName() == name_of_deleting_list) {
					cout << "Отдел найден." << endl;
					system("pause");
					search_deletting_list->DeletWorker();
					return;
				}
			}
			cout << "Отдел не найден!" << endl;
			system("pause");
		}
	}
	void DelAll() {  //удалить всё
		if (list[0]->GetNext() == NULL) { return; }
		else {
			while (list[0]->GetNext() != NULL)//обход отдела
			{
				Section *temp = list[0]->GetNext();
					temp->DeletSection();
					list[0]->SetNext(temp->GetNext());
					if (temp->GetPstack() == NULL) {//если сотрудники удалены
						temp->SetKey(1);
						temp->Setname("");
						temp->SetNext(NULL);
					}
				}
		}
	}
	void DeleteSection() {  //удалить отдел
		if (list[0]->GetNext() == NULL) { cout << "Отделы пусты. Создайте отдел!" << endl; system("pause"); return; }
		else {
			cout << "Отдел для удаления :";
			string name_of_deleting_list;
			getline(cin, name_of_deleting_list);
			name_of_deleting_list = ClearWords(name_of_deleting_list);
			Section *search_deletting_list = list[0];
			Section *search_del = list[0];
			bool h = true;
			while (search_deletting_list->GetNext() != NULL)//обход отдела
			{
				search_deletting_list = search_deletting_list->GetNext();//переход к след отделу
				if (h == false) { search_del = search_del->GetNext(); }//предыдущий
				if (h == true) { h = false; }//отдел
				if (search_deletting_list->GetName() == name_of_deleting_list) //если нашёл отдел
				{
					search_deletting_list->DeletSection();
					if (search_deletting_list->GetPstack() == NULL) {//если сотрудники удалены
						Section *del = search_deletting_list;//удаляемый отдел
						search_del->SetNext(search_deletting_list->GetNext());
						del->SetKey(1);
						del->Setname("");
						del->SetNext(NULL);
						cout << "Отдел удалён!" << endl;
						system("pause");
						return;
					}
				}
			}
			cout << "Отдел не найден!" << endl;
			system("pause");
		}

	}
	void Start()//отметить как пустые
	{
		for (int i = 1; i<N; i++)
		{
			list[i] = new Section();
			list[i]->SetKey(1);
		}
	}
	string ClearWords(string word) {    //преобразовать строку
		string endword;
		if (word.size() > 10000) {
			cout << "Ошибка! Вводимые символы не должны быть больше 1000!" << endl;
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
	void SearchWorker() { //поиск сотрудника
		string http = "";
		string gg = "";
		Section *dom = list[0]->GetNext();
		while (http == "") {
			system("cls");
			cout << "Название отдела :" << endl;
			getline(cin, http);
			http = ClearWords(http);
		}
		while (dom != NULL) {
			if (dom->GetName() == http) {
				while (gg == "") {
					system("cls");
					cout << "Поиск сотрудника (Фамилия) :" << endl;
					getline(cin, gg);
					gg = ClearWords(gg);
				}
				dom->SearchWorker(gg);
				return;
			}
			dom = dom->GetNext();
		}
		cout << "Отдел не найден!" << endl;
		system("pause");
	}
	void SaveToFile() { //сохранить в файл
		fstream txt("file.txt", ios::app);
		Section *temp = list[0];
		if (txt.is_open()) // вызов метода is_open()
		{
			while (temp->GetNext() != NULL)
			{
				temp = temp->GetNext();
				txt << "						   //Отдел//" << endl;
				txt << "                           "<<temp->GetName() << endl;
				temp->SaveToFile();
			}
			txt.close();
			cout << "Данные сохранены в файл." << endl;
			system("pause");
		}
		else
		{
			cout << "Файл не открыт!\n\n" << endl;
			system("pause");
			return;
		}
	}
	int FreeList()    //поиск пустого списка (отдел)
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
	void AddSection()	//добавление отделов
	{
		int k = FreeList();
		if (k == -5)//если заполнен
		{
			cout << "Число отделений достигла лимита!" << endl;
			system("pause");
			return;
		}
		else { Section *temp = list[k]; }
		if (list[0]->GetNext() == NULL)
		{
			string ffame;
			do {
				system("cls");
				cout << "Название отдела :";
				getline(cin, ffame);
				ffame = ClearWords(ffame);
			} while (ffame == ""|| ffame=="//Отдел//" || ffame == "//Сотрудники//" || pust(ffame) == -1);
			list[k]->Setname(ffame);
			list[k]->SetNull();
			list[0]->SetNext(list[k]);
			cout << "Отдел добавлен!" << endl;
			system("pause");
		}
		else//не заполнен
		{
			string choose;//до или после
			do
			{
				cout << "1 - Добавить отдел после заднного отдела \n2 - Добавить отдел до заданного отдела" << endl;
				getline(cin, choose);
				choose = ClearWords(choose);
			} while (choose != "1" && choose != "2");
			cout << "Поиск отдела : " << endl;
			string ask;//значение отдела для поиска
			getline(cin, ask);
			ask = ClearWords(ask);
			if (choose == "1") {//после
				Section *poisk = list[0];
				while (poisk->GetNext() != NULL)//обход отдела
				{
					poisk = poisk->GetNext();
					if (poisk->GetName() == ask)//если нашёл
					{
						cout << "Отдел найден\n-------------------------" << endl;
						string fame;
						do {
							system("cls");
							cout << "Название отдела :" << endl;
							getline(cin, fame);
							fame = ClearWords(fame);
						} while (fame == "" || fame == "//Отдел//" || fame == "//Сотрудники//" || pust(fame) == -1);
						list[k]->Setname(fame);
						list[k]->SetNull();
						list[k]->SetNext(poisk->GetNext());
						poisk->SetNext(list[k]);
						cout << "Отдел добавлен" << endl;
						system("pause");
						return;
					}
				}
				cout << "Элемент не найден!" << endl;
				system("pause");
				list[k]->SetKey(1);
				return;
			}
			if (choose == "2") {
				Section *poisk1 = list[0];
				Section *last = list[0];
				while (poisk1->GetNext() != NULL)//обход отдела
				{
					poisk1 = poisk1->GetNext();
					if (poisk1->GetName() == ask)//если нашёл
					{
						cout << "Отдел найден\n-------------------------" << endl;
						cout << "Название отдела :" << endl;
						string fame;
						do {
							system("cls");
							cout << "Название отдела :" << endl;
							getline(cin, fame);
							fame = ClearWords(fame);
						} while (fame == "" || fame == "//Отдел//" || fame == "//Сотрудники//" || pust(fame) == -1);
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
						cout << "Отдел добавлен" << endl;
						system("pause");
						return;
					}
					last = last->GetNext();
				}
				cout << "Элемент не найден!" << endl;
				system("pause");
				list[k]->SetKey(1);
				return;
			}
		}
	}
	int pust(string h) //проверка на пустоту
	{
			bool ad = false;
			for (int j = 0; j < h.length(); j++)
			{
				if (h.at(j) != ' ') { ad = true; }
			}
			if (ad == true) {
				return 1;//1 - символ есть
			}
			else { return -1; }//-1 - символа нету
	}
	void DownloadFromFile()    //загрузка из файла
	{
		Section *temp = list[0];
		DelAll();
		int k=0;
		int key = 0;
		string h="";
		ifstream txt("file.txt");
		if (txt.is_open()) // вызов метода is_open()
		{
			getline(txt, h);
			h = ClearWords(h);
			while (key != 5)
			{
				if (h == "//Отдел//") {
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
					if (h != "//Отдел//"&&h != "//Сотрудники//"&&!h.empty())
					{
						k = FreeList();
						if (k == -5)//если заполнен
						{
							cout << "Число отделений достигла лимита!" << endl;
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
						if (h != "//Отдел//" && h != "//Сотрудники//")
						{
							cout << "Ошибка! В файле каждый отдел должен иметь свою метку!"<<endl<<"Отдел "<<h<<" не имеет своей метки!"<<endl;
							system("pause");
							txt.close();
							return;
						}
					}
				}
				else if (h == "//Сотрудники//") {
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
						if ((txt.eof()) || h == "//Отдел//" || h == "//Сотрудники//") { a = 1; }
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
							if (h1 != "//Отдел//" && h1 != "//Сотрудники//" && !h1.empty()&&!(pust(h1) == -1))
							{
								temp->AddWork(h, h1);
							}
							else {
								a = 1;
								cout << "Ошибка! Сотрудник должен иметь должность!!!" << endl << "сотрудник по фамилии " << h << " не имеет должности!" << endl;
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
				if (h != "//Отдел//" && h != "//Сотрудники//"&&!h.empty())
				{
					bool ad = false;
					for (int j = 0; j < h.length(); j++)
					{
						if (h.at(j) != ' ') { ad = true; }
					}
					if (ad == true) {
						cout << "Ошибка! Данные находятся до первой метки!" << endl;
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
			cout << "Файл не открыт!" << endl;
			system("pause");
			return;
		}
	}
	void AddWorker()    //добавить сотрудника
	{
		if (list[0]->GetNext() == NULL)//отделов нет
		{
			cout << "отделы не добавлены! создайте отдел!" << endl;
			system("pause");
			return;
		}
		else//отделы есть
		{
			cout << "название отдела для добавления сотрудников : " << endl;
			string otdel_poisk;
			getline(cin, otdel_poisk);
			otdel_poisk = ClearWords(otdel_poisk);
			Section *poisk_list = list[0];
			while (poisk_list->GetNext() != NULL)//обход отделов
			{
				poisk_list = poisk_list->GetNext();
				if (poisk_list->GetName() == otdel_poisk)//поиск нашёл отдел
				{
					cout << "Отдел найден." << endl;
					system("pause");
					string name_worker = "";
					string mayor_worker = "";
					if (poisk_list->GetPstack() == NULL)//если первый элемент
					{
						do {
							system("cls");
							cout << "фамилия сотрудника : " << endl;
							getline(cin, name_worker);
							name_worker = ClearWords(name_worker);
						} while (name_worker == "" || name_worker== "//Сотрудники//" || name_worker == "//Отдел//"||pust(name_worker)==-1);
						do {
							system("cls");
							cout << "должность сотрудника : " << endl;
							getline(cin, mayor_worker);
							mayor_worker = ClearWords(mayor_worker);
						} while (mayor_worker == "" || mayor_worker== "//Сотрудники//" || mayor_worker == "//Отдел//" || pust(mayor_worker) == -1);
						poisk_list->FirstWorker(name_worker, mayor_worker);
						cout << "Сотрудник добавлен!" << endl;
						system("pause");
						return;
					}
					else {
						cout << "1 - добавить сотрудника после сотрудника (поиск с начала) \n2 - добавить сотрудника до сотдрудника (с начала)\n3 - добавить сотрудника после сотрудника (поиск с конца) \n4 - добавить сотрудника до сотдрудника (с конца)" << endl;
						string dobav;// 1 или 2
						do {
							getline(cin, dobav); 
							dobav = ClearWords(dobav);
						} while (dobav != "1" && dobav != "2"&& dobav != "3"&& dobav != "4");
						string search_work;// поиск сотрудника
						cout << "фамилия сотрудника для поиска : ";
						getline(cin, search_work);
						search_work = ClearWords(search_work);
						poisk_list->AddWorker(dobav, search_work);
						return;
					}
				}
			}
			cout << "Отдел не найден." << endl;
			system("pause");
		}
	}
	void SearchSection() {      //поиск отдела
		string http = "";
		int summer = 0;
		Section *dom = list[0]->GetNext();
		while (http == "") {
			system("cls");
			cout << "Поиск отдела (Название) :" << endl;
			getline(cin, http);
			http = ClearWords(http);
		}
		while (dom != NULL) {
			if (dom->GetName() == http) { summer++; }
			dom = dom->GetNext();
		}
		cout << "Нашлось " << summer << " отделов" << endl;
		system("pause");
	}
	void Show()		//вывод на консоль
	{
		Section *temp = list[0];
		cout << "                 Организация : " + list[0]->GetName() << endl;
		while (temp->GetNext() != NULL)
		{
			temp = temp->GetNext();
			cout << "      Отделение : " + temp->GetName() << endl;
			temp->Show();
		}
		system("pause");
	}
	Content();
	~Content();
};