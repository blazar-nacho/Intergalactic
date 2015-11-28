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
#include <shark/Data/Csv.h> 
#include <shark/Algorithms/Trainers/RFTrainer.h>
#include <shark/ObjectiveFunctions/Loss/ZeroOneLoss.h>
#include <iostream>


using namespace std; 
using namespace shark;

typedef UnlabeledData<RealVector> data_shark;

void delete_data(vector<Row*>* datac) {

	for (size_t i = 0; i < datac->size(); i++) 
		delete datac->at(i);	
	datac->clear();
}


int main(void) {

/*
	CSV_reader *reader = new CSV_reader();
	
	bool test = true;
	vector<Row*> datac = reader->parse("test.csv", test);

	cout << datac.size() << endl;

	//reader->write(datac, "test_scal.csv");

	delete reader;


	for (size_t i = 0; i < datac[15]->getFieldsNum().size(); i++) 
		cout << datac[15]->get(i) << " + ";
	cout << endl;
*/
	//data_shark* train = new data_shark(data[15]->getFieldsNum());
	
/*
	for (size_t i = 0; i < data.size(); i++) 
		delete data[i];
	
	data.clear();
*/


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

	reader->write(datac, "test_scal.csv");

	delete reader;
	
	delete_data(&datac);

/*
	ClassificationDataset data, dataTest;
	importCSV(data, "train_scal.csv", FIRST_COLUMN, ',');
	importCSV(dataTest, "test_scal.csv", FIRST_COLUMN, ',');
	   
	//Split the dataset into a training and a test dataset
	//ClassificationDataset dataTest = splitAtElement(data,(int)datac.size()/2);

	cout << "Training set - number of data points: " << data.numberOfElements()
		<< " number of classes: " << numberOfClasses(data)
		<< " input dimension: " << inputDimension(data) << endl;
 
	cout << "Test set - number of data points: " << dataTest.numberOfElements()
		<< " number of classes: " << numberOfClasses(dataTest)
		<< " input dimension: " << inputDimension(dataTest) << endl;
    
	//Generate a random forest
	RFTrainer trainer;
	RFClassifier model;
	trainer.train(model, data);

	// evaluate Random Forest classifier
	ZeroOneLoss<unsigned int, RealVector> loss;
	Data<RealVector> prediction = model(data.inputs());
	cout << "Random Forest on training set accuracy: " << 1. - loss.eval(data.labels(), prediction) << endl;
	
	prediction = model(dataTest.inputs());
	cout << "Random Forest on test set accuracy:     " << 1. - loss.eval(dataTest.labels(), prediction) << endl;

	exportCSV(prediction, "predicted.csv");
	
*/
	return EXIT_SUCCESS;
}
