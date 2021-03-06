#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "Sklad.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string name_sklad;// название скалада
	string start_again = "";
	int sikl = 0;
	do {
		system("cls");
		do//проверка на пустоту
		{
			system("cls");
			cout << "Название склада : ";
			getline(cin, name_sklad);
			bool stop = false;
			for (int j = 0; j < name_sklad.length(); j++)
			{
				if (name_sklad.at(j) != ' '&&name_sklad.at(j)!='\t') { stop = true; }
			}
			if (stop == true) {
				sikl = 1;//1 - символ есть
			}
			else { sikl = -1; }//-1 - символа нету
		} while (name_sklad == "" || sikl == -1);
		int number = 0;//число секций
		string kolvo="";
		while (number <= 0 || number > 100)
		{
			system("cls");
			cout << "Количество секций : " << endl;
			getline(cin, kolvo);//ввод строки
			number = atoi(kolvo.c_str());//преобразование к int
			for (int i = 0; i < kolvo.size(); i++) {
				if (kolvo.at(i) != '1' && kolvo.at(i) != '0' && kolvo.at(i) != '2' && kolvo.at(i) != '3' && kolvo.at(i) != '4' && kolvo.at(i) != '5' && kolvo.at(i) != '6' && kolvo.at(i) != '7' && kolvo.at(i) != '8' && kolvo.at(i) != '9')
				{
					number = -1;
				}
			}
			if (number <= 0 || number > 100) { cout << "Ошибка! Введите размер секций в диапазоне от 1 до 100" << endl; system("pause"); }
		}
		Sklad sklad = Sklad(name_sklad,number);
		bool menu_sikl = true;
		while (menu_sikl != false)
		{
			system("cls");
			cout << "1 - Добавить секцию \n2 - Добавить ячейку \n3 - Удалить секцию \n4 - Удалить ячейку \n5 - Вывод на экран \n6 - Сохранить в файл \n7 - Загрузить из файла\n8 - Удаление всей структуры \n9 - Выход из программы" << endl;
			string ask;
			getline(cin, ask);
			start_again = ask;
			if (ask == "1") {
				sklad.AddSection();
			}
			else if (ask == "2") {
				sklad.AddCell();
			}
			else if (ask == "3") {
				sklad.DeleteSection();
			}
			else if (ask == "4") {
				sklad.DeleteCell();
			}
			else if (ask == "5") {
				system("cls");
				sklad.Show();
			}
			else if (ask == "6") {
				string saving = "";
				cout << "1 - Сохранить данные в конец файла" << endl << "2 - Перезапись файла" << endl;
				getline(cin, saving);
				if (saving == "1" || saving == "2")
				{
					sklad.SaveToFile(saving);
				}
				else {
					cout << "Ошибка! Введите цифру 1 или 2" << endl;
					system("pause");
				}
			}
			else if (ask == "7") {
				string a="";
				system("cls");
				cout << "Сохранить данные в файл перед загрузкой?" << endl;
				cout << "1 - Сохранить данные в конец файла и загрузить " << endl << "2 - Перезаписать файл и загрузить " << endl << "3 - Загрузить данные без сохранения" << endl;
				getline(cin, a);
				if (a == "1" || a == "2")
				{
					sklad.SaveToFile(a);
					sklad.DownloadFromFile();
				}
				else if (a == "3")
				{
					sklad.DownloadFromFile();
				}
				else {
					cout << "Ошибка! Введите цифру 1 или 2 или 3" << endl;
					system("pause");
				}
			}
			else if (ask == "8") {
				sklad.~Sklad();
				cout << "Структура удалена" << endl;
				system("pause");
				menu_sikl = false;
			}
			else if (ask == "9") {
				sklad.~Sklad();
				menu_sikl = false;
			}
		}
	} while (start_again != "9");
	return 0;
}
