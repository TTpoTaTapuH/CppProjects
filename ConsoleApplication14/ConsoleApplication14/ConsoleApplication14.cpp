// ConsoleApplication13.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <math.h>
#include "conio.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
int kolvo = 0;
int *Make()
{
	cout << "Кол-во элементов :" << endl;
	cin >> kolvo;
	int *arr = NULL;
	arr = new int[kolvo];
	for (int i = 0; i<kolvo; i++)
	{
		arr[i] = rand() % 100 + 1;
	}
	cout << "Массив создан" << endl;
	system("pause");
	return arr;
}
void show(int *array)
{
	int a = 0;
	for (int i = 0; i<kolvo; i++)
	{
		if (a == 20)
		{
			cout << endl;
			a = 0;
		}
		cout << setw(4) << array[i];
		a++;
	}
	cout << endl;
	system("pause");
}
void obmen(int *arr1)
{
	int srav = 0, peres = 0;
	int temp;
	for (int i = 0; i < kolvo; i++)
	{
		for (int j = kolvo - 1; j > i; j--, srav++) {
			if (arr1[j - 1] > arr1[j])
			{
				temp = arr1[j - 1];
				arr1[j - 1] = arr1[j];
				arr1[j] = temp;
				peres++;
			}
		}
	}
	system("cls");
	cout << "Число сравнений: " << srav << endl << "Число перестановок: " << peres << endl;
	system("pause");
	system("cls");
	show(arr1);
}
void QuickSort(int *mass, int left, int right, int &srav, int &per)
{
	if (mass == NULL)
	{
		return;
	}
	int i = left, j = right;
	int medium = mass[(i + j) / 2];
	do
	{
		srav++;
		while (mass[i] < medium)
		{
			i++;
			srav++;
		}
		srav++;
		while (mass[j] > medium)
		{
			srav++;
			j--;
		}
		if (i <= j)
		{
			per++;
			int temp = mass[i];
			mass[i] = mass[j];
			mass[j] = temp;
			i++;
			j--;
		}
	} while (i < j);
	if (left < j)
	{
		QuickSort(mass, left, j, srav, per);
	}
	if (right > i)
	{
		QuickSort(mass, i, right, srav, per);
	}
}
void Shell(int *myarray) { 
	int num = (int)log2(kolvo);
	int srav = 0, peres = 0;
	int *Shag = new int[num];
	for (int i = 0; num >= 1; num--, i++)
	{
		Shag[i] = pow(2, num) - 1;
	}
	for (int m = 0; m < (int)log2(kolvo); m++)
	{
		for (int i = Shag[m]; i < kolvo; i++)
		{
			peres++;
			int temp = myarray[i];
			int j = i - Shag[m];
			srav++;
			while (j >= 0 && temp < myarray[j])
			{
				peres++;
				srav++;
				myarray[j + Shag[m]] = myarray[j];
				j = j - Shag[m];
			}
			peres++;
			myarray[j + Shag[m]] = temp;
		}
	}
	peres /= 3;
	system("cls");
	cout << "Число сравнений: " << srav << endl << "Число перестановок: " << peres << endl;
	system("pause");
	system("cls");
	show(myarray);
	system("pause");
}
void ShiftHelp(int *Array, int i, int count, int &srav, int &peres) {
	int temp;
	int left = 2 * i + 1;//выстраиваем в виде дерева, о(n)
	int right = left + 1;
	int max = left;
	while (max < count) {
		if (right < count) {
			if (Array[left] < Array[right]) {
				max = right;
				srav++;
			}
		}
		if (Array[i] < Array[max]) {
			srav++;
			temp = Array[i];//меняем местами
			Array[i] = Array[max];
			Array[max] = temp;
			peres++;
		}
		else {
			break;
		}
		i = max;
		left = 2 * i + 1;
		right = left + 1;
		max = left;
	}
}
void Pyramida(int *myarray, int size)
{
	int peres = 0, srav = 0;
	int i, temp;
	for (i = size / 2 - 1; i >= 0; i--) {
		ShiftHelp(myarray, i, size, srav, peres);
	}
	for (i = size - 1; i > 0; i--) {
		temp = myarray[0];
		myarray[0] = myarray[i];
		myarray[i] = temp;
		peres++;
		ShiftHelp(myarray, 0, i, srav, peres);
	}
	cout << "пирамидальная сортировка :" << endl;
	cout << "число сравнений : " << srav << endl;
	cout << "число перестановок : " << peres << endl;
	system("pause");
}
void vibor(int *lol)
{
	int srav = 0, peres = 0;
	int temp, k;
	for (int i = 0; i < kolvo; i++)
	{
		k = i;
		for (int j = k + 1; j < kolvo; j++)
		{
			srav++;
			if (lol[j] < lol[k])
			{
				k = j;
			}
		}
		if (k != i) {
			temp = lol[i];
			lol[i] = lol[k];
			lol[k] = temp;
			peres++;
		}
	}
	system("cls");
	cout << "Число сравнений: " << srav << endl << "Число перестановок: " << peres << endl;
	system("pause");
	system("cls");
	show(lol);
	system("pause");
}

void vstavka(int *lol)
{
	int srav = 0, peres = 0;
	int temp, j = 0;
	int y = 0;
	for (int i = 1; i < kolvo; i++)
	{
		peres++;
		temp = lol[i];
		j = i - 1;
		srav++;
		while (j >= 0 && temp < lol[j])
		{
			srav++;
			peres++;
			lol[j + 1] = lol[j];
			j = j - 1;
		}
		peres++;
		lol[j + 1] = temp;
	}
	peres /= 3;
	system("cls");
	cout << "Число сравнений: " << srav << endl << "Число перестановок: " << peres << endl;
	system("pause");
	system("cls");
	show(lol);
}
void copyarray(int *arr, int *newarr)
{
	for (int i = 0; i < kolvo; i++)
	{
		newarr[i] = arr[i];
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	int *list = NULL;
	int *arr = NULL;
	int ask = 0;
	do {
		system("cls");
		cout << "0 - Показать созданный массив\n1 - создать массив \n2 - сортировка обменом (метод пузырька) \n3 - сортировка выбором \n4 - сортировка вставками \n5 - Метод Шелла\n6 - Быстрая сортировка\n7 - пирамидальная сортировка \n7 - выход" << endl;
		cin >> ask;
		switch (ask) {
		case 0:
			if (arr != NULL) {
				show(arr);
			}
			else { cout << "Массив пуст" << endl; system("pause"); }
			break;
		case 1:
			if (arr != NULL) {
				delete[] arr;
				delete[] list;
			}
			arr = Make();
			list = new int[kolvo];
			show(arr);
			break;
		case 2:
			if (arr != NULL) {
				copyarray(arr, list);
				obmen(list);
			}
			break;
		case 3:
			if (arr != NULL) {
				copyarray(arr, list);
				vibor(list);
			}
			break;
		case 4:
			if (arr != NULL) {
				copyarray(arr, list);
				vstavka(list);
			}
			break;
		case 5:
			if (arr != NULL) {
				copyarray(arr, list);
				Shell(list);
			}
			break;
		case 6:
		{
			if (arr != NULL) {
				copyarray(arr, list);
				int srav = 0;
				int peres = 0;
				QuickSort(list, 0, kolvo - 1, srav, peres);
				cout << "Число сравнений - " << srav << endl << "Число перестановок - " << peres << endl;
				system("pause");
				system("cls");
				show(list);
			}}
			break;
		case 7:
			if (arr != NULL) {
				copyarray(arr, list);
				Pyramida(list,kolvo);
				system("cls");
				show(list);
				system("pause");
			}
			break;
		}
	} while (ask != 8);
	system("pause");
	return 0;
}

