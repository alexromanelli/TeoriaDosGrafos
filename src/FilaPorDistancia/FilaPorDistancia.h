/*
 * FilaPorDistancia.h
 *
 *  Created on: 25 de abr de 2018
 *      Author: alex
 */

#ifndef FILAPORDISTANCIA_H_
#define FILAPORDISTANCIA_H_

class ElementoFila {
private:
	int vertice;
	int distancia;
public:
	ElementoFila() { this->vertice = -1; this->distancia = 0; }
	ElementoFila(int v, int d) { this->vertice = v; this->distancia = d; }
	void setVertice(int v) { this->vertice = v; }
	void setDistancia(int d) { this->distancia = d; }
	int getVertice() { return this->vertice; }
	int getDistancia() { return this->distancia; }
};

class FilaPorDistancia {
public:
	FilaPorDistancia() {}
	virtual ~FilaPorDistancia() {}
	virtual ElementoFila* inserirElemento(int vertice, int distancia) = 0;
	virtual bool retirarElemento(int& vertice, int& distancia) = 0;
	virtual void alterarDistanciaElemento(int vertice, int distancia) = 0;
};

#endif /* FILAPORDISTANCIA_H_ */
