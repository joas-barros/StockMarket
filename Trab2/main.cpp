// Importando as bibliotecas utilizados no programa
#include <iostream>
#include "Stock.h"
#include "Text.h"
#include "Date.h"
#include "Color.h"
using namespace std;

// Arquivo principal do programa 

int main() {
	// Cor principal das letras do programa
	Colors colorFG = YELLOW_FG;

	// Calculo para definir as cores de fundo e intensivo do programa, que serão respectivamente 10 e 60 unidades maiores que a cor da letra
	int colorBGValue = colorFG + 10;
	int colorIValue = colorFG + 60;

	// Utilizando o type casting para converter os tipos int em Colors pois esse é o tipo que é passado como parametro para as funções
	Colors colorBG = (Colors) colorBGValue;
	Colors colorI = (Colors) colorIValue;

	// ===========================================
	//               Carteira de Ações
	// ===========================================

	textColored(" Carteira de Ações ", BLACK_FG, colorBG);
	cout << endl;

	// Pegando a quantidade de empresas passadas pelo usuário
	textColored("\nQuantidade de empresas [ ]\b\b", colorI, BLACK_BG);
	unsigned stockQuantity;
	cin >> stockQuantity;
	cin.get(); // Pegando o caractere \n para que ele não interfira na leituras das strings
	repeatChar('-', 30, colorFG, BLACK_BG);

	// Criando o vator dinâmico que representará as empresas da carteira
	Company* companies = new Company[stockQuantity];

	// Lendo as informações passadas pelo usuario para o vetor das empresas
	for (int i = 0; i < stockQuantity; i++) {
		
		textColored("Empresa: ", colorI, BLACK_BG);
		cin.getline(companies[i].name, 30);
		textColored("Ticker: ", colorI, BLACK_BG);
		cin >> companies[i].ticker;
		capitalLetter((companies[i].ticker)); // função usada para passar todos os cacteres do ticker para maiuscula
		textColored("Transações: ", colorI, BLACK_BG);
		cin >> companies[i].transactions;
		cin.get();

		// Criando o vetor dinamico de transações a partir do numéro de transações passados pelo usuario.
		companies[i].ptr = new Transaction[companies[i].transactions];
		repeatChar('-', 30, colorFG, BLACK_BG);

	}

	// ===========================================
	//            Transações Realizadas
	// ===========================================
	textColored("\n Transações realizadas ", BLACK_FG, colorBG);
	cout << endl;

	// O primeiro for serve para exibir a ação da empresa em que está sendo efetuada as transações 
	for (int i = 0; i < stockQuantity; i++) {
		
		cout << endl;
		textColored(companies[i].name, colorFG, BLACK_BG);
		textColored(" - ", colorFG, BLACK_BG);
		textColored(companies[i].ticker, colorFG, BLACK_BG);
		textColored(":", colorFG, BLACK_BG);
		cout << endl;

		// O segundo for irá servir justamente para ler os dados de cada transação feita pelo usuario
		// ou seja, a data a quantidade e o preço
		// O laço vai de 0 até a quantidade de transações
		// foi-se utilizado dois for por se tratar de um vetor dentro de um vetor
		for (int j = 0; j < companies[i].transactions; j++) {
			textColored("\nData: ", colorI, BLACK_BG);
			cin >> companies[i].ptr[j].date;
			textColored("Quantidade: ", colorI, BLACK_BG);
			cin >> companies[i].ptr[j].quantity;
			textColored("Preço: ", colorI, BLACK_BG);
			cin >> companies[i].ptr[j].price;
		}
	}

	// ===========================================
	//              Resumo da Carteira
	// ===========================================

	// Função que gera a tabela de resumo e retorna o valor do total investido para ser utilizado na construção do gráfico
	float totalInvested = wallet(companies, stockQuantity, colorFG, colorBG);

	// ===========================================
	//           Rentabilidade da Carteira
	// ===========================================

	// Recebe as informações de aporte anual e rendimento estimado do usuario
	textColored("\nAporte anual R$[    ]\b\b\b\b\b", colorI, BLACK_BG);
	float annualInvestiment;
	cin >> annualInvestiment;
	textColored("Rendimento anual estimado [  ]%\b\b\b\b", colorI, BLACK_BG);
	float annualYield;
	cin >> annualYield;

	// Inicialização dos vetores estaticos de 21 posições que serão utilizados na construção da tabela e do gráfico
	float invested[21];
	float income[21];
	float accumulated[21];
	unsigned normalizedVector[21];

	// Inicializando as matrizes que serão utilizadas para auxiliar na construção do gráfico com base no vetor normalizado.
	// Elas começaram com 0 em todas suas posições.
	unsigned chartMatrix[21][21] = { 0 };
	unsigned chartTransposedMatrix[21][21] = { 0 };

	// Atribuindo o valor da primeira posição dos vetores.
	invested[0] = totalInvested;
	income[0] = 0;
	accumulated[0] = totalInvested;

	// Preenchendo os valores do valor investido somando a posição anterior com o aporte anual.
	for (int i = 1; i < 21; i++)
		invested[i] = invested[i - 1] + annualInvestiment;

	// Preenchendo os valores dos vetores de renda e acumulado simultaneamente, pois um depende do outro 
	for (int i = 1; i < 21; i++) {
		income[i] = (accumulated[i - 1] + annualInvestiment) * annualYield / 100;
		accumulated[i] = accumulated[i - 1] + annualInvestiment + income[i];
	}
	// O for dos 3 vetores anteriores começaram com 1 pois o valor da primeira posição já estava definido.

	// Preenchendo os valores do vetor normalizado para fazer o gráfico
	for (int i = 0; i < 21; i++) {
		// Dividimos o acumulado da posição pelo maior valor acumulado e multiplicamos pelo altura desejada, ou seja 21 que é a quantidade de posições
		// a função ceil sempre irá arredondar o valor da divisão para cima
		normalizedVector[i] = ceil(accumulated[i] / accumulated[20] * 21);
	}

	// Passando os valores do vetor normalizado para a matriz que irá simular a plotagem do gráfico
	// Aonde for 0 na matriz será o espaço vazio no gráfico, aonde for 1 será plotado o quadrado
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			// Os valores que receberam 1 seram aqueles em que a posição da coluna for menor ou igual a 21 menos o valor do vetor normalizado correpondente a linha da matriz
			// Com isso a quantidade de 1s na linha será igual ao valor do vetor normalizado no indice da respectiva linha
			// Efetuamos a operação de subtração para que os 1s fiquem no final da linha como o gráfico deve ser plotado
			if (j >= 21 - normalizedVector[i]) {
				chartMatrix[i][j] = 1;
			}
		}
	}

	// Como o gráfico é plotado como base nas colunas e não nas linhas, precisamos fazer a transposta da matriz para realizar a plotagram do gráfico.
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			// Realizamos a transposta da matriz invertendo as posições de line e coluna da matriz base para uma nova.
			chartTransposedMatrix[i][j] = chartMatrix[j][i];
		}
	}
	
	// Texto da rentabilidade do gráfico com umas linhas logo abaixo
	cout << endl;
	textAlignment("Rentabilidade da Carteira", BLACK_FG, colorBG, 57);
	textAlignment("", BLACK_FG, colorBG, 32);
	cout << endl;
	repeatChar('-', 89, colorFG, BLACK_BG);
	

	// Alinhando os textos que serão exibidos como titulo da tabela
	textAlignment("Ano", BLACK_FG, colorBG, 4);
	textAlignment("Investido", BLACK_FG, colorBG, 11);
	textAlignment("Rendimento", BLACK_FG, colorBG, 12);
	textAlignment("Acumulado", BLACK_FG, colorBG, 12);
	textAlignment("Gráfico", BLACK_FG, colorBG, 32);
	textAlignment("", BLACK_FG, colorBG, 18);
	cout << endl;
	// Faz com que os valores em ponto flutuante sejam exibidos com 2 casas decimais depois da vírgula
	cout << fixed;
	cout.precision(2);

	// O for a seguir exibe as informações de cada ano de investimento
	for (int i = 0; i < 21; i++) {
		intAlignment(i, BLACK_FG, colorBG, 3); // Exibe o ano
		textAlignment("", BLACK_FG, colorBG, 1); // Cria um espaço colorido após o ano
		floatAlignment(invested[i], WHITE_FG, BLACK_BG, 11); // Exibe o investido
		floatAlignment(income[i], WHITE_FG, BLACK_BG, 12); // Exibe a renda
		floatAlignment(accumulated[i], WHITE_FG, BLACK_BG, 12); // Exibe o acumulado
		drawingChart(chartTransposedMatrix[i], colorI, BLACK_BG); // Plota a linha do gráfico, sendo passada a respectiva linha da matriz transposta
		cout << endl;
	}
	repeatChar('-', 89, colorFG, BLACK_BG);


	// Deletamos todos os vetores de locação dinamica gerados para receber as informações das transações
	for (int i = 0; i < stockQuantity; i++) {
		delete[] companies[i].ptr;
	}

	// Deletamos o vetor de empresas
	delete[] companies;
	
	return 0;
}