#include <iostream>
#include "Stock.h"
#include "Color.h"
#include "Text.h"
using namespace std;

// arquivo aonde é definido o corpo das funções da biblioteca Stock


// Função para calcular o total de ações compradas de uma determinada empresa
unsigned totalStocks(Transaction t[], unsigned size) {
	unsigned result = 0;
	// Basta somar q quantidade somprada em cada transação
	for (int i = 0; i < size; i++) {
		result += t[i].quantity;
	}
	return result;
}

// Função para calcular o total investido em uma determinada empresa
float amountInvested(Transaction t[], unsigned size) {
	float result = 0;
	// Basta somar o produto do preço pela quantidade de ações compradas em cada transação
	for (int i = 0; i < size; i++) {
		result += (t[i].price * t[i].quantity);
	}
	return result;
}

// Função para calcular o preço médio de uma determinada ação
float averagePrice(Transaction t[], unsigned size) {
	// Como o preço médio é a média ponderada entre a quantidade de ações pelo preço
	// Basta pegarmos o total investido, ou seja, a soma do produto do preço pela quantidade, dividido pelo total da quantidade
	return  (float) amountInvested(t, size) / totalStocks(t, size);
}


// função para exibir a tabela resumo dos invetimento e calcular o total investido
float wallet(Company c[], unsigned size, Colors colorFG, Colors colorBG) {
	float result = 0;
	cout << endl;
	// Será exibido todas as informações de título da tabela com as funções de alinhamento e colorir
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
	textColored(" Preço Médio ", BLACK_FG, colorBG);
	textAlignment("", colorFG, BLACK_BG, 3);
	textColored(" Investido ", BLACK_FG, colorBG);
	cout << endl;

	// Faz com que os valores em ponto flutuante sejam exibidos com 2 casas decimais depois da vírgula
	cout << fixed;
	cout.precision(2);

	// O for abaixo irá calcular todos os valores de total invetido, preço médio e quantidade comprada com a alinhamento adequado
	for (int i = 0; i < size; i++) {
		
		// Foi-se utilizado o left para que o texto seja alinhado a esquerda e o próximo texto seja alinhado a partir do final do width ao inves do final do texto, padronizando assim o espaçamento 
		cout << left; cout.width(16); cout << c[i].name;
		textAlignment(c[i].ticker, WHITE_FG, BLACK_BG, 6); // exibindo o ticker alinhado

		// Os proximos valores foram calculados com as funções criadas anteriormente, sendo passado como parametro o vetor de transações e o número de transações
		intAlignment(totalStocks(c[i].ptr, c[i].transactions), WHITE_FG, BLACK_BG, 14); // Exibindo a quantidade
		floatAlignment(averagePrice(c[i].ptr, c[i].transactions), WHITE_FG, BLACK_BG, 16); // Exibindo o preço médio
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
