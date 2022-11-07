#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<float.h>
#include <unordered_map>
#include <unordered_set>

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
	int get_id() { return idpipe; }

private:
	double lenght = 0, diameter = 0;
	int idpipe = 0;

};

class ComSt
{
public:
	string name = "";
	static int max_idc;
	ComSt() {
		idcomst = max_idc++;
	}
	friend istream& operator>> (istream& in, ComSt& cs);
	friend ostream& operator<< (ostream& out, ComSt& cs);
	void edit_ComSt();
	void save_ComSt(ofstream& file);
	void load_ComSt(ifstream& file);
	int get_idc() { return idcomst; }
	double get_unused() { return (((double)workshop - (double)working_ws) / (double)workshop) * 100; }
private:
	int workshop, working_ws, idcomst;
	double effeciency;

};

int Pipe::max_id = 0;
int ComSt::max_idc = 0;

unordered_set <int> iddp;
unordered_set <int> iddcs;