#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#pragma once
using namespace std;
class City
{
private:
	string name_of_city = "";
	string number_of_people = "";
public:
	City(string name, string number) {
		name_of_city = name;
		number_of_people = number;
	}
	void Set_name_of_city(string name) {
		name_of_city = name;
	}
	string Get_name_of_city() {
		return name_of_city;
	}
	void Set_number_of_people(string number) {
		number_of_people = number;
	}
	string Get_number_of_people() {
		return number_of_people;
	}
	City() {}
	~City() {
		name_of_city = "";
		number_of_people = "";
	}
};

