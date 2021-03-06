// kursovaya_andrey.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "Country.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string Name_of_Country="";
	string start_to_again = "";
	bool if_empty = true;
	do {
		system("cls");
		do
		{
			system("cls");
			cout << "Название Страны : ";
			getline(cin, Name_of_Country);
			bool find_char = false;
			for (int j = 0; j < Name_of_Country.length(); j++)
			{
				if (Name_of_Country.at(j) != ' '&& Name_of_Country.at(j) != '\t') { find_char = true; }
			}
			if (find_char == true) {
				if_empty = false;
			}
			else { if_empty = true; }
		} while (Name_of_Country == "" || if_empty == true);
		
		Country country = Country(Name_of_Country);
		bool start_menu = true;
		while (start_menu != false)
		{
			system("cls");
			cout << "1 - Добавить Республику \n2 - Добавить город \n3 - Удалить Республику \n4 - Удалить город \n5 - Вывод на экран \n6 - Сохранить в файл \n7 - Загрузить из файла\n8 - Удаление всей структуры \n9 - Выход из программы" << endl;
			string choice;
			getline(cin, choice);
			start_to_again = choice;
			if (choice == "1") {
				country.Add_Republic();
			}
			else if (choice == "2") {
				country.Add_City();
			}
			else if (choice == "3") {
				country.Remove_Republic();
			}
			else if (choice == "4") {
				country.Remove_City();
			}
			else if (choice == "5") {
				system("cls");
				country.Show();
			}
			else if (choice == "6") {
				string saving = "";
				cout << "1 - Сохранить данные в конец файла" << endl << "2 - Перезаписать файл" << endl;
				getline(cin, saving);
				country.Save_to_file(saving);
			}
			else if (choice == "7") {
				string a;
				system("cls");
				cout << "Сохранить данные перед загрузкой?" << endl;
				cout << "1 - Сохранить данные в конец файла перед загрузкой данных " << endl << "2 - Перезаписать файл перед загрузкой данных " << endl << "3 - Загрузить данные без сохранения" << endl;
				getline(cin, a);
				if (a == "1" || a == "2")
				{
					country.Save_to_file(a);
					country.Download_From_File();
					cout << "Данные загрузились из файла" << endl;
					system("pause");
				}
				else if (a == "3")
				{
					country.Download_From_File();
					cout << "Данные загрузились из файла" << endl;
					system("pause");
				}
				else { cout << "Ошибка! Введите цифру 1 или 2 или 3!" << endl; system("pause"); }
			}
			else if (choice == "8") {
				country.~Country();
				cout << "Структура удалена" << endl;
				system("pause");
				start_menu = false;
			}
			else if (choice == "9") {
				country.~Country();
				start_menu = false;
			}
		}
	} while (start_to_again != "9");
    return 0;
}

