/*
 * CSV_reader.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: Intergalactic
 */

#include "CSV_reader.h"
#include "Standard_Scaler.h"


using namespace std;


Row::Row(string line, bool test, bool originalSet){

		if (originalSet && !test){
			// donde empieza el campo
			size_t found = 0;			

			// for en vez de while porque necesito todas las columnas
			// sino devolver vacio
			for (int i= 0; i < TRAIN_COLS; i++) {
				// extrae el campo 
				string field = extractField(line, &found);		
				
				// si no se parsea bien un campo, marco para quitar				
				if (field.compare("") == 0) {
					fieldsNum.clear();
					break;
				}

				// opera el campo dependiendo del tipo		
				double fieldNum = operateField(field, i);				

				if ((fieldNum != DROP) && (i > 0)) {					
					fieldsNum.push_back(fieldNum);
				}

				// si i=0 es Dates, corregir
				// double para std scaling
				if (i==0) {
					fieldsNum.push_back((double)dates.t_year);
					fieldsNum.push_back((double)dates.t_month);
					fieldsNum.push_back((double)dates.t_day);
					fieldsNum.push_back((double)dates.t_hour);
					fieldsNum.push_back((double)dates.t_min);
				}
					

			}
			

		}

	}

string Row::extractField(string line, size_t* pos)
{
	size_t posAux;
	size_t posPre = *pos;
	if (line.size() == 0) return "";

	if (line[posPre] == '"'){
		posAux= line.find('"', posPre+2);
		*pos = posAux+2;

		return line.substr(posPre+1, posAux - posPre -1);

	}

	posAux= line.find(",", posPre+1);
	*pos = posAux+1;
	return line.substr(posPre, posAux - posPre);

}


vector<double> Row::getFieldsNum(){
	return fieldsNum;
}
timedates_t Row::getDates(){
	return dates;
}

double Row::operateField(string field, size_t fieldId)
{
	if (train_labels.at(fieldId).compare("Dates") == 0) {
		parseDates(field);
		return 0.0f;
	}

	if ((train_labels.at(fieldId).compare("X") == 0)
	|| (train_labels.at(fieldId).compare("Y") == 0)){		
		return stof(field);
	}

	if (train_labels.at(fieldId).compare("Category") == 0)
		return categories.at(field);

	if (train_labels.at(fieldId).compare("PdDistrict") == 0)
		return pd_district.at(field);

	if (train_labels.at(fieldId).compare("DayOfWeek") == 0)
		return days.at(field);

	/*if ((train_labels.at(fieldId).compare("Descript") == 0) 
	|| (train_labels.at(fieldId).compare("Resolution") == 0))
		return DROP;*/

	return DROP;


}

void Row::parseDates(string field){	
	if (field.size() < 2) return;

	size_t ff1 = field.find("-", 1);
	dates.t_year = stoi(field.substr(0, ff1));
	size_t ff2 = field.find("-", ff1 + 1);
	dates.t_month = stoi(field.substr(ff1+1, ff2 - ff1));
	ff1 = field.find(" ", ff2 + 1);
	dates.t_day = stoi(field.substr(ff2+1, ff1 - ff2));

	ff2 = field.find(":", ff1 +1);
	dates.t_hour = stoi(field.substr(ff1+1 , ff2 -ff1));
	ff1 = field.find(":", ff2 + 1);
	dates.t_min = stoi(field.substr(ff2+1, ff1 - ff2));

}

double Row::get(size_t pos) {
	return fieldsNum.at(pos);
}

size_t Row::get_size() {
	return fieldsNum.size();
}

void Row::set(size_t pos, double newval){
	fieldsNum[pos] = newval;
}



Row::~Row(){

	fieldsNum.clear();

	}





CSV_reader::CSV_reader(){}

vector<Row*> CSV_reader::parse(string file_path, bool test, bool originalSet){
		ifstream csv_file(file_path);
		vector<Row*> output;

		if (!csv_file.is_open())
			return output;	
		
		string line;
		getline(csv_file, line);
		while (!csv_file.eof()){			
		
			getline(csv_file, line);
			//if (!test)			
			Row* oneRow = new Row(line, test, originalSet);
			// si se parseo bien la agrego
			if (!oneRow->getFieldsNum().empty())
				output.push_back(oneRow);
			else 
				delete oneRow;



		}

		Standard_Scaler* scaler = new Standard_Scaler();
		scaler->fit(output);
		output = scaler->transform(output);

		delete scaler;

		csv_file.close();

		return output;
}


void CSV_reader::write(vector<Row*> input, string out){

	remove(out.c_str());
	ofstream output(out.c_str(), ios::app);

	output<< fixed << setprecision(8) ;
	for (size_t i=0; i<input.size(); i++) {
		for (size_t j = 0; j<input[i]->get_size()-1; j++)
			output << input[i]->get(j) << "," ;
		output << input[i]->get(input[i]->get_size()-1) << endl;
	}


}






