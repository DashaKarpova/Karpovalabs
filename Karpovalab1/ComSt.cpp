#include "Header.h"
#include "ComSt.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<float.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int ComSt::max_idcs = 0;

istream& operator>>(istream& in, ComSt& cs) {
	cout << "\n Index of ComSt " << cs.idcomst;
	cout << "\nInput name";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(in, cs.name);
	cout << "\nNumber_of_workshop";
	cs.workshop = getcorrectnumber(0, INT_MAX);
	cout << "\nNumber_of_Working_workshop";
	cs.working_ws = getcorrectnumber(0, cs.workshop);
	cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
	cout << "\nEffeciency:" << cs.effeciency << "%" << endl;
	return in;
}

ostream& operator<< (ostream& out, ComSt& cs) {
	out << "\nIndex of CS: " << cs.idcomst << "\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
		<< "\nNumber of working workshops: " << cs.working_ws << "\nEffeciency: "
		<< cs.effeciency << "%" << endl;
	return out;
}

void ComSt::edit_ComSt() {
	cout << "Workshops " << workshop << endl;
	cout << "Working workshops " << working_ws << endl;
	cout << "Enter new number of working workshops" << endl;
	working_ws = getcorrectnumber(0, workshop);
}

void ComSt::save_ComSt(ofstream& file) {
	file << idcomst << endl << name << endl
		<< workshop << endl << working_ws << endl << effeciency << endl;
}


void ComSt::load_ComSt(ifstream& file2) {
	file2 >> idcomst;
	file2.ignore();
	getline(file2, name);
	file2 >> workshop;
	file2 >> working_ws;
	file2 >> effeciency;

}