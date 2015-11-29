//============================================================================
// Name        : SF_Crime.cpp
// Author      : Intergalactic
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "CSV_reader.h"
#include <mlpack/core.hpp>
#include <iostream>
#include "pca.h"
using namespace std;

void delete_data(vector<Row*>* datac) {

	for (size_t i = 0; i < datac->size(); i++) 
		delete datac->at(i);	
	datac->clear();
}

vector<double> one_dimension(vector<Row*> data, int dimensions=1)
{
	vector<double> reduced;	
	if (data.empty()) return reduced;

	stats::pca pca(data.at(0)->get_size());

	for (size_t i = 0; i< data.size(); i++)
		pca.add_record(data.at(i)->getFieldsNum());

	pca.solve();
	

	vector<double> pca_col1 = pca.get_principal(0);

	for (size_t i = 0; i< data.size(); i++){
		vector<double> row_i = data[i]->getFieldsNum();
		reduced.push_back(inner_product(begin(row_i), end(row_i), begin(pca_col1), 0.0));
	}
		
		
	return reduced;


}


int main(void) {


	// carga modificacion estandarizacion de train
	CSV_reader *reader = new CSV_reader();
	
	vector<Row*> datac = reader->parse("train.csv");

	cout << datac.size() << endl;

	reader->write(datac, "train_scal.csv");

	delete reader;
	
	delete_data(&datac);


	// carga modificacion estandarizacion de test
	reader = new CSV_reader();
	
	bool test = true;
	datac = reader->parse("test.csv", test);

	cout << datac.size() << endl;

	// Aplica PCA reduce a una dimension
	reader->remove_column(datac, 0);
	vector<double> test_red = one_dimension(datac);	

	reader->write(test_red, "test_red.csv");

	reader->write(datac, "test_scal.csv");

	delete reader;
	
	delete_data(&datac);




	return EXIT_SUCCESS;
}
