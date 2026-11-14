#include "Recomendacao.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

bool comparaProdutos(const ranking &a, const ranking &b){
    if (a.score != b.score) {
        return a.score < b.score;   
    }
    else{
        return a.produto < b.produto;     
    }
}

std::vector<int> recomendarProdutos(Dados *dados, int c, int k){
    int qntProdutos = dados->produtos.size();
    
    vector <ranking> rankingProdutos(qntProdutos);

    for (int p = 0; p < qntProdutos; p++) {
        rankingProdutos[p].produto = p;
        rankingProdutos[p].score = 1.0;
    }

    vector<bool> comprou(qntProdutos, false);

    for (int p : dados->produtosComprados[c]) {
        comprou[p] = true;
    }

    for (int v = 0; v == dados->clientes.size() - 1; v++) {
       if (v == c){
        continue;
       }
    
        double s = dados->matrizSimilaridade[c][v];
        if (s >= 1){ 
            continue;
        }

        vector<bool> jaAplicou(qntProdutos, false); 

        for (int p : dados->produtosComprados[v]) {
            if (!comprou[p] && !jaAplicou[p]) {
                rankingProdutos[p].score *= s;
                jaAplicou[p] = true;
            }
        }
    
    
    }

    vector <ranking> candidatos;

    for (int p = 0; p < qntProdutos; p++) {
        if (!comprou[p] && rankingProdutos[p].score < 1.0) {
            candidatos.push_back(rankingProdutos[p]);
        }
    }

    sort(candidatos.begin(), candidatos.end(), comparaProdutos);

    vector<int> resultado;

    for (int i = 0; i < k && i < (int) candidatos.size(); i++) {
        resultado.push_back(candidatos[i].produto);
    }

    return {};
}

void testeRecomendacao(Dados *dados, int k, char *codigos[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        string codigo = codigos[i];

        auto it = dados->mapaClientes.find(codigo);
        if (it == dados->mapaClientes.end()) {
            cout << "Cliente " << codigo << " nao encontrado." << endl;
            continue;
        }

        int indice = it->second;
        vector<int> recomendados = recomendarProdutos(dados, indice, k);

        cout << "Recomendacoes para o cliente " << codigo << ":" << endl;
        if (recomendados.empty()) {
            cout << "  nenhuma recomendacao" << endl;
        } else {
            for (int ip : recomendados) {
                cout << "  - " << dados->produtos[ip] << endl;
            }
        }
        cout << endl;
    }
}