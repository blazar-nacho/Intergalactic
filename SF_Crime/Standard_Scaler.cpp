/*
 * Standard_Scaler.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: Intergalactic
 */

#include "Standard_Scaler.h"
#include <math.h>

using namespace std;

Standard_Scaler::Standard_Scaler()
{
}



void Standard_Scaler::fit(vector<Row*> data)
{
	if (data.empty()) return;

	// means:
	// inicializo sumas en cero
	vector<long double> sums;
	for (size_t j=0; j< data.at(0)->get_size(); j++)
		sums.push_back(0.0);

	// suma de cada elemento de cada elemento de cada columna
	for (size_t i=0; i< data.size(); i++)
		for (size_t j=0; j< data[i]->get_size(); j++)
			sums[j] += data[i]->get(j);
	// calculo cada mean
	for (size_t j=0; j< sums.size(); j++)
		means.push_back((float)(sums[j] / data.size()));

	
	// standard deviations:
	// inicializo sumas en cero, otra vez
	for (size_t j=0; j< data.at(0)->get_size(); j++)
		sums[j] = 0.0;

	// suma de cada desviación cuadrada de cada elemento de cada columna
	for (size_t i=0; i< data.size(); i++)
		for (size_t j=0; j< data[i]->get_size(); j++)
			sums[j] += pow(data[i]->get(j) - means.at(j), 2.0);

	// calculo cada sd
	for (size_t j=0; j< sums.size(); j++)
		sds.push_back((float)sqrt(sums[j] / data.size()));


			
}



vector<Row*> Standard_Scaler::transform(vector<Row*> data)
{
	for (size_t i=0; i< data.size(); i++)
		for (size_t j=0; j< data[i]->get_size(); j++)
			data[i]->set(j, (data[i]->get(j) - means.at(j)) / sds.at(j) );

	return data;
}




Standard_Scaler::~Standard_Scaler(){}
