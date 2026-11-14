#include <stdio.h>
#include <iostream>
#include "dados.h"
using namespace std;

void extrairDados(Dados *dados, char *nomeArquivo) {
    char data[9];
    char codCliente[20];
    char codProduto[20];
    char nome[200];

    const char *formato = " %8[^,],%19[^,],%19[^,],%199[^\r\n]";
    
    int indiceCliente;
    int indiceProduto;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, formato, data, codCliente, codProduto, nome) == 4) {
        if (dados->mapaClientes.find(codCliente) == dados->mapaClientes.end()) {
            dados->mapaClientes[codCliente] = dados->clientes.size();
            dados->clientes.push_back(codCliente);
        }

        if (dados->mapaProdutos.find(codProduto) == dados->mapaProdutos.end()) {
            dados->mapaProdutos[codProduto] = dados->produtos.size();
            dados->produtos.push_back(codProduto);
        }
    }

    dados->produtosComprados.resize(dados->clientes.size());

    rewind(arquivo);
    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, formato, data, codCliente, codProduto, nome) == 4) {
        int ic = dados->mapaClientes[codCliente];
        int ip = dados->mapaProdutos[codProduto];
        dados->produtosComprados[ic].push_back(ip);
    }

    fclose(arquivo);
}