/*
 * Grafo.h
 *
 *  Created on: 14 de abr de 2018
 *      Author: alex
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <vector>
#include <list>

typedef struct {
	int lado1;
	int lado2;
} Aresta;

typedef struct {
	int vertice;
	int custo;
} Vizinho;

class Grafo {
public:
	// constantes para algoritmo de caminho mínimo de Dijkstra
	static const int SEM_ANTECESSOR;

	int n;
	std::vector<std::vector<Vizinho*>> listaAdjacencias;

	Grafo();
	virtual ~Grafo();

	bool todosVerticesTemGrauPar();
	bool ehConexo();
	bool ehSimples();
	bool ehPonte(Aresta e);
	int vizinhoNaoPonte(int vertice);
	std::list<int> determinarCicloEuleriano();
	void removerAresta(int vertice1, int vertice2);

	bool todasArestasTemCustoPositivo();
	std::list<int> obterComponenteConexaDeVertice(int vertice);
	void caminhosCustoMinimo_Dijkstra(int verticeOrigem, std::vector<int>& antecessor);
};

#endif /* GRAFO_H_ */
