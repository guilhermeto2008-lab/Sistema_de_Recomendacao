#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Uso: %s <dados_venda_cluster_0.csv>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    vector <string> Clientes;
    map <string, int> Cliente;
    
    vector <string> Produto;
    map <string, int> Produtos;

    char data[9];
    char cliente[20];
    int produto;
    char nome[200];

    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %8[^,],%19[^,],%d,%199[^\r\n]",
                  data, cliente, &produto, nome) == 4) {
        printf("Data: %s | Cliente: %s | Produto: %d | Nome: %s\n",
               data, cliente, produto, nome);
        
        Clientes.push_back(cliente);
        Produto.push_back(nome);
        
        Cliente[cliente]++;
        Produtos[nome]++;
               
    }

    fclose(arquivo);

    for (size_t i = 0; i < Clientes.size(); i++) {
        string nomeDoCliente = Clientes[i];
        cout << Cliente[nomeDoCliente] << endl;
    }

    return 0;
}