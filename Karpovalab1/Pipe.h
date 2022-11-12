#pragma once
#include <iostream>
#include <string>
#include<vector>
#include <string>
#include<float.h>
#include <fstream>
#include<float.h>

using namespace std;

class Pipe
{
public:
	static int max_id;
	string name = "";
	bool status = 0;
	Pipe() {
		idpipe = max_id++;
	}
	friend istream& operator>> (istream& in, Pipe& p);
	friend ostream& operator<< (ostream& out, Pipe& p);
	void edit_Pipe();
	void save_pipe(ofstream& file);
	void load_pipe(ifstream& file);
	int get_id() { return idpipe; };

private:
	double lenght = 0, diameter = 0;
	int idpipe = 0;

};

int Pipe::max_id = 0;

