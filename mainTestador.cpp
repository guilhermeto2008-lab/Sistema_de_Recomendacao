#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"

int main(int argc, char *argv[]) {
    Dados dados;
    int escolhaModulo = 0;
    int i;

    for (i = 1; i < argc; i++) {
        extrairDados(&dados, argv[i]);
    }

    printf("Escolha qual módulo deseja testar:\n");
    printf("1 para ListaCompras.\n2 para Similaridade.\n3 para Recomendação.\n\n");

    while (escolhaModulo != 1 || escolhaModulo != 2 || escolhaModulo != 3) {
        scanf("%d", &escolhaModulo);
        cout << endl;

        switch (escolhaModulo) {
            // Teste ListaCompras
            case 1:
                // Printa os dados
                for (i = 0; i < size(dados.produtosComprados); ++i) {
                    cout << dados.clientes[i] << ": ";
                    for (int indiceProduto : dados.produtosComprados[i]) {
                        cout << dados.produtos[indiceProduto] << ", ";
                    }
                    getchar();
                }
                cout << endl;

                break;

            // Teste Similaridade
            case 2:
                break;

            // Teste Recomendação
            case 3:
                break;

            default:
                printf("Alternativa inválida. Digite novamente: ");
        }
    }
}