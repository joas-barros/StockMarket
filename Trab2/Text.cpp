#include <iostream>
#include "Text.h"
#include "Color.h"
using namespace std;

// arquivo aonde � definido o corpo das fun��es da biblioteca Text

// Fun��o para repetir um deteminado caractere multiplas vezes manipulando sua cor e a do fundo
void repeatChar(char c, unsigned size, Colors fg, Colors bg) {
	// Manipulamos as cores do texto com base nos parametros da fun��o
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	// Imprimimos o caractere conforme o parametro size
	for (int i = 0; i < size; i++) {
		cout << c;
	}
	// resetamos a cor
	cout << "\033[m" << endl;
}

// Mudamos a cor da letra e do fundo de um texto conforme informa��es passadas pelo parametro
// Semelhante ao repeatChar s� que dessa vez para uma string
void textColored(const char word[], Colors fg, Colors bg) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	cout << word;
	cout << "\033[m";
}

// Fun��o para mudar as letras de um texto para maiuscula
void capitalLetter(char ticker[]) {

	// criamos um ponteiro para manipular os caracteres atraves do seu endere�o de mem�ria
	// sendo esse ponteiro igual ao endere�o do primeiro caractere
	char* p = ticker;
	for (int i = 0; i < strlen(ticker); i++)
		// Utilizando aritmetica de vetores atualizamos o endere�o de memoria de vetor e mudamos seu caractere atraves da fun��o toupper sem retornar nada no final
		*(p + i) = toupper(ticker[i]);
}


// Fun��o para alinhar o texto e mudar sua cor
void textAlignment(const char text[], Colors fg, Colors bg, unsigned size) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	// O alinhamento ser� feito com base no parametro size e ser� sempre feito pela direita
	cout << right; cout.width(size); cout << text;
	cout << "\033[m";
}

// Vers�o da fun��o de alinhamento para ponto flutuante
void floatAlignment(float number, Colors fg, Colors bg, unsigned size) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	cout << right; cout.width(size); cout << number;
	cout << "\033[m";
}

// Vers�o da fun��o de alinhamento para inteiro
void intAlignment(int number, Colors fg, Colors bg, unsigned size) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	cout << right; cout.width(size); cout << number;
	cout << "\033[m";
}

// Fun��o em que ir� ser exibido os quadrados do gr�fico junto com sua cor
void drawingChart(unsigned matrix[], Colors fg, Colors bg) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	// Alinahmento padr�o aonde ir� come�ar o gr�fico na tabela
	cout << right; cout.width(9);
	// Ser� passado o vetor de cada linha do gr�fico, os elementos ser�o analisados um por um atraves do for
	// Caso seja 1 ir� exibir o quadrado, caso contrario, ir� exibir um espa�o vazio.
	for (int i = 0; i < 21; i++) {
		if (matrix[i] == 1)
			cout << "\xDC ";
		else
			cout << "  ";
	}
	cout << "\033[m";
}

