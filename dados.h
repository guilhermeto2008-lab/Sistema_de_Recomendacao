#ifndef DADOS_H
#define DADOS_H

#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

struct Dados {
    vector <string> clientes;
    map <string, int> mapaClientes;
    
    vector <string> produtos;
    map <string, int> mapaProdutos;

    vector<list<int>> produtosComprados;

    vector<vector<int>> matrizSimilaridade;
};

#endif