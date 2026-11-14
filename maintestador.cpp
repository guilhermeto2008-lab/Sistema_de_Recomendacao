#include <stdio.h>
#include <string.h>
#include <iostream>
#include "dados.h"

#include "ListaCompras.h"
#include "Similaridade.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Uso: %s <dados_venda_cluster_0.csv>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    else {
        Dados dados;
        int escolhaModulo = 0;
        int i;

        for (i = 1; i < argc; i++) {
            extrairDados(&dados, argv[i]);
        }

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
                    cout << "Processou os dados" << endl;
                    testeSimilaridade(&dados);
                    break;

                // Teste Recomendação
                case 3:
                    break;

                default:
                    printf("Alternativa inválida. Digite novamente: ");
            }
        }
    }
}