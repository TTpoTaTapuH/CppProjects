#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
#pragma once
class Celler
{
private:
	Celler *next;
	string number, busy;
public:
	Celler(string number1, string empl)
	{
		number = number1;
		busy = empl;
	}
	Celler* GetNext() { return next; }
	void SetNext(Celler *ptr) { next = ptr; }
	string GetNumber() { return number; }
	void SetNumber(string txt) { number = txt; }
	string GetEmployment() { return busy; }
	void SetEmployment(string employmenty) { busy = employmenty; }
	Celler() {}
	~Celler() {	
		next = NULL;
		number = "";
		busy = "";
	}
};

