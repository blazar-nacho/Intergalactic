/*
 * CSV_reader.h
 *
 *  Created on: 8 de nov. de 2015
 *      Author: Intergalactic
 */
#pragma once

#ifndef CSV_READER_H_
#define CSV_READER_H_

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class CSV_row{

public:

CSV_row(string line, bool test, bool originalSet);

~CSV_row();

};

class CSV_reader {

public:

CSV_reader();

// test true si es test set, false si no, sería train. originalSet true si son los set originales,
// false si son los modificados para agregar temperatura, lluvias, etc
vector <CSV_row*> parse(string file_path, bool test=false, bool originalSet=true);



};



#endif /* CSV_READER_H_ */
