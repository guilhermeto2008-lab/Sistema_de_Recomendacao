#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "dados.h"

#include "ListaCompras.h"
#include "Similaridade.h"
#include "recomendacao.h"


int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Uso: %s <dados_venda_cluster_7.csv>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    else {
        Dados dados;
        int escolhaModulo = 0;
        int i;
        int k = atoi(argv[1]);

        if (k <= 0){
            printf("O k deve ser maior que zero.");
            exit(EXIT_FAILURE);
        }

        for (i = 5; i < argc; i++) {
            extrairDados(&dados, argv[i]);
        }

        printf("%d", k);
        printf("%d", dados.clientes.size());

        printf("Escolha qual módulo deseja testar:\n");
        printf("1 para ListaCompras.\n2 para Similaridade.\n3 para Recomendação.\n\n");

        while (escolhaModulo != 1 && escolhaModulo != 2 && escolhaModulo != 3) {
            scanf("%d", &escolhaModulo);
            getchar();
            cout << endl;

            switch (escolhaModulo) {
                // Teste ListaCompras
                case 1:
                    testeListaCompras(&dados);
                    break;

                // Teste Similaridade
                case 2:
                    construirMatrizSimilaridade(&dados);
                    testeSimilaridade(&dados);
                    break;

                // Teste Recomendação
                case 3:
                    if (dados.matrizSimilaridade.empty()) {
                        construirMatrizSimilaridade(&dados);
                    }
                    testeRecomendacao(&dados);
                    break;

                default:
                    printf("Alternativa inválida. Digite novamente: ");
            }
        }
    }
}