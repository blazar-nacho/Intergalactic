/*
 * CSV_reader.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: nacho
 */

#include "CSV_reader.h"

using namespace std;

class CSV_reader {

	CSV_reader(){}

	static vector<CSV_row*>* parse(string file_path, bool test, bool originalSet){
		ifstream csv_file(file_path);

		if (!csv_file.is_open())
			return NULL;
		while (!csv_file.eof()){
			string oneRow;
			getline(csv_file, oneRow);

			vector<CSV_row*> output;
			output.push_back(new CSV_row(oneRow, test, originalSet));


		}

		return NULL;
	}


};

class CSV_row{

	CSV_row(string line, bool test, bool originalSet){

		if (test){

		}

	}

	~CSV_row(){

	}
};



