#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "ComSt.h"

using namespace std;

class work_with_graphs
{
public:
	unordered_map <int, Pipe> pipe_group;
	unordered_map <int, ComSt> cs_group;
	struct Graph {
		static int max_idg;
		int id;
		int id_entrance;
		int id_exit;
		int id_pipe;
	};
	void information();
	void save_data();
	void load_data();
	void editcs();
	vector<int> search_cs();
	void editpipe();
	vector<int> search_p();
	friend istream& operator>> (istream& in, work_with_graphs& s);
	friend ostream& operator<<(ostream& out, unordered_set<int> s);
	unordered_map <int, Graph> graphs;
	int check_pipe(int x);
	bool checking(int x);
	int edge(int x);
	int check_graph(int x);
	int check_existing(int x);
	bool check_only(int x, int y);
	bool check_cs(int x);
	bool check_objective(int x);
};
