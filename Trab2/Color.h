#pragma once

// Arquivo onde s�o definidos o enum com as constantes do tipo Colors

enum Colors {BLACK_FG = 30, RED_FG, GREEN_FG, YELLOW_FG, BLUE_FG, PURPLE_FG, CYAN_FG, WHITE_FG, // cores das letras
			BLACK_BG = 40, RED_BG, GREEN_BG, YELLOW_BG, BLUE_BG, PURPLE_BG, CYAN_BG, WHITE_BG, // cores do fundo
			BLACK_INTENSIVE = 90, RED_INTENSIVE, GREEN_INTENSIVE, YELLOW_INTENSIVE, BLUE_INTENSIVE, PURPLE_INTENSIVE, CYAN_INTENSIVE, WHITE_INTENSIVE}; // cores intensas

// Como um enum por padr�o define o valor das proximas constantes acrescentando 1 ao valor da contante anterior, s� foi preciso definir o primeiro valor de cada (no caso a preta) e deixar o compilador complatar o resto
