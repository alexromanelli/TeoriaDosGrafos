/*
 * Grafo.cpp
 *
 *  Created on: 14 de abr de 2018
 *      Author: alex
 */

#include "Grafo.h"
#include <vector>
#include <list>
#include <climits>
#include "FilaPorDistancia/FilaPorDistanciaVector.h"

const int Grafo::SEM_ANTECESSOR = -1;

Grafo::Grafo() {
	n = 0;
}

Grafo::~Grafo() {
}

bool Grafo::ehConexo() {
	// prepara vetor para registrar se vértice já foi visitado
	bool* visitado = new bool[n];
	for (int i = 0; i < n; i++) {
		visitado[i] = false;
	}
	// quantidade de vértices visitados
	int visitados = 0;

	// percorre as listas de adjacências para registrar os vértices conectados
	std::list<int> verticesParaVisitar;
	verticesParaVisitar.push_front(0);
	while (verticesParaVisitar.size() > 0) {
		// obtém primeiro vértice da lista
		int v = verticesParaVisitar.front();
		verticesParaVisitar.pop_front();
		// verifica se v ainda não foi visitado
		if (visitado[v])
			continue;
		// marca v como visitado
		visitado[v] = true;
		visitados++;
		// inclui vértices adjacentes a v na lista para visitar
		for (unsigned int i = 0; i < listaAdjacencias[v].size(); i++) {
			int adjacente = listaAdjacencias[v][i]->vertice;
			verticesParaVisitar.push_back(adjacente);
		}
	}
	// se, ao término, a quantidade de visitados é o número de vértices do grafo, então é conexo
	return visitados == n;
}

bool Grafo::todosVerticesTemGrauPar() {
	for (int i = 0; i < n; i++) {
		if (listaAdjacencias[i].size() % 2 != 0)
			return false;
	}
	return true;
}

bool Grafo::ehSimples() {
	for (int i = 0; i < n; i++) {
		// verifica ciclos (assume-se que não há arestas paralelas)
		for (unsigned int j = 0; j < listaAdjacencias[i].size(); j++) {
			if (listaAdjacencias[i][j]->vertice == i)
				return false;
		}
	}
	return true;
}

bool Grafo::ehPonte(Aresta e) {
	int u = e.lado1;
	int v = e.lado2;

	// verificar se, para algum vizinho de u, exceto o próprio v, há caminho para v (que não passe por u)

	// criar lista de vértices a verificar
	std::list<int> verticesParaVerificar;
	for (unsigned int i = 0; i < listaAdjacencias[u].size(); i++) {
		if (listaAdjacencias[u][i]->vertice != v)
			verticesParaVerificar.push_back(listaAdjacencias[u][i]->vertice);
	}
	// criar vetor para registrar os vértices verificados, para não repetir
	bool* verificado = new bool[n];
	for (int i = 0; i < n; i++)
		verificado[i] = false;

	// fazer a verificação de cada vértice na lista de verificação (fila)
	while (verticesParaVerificar.size() > 0) {
		int w = verticesParaVerificar.front();
		verticesParaVerificar.pop_front();
		verificado[w] = true;
		// adiciona os vizinhos de w à lista de vértices a verificar, exceto se for u
		for (unsigned int i = 0; i < listaAdjacencias[w].size(); i++) {
			if (listaAdjacencias[w][i]->vertice != u) {
				// se o vértice adjacente a w for v, então não é ponte
				if (listaAdjacencias[w][i]->vertice == v)
					return false;
				// senão, adicionar à lista de vértices a verificar (se não tiver sido verificado ainda)
				if (!verificado[listaAdjacencias[w][i]->vertice])
					verticesParaVerificar.push_back(listaAdjacencias[w][i]->vertice);
			}
		}
	}

	return true;
}

int Grafo::vizinhoNaoPonte(int vertice) {
	Aresta e;
	e.lado1 = vertice;
	for (unsigned int i = 0; i < listaAdjacencias[vertice].size(); i++) {
		e.lado2 = listaAdjacencias[vertice][i]->vertice;
		if (!ehPonte(e))
			return listaAdjacencias[vertice][i]->vertice;
	}
	return -1;
}

std::list<int> Grafo::determinarCicloEuleriano() {
	int w = 0; // vértice arbitrário para ser tomado como partida do ciclo euleriano
	std::list<int> EC;
	EC.push_back(w);
	int CV = w;
	std::list<int> E_;
	while (listaAdjacencias[w].size() > 0) {
		int v;
		if (listaAdjacencias[CV].size() > 1) {
			// encontrar aresta para vizinho que não seja ponte
			v = vizinhoNaoPonte(CV);
		} else {
			v = listaAdjacencias[CV][0]->vertice;
		}
		removerAresta(CV, v);
		E_.push_back(v);
		CV = v;
		EC.push_back(CV);
	}
	return EC;
}

void Grafo::removerAresta(int v1, int v2) {
	for (std::vector<Vizinho*>::iterator iter1 = listaAdjacencias[v1].begin();
			iter1 != listaAdjacencias[v1].end();
			iter1++) {
		if ((*iter1)->vertice == v2) {
			listaAdjacencias[v1].erase(iter1);
			break;
		}
	}
	for (std::vector<Vizinho*>::iterator iter2 = listaAdjacencias[v2].begin();
			iter2 != listaAdjacencias[v2].end();
			iter2++) {
		if ((*iter2)->vertice == v1) {
			listaAdjacencias[v2].erase(iter2);
			break;
		}
	}
}

bool Grafo::todasArestasTemCustoPositivo() {
	for (std::vector<std::vector<Vizinho*>>::iterator iter1 = listaAdjacencias.begin();
			iter1 != listaAdjacencias.end();
			iter1++) {
		for (std::vector<Vizinho*>::iterator iter2 = (*iter1).begin();
				iter2 != (*iter1).end();
				iter2++) {
			if ((*iter2)->custo < 0)
				return false;
		}
	}
	return true;
}

std::list<int> Grafo::obterComponenteConexaDeVertice(int vertice) {
	// prepara vetor para registrar se vértice já foi visitado
	bool* visitado = new bool[n];
	for (int i = 0; i < n; i++) {
		visitado[i] = false;
	}

	std::list<int> verticesConectados;

	std::list<int> verticesParaVerificar;
	verticesParaVerificar.push_front(vertice);
	visitado[vertice] = true;
	while (verticesParaVerificar.size() > 0) {
		int v = verticesParaVerificar.front();
		verticesParaVerificar.pop_front();

		verticesConectados.push_back(v);

		for (std::vector<Vizinho*>::iterator iter1 = listaAdjacencias[v].begin();
				iter1 != listaAdjacencias[v].end(); iter1++) {
			int v_ = (*iter1)->vertice;
			if (!visitado[v_]) {
				verticesParaVerificar.push_front(v_);
				visitado[v_] = true;
			}
		}

	}
	return verticesConectados;
}

void Grafo::caminhosCustoMinimo_Dijkstra(int verticeOrigem, std::vector<int>& antecessor) {
	FilaPorDistancia_Vector distanciaMinima;
	ElementoFila* indice[n];
	for (int i = 0; i < n; i++) {
		if (i == verticeOrigem)
			indice[i] = distanciaMinima.inserirElemento(i, 0);
		else
			indice[i] = distanciaMinima.inserirElemento(i, INT_MAX);
	}

	int contagemAberto = obterComponenteConexaDeVertice(verticeOrigem).size();
	antecessor[verticeOrigem] = SEM_ANTECESSOR;
	while (contagemAberto > 0) {
		int k, d;
		distanciaMinima.retirarElemento(k, d);
		delete indice[k];
		indice[k] = NULL;
		contagemAberto--;

		for (std::vector<Vizinho*>::iterator vizinho = listaAdjacencias[k].begin();
				vizinho != listaAdjacencias[k].end(); vizinho++) {
			if (indice[(*vizinho)->vertice] == NULL) // não está em Aberto
				continue;

			int verticeVizinho = (*vizinho)->vertice;
			int custoArestaVizinho = (*vizinho)->custo;
			if (indice[verticeVizinho]->getDistancia() > d + custoArestaVizinho) {
				distanciaMinima.alterarDistanciaElemento(verticeVizinho, d + custoArestaVizinho);
				antecessor[verticeVizinho] = k;
			}
		}
	}
}
