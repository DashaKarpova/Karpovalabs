#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include<vector>
#include<float.h>
#include <fstream>

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
	string outputstatus(bool status);
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



