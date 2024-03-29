#include <iostream>
#include "Text.h"
#include "Color.h"
using namespace std;

// arquivo aonde é definido o corpo das funções da biblioteca Text

// Função para repetir um deteminado caractere multiplas vezes manipulando sua cor e a do fundo
void repeatChar(char c, unsigned size, Colors fg, Colors bg) {
	// Manipulamos as cores do texto com base nos parametros da função
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	// Imprimimos o caractere conforme o parametro size
	for (int i = 0; i < size; i++) {
		cout << c;
	}
	// resetamos a cor
	cout << "\033[m" << endl;
}

// Mudamos a cor da letra e do fundo de um texto conforme informações passadas pelo parametro
// Semelhante ao repeatChar só que dessa vez para uma string
void textColored(const char word[], Colors fg, Colors bg) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	cout << word;
	cout << "\033[m";
}

// Função para mudar as letras de um texto para maiuscula
void capitalLetter(char ticker[]) {

	// criamos um ponteiro para manipular os caracteres atraves do seu endereço de memória
	// sendo esse ponteiro igual ao endereço do primeiro caractere
	char* p = ticker;
	for (int i = 0; i < strlen(ticker); i++)
		// Utilizando aritmetica de vetores atualizamos o endereço de memoria de vetor e mudamos seu caractere atraves da função toupper sem retornar nada no final
		*(p + i) = toupper(ticker[i]);
}


// Função para alinhar o texto e mudar sua cor
void textAlignment(const char text[], Colors fg, Colors bg, unsigned size) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	// O alinhamento será feito com base no parametro size e será sempre feito pela direita
	cout << right; cout.width(size); cout << text;
	cout << "\033[m";
}

// Versão da função de alinhamento para ponto flutuante
void floatAlignment(float number, Colors fg, Colors bg, unsigned size) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	cout << right; cout.width(size); cout << number;
	cout << "\033[m";
}

// Versão da função de alinhamento para inteiro
void intAlignment(int number, Colors fg, Colors bg, unsigned size) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	cout << right; cout.width(size); cout << number;
	cout << "\033[m";
}

// Função em que irá ser exibido os quadrados do gráfico junto com sua cor
void drawingChart(unsigned matrix[], Colors fg, Colors bg) {
	cout << "\033[" << "0;" << fg << ";" << bg << "m";
	// Alinahmento padrão aonde irá começar o gráfico na tabela
	cout << right; cout.width(9);
	// Será passado o vetor de cada linha do gráfico, os elementos serão analisados um por um atraves do for
	// Caso seja 1 irá exibir o quadrado, caso contrario, irá exibir um espaço vazio.
	for (int i = 0; i < 21; i++) {
		if (matrix[i] == 1)
			cout << "\xDC ";
		else
			cout << "  ";
	}
	cout << "\033[m";
}

