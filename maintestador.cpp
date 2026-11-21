#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "dados.h"

#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"


int main(int argc, char *argv[]) {
    Dados dados;
    int escolhaModulo;
    int i;
    double tempoExecucao;

    if (strcmp(argv[1], "-l") == 0)
        escolhaModulo = 1;
    else if (strcmp(argv[1], "-s") == 0)
        escolhaModulo = 2;
    else if (strcmp(argv[1], "-r") == 0)
        escolhaModulo = 3;

    extrairDados(&dados, argv[2]);

    switch (escolhaModulo) {
        // Teste ListaCompras
        case 1:
            if (argc < 6) {
                printf("Uso: %s -l <dados_venda_cluster_7.csv> cod1 cod2 ... codn\n", argv[0]);
                exit(EXIT_FAILURE);
            }

            for (i = 3; i < argc; ++i) {
                testeListaCompras(&dados, argv[i]);
            }
            break;

        // Teste Similaridade
        case 2:
            if (argc != 5) {
                printf("Uso: %s -s <dados_venda_cluster_7.csv> otimizado(0/1) codCliente\n", argv[0]);
                exit(EXIT_FAILURE);
            }

            tempoExecucao = construirMatrizSimilaridade(&dados, atoi(argv[3]));
        cout << "Tempo construção da matriz similaridade de ordem " << dados.matrizSimilaridade.size() << ": " << tempoExecucao << " segundos." << endl;

            testeSimilaridade(&dados, argv[4]);
            break;

        // Teste Recomendação
        case 3:
            if (argc < 7) {
                printf("Uso: %s -r <dados_venda_cluster_7.csv> k cod1 cod2 ... codn\n", argv[0]);
                exit(EXIT_FAILURE);
            }
            construirMatrizSimilaridade(&dados);

            char *clientes[3];
            for (i = 0; i < 3; ++i) {
                clientes[i] = argv[4 + i];
            }

            testeRecomendacao(&dados, atoi(argv[3]), clientes, 3);
            break;
    }

    return 0;
}