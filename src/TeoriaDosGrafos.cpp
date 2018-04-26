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

Grafo* lerGrafo(bool interativo, bool valorado) {
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
			std::string mensagem = (valorado ? "   -> vizinhos (pares [vizinho] [custo]) do vértice " : "   -> vizinhos do vértice ");
			cout << mensagem << i + 1 << ": ";
		}
		// separar os números dos vértices por espaços
		for (int j = 0; j < d_i; j++) {
			int vizinho;
			cin >> vizinho;
			Vizinho* viz = new Vizinho();
			viz->vertice = vizinho - 1;
			if (valorado) {
				int custo;
				cin >> custo;
				viz->custo = custo;
			} else {
				viz->custo = 1; // no grafo não valorado, todas as arestas têm custo unitário
			}
			G->listaAdjacencias[i].push_back(viz);
		}
	}

	return G;
}

void executarAlgoritmo_CicloEuleriano(bool interativo) {
	if (interativo) {
		cout << endl << endl << "Algoritmo para determinação de ciclo euleriano em grafo euleriano." << endl;
	}

	Grafo* G = lerGrafo(interativo, false);

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

void executarAlgoritmo_Dijkstra(bool interativo) {
	if (interativo) {
		cout << endl << endl << "Algoritmo para determinação de caminho de custo mínimo de Dijkstra." << endl;
	}

	Grafo* G = lerGrafo(interativo, true);

	// verificar características necessárias para o algoritmo de Dijkstra (custos positivos)
	if (!G->todasArestasTemCustoPositivo()) {
		cout << "  Grafo não possui todas as arestas com custos positivos." << endl;
	} else {
		// computar os caminhos de custo mínimo partindo do primeiro vértice até os demais
		std::vector<int> antecessor;
		antecessor.resize(G->n, Grafo::SEM_ANTECESSOR);
		int origem = 0;
		G->caminhosCustoMinimo_Dijkstra(origem, antecessor);

		// apresentar a árvore de caminhos (se grafo não for conexo, a lista de vértices inatingíveis procede)
		if (interativo)
			cout << "  ---> Caminhos de custo mínimo: " << endl;

		for (int i = 0; i < G->n; i++) {
			// apresentar o caminho da origem até o vértice i
			if (i == origem) {
				printf("       [%d] ---> [%d] : %d\n", origem + 1, i + 1, origem + 1);
			} else {
				printf("       [%d] ---> [%d] : ", origem + 1, i + 1);
				if (antecessor[i] == Grafo::SEM_ANTECESSOR) {
					// vértice inatingível a partir da origem
					printf(" inatingível\n");
					continue;
				}
				std::list<int> sequencia;
				sequencia.push_front(i);
				int atual = antecessor[i];
				while (atual != Grafo::SEM_ANTECESSOR) {
					sequencia.push_front(atual);
					atual = antecessor[atual];
				}
				for (std::list<int>::iterator iter = sequencia.begin(); iter != sequencia.end(); iter++) {
					printf("%d ", (*iter) + 1);
				}
				printf("\n");
			}
		}
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
			cout << "     (1) Ciclo euleriano em grafo euleriano." << endl;
			cout << "     (2) Caminhos de custo mínimo da origem para os demais vértices." << endl;
			cout << endl;
			cout << "     ---> Digite o número da opção desejada, ou 0 para sair: ";
			int opcao;
			cin >> opcao;
			switch (opcao) {
			case 1:
				executarAlgoritmo_CicloEuleriano(true);
				break;
			case 2:
				executarAlgoritmo_Dijkstra(true);
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
