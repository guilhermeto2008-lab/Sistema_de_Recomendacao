#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"
using namespace std;

void extrairDados(Dados *dados, char *nomeArquivo) {
    char data[9];
    char codCliente[20];
    char codProduto[20];
    char nome[200];

    int codProdutoInt;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %8[^,],%19[^,],%d,%199[^\r\n]",
                data, codCliente, codProdutoInt, nome) == 4) {

        if (dados->mapaClientes.find(codCliente) == dados->mapaClientes.end()) {
            dados->mapaClientes[codCliente] = dados->clientes.size();
            dados->clientes.push_back(codCliente);
        }

        if (dados->mapaProdutos.find(codProduto) == dados->mapaProdutos.end()) {
            dados->mapaProdutos[codProduto] = dados->produtos.size();
            dados->produtos.push_back(nome);
        }   
    }

    rewind(arquivo);
    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, "%8[^,],%19[^,],%19[^,],%199[^\r\n]",
                data, codCliente, codProduto, nome) == 4) {
        int ic = dados->mapaClientes[codCliente];
        int ip = dados->mapaProdutos[codProduto];
        dados->produtosComprados[ic].push_back(ip);
    }

    fclose(arquivo);
}