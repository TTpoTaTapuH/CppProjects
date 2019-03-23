#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <conio.h>
#include <string>
#include <windows.h>
#include "Worker.h"
#pragma once
using namespace std; 
class Section
{
private:
	Section *next;
	int key;
	string name;
	Worker *pstack;
public:
	Section(string txt) {
		name = txt;
		pstack = NULL;
	}
	void SetNull() {
		pstack = NULL;
		next = NULL;
	}
	void Show() {
		Worker *st = pstack;
		while (st != NULL)
		{
			cout << "Фамилия  : " + st->GetName() << endl;
			cout << "Дожность : " + st->GetMayor() << endl;
			cout << "" << endl;
			st = st->GetRight();
		}
	}
	int pust(string h)
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
	void DeletWorker() {
			if (pstack == NULL) { cout << "Список сотрудников пуст. Добавьте сотрудников!" << endl; return; }
			Worker *search_stack = pstack;
			string name_stack;
			string askdel = "";
			while (askdel != "1" && askdel != "2") {
				cout << "1 - Поиск сотрудника для удаления (с начала) \n2 - Поиск сотрудника для удаления (с конца)" << endl;
				getline(cin, askdel);
				askdel = ClearWords(askdel);
			}
			cout << "Фамилия сотрудника для удаления : ";
			getline(cin, name_stack);
			name_stack = ClearWords(name_stack);
			if (askdel == "1")
			{
				while (search_stack != NULL)
				{
					if (search_stack->GetName() == name_stack)
					{
						if (search_stack->GetLeft() == NULL) {
							Worker *del1 = pstack;
							if (pstack->GetRight() != NULL)
							{
								pstack->GetRight()->SetLeft(NULL);
							}
							pstack = pstack->GetRight();
							delete del1;
							cout << "Сотрудник удалён." << endl;
							system("pause");
							return;
						}
						else {
							search_stack->GetLeft()->SetRight(search_stack->GetRight());
							if (search_stack->GetRight() != NULL) {
								search_stack->GetRight()->SetLeft(search_stack->GetLeft());
							}
							delete search_stack;
							cout << "Сотрудник удалён." << endl;
							system("pause");
							return;
						}
					}
					search_stack = search_stack->GetRight();
				}

				cout << "Сотрудник не найден!" << endl;
				system("pause");
				return;
			}
			if (askdel == "2") {
				while (search_stack->GetRight() != NULL)
				{
					search_stack = search_stack->GetRight();
				}
				while (search_stack != NULL)
				{
					if (search_stack->GetName() == name_stack)
					{
						if (search_stack->GetLeft() == NULL) {
							Worker *del = pstack;
							if (pstack->GetRight() != NULL)
							{
								pstack->GetRight()->SetLeft(NULL);
							}
							pstack = pstack->GetRight();
							delete del;
							cout << "Сотрудник удалён." << endl;
							system("pause");
							return;
						}
						else {
							search_stack->GetLeft()->SetRight(search_stack->GetRight());
							if (search_stack->GetRight() != NULL)
							{
								search_stack->GetRight()->SetLeft(search_stack->GetLeft());
							}
							delete search_stack;
							cout << "Сотрудник удалён." << endl;
							system("pause");
							return;
						}
					}
					search_stack = search_stack->GetLeft();
				}
				cout << "Сотрудник не найден!" << endl;
				system("pause");
				return;
			}
	}
	string ClearWords(string word) {    //преобразовать строку
		if (word.size() > 10000) {
			cout << "Ошибка! Вводимые символы не должны быть больше 1000!" << endl;
			system("pause");
			return "Error";
		}
		string endword;
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
	void AddWork(string dobav, string work1)
	{
		Worker *work;
		if (pstack == NULL) {
			work = new Worker(dobav, work1);
			work->SetLeft(NULL);
			work->SetRight(NULL);
			pstack = work;
			return;
		}
		work = pstack;
		int a = 0;
			while (a!=1)//поиск соответсвия
			{
				if(work->GetRight()!=NULL)
				work = work->GetRight();
				if(work->GetRight()==NULL)
				{
					a = 1;
				}
			}
			Worker *new_work1 = new Worker(dobav, work1);
			new_work1->SetRight(work->GetRight());
			new_work1->SetLeft(work);
			if (work->GetRight() != NULL) { work->GetRight()->SetLeft(new_work1); }
			else {}
			work->SetRight(new_work1);
			return;
	}
	void AddWorker(string dobav, string search_work)
	{
		string name_worker = "", mayor_worker = "";
		Worker *work = pstack;
		if (dobav == "1" || dobav == "2")
		{
			while (work != NULL)//поиск соответсвия
			{
				if (work->GetName() == search_work) { break; }
				work = pstack->GetRight();
			}
			if (work == NULL) {
				cout << "Поиск не нашёл сотрудника" << endl;
				system("pause");
				return; }//если не нашёл
		}
		if (dobav == "3" || dobav == "4")
		{
			while (work->GetRight() != NULL) { work = work->GetRight(); }
			while (work != NULL)//поиск соответсвия
			{
				if (work->GetName() == search_work) { break; }
				work = work->GetLeft();
			}
			if (work == NULL) { 
				cout << "Поиск не нашёл сотрудника" << endl;
				system("pause");
				return; }//если не нашёл
		}
		if (dobav == "1" || dobav == "3")//после
		{
			do {
				system("cls");
				cout << "фамилия сотрудника : " << endl;
				getline(cin, name_worker);
				name_worker = ClearWords(name_worker);
			} while (name_worker == "" || name_worker == "//Сотрудники//" || name_worker == "//Отдел//" || pust(name_worker)==-1);
			do {
				system("cls");
				cout << "должность сотрудника : " << endl;
				getline(cin, mayor_worker);
				mayor_worker = ClearWords(mayor_worker);
			} while (mayor_worker == "" || mayor_worker == "//Сотрудники//" || mayor_worker == "//Отдел//" || pust(mayor_worker) == -1);
			Worker *new_work1 = new Worker(name_worker, mayor_worker);
			new_work1->SetRight(work->GetRight());
			new_work1->SetLeft(work);
			if (work->GetRight() != NULL) { work->GetRight()->SetLeft(new_work1); }
			else {}
			work->SetRight(new_work1);
			cout << "Сотрудник добавлен!" << endl;
			system("pause");
			return;
		}
		if (dobav == "2" || dobav == "4")//до
		{
			do {
				system("cls");
				cout << "фамилия сотрудника : " << endl;
				getline(cin, name_worker);
				name_worker = ClearWords(name_worker);
			} while (name_worker == "" || name_worker == "//Сотрудники//" || name_worker == "//Отдел//" || pust(name_worker) == -1);
			do {
				system("cls");
				cout << "должность сотрудника : " << endl;
				getline(cin, mayor_worker);
				mayor_worker = ClearWords(mayor_worker);
			} while (mayor_worker == "" || mayor_worker == "//Сотрудники//" || mayor_worker == "//Отдел//" || pust(mayor_worker) == -1);
			Worker *new_work1 = new Worker(name_worker, mayor_worker);
			new_work1->SetRight(work);
			new_work1->SetLeft(work->GetLeft());
			if (work->GetLeft() != NULL) { work->GetLeft()->SetRight(new_work1); }
			else { pstack = new_work1; }
			work->SetLeft(new_work1);
			cout << "Сотрудник добавлен!" << endl;
			system("pause");
			return;
		}
	}
	void DeletSection() {
		while (pstack != NULL)//обход сотрудника
		{
			Worker *del = pstack;//удаляемый сотрудник
			pstack = pstack->GetRight();//переход к следующему сотруднику
			delete del;//удалить сотрудника
		}
	}
	void SaveToFile() {
		Worker *ask = pstack;
		fstream txt("file.txt", ios::app);
		if (txt.is_open()) // вызов метода is_open()
		{
			txt << "		 //Сотрудники//" << endl;
			while (ask != NULL)
			{
				txt << "	 "<<ask->GetName() << endl;
				txt << " " << ask->GetMayor() << endl;
				ask = ask->GetRight();
			}
			txt.close();
		}
		else
		{
			cout << "Файл не открыт!\n\n" << endl;
			system("pause");
			return;
		}
	}
	void SearchWorker(string gg) {
		Worker *work = pstack;
		int summer = 0;
		while (work != NULL) {
			if (work->GetName() == gg) { summer++; }
			work = work->GetRight();
		}
		cout << "Нашлось " << summer << " отделов" << endl;
		system("pause");
	}
	void FirstWorker(string nm, string mr) {
		Worker *new_stack = new Worker(nm, mr);
		new_stack->First_Worker();
		pstack = new_stack;
	}
	Worker* GetPstack() { return pstack; }
	void SetKey(int a) {	key = a; }
	int GetKey() {		return key;	}
	Section* GetNext() {	return next; }
	void SetNext(Section *ptr)	{	next = ptr;	}
	void Setname(string nam) {		name = nam;	}
	string GetName() {		return name;	}
	Section();
	~Section();
};