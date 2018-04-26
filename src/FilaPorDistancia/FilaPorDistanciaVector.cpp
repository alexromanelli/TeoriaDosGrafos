/*
 * FilaPorDistanciaVector.cpp
 *
 *  Created on: 25 de abr de 2018
 *      Author: alex
 */

#include "FilaPorDistanciaVector.h"

FilaPorDistancia_Vector::FilaPorDistancia_Vector() {
}

FilaPorDistancia_Vector::~FilaPorDistancia_Vector() {
	for (unsigned int i = 0; i < fila.size(); i++)
		delete fila[i];
}

ElementoFila* FilaPorDistancia_Vector::inserirElemento(int vertice, int distancia) {
	ElementoFila* elemento = new ElementoFila(vertice, distancia);
	if (fila.size() == 0) {
		fila.push_back(elemento);
		return elemento;
	}
	std::vector<ElementoFila*>::iterator pos = fila.begin();
	while (pos != fila.end()) {
		if ((*pos)->getDistancia() > distancia)
			break;
		pos++;
	}
	fila.insert(pos, elemento);
	return elemento;
}

void FilaPorDistancia_Vector::alterarDistanciaElemento(int vertice, int distancia) {
	// encontra posição do vértice
	int pos = 0;
	for (unsigned int i = 0; i < fila.size(); i++) {
		if (fila[i]->getVertice() == vertice)
			break;
		pos++;
	}
	// altera distância
	fila[pos]->setDistancia(distancia);
	// reposiciona elemento, mantendo ordenação
	for (int i = pos - 1; i >= 0; i--) {
		if (fila[i]->getDistancia() > distancia) {
			// troca elementos
			ElementoFila* t = fila[i];
			fila[i] = fila[i + 1];
			fila[i + 1] = t;
		} else {
			break;
		}
	}
}

bool FilaPorDistancia_Vector::retirarElemento(int& vertice, int& distancia) {
	if (fila.size() > 0) {
		ElementoFila* elemento = fila[0];
		vertice = elemento->getVertice();
		distancia = elemento->getDistancia();
		fila.erase(fila.begin());
		return true;
	}
	return false;
}
