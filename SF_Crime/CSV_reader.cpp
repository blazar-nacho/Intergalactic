/*
 * CSV_reader.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: Intergalactic
 */

#include "CSV_reader.h"

#include "timedates_t.h"

using namespace std;


CSV_row::CSV_row(string line, bool test, bool originalSet){

		/*timedates_t time;
		string dates, category, descript, dayofweek, pddistrict, resolution, address;
		float x, y;
		int tmax, tmin, tavrg;
		bool rain;*/


		if (originalSet && test){
			size_t found_start = 0;
			size_t found_end = 0;
			while (found_end != string::npos) {
				found_end = line.find(",", found_start + 1);

				found_start = found_end;

			}

		}

	}

CSV_row::~CSV_row(){

	}





CSV_reader::CSV_reader(){}

vector<CSV_row*> CSV_reader::parse(string file_path, bool test, bool originalSet){
		ifstream csv_file(file_path);
		vector<CSV_row*> output;

		if (!csv_file.is_open())
			return output;
		while (!csv_file.eof()){
			string oneRow;
			getline(csv_file, oneRow);
			
			output.push_back(new CSV_row(oneRow, test, originalSet));


		}

		return output;
}








