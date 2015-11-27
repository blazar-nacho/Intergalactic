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

int main(void) {

	CSV_reader *reader = new CSV_reader();
	
	vector<Row*> datac = reader->parse("train.csv");

	cout << datac.size() << endl;

	reader->write(datac, "train_scal.csv");

	delete reader;


	/*for (size_t i = 0; i < data[15]->getFieldsNum().size(); i++) 
		printf("%f + ", data[15]->getFieldsNum().at(i));
		//cout << data[15]->getFieldsNum().at(i) << " + ";
	printf("\n");*/

	//data_shark* train = new data_shark(data[15]->getFieldsNum());
	
/*
	for (size_t i = 0; i < data.size(); i++) 
		delete data[i];
	
	data.clear();
*/

	ClassificationDataset data;
	importCSV(data, "train_scal.csv", FIRST_COLUMN, ',');
	   
	//Split the dataset into a training and a test dataset
	ClassificationDataset dataTest = splitAtElement(data,311);

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

	return EXIT_SUCCESS;
}
