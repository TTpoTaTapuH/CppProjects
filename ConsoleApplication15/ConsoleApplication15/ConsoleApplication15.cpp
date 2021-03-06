// ConsoleApplication15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;
struct List
{
	int inf;
	List *next;
	List *left;
};
struct Array {
	List *item;
	List *tail;
};
void Randoming(int *&mass, int size) {//перемешка
	for (int i = 0; i < size; i++) {
		int k = rand() % size;
		int type = mass[i];
		mass[i] = mass[k];
		mass[k] = type;
	}
}
void create(int *&mass, int size)//массив с неповт. ключами
{
	for (int t = 0; t < size; t++)
	{
		mass[t] = t;
	}
	Randoming(mass, size);
}
void createPov(int *&povtor, int size) {//с повтором
	for (int t = 0; t < size; t++)
	{
		povtor[t] = rand()%size;
	}
	cout << "Массив создан." << endl;
	system("pause");
}
void print(int *arr, int size) {//вывод
	int a = 0;
	for (int i = 0; i < size; i++)
	{
		if (a == 20)
		{
			cout << endl;
			a = 0;
		}
		cout << setw(4) << arr[i];
		a++;
	}
	cout << endl;
	system("pause");
}
void KarmanSort(int *&arr1, int size)//без массива
{
	int perestanovka = 0, sravnenie = 0;
	for (int i = 0; i < size; i++)
	{
		sravnenie++;
		while (arr1[i] != i)
		{
			sravnenie++;
			int temp = arr1[i];
			arr1[i] = arr1[temp];
			arr1[temp] = temp;
			perestanovka++;
		}
	}
	cout << "\nКарманная сортировка:\nСравнений: " << sravnenie << ".\nПерестановок: " << perestanovka << endl;
	system("pause");
}
void KarmanPovtor(int *arr, int size) {//с повтором
	Array *array = new Array[size];
	int perestanovka = 0, sravnenie = 0;
	cout << "Неотсортированный массив" << endl;
	for (int i = 0; i < size; i++)
	{
		array[i].item = NULL;
	}
	print(arr, size);
	for (int i = 0; i < size; i++)
	{
		perestanovka++;
		List *temp = array[arr[i]].item;
		array[arr[i]].item = new List;
		array[arr[i]].item->next = temp;
		array[arr[i]].item->inf = arr[i];
	}
	for (int i = 0, j = 0; i < size; i++)
	{

		while (array[i].item != NULL && i < size)
		{
			sravnenie++;
			perestanovka++;
			arr[j] = array[i].item->inf;
			j++;
			array[i].item = array[i].item->next;
		}
	}
	system("pause");
	cout << "Отсортированный массив" << endl;
	print(arr, size);
	cout << "\nКарманная сортировка:\nСравнений: " << sravnenie << ".\nПерестановок: " << perestanovka << endl;
	system("pause");
}
void KarmanArraySort(int *&arr1, int size) {//с массивом
	int perestanovka = 0;
	int *result = new int[size];
	for (int i = 0; i < size; i++)
	{
		result[arr1[i]] = arr1[i];
		perestanovka++;
	}
	for (int i = 0; i < size; i++)
	{
		arr1[i] = result[i];
	}
	cout << "Карманная сортировка с вспомогательным массивом:\nСравнений: 0.\nПерестановок:"<< perestanovka <<endl;
	system("pause");
}
void createRazradi(int *&arr, int size) {//поразрядно
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 900 + 100;
	}
	print(arr, size);
}
void porazrad(int *&arr, int size) {//пораязрядная сортировка
	int perestanovka = 0, sravnenie = 0;
	Array *result = new Array[size];
	for (int bitwise = 1; bitwise < 1000; bitwise *= 10)
	{
		for (int i = 0; i < 10; i++)
		{
			result[i].item = NULL;
			result[i].tail = NULL;
		}
		for (int i = 0; i < size; i++)
		{
			perestanovka++;
			int index = (arr[i] % (10 * bitwise)) / bitwise;
			List *next = result[index].item;
			result[index].item = new List;
			result[index].item->next = next;
			result[index].item->left = NULL;
			result[index].item->inf = arr[i];
			if (next != NULL)
			{
				next->left = result[index].item;
			}
			else
			{
				result[index].tail = result[index].item;
			}
		}
		for (int i = 0, j = 0; i < 10; i++, sravnenie++)
		{
			while (result[i].tail != NULL && j < size)
			{
				sravnenie++;
				perestanovka++;
				arr[j] = result[i].tail->inf;
				result[i].tail = result[i].tail->left;
				j++;
			}
		}
	}
	cout << endl;
	print(arr, size);
	cout << endl<<"Поразрядная сортировка: "<<endl<<"Сравнений: " << sravnenie <<endl<<"Перестановок: " << perestanovka / 3 <<endl;
	system("pause");
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int a = 0;
	int size;
	int *arr = NULL;
	int *arr1 = NULL;
	int *povtor = NULL;
	bool sort = false;
	while (a != 8)
	{
		system("cls");
		cout << "1 - создать массив без повторений." << endl;
		cout << "2 - вывести исходный массив на экран." << endl;
		cout << "3 - выполнить карманную сортировку без второго массива. " << endl;
		cout << "4 - вывести результат сортировки." << endl;
		cout << "5 - выполнить карманную сортировку с двумя массивами." << endl;
		cout << "6 - выполнить карманную сортировку с повторениями." << endl;
		cout << "7 - выполнить поразрядную сортировку." << endl;
		cout << "8 - выйти" << endl;
		cin >> a;
		switch (a)
		{
		case(1):
		{
			if (arr != NULL || arr1 != NULL) {
				delete arr, arr1;
				arr = NULL;
				arr1 = NULL;
			}
			cout << "Введите размер массива: ";
			cin >> size;
			cout << endl;
			arr = new int[size];
			arr1 = new int[size];
			create(arr, size);
			cout << "Массив создан!" << endl;
			break;
		}
		case(2):
		{
			if (arr != NULL) {
				cout << "Неотсортированный массив: " << endl;
				print(arr, size);
				break;
			}
		}
		case(3):
		{
			if (arr != NULL) {
				for (int i = 0; i < size; i++)
				{
					arr1[i] = arr[i];
				}
				KarmanSort(arr1, size);
			}
			break;
		}
		case(4):
		{
			if (arr1 != NULL) {
				print(arr1, size);
			}
			break;
		}
		case(5):
		{
			for (int i = 0; i < size; i++)
			{
				arr1[i] = arr[i];
			}
			KarmanArraySort(arr1, size);
			break;
		}
		case(6):
		{
			cout << "Введите размер массива: ";
			cin >> size;
			povtor = new int[size];
			createPov(povtor, size);
			cout << "Новый массив создан!" << endl;
			KarmanPovtor(povtor, size);
			cout << "Сортировка выполнена!" << endl;
			break;
		}
		case(7):
		{
			cout << "Введите размер массива: ";
			cin >> size;
			cout << endl;
			int *arrt = new int[size];
			createRazradi(arrt, size);
			cout << "Новый массив создан!" << endl;
			porazrad(arrt, size);
			cout << "Сортировка выполнена!" << endl;
		}
		}
	}
    return 0;
}

