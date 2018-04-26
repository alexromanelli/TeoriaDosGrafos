/*
 * FilaPorDistanciaVector.h
 *
 *  Created on: 25 de abr de 2018
 *      Author: alex
 */

#ifndef FILAPORDISTANCIAVECTOR_H_
#define FILAPORDISTANCIAVECTOR_H_

#include "FilaPorDistancia.h"
#include <vector>

class FilaPorDistancia_Vector : FilaPorDistancia {
private:
	std::vector<ElementoFila*> fila;
public:
	FilaPorDistancia_Vector();
	virtual ~FilaPorDistancia_Vector();
	ElementoFila* inserirElemento(int vertice, int distancia) override;
	bool retirarElemento(int& vertice, int& distancia) override;
	void alterarDistanciaElemento(int vertice, int distancia) override;
};

#endif /* FILAPORDISTANCIAVECTOR_H_ */
