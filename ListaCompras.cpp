#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
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

    vector <string> clientes;
    map <string, int> mapaClientes;
    
    vector <string> produtos;
    map <string, int> mapaProdutos;

    char data[16];
    char codCliente[32];
    char codProduto[32];
    char nome[200];

     const char *formato = " %15[^,],%31[^,],%31[^,],%199[^\r\n]";

    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %8[^,],%19[^,],%d,%199[^\r\n]",
                  data, codCliente, codProduto, nome) == 4) {

         if (mapaClientes.find(codCliente) == mapaClientes.end()) {
            mapaClientes[codCliente] = clientes.size();
            clientes.push_back(codCliente);
        }

        if (mapaProdutos.find(codProduto) == mapaProdutos.end()) {
            mapaProdutos[codProduto] = produtos.size();
            produtos.push_back(nome);
        }   
    }

    vector<list<int>> listaCompras(clientes.size());

    rewind(arquivo);
    fscanf(arquivo, "%*[^\n]");        // pula o cabecalho de novo

    while (fscanf(arquivo, formato, data, codCliente, codProduto, nome) == 4) {
        int ic = mapaClientes[codCliente];
        int ip = mapaProdutos[codProduto];
        listaCompras[ic].push_back(ip);
    }


    fclose(arquivo);

    return 0;
}