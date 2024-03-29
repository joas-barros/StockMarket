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

	// Calculo para definir as cores de fundo e intensivo do programa, que ser�o respectivamente 10 e 60 unidades maiores que a cor da letra
	int colorBGValue = colorFG + 10;
	int colorIValue = colorFG + 60;

	// Utilizando o type casting para converter os tipos int em Colors pois esse � o tipo que � passado como parametro para as fun��es
	Colors colorBG = (Colors) colorBGValue;
	Colors colorI = (Colors) colorIValue;

	// ===========================================
	//               Carteira de A��es
	// ===========================================

	textColored(" Carteira de A��es ", BLACK_FG, colorBG);
	cout << endl;

	// Pegando a quantidade de empresas passadas pelo usu�rio
	textColored("\nQuantidade de empresas [ ]\b\b", colorI, BLACK_BG);
	unsigned stockQuantity;
	cin >> stockQuantity;
	cin.get(); // Pegando o caractere \n para que ele n�o interfira na leituras das strings
	repeatChar('-', 30, colorFG, BLACK_BG);

	// Criando o vator din�mico que representar� as empresas da carteira
	Company* companies = new Company[stockQuantity];

	// Lendo as informa��es passadas pelo usuario para o vetor das empresas
	for (int i = 0; i < stockQuantity; i++) {
		
		textColored("Empresa: ", colorI, BLACK_BG);
		cin.getline(companies[i].name, 30);
		textColored("Ticker: ", colorI, BLACK_BG);
		cin >> companies[i].ticker;
		capitalLetter((companies[i].ticker)); // fun��o usada para passar todos os cacteres do ticker para maiuscula
		textColored("Transa��es: ", colorI, BLACK_BG);
		cin >> companies[i].transactions;
		cin.get();

		// Criando o vetor dinamico de transa��es a partir do num�ro de transa��es passados pelo usuario.
		companies[i].ptr = new Transaction[companies[i].transactions];
		repeatChar('-', 30, colorFG, BLACK_BG);

	}

	// ===========================================
	//            Transa��es Realizadas
	// ===========================================
	textColored("\n Transa��es realizadas ", BLACK_FG, colorBG);
	cout << endl;

	// O primeiro for serve para exibir a a��o da empresa em que est� sendo efetuada as transa��es 
	for (int i = 0; i < stockQuantity; i++) {
		
		cout << endl;
		textColored(companies[i].name, colorFG, BLACK_BG);
		textColored(" - ", colorFG, BLACK_BG);
		textColored(companies[i].ticker, colorFG, BLACK_BG);
		textColored(":", colorFG, BLACK_BG);
		cout << endl;

		// O segundo for ir� servir justamente para ler os dados de cada transa��o feita pelo usuario
		// ou seja, a data a quantidade e o pre�o
		// O la�o vai de 0 at� a quantidade de transa��es
		// foi-se utilizado dois for por se tratar de um vetor dentro de um vetor
		for (int j = 0; j < companies[i].transactions; j++) {
			textColored("\nData: ", colorI, BLACK_BG);
			cin >> companies[i].ptr[j].date;
			textColored("Quantidade: ", colorI, BLACK_BG);
			cin >> companies[i].ptr[j].quantity;
			textColored("Pre�o: ", colorI, BLACK_BG);
			cin >> companies[i].ptr[j].price;
		}
	}

	// ===========================================
	//              Resumo da Carteira
	// ===========================================

	// Fun��o que gera a tabela de resumo e retorna o valor do total investido para ser utilizado na constru��o do gr�fico
	float totalInvested = wallet(companies, stockQuantity, colorFG, colorBG);

	// ===========================================
	//           Rentabilidade da Carteira
	// ===========================================

	// Recebe as informa��es de aporte anual e rendimento estimado do usuario
	textColored("\nAporte anual R$[    ]\b\b\b\b\b", colorI, BLACK_BG);
	float annualInvestiment;
	cin >> annualInvestiment;
	textColored("Rendimento anual estimado [  ]%\b\b\b\b", colorI, BLACK_BG);
	float annualYield;
	cin >> annualYield;

	// Inicializa��o dos vetores estaticos de 21 posi��es que ser�o utilizados na constru��o da tabela e do gr�fico
	float invested[21];
	float income[21];
	float accumulated[21];
	unsigned normalizedVector[21];

	// Inicializando as matrizes que ser�o utilizadas para auxiliar na constru��o do gr�fico com base no vetor normalizado.
	// Elas come�aram com 0 em todas suas posi��es.
	unsigned chartMatrix[21][21] = { 0 };
	unsigned chartTransposedMatrix[21][21] = { 0 };

	// Atribuindo o valor da primeira posi��o dos vetores.
	invested[0] = totalInvested;
	income[0] = 0;
	accumulated[0] = totalInvested;

	// Preenchendo os valores do valor investido somando a posi��o anterior com o aporte anual.
	for (int i = 1; i < 21; i++)
		invested[i] = invested[i - 1] + annualInvestiment;

	// Preenchendo os valores dos vetores de renda e acumulado simultaneamente, pois um depende do outro 
	for (int i = 1; i < 21; i++) {
		income[i] = (accumulated[i - 1] + annualInvestiment) * annualYield / 100;
		accumulated[i] = accumulated[i - 1] + annualInvestiment + income[i];
	}
	// O for dos 3 vetores anteriores come�aram com 1 pois o valor da primeira posi��o j� estava definido.

	// Preenchendo os valores do vetor normalizado para fazer o gr�fico
	for (int i = 0; i < 21; i++) {
		// Dividimos o acumulado da posi��o pelo maior valor acumulado e multiplicamos pelo altura desejada, ou seja 21 que � a quantidade de posi��es
		// a fun��o ceil sempre ir� arredondar o valor da divis�o para cima
		normalizedVector[i] = ceil(accumulated[i] / accumulated[20] * 21);
	}

	// Passando os valores do vetor normalizado para a matriz que ir� simular a plotagem do gr�fico
	// Aonde for 0 na matriz ser� o espa�o vazio no gr�fico, aonde for 1 ser� plotado o quadrado
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			// Os valores que receberam 1 seram aqueles em que a posi��o da coluna for menor ou igual a 21 menos o valor do vetor normalizado correpondente a linha da matriz
			// Com isso a quantidade de 1s na linha ser� igual ao valor do vetor normalizado no indice da respectiva linha
			// Efetuamos a opera��o de subtra��o para que os 1s fiquem no final da linha como o gr�fico deve ser plotado
			if (j >= 21 - normalizedVector[i]) {
				chartMatrix[i][j] = 1;
			}
		}
	}

	// Como o gr�fico � plotado como base nas colunas e n�o nas linhas, precisamos fazer a transposta da matriz para realizar a plotagram do gr�fico.
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			// Realizamos a transposta da matriz invertendo as posi��es de line e coluna da matriz base para uma nova.
			chartTransposedMatrix[i][j] = chartMatrix[j][i];
		}
	}
	
	// Texto da rentabilidade do gr�fico com umas linhas logo abaixo
	cout << endl;
	textAlignment("Rentabilidade da Carteira", BLACK_FG, colorBG, 57);
	textAlignment("", BLACK_FG, colorBG, 32);
	cout << endl;
	repeatChar('-', 89, colorFG, BLACK_BG);
	

	// Alinhando os textos que ser�o exibidos como titulo da tabela
	textAlignment("Ano", BLACK_FG, colorBG, 4);
	textAlignment("Investido", BLACK_FG, colorBG, 11);
	textAlignment("Rendimento", BLACK_FG, colorBG, 12);
	textAlignment("Acumulado", BLACK_FG, colorBG, 12);
	textAlignment("Gr�fico", BLACK_FG, colorBG, 32);
	textAlignment("", BLACK_FG, colorBG, 18);
	cout << endl;
	// Faz com que os valores em ponto flutuante sejam exibidos com 2 casas decimais depois da v�rgula
	cout << fixed;
	cout.precision(2);

	// O for a seguir exibe as informa��es de cada ano de investimento
	for (int i = 0; i < 21; i++) {
		intAlignment(i, BLACK_FG, colorBG, 3); // Exibe o ano
		textAlignment("", BLACK_FG, colorBG, 1); // Cria um espa�o colorido ap�s o ano
		floatAlignment(invested[i], WHITE_FG, BLACK_BG, 11); // Exibe o investido
		floatAlignment(income[i], WHITE_FG, BLACK_BG, 12); // Exibe a renda
		floatAlignment(accumulated[i], WHITE_FG, BLACK_BG, 12); // Exibe o acumulado
		drawingChart(chartTransposedMatrix[i], colorI, BLACK_BG); // Plota a linha do gr�fico, sendo passada a respectiva linha da matriz transposta
		cout << endl;
	}
	repeatChar('-', 89, colorFG, BLACK_BG);


	// Deletamos todos os vetores de loca��o dinamica gerados para receber as informa��es das transa��es
	for (int i = 0; i < stockQuantity; i++) {
		delete[] companies[i].ptr;
	}

	// Deletamos o vetor de empresas
	delete[] companies;
	
	return 0;
}