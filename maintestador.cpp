#include <stdio.h>
#include <string.h>
#include <iostream>
#include "dados.h"

#include "ListaCompras.h"
#include "Similaridade.h"

void testeListaCompras(Dados *dados) {
    char codCliente[9];
    int indiceCliente;

    while (1) {
        cout << "Digite o código do cliente ou fim para sair: ";
        fgets(codCliente, 9, stdin);
        codCliente[strcspn(codCliente, "\n")] = '\0';

        if (strcmp(codCliente, "fim") == 0) {
            return;
        }

        else {
            indiceCliente = dados->mapaClientes[codCliente];
            cout << "Produtos comprados por " << codCliente << ": ";

            for (int indiceProduto : dados->produtosComprados[indiceCliente]) {
                    cout << dados->produtos[indiceProduto] << " ";
            }
            cout << endl;
        }

        getchar();
    }
}

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
            cout << endl;

            switch (escolhaModulo) {
                // Teste ListaCompras
                case 1:
                    getchar();
                    testeListaCompras(&dados);
                    break;

                // Teste Similaridade
                case 2:
                    construirMatrizSimilaridade(&dados);
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