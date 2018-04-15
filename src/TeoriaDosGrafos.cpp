//============================================================================
// Name        : TeoriaDosGrafos.cpp
// Author      : Alexandre Romanelli
// Version     :
// Copyright   : Cópia permitida, desde que o autor seja citado.
// Description : Programa para testes de algoritmos sobre grafos.
//============================================================================

#include "Grafo.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

Grafo* lerGrafo(bool interativo) {
	// obter a quantidade de vértices
	if (interativo)
		cout << "  Quantidade de vértices: ";
	int n;
	cin >> n;

	if (n <= 0) {
		if (interativo)
			cout << "   grafo vazio." << endl;
		return NULL;
	}

	Grafo* G = new Grafo();
	G->n = n;

	// ler a lista de vizinhos de cada vértice (e verificar se todos têm grau par)
	//    (verificar também se o grafo não tem laço)
	if (interativo)
		cout << "  Lista de vizinhos:" << endl;
	G->listaAdjacencias.resize(n);
	for (int i = 0; i < n; i++) {
		if (interativo)
			cout << "  quantidade de vizinhos do vértice " << i + 1 << ": ";
		int d_i;
		cin >> d_i;
		//G->listaAdjacencias[i].resize(d_i, 0);

		if (interativo) {
			cout << "   -> vizinhos do vértice " << i + 1 << ": ";
		}
		// separar os números dos vértices por espaços
		for (int j = 0; j < d_i; j++) {
			int vizinho;
			cin >> vizinho;
			G->listaAdjacencias[i].push_back(vizinho - 1);
		}
	}

	return G;
}

void executarAlgoritmo_CicloEuleriano(bool interativo) {
	if (interativo) {
		cout << endl << endl << "Algoritmo para determinação de ciclo euleriano em grafo euleriano." << endl;
	}

	Grafo* G = lerGrafo(interativo);

	// verificar as características de existência de ciclo euleriano
	if (!G->todosVerticesTemGrauPar()) {
		cout << "  Grafo não possui todos os vértices com grau par." << endl;
	} else if (!G->ehSimples()) {
		cout << "  Grafo não é simples." << endl;
	} else if (!G->ehConexo()) {
		cout << "  Grafo não é conexo." << endl;
	} else {
		// computar o ciclo euleriano
		std::list<int> cicloEuleriano = G->determinarCicloEuleriano();

		// apresentar o ciclo euleriano
		if (interativo)
			cout << "  ---> Ciclo euleriano: [ ";
		for (int i : cicloEuleriano)
			cout << i + 1 << " ";
		if (interativo)
			cout << "]";
		cout << endl;
	}

	if (interativo) {
		cout << endl << endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {

		// interativo com humano

		cout << "+---------------------------------------------------------------+" << endl;
		cout << "| Descrição: Programa para testes de algoritmos sobre grafos    |" << endl;
		cout << "|            (desenvolvido na disciplina de Teoria dos Grafos)  |" << endl;
		cout << "|                                                               |" << endl;
		cout << "| Autor:     Alexandre Romanelli                                |" << endl;
		cout << "| Período:   2018-1                                             |" << endl;
		cout << "+---------------------------------------------------------------+" << endl;
		cout << endl;
		// menu de algoritmos para executar
		while (true) {
			// exibir opções
			cout << "   Opções:" << endl;
			cout << "     (1) Determinação de ciclo euleriano em grafo euleriano." << endl;
			cout << endl;
			cout << "     ---> Digite o número da opção desejada, ou 0 para sair: ";
			int opcao;
			cin >> opcao;
			switch (opcao) {
			case 1:
				executarAlgoritmo_CicloEuleriano(true);
				break;
			}
			if (opcao == 0)
				break;
		}
	} else {

		// para testes em lote
		int opcao = atoi(argv[1]);

		switch (opcao) {
		case 1:
			executarAlgoritmo_CicloEuleriano(false);
			break;
		}

	}
	return 0;
}
