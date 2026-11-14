#include <stdio.h>
#include <iostream>
#include <string.h>
#include "dados.h"

using namespace std;

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
            for (k = 0; k < qntProdutos; ++k) {
                matrizIntersecao[i][j] += matrizCompleta[i][k] * transpostaCompleta[k][j];
            }
        }
    }

    // Redimensiona a matriz similaridade
    dados->matrizSimilaridade.resize(qntClientes);
    for (i = 0; i < dados->matrizSimilaridade.size(); ++i) {
        dados->matrizSimilaridade[i].resize(qntClientes);
    }

    // Preenche a matriz similaridade
    for (i = 0; i < qntClientes; ++i) {
        for (j = 0; j < qntClientes; ++j) {
            dados->matrizSimilaridade[i][j] = 1 - (matrizIntersecao[i][j] / dados->produtosComprados[i].size());
        }
    }
}

void testeSimilaridade(Dados *dados) {
    char codCliente[9];
    int i, inicio;
    int indiceCliente, maisSimilar, valorMaisSimilar;

    while (1) {
        cout << "Digite o código do cliente ou fim para sair: ";
        fgets(codCliente, 9, stdin);
        codCliente[strcspn(codCliente, "\n")] = '\0';

        if (strcmp(codCliente, "fim") == 0) {
            return;
        }

        else {
            indiceCliente = dados->mapaClientes[codCliente];
            if (indiceCliente != 0) {
                maisSimilar = 0;
                valorMaisSimilar = dados->matrizSimilaridade[indiceCliente][maisSimilar];
                inicio = 1;
            }
            else {
                maisSimilar = 1;
                valorMaisSimilar = dados->matrizSimilaridade[indiceCliente][maisSimilar];
                inicio = 2;
            }

            for (i = inicio; i < dados->matrizSimilaridade.size(); ++i) {
                if (i != indiceCliente && dados->matrizSimilaridade[indiceCliente][i] < valorMaisSimilar) {
                    maisSimilar = i;
                    valorMaisSimilar = dados->matrizSimilaridade[indiceCliente][i];
                }
                // Cliente não se compara a ele mesmo
                else
                    continue;
            }

            cout << "O comprador mais similar a " << codCliente << " é " << dados->clientes[maisSimilar] << endl;
        }

        getchar();
    }
}