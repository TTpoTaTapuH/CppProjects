#include "stdafx.h"
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <cstdlib>
#include <istream>
#include <conio.h>
#include <string>
#include <windows.h>
#include "Content.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");
	string KAI;// название организации
	setlocale(LC_ALL, "RUS");
	string WMI = "XAXA";
	int tt = 0;
	do {
		system("cls");
		do//проверка на пустоту
		{
			system("cls");
			cout << "Добрый день." << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Название вашей организации : ";
			getline(cin, KAI);
			bool ad = false;
			for (int j = 0; j < KAI.length(); j++)
			{
				if (KAI.at(j) != ' ') { ad = true; }
			}
			if (ad == true) {
				tt = 1;//1 - символ есть
			}
			else { tt = -1; }//-1 - символа нету
		} while (KAI == "" || tt == -1 || KAI == "//Отдел//" || KAI == "//Сотрудники//");
		int number = int();//число отделов

		string S;
		while (number <= 0 || number > 100)
		{
			system("cls");
			cout << "Количество отделов в организации : " << endl;
			getline(cin, S);//ввод строки
			number = atoi(S.c_str());//преобразование к int
			if (number <= 0 || number > 100) { cout << "Ошибка! Введите размер отделов от 1 до 100" << endl; system("pause"); }
		}
		Content content = Content(number, KAI);//число отделов и название организации
		bool stop = true;//пока не выйдет
		while (stop != false)
		{
			system("cls");
			cout << "1 - Добавить отдел \n2 - Добавить сотрудников \n3 - Удалить отдел \n4 - Удалить сотрудника \n5 - Поиск отдела \n6 - Поиск сотрудника \n7 - Вывод на экран \n8 - Сохранить в файл \n9 - Загрузить из файла\n10 - Удаление всей структуры \n11 - Выход из программы" << endl;
			string ask;
			getline(cin, ask);
			WMI = ask;
			if (ask == "1") {
				content.AddSection();
			}
			else if (ask == "2") {
				content.AddWorker();
			}
			else if (ask == "3") {
				content.DeleteSection();
			}
			else if (ask == "4") {
				content.DeleteWorker();
			}
			else if (ask == "5") {
				content.SearchSection();
			}
			else if (ask == "6") {
				content.SearchWorker();
			}
			else if (ask == "7") {
				system("cls");
				content.Show();
			}
			else if (ask == "8") {
				content.SaveToFile();
			}
			else if (ask == "9") {
				int a;
				system("cls");
				cout << "Сохранить данные файлы перед загрузкой?" << endl;
				cout << "1 - Сохранить данные в файл " << endl << "2 - Загрузить данные без сохранения" << endl;
				cin >> a;

				if (a == 1)
				{
					content.SaveToFile();
					content.DownloadFromFile();
				}
				else
				{
					content.DownloadFromFile();
				}
			}
			else if (ask == "10") {
				content.DelAll();
				cout << "Структура удалена" << endl;
				system("pause");
				content.~Content();
				stop = false;
			}
			else if (ask == "11") { stop = false; }
		}
	} while (WMI != "11");
	return 0;
}

