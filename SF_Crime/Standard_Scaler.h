/*
 * Standard_Scaler.h
 *
 *  Created on: 8 de nov. de 2015
 *      Author: Intergalactic
 */
#pragma once

#ifndef STANDARD_SCALER_H_
#define STANDARD_SCALER_H_

#include <iostream>
#include "CSV_reader.h"


class Standard_Scaler {

public:
	Standard_Scaler();

	void fit(vector<Row*>);
	vector<Row*> transform(vector<Row*>);

	~Standard_Scaler();

private:

vector<float> means;
vector<float> sds;

};

#endif /* STANDARD_SCALER_H_ */
