#include <stdio.h>
#include <iostream>
#include "dados.h"
using namespace std;

void extrairDados(Dados *dados, char *nomeArquivo) {
    char data[9];
    char codCliente[9];
    char codProduto[6];
    char nome[200];

    int jaComputou;

    const char *formato = " %8[^,],%8[^,],%5[^,],%199[^\r\n]";

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

        jaComputou = 0;

        for (int ipComprado : dados->produtosComprados[ic]) {
            if (ip == ipComprado) {
                jaComputou = 1;
                break;
            }
        }

        if (!jaComputou)
            dados->produtosComprados[ic].push_back(ip);
    }

    fclose(arquivo);
}

void testeListaCompras(Dados *dados, char *codCliente) {
    int indiceCliente;

    indiceCliente = dados->mapaClientes[codCliente];
    cout << "Produtos comprados por " << codCliente << ": ";

    for (int indiceProduto : dados->produtosComprados[indiceCliente]) {
        cout << dados->produtos[indiceProduto] << " ";
    }
    cout << endl;
}