#include <iostream>
#pragma once
using namespace std;

// Arquivo onde s�o definidos os prototipos das fun��es e os registros da biblioteca Date

// Registro do tipo data
struct Date
{
	unsigned day; // dia
	unsigned month; // mes
	unsigned year; // ano
};

// prototipos 

istream& operator>>(istream&, Date&);
ostream& operator<<(ostream&, Date&);