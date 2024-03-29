#pragma once
#include "Date.h"
#include "Color.h"

// Arquivo onde s�o definidos os prototipos das fun��es e os registros da biblioteca Stocks


// Registro do tipo transa��o
struct Transaction
{
	Date date; // data
	unsigned quantity; // quantidade
	float price; // pre�o
};

// Registro do tipo empresa
struct Company
{
	char name[30]; // nome
	char ticker[5]; // ticker
	unsigned transactions; // transa��o
	Transaction* ptr; // ponteiro em que ir� ser criado os vetores de transa��o por aloca��o dinamica de dad empresa
};

// prototipos

unsigned totalStocks(Transaction[], unsigned);

float averagePrice(Transaction[], unsigned);

float amountInvested(Transaction[], unsigned);

float wallet(Company[], unsigned, Colors, Colors);
