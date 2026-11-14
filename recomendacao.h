#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <vector>
#include "dados.h"

struct ranking {
    int produto;
    double score;
};

std::vector<int> recomendarProdutos(Dados *dados, int c, int k);

void testeRecomendacao(Dados *dados, int k, char *codigos[], int qtd);

#endif