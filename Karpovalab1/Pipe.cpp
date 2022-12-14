#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include "Header.h"
using namespace std;
//unordered_map<int, Pipe> pipe_group;

string Pipe:: outputstatus() {
	return status ? "works" : "is repearing";
}

int Pipe::max_id = 1;

istream& operator>> (istream& in, Pipe& p) {
	cout << "\n Index of pipe" << p.idpipe;
	cout << "\nInput name ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, p.name);
	cout << "\n Input lenght ";
	p.lenght = getcorrectnumber(0.0, DBL_MAX);
	cout << "\n Input diameter ";
	p.diameter = getcorrectnumber(0.0, DBL_MAX);
	cout << "\nChoose status of pipe(0 if repairing, 1 if works)";
	p.status = getcorrectnumber(0, 1);
	cout << p.outputstatus() << endl;
	return in;
}

ostream& operator<<(ostream& out, Pipe& p) {
	out << "\nIndex of pipe: " << p.idpipe << "\nPipe info: " << "\nName: " << p.name << "\nLenght: " << p.lenght << "\nDiameter : " << p.diameter
		<< "\nStatus: " << p.outputstatus() << endl;
	return out;
}

void Pipe::edit_Pipe() {
	cout << "Status: " << outputstatus() << endl;
	cout << "Enter new status(0- repaire, 1- work)" << endl;
	status = getcorrectnumber(0, 1);
	cout << outputstatus();
}


void Pipe::save_pipe(ofstream& file) {
	file << idpipe << endl << name << endl << lenght << endl << diameter << endl << status << endl;
}

void Pipe::load_pipe(ifstream& file2) {
	file2 >> idpipe;
	getline(file2, name);
	getline(file2, name);
	file2 >> lenght;
	file2 >> diameter;
	file2 >> status;
}
