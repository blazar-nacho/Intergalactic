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
#include <stdlib.h> 
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

#define CAT_VEC {make_pair("ARSON",1), make_pair("ASSAULT",2), make_pair("BAD CHECKS",3), make_pair("BRIBERY",4), make_pair("BURGLARY",5), make_pair("DISORDERLY CONDUCT",6), make_pair("DRIVING UNDER THE INFLUENCE",7), make_pair("DRUG/NARCOTIC",8), make_pair("DRUNKENNESS",9), make_pair("EMBEZZLEMENT",10), make_pair("EXTORTION",11), make_pair("FAMILY OFFENSES",12), make_pair("FORGERY/COUNTERFEITING",13), make_pair("FRAUD",14), make_pair("GAMBLING",15), make_pair("KIDNAPPING",16), make_pair("LARCENY/THEFT",17), make_pair("LIQUOR LAWS",18), make_pair("LOITERING",19), make_pair("MISSING PERSON",20), make_pair("NON-CRIMINAL",21), make_pair("OTHER OFFENSES",22), make_pair("PORNOGRAPHY/OBSCENE MAT",23), make_pair("PROSTITUTION",24), make_pair("RECOVERED VEHICLE",25), make_pair("ROBBERY",26), make_pair("RUNAWAY",27), make_pair("SECONDARY CODES",28), make_pair("SEX OFFENSES FORCIBLE",29), make_pair("SEX OFFENSES NON FORCIBLE",30), make_pair("STOLEN PROPERTY",31), make_pair("SUICIDE",32), make_pair("SUSPICIOUS OCC",33), make_pair("TREA",34), make_pair("TRESPASS",35), make_pair("VANDALISM",36), make_pair("VEHICLE THEFT",37), make_pair("WARRANTS",38), make_pair("WEAPON LAWS",39)}

#define DAY_VEC {make_pair("Monday",1), make_pair("Tuesday",2), make_pair("Wednesday",3), make_pair("Thursday",4), make_pair("Friday",5), make_pair("Saturday",6), make_pair("Sunday",7)}

#define PD_VEC {make_pair("BAYVIEW",1), make_pair("CENTRAL",2), make_pair("INGLESIDE",3), make_pair("MISSION",4), make_pair("NORTHERN",5), make_pair("PARK",6), make_pair("RICHMOND",7), make_pair("SOUTHERN",8), make_pair("TARAVAL",9), make_pair("TENDERLOIN",10)}

using namespace std;

typedef map<string, double>  lbl_num;

class Row{

public:

Row(string line, bool test, bool originalSet, const vector<string>* tr_l, const vector<string>* te_l, 
	const lbl_num* ca_m, const lbl_num* da_m, const lbl_num* pd_m);



vector<double> getFieldsNum();
double get(size_t pos);
void set(size_t pos, double newval);
void remove(size_t pos);
size_t get_size();

timedates_t getDates();

~Row();

private:
vector<double> fieldsNum;
timedates_t dates;

string extractField(string line, size_t* pos);

double operateTestField(string field, size_t fieldId, const vector<string>* tr_l, const vector<string>* te_l, 
	const lbl_num* ca_m, const lbl_num* da_m, const lbl_num* pd_m);
double operateTrainField(string field, size_t fieldId, const vector<string>* tr_l, const vector<string>* te_l, 
	const lbl_num* ca_m, const lbl_num* da_m, const lbl_num* pd_m);

double operateField(string field, size_t fieldId, bool test, const vector<string>* tr_l, const vector<string>* te_l, 
	const lbl_num* ca_m, const lbl_num* da_m, const lbl_num* pd_m);
void parseDates(string field);



};


class CSV_reader {

public:

CSV_reader();

// test true si es test set, false si no, sería train. originalSet true si son los set originales,
// false si son los modificados para agregar temperatura, lluvias, etc
vector<Row*> parse(string file_path, bool test=false, bool originalSet=true);

void write(vector<Row*> input, string out);

void write(vector<double> input, string out);

void remove_column(vector<Row*> input, size_t pos);

private:


const vector<string>* tr_l; // train labels
const vector<string>* te_l; // test_labels
const lbl_num* ca_m; //category map
const lbl_num* da_m; // days map
const lbl_num* pd_m; // pd_district map

void maps_init();

};



#endif /* CSV_READER_H_ */
