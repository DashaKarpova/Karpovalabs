#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<float.h>


using namespace std;

class ComSt
{
public:
	string name = "";
	static int max_idcs;
	ComSt() {
		idcomst = max_idcs++;
	}
	friend istream& operator>> (istream& in, ComSt& cs);
	friend ostream& operator<< (ostream& out, ComSt& cs);
	void edit_ComSt();
	void save_ComSt(ofstream& file);
	void load_ComSt(ifstream& file);
	int get_idc() { return idcomst; };
	double get_unused() { return (((double)workshop - (double)working_ws) / (double)workshop) * 100; };
private:
	int workshop, working_ws, idcomst;
	double effeciency;

}; 
