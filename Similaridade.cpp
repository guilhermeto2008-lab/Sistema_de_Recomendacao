#include <iostream>
#include "dados.h"

using namespace std;

void construirMatrizSimilaridade(Dados *dados) {
    int i, j, k;

    int qntClientes = dados->clientes.size(), qntProdutos = dados->produtos.size();

    vector<vector<int>> matrizCompleta;

    // Preenche a matriz com 0 (não comprou o produto)
    matrizCompleta.resize(qntClientes);
    for (i = 0; i < qntClientes; ++i) {
        matrizCompleta[i].resize(qntProdutos);
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
            for (k = 0; k < qntProdutos; ++k) {
                matrizIntersecao[i][j] = matrizIntersecao[i][j] + (matrizCompleta[i][k] * transpostaCompleta[k][j]);
            }
        }
    }

    // Redimensiona a matriz similaridade
    dados->matrizSimilaridade.resize(qntClientes);
    for (i = 0; i < qntClientes; ++i) {
        dados->matrizSimilaridade[i].resize(qntClientes);
    }

    // Preenche a matriz similaridade
    for (i = 0; i < qntClientes; ++i) {
        for (j = 0; j < qntClientes; ++j) {
            dados->matrizSimilaridade[i][j] = 1 - ((float)matrizIntersecao[i][j] / dados->produtosComprados[i].size());
        }
    }
}

void testeSimilaridade(Dados *dados, char* codCliente) {
    int i;
    int indiceCliente, maisSimilar;
    float valorMaisSimilar;

    indiceCliente = dados->mapaClientes[codCliente];
    if (indiceCliente != 0) {
        maisSimilar = 0;
        valorMaisSimilar = dados->matrizSimilaridade[indiceCliente][maisSimilar];
    }
    else {
        maisSimilar = 1;
        valorMaisSimilar = dados->matrizSimilaridade[indiceCliente][maisSimilar];
    }

    for (i = maisSimilar + 1; i < dados->matrizSimilaridade.size(); ++i) {
        if (i != indiceCliente) {
            if (dados->matrizSimilaridade[indiceCliente][i] < valorMaisSimilar) {
                maisSimilar = i;
                valorMaisSimilar = dados->matrizSimilaridade[indiceCliente][i];
            }
        }
    }

        cout << "O comprador mais similar a " << codCliente << " é " << dados->clientes[maisSimilar] << endl;
}