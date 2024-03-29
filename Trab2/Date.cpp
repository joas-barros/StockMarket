#include <iostream>
#include "Date.h"
using namespace std;

// arquivo aonde é definido o corpo das funções da biblioteca Date

// Manipulando o cin para que ele possa ler o tipo date como tipo primitivo
istream& operator>>(istream& is, Date& entrada) {
	// Lendo todos os atributos do registro e dando cin.ignore() nos caracteres '/'
	cin >> entrada.day;
	cin.ignore();
	cin >> entrada.month;
	cin.ignore();
	cin >> entrada.year;
	cin.ignore(); // ignore final no /n

	return is;
}

// Manipulando o cout para que ele possa exibir o tipo date como tipo primitivo
ostream& operator<<(ostream& os, Date& saida) {
	os << saida.day;
	os << "/";
	os << saida.month;
	os << "/";
	os << saida.year;

	return os;
}
