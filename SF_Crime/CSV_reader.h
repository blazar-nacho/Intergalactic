/*
 * CSV_reader.h
 *
 *  Created on: 8 de nov. de 2015
 *      Author: Intergalactic
 */
#pragma once

#ifndef CSV_READER_H_
#define CSV_READER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include "timedates_t.h"

#define DROP -1000
#define TRAIN_COLS 9
#define TRAIN_VEC {"Dates","Category","Descript","DayOfWeek","PdDistrict","Resolution","Address","X","Y"}

#define TEST_COLS 7
#define TEST_VEC {"Id","Dates","DayOfWeek","PdDistrict","Address","X","Y"}

#define CAT_VEC {{"ARSON",1},{"ASSAULT",2},{"BAD CHECKS",3},{"BRIBERY",4},{"BURGLARY",5},{"DISORDERLY CONDUCT",6},{"DRIVING UNDER THE INFLUENCE",7},{"DRUG/NARCOTIC",8},{"DRUNKENNESS",9},{"EMBEZZLEMENT",10},{"EXTORTION",11},{"FAMILY OFFENSES",12},{"FORGERY/COUNTERFEITING",13},{"FRAUD",14},{"GAMBLING",15},{"KIDNAPPING",16},{"LARCENY/THEFT",17},{"LIQUOR LAWS",18},{"LOITERING",19},{"MISSING PERSON",20},{"NON-CRIMINAL",21},{"OTHER OFFENSES",22},{"PORNOGRAPHY/OBSCENE MAT",23},{"PROSTITUTION",24},{"RECOVERED VEHICLE",25},{"ROBBERY",26},{"RUNAWAY",27},{"SECONDARY CODES",28},{"SEX OFFENSES FORCIBLE",29},{"SEX OFFENSES NON FORCIBLE",30},{"STOLEN PROPERTY",31},{"SUICIDE",32},{"SUSPICIOUS OCC",33},{"TREA",34},{"TRESPASS",35},{"VANDALISM",36},{"VEHICLE THEFT",37},{"WARRANTS",38},{"WEAPON LAWS",39}}

#define DAY_VEC {{"Monday",1},{"Tuesday",2},{"Wednesday",3},{"Thursday",4},{"Friday",5},{"Saturday",6},{"Sunday",7}}

#define PD_VEC {{"BAYVIEW",1},{"CENTRAL",2},{"INGLESIDE",3},{"MISSION",4},{"NORTHERN",5},{"PARK",6},{"RICHMOND",7},{"SOUTHERN",8},{"TARAVAL",9},{"TENDERLOIN",10}}

using namespace std;

typedef map<string, double>  lbl_num;

const vector<string> train_labels = TRAIN_VEC;
const vector<string> test_labels = TEST_VEC;
const lbl_num categories = CAT_VEC;
const lbl_num days = DAY_VEC;
const lbl_num pd_district = PD_VEC;

class Row{

public:

Row(string line, bool test, bool originalSet);

vector<double> getFieldsNum();
double get(size_t pos);
void set(size_t pos, double newval);
size_t get_size();

timedates_t getDates();

~Row();

private:
vector<double> fieldsNum;
timedates_t dates;

string extractField(string line, size_t* pos);

double operateTestField(string field, size_t fieldId);
double operateTrainField(string field, size_t fieldId);

double operateField(string field, size_t fieldId, bool test);
void parseDates(string field);



};


class CSV_reader {

public:

CSV_reader();

// test true si es test set, false si no, sería train. originalSet true si son los set originales,
// false si son los modificados para agregar temperatura, lluvias, etc
vector<Row*> parse(string file_path, bool test=false, bool originalSet=true);

void write(vector<Row*> input, string out);

};



#endif /* CSV_READER_H_ */
