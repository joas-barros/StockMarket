#include <iostream>
#include "Stock.h"
#include "Color.h"
#include "Text.h"
using namespace std;

// arquivo aonde � definido o corpo das fun��es da biblioteca Stock


// Fun��o para calcular o total de a��es compradas de uma determinada empresa
unsigned totalStocks(Transaction t[], unsigned size) {
	unsigned result = 0;
	// Basta somar q quantidade somprada em cada transa��o
	for (int i = 0; i < size; i++) {
		result += t[i].quantity;
	}
	return result;
}

// Fun��o para calcular o total investido em uma determinada empresa
float amountInvested(Transaction t[], unsigned size) {
	float result = 0;
	// Basta somar o produto do pre�o pela quantidade de a��es compradas em cada transa��o
	for (int i = 0; i < size; i++) {
		result += (t[i].price * t[i].quantity);
	}
	return result;
}

// Fun��o para calcular o pre�o m�dio de uma determinada a��o
float averagePrice(Transaction t[], unsigned size) {
	// Como o pre�o m�dio � a m�dia ponderada entre a quantidade de a��es pelo pre�o
	// Basta pegarmos o total investido, ou seja, a soma do produto do pre�o pela quantidade, dividido pelo total da quantidade
	return  (float) amountInvested(t, size) / totalStocks(t, size);
}


// fun��o para exibir a tabela resumo dos invetimento e calcular o total investido
float wallet(Company c[], unsigned size, Colors colorFG, Colors colorBG) {
	float result = 0;
	cout << endl;
	// Ser� exibido todas as informa��es de t�tulo da tabela com as fun��es de alinhamento e colorir
	textAlignment("Resumo da carteira", BLACK_FG, colorBG, 44);
	textAlignment("", BLACK_FG, colorBG, 26);
	cout << endl;
	repeatChar('-', 70, colorFG, BLACK_BG);
	textColored(" Empresa ", BLACK_FG, colorBG);
	textAlignment("", colorFG, BLACK_BG, 7);
	textColored(" Ticker ", BLACK_FG, colorBG);
	textAlignment("", colorFG, BLACK_BG, 8);
	textColored(" Qtd. ", BLACK_FG, colorBG);
	textAlignment("", colorFG, BLACK_BG, 5);
	textColored(" Pre�o M�dio ", BLACK_FG, colorBG);
	textAlignment("", colorFG, BLACK_BG, 3);
	textColored(" Investido ", BLACK_FG, colorBG);
	cout << endl;

	// Faz com que os valores em ponto flutuante sejam exibidos com 2 casas decimais depois da v�rgula
	cout << fixed;
	cout.precision(2);

	// O for abaixo ir� calcular todos os valores de total invetido, pre�o m�dio e quantidade comprada com a alinhamento adequado
	for (int i = 0; i < size; i++) {
		
		// Foi-se utilizado o left para que o texto seja alinhado a esquerda e o pr�ximo texto seja alinhado a partir do final do width ao inves do final do texto, padronizando assim o espa�amento 
		cout << left; cout.width(16); cout << c[i].name;
		textAlignment(c[i].ticker, WHITE_FG, BLACK_BG, 6); // exibindo o ticker alinhado

		// Os proximos valores foram calculados com as fun��es criadas anteriormente, sendo passado como parametro o vetor de transa��es e o n�mero de transa��es
		intAlignment(totalStocks(c[i].ptr, c[i].transactions), WHITE_FG, BLACK_BG, 14); // Exibindo a quantidade
		floatAlignment(averagePrice(c[i].ptr, c[i].transactions), WHITE_FG, BLACK_BG, 16); // Exibindo o pre�o m�dio
		floatAlignment(amountInvested(c[i].ptr, c[i].transactions), WHITE_FG, BLACK_BG, 18); // Exibindo o valor investido
		cout << endl;
		result += amountInvested(c[i].ptr, c[i].transactions); // somando o valor investido em cada empresa para retornar tudo no final
	}
	repeatChar('-', 70, colorFG, BLACK_BG);
	textColored("Total Investido:", BLACK_FG, colorBG); 
	
	floatAlignment(result, BLACK_FG, colorBG, 54); // Exibindo o total investido
	cout << endl;
	return result;
}
