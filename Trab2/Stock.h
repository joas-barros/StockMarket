#pragma once
#include "Date.h"
#include "Color.h"

// Arquivo onde são definidos os prototipos das funções e os registros da biblioteca Stocks


// Registro do tipo transação
struct Transaction
{
	Date date; // data
	unsigned quantity; // quantidade
	float price; // preço
};

// Registro do tipo empresa
struct Company
{
	char name[30]; // nome
	char ticker[5]; // ticker
	unsigned transactions; // transação
	Transaction* ptr; // ponteiro em que irá ser criado os vetores de transação por alocação dinamica de dad empresa
};

// prototipos

unsigned totalStocks(Transaction[], unsigned);

float averagePrice(Transaction[], unsigned);

float amountInvested(Transaction[], unsigned);

float wallet(Company[], unsigned, Colors, Colors);
