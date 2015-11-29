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

//headers needed for ELM
#include <shark/Models/LinearModel.h>
#include <shark/Models/ConcatenatedModel.h>
#include <shark/Models/FFNet.h>
#include <shark/Rng/Normal.h>
#include <shark/Algorithms/Trainers/NormalizeComponentsUnitVariance.h>
#include <shark/Algorithms/Trainers/LinearRegression.h>

//header needed for the problem
#include <shark/Data/DataDistribution.h>

//just for evaluation of the ELM
#include <shark/ObjectiveFunctions/Loss/SquaredLoss.h>
#include <iostream>
#include "pca.h"
using namespace std;
using namespace shark;

using namespace std; 
using namespace shark;

typedef UnlabeledData<RealVector> data_shark;

void delete_data(vector<Row*>* datac) {

	for (size_t i = 0; i < datac->size(); i++) 
		delete datac->at(i);	
	datac->clear();
}

class Problem:public LabeledDataDistribution<RealVector,RealVector>{
public:
	void draw(RealVector& input, RealVector& label)const
	{
		input.resize(2);
		label.resize(1);
		input(0) = Rng::uni(-5, 5);
		input(1) = Rng::uni(-5, 5);
		if(input(0) != 0)
			label(0) = sin(input(0)) / input(0) + input(1) + Rng::gauss(0.0, 0.1);
		else
			label(0) = 1 + input(1) + Rng::gauss(0.0, 0.1);
	}
};	


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



	
	//change these constants for your own problem
	size_t hiddenNeurons = 17;
	size_t numSamples = 1000;
	unsigned int randomSeed = 42;
  
	//configure random number generator
	Rng::seed(randomSeed);
 
	//create the regression problem
	Problem problem;
	RegressionDataset data= problem.generateDataset(numSamples);
	

	cout << data.inputs() << endl;

	//importCSV(data, "train_scal.csv", FIRST_COLUMN, ',');
	size_t inputDim = inputDimension(data);
  
	//usually an elm uses zero mean unit variance inputs. so we should
	//normalize the data first
	Normalizer<> normalizer;
	NormalizeComponentsUnitVariance<> normalizingTrainer(true);
	normalizingTrainer.train(normalizer,data.inputs());
	  
	// now we construct the hidden layer of the elm
	// we create a two layer network and initialize it randomly. By keeping the random
	// hidden weights and only learning the visible later, we will create the elm
	FFNet<LogisticNeuron,LogisticNeuron> elmNetwork;
	elmNetwork.setStructure(inputDim,hiddenNeurons,labelDimension(data));
	initRandomNormal(elmNetwork,1);
	 
	//We need to train the linear part. in this simple example we use the elm standard
	//technique: linear regression. For this we need to propagate the data first 
	// through the normalization and the hidden layer of the elm
	RegressionDataset transformedData = transformInputs(data,normalizer);
	transformedData.inputs() = elmNetwork.evalLayer(0,transformedData.inputs());
	LinearModel<> elmOutput;
	LinearRegression trainer;
	trainer.train(elmOutput,transformedData);
  
	//we need to set the learned weights of the hidden layer of the elm
	elmNetwork.setLayer(1,elmOutput.matrix(),elmOutput.offset());
	
	  
	ConcatenatedModel<RealVector,RealVector> elm = normalizer >> elmNetwork;
	//to test whether everything works, we will evaluate the elm and the elmOutput layer separately
	//both results should be identical
	SquaredLoss<> loss;
	double outputResult = loss(transformedData.labels(),elmOutput(transformedData.inputs()));
	double elmResult = loss(transformedData.labels(),elm(data.inputs()));
	
	cout<<"Results"<<std::endl;
	cout<<"============"<<std::endl;
	cout<<"output Layer: "<< outputResult<<std::endl;
	cout<<"ELM: "<< elmResult<<std::endl;








/*
	std::vector<RealMatrix> U, V, W;

	svd(data,U,V,W);

	PCA pca_train(data);
	unsigned m = 70;
	LinearModel<> enc;
	pca_train.encoder(enc, m);
*/
/*
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
