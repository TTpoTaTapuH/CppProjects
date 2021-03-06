#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include "Table.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);//язык консоли - русский
	SetConsoleOutputCP(1251);//ввод русского языка из консоли
	system("color F0");//цветк онсоли
	string name_table;// название таблицы
	string exit = "";//выход из программы - условие
	int pust = 0;//условие пустоты введённой строки
	do {
		system("cls");//очистка консоли
		do//проверка на пустоту
		{
			system("cls");
			cout << "Заголовок таблицы : ";
			getline(cin, name_table);//ввод  строки в переменную названии таблицы
			bool reading_void = false;//условие пустоты строки
			for (int j = 0; j < name_table.length(); j++)//сравниваем каждый элемент на пустоту
			{
				if (name_table.at(j) != ' ') { reading_void = true; }//если не пусто
			}
			if (reading_void == true) {//выходим из цикла
				pust = 1;//1 - символ есть
			}
			else { pust = -1; }//-1 - символа нету
		} while (name_table == "" || pust == -1 || name_table == "Строка:" || name_table == "Ячейки:");
		Table table = Table(name_table);//число отделов и название организации
		bool stop = true;//пока не выйдет
		while (stop != false)
		{
			system("cls");
			cout << "1 - Добавить строку \n2 - Добавить ячейку \n3 - Удалить строку \n4 - Удалить ячейку \n5 - Поиск строки \n6 - Поиск ячейки \n7 - Вывод на экран \n8 - Сохранить в файл \n9 - Загрузить из файла\n10 - Удаление всей структуры \n11 - Выход из программы" << endl;
			string ask;
			getline(cin, ask);
			exit = ask;
			if (ask == "1") {
				table.Add_Line();
			}
			else if (ask == "2") {
				table.Add_Cell();
			}
			else if (ask == "3") {
				table.Delete_Line();
			}
			else if (ask == "4") {
				table.Delete_Cell();
			}
			else if (ask == "5") {
				table.Search(1);
			}
			else if (ask == "6") {
				table.Search(2);
			}
			else if (ask == "7") {
				system("cls");
				table.Show();
			}
			else if (ask == "8") {
				string saving = "";
				cout << "1 - Сохранить данные в конец файла" << endl << "2 - Перезаписать файл" << endl;
				getline(cin, saving);
				table.Save_To_File(saving);
			}
			else if (ask == "9") {
				string a;
				system("cls");
				cout << "Сохранить данные перед загрузкой?" << endl;
				cout << "1 - Сохранить данные в конец файла перед загрузкой данных " << endl << "2 - Перезаписать файл перед загрузкой данных " << endl << "3 - Загрузить данные без сохранения" << endl;
				getline(cin, a);
				if (a == "1" || a == "2")
				{
					table.Save_To_File(a);
					table.Download_From_File();
					cout << "Данные загрузились из файла" << endl;
					system("pause");
				}
				else if (a == "3")
				{
					table.Download_From_File();
					cout << "Данные загрузились из файла" << endl;
					system("pause");
				}
				else { cout << "Ошибка! Введите цифру 1 или 2 или 3!" << endl; system("pause"); }
			}
			else if (ask == "10") {
				table.~Table();
				cout << "Структура удалена" << endl;
				system("pause");
				stop = false;
			}
			else if (ask == "11") {
				table.~Table();
				stop = false;
			}
		}
	} while (exit != "11");
	return 0;
}

