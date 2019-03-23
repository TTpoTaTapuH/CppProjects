#include "stdafx.h"
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <cstdlib>
#include <istream>
#include <conio.h>
#include <string>
using namespace std;
#pragma once
class Worker
{
private:
	Worker *right;
	Worker *left;
	string name, mayor;
public:
	Worker(string name1, string mayor1)
	{
		name = name1;
		mayor = mayor1;
	}
	void First_Worker()
	{
		right = NULL;
		left = NULL;
	}
	Worker* GetRight() { return right; }
	void SetRight(Worker *ptr) { right = ptr; }
	Worker* GetLeft() {	return left; }
	void SetLeft(Worker *ptr) {	left = ptr;	}
	string GetName() { return name; }
	void SetName(string txt) { name = txt; }
	string GetMayor() { return mayor; }
	void SetMayor(string may) { mayor = may; }
	Worker();
	~Worker();
};