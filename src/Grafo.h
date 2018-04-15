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

class Grafo {
public:
	int n;
	std::vector<std::vector<int>> listaAdjacencias;

	Grafo();
	bool todosVerticesTemGrauPar();
	bool ehConexo();
	bool ehSimples();
	bool ehPonte(Aresta e);
	int vizinhoNaoPonte(int vertice);
	std::list<int> determinaCicloEuleriano();
	void removerAresta(int vertice1, int vertice2);
	virtual ~Grafo();
};

#endif /* GRAFO_H_ */
