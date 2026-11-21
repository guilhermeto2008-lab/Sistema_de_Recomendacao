#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

using namespace std;

#include "dados.h"

double construirMatrizSimilaridade(Dados *dados, int otimizado=1);

void testeSimilaridade(Dados *dados, char *codCliente);

#endif