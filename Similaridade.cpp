#include <stdio.h>
#include "dados.h"

void construirMatrizSimilaridade(Dados *dados) {
    int i, j, k;

    int qntClientes = dados->clientes.size(), qntProdutos = dados->produtos.size();

    vector<vector<int>> matrizCompleta;

    // Preenche a matriz com 0 (não comprou o produto)
    matrizCompleta.resize(qntClientes);
    for (i = 0; i < qntClientes; ++i) {
        for (j = 0; j < qntProdutos; ++j) {
            matrizCompleta[i].push_back(0);
        }
    }

    // Preenche os produtos comprados com 1 (comprou o produto)
    for (i = 0; i < qntClientes; ++i) {
        for (int indiceProduto : dados->produtosComprados[i]) {
            matrizCompleta[i][indiceProduto] = 1;
        }
    }

    vector<vector<int>> transpostaCompleta;

    // Redimensiona a matriz transposta
    transpostaCompleta.resize(qntProdutos);
    for (i = 0; i < qntProdutos; ++i) {
        transpostaCompleta[i].resize(qntClientes);
    }

    // Preenche a matriz transposta
    for (i = 0; i < qntClientes; ++i) {
        for (j = 0; j < qntProdutos; ++j) {
            transpostaCompleta[j][i] = matrizCompleta[i][j];
        }
    }

    vector<vector<int>> matrizIntersecao;

    // Redimensiona a matriz interseção
    matrizIntersecao.resize(qntClientes);
    for (i = 0; i < qntClientes; ++i) {
        matrizIntersecao[i].resize(qntClientes);
    }

    // Multiplica a matriz Completa pela transposta para criar a interseção
    for (i = 0; i < qntClientes; ++i) {
        for (j = 0; j < qntClientes; ++j) {
            matrizIntersecao[i][j] = 0;
            for (j = 0; j < qntProdutos; ++k) {
                matrizIntersecao[i][j] += matrizCompleta[i][k] * transpostaCompleta[k][j];
            }
        }
    }

    // Redimensiona a matriz similaridade
    dados->matrizSimilaridade.resize(qntClientes);
    for (i = 0; i < dados->matrizSimilaridade.size(); ++i) {
        dados->matrizSimilaridade.resize(qntClientes);
    }

    // Preenche a matriz similaridade
    for (i = 0; i < qntClientes; ++i) {
        for 
    }
}