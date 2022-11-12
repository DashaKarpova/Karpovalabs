﻿#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<float.h>
#include "Pipe.h"
#include "ComSt.h"
#include "Header.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;
unordered_map<int, Pipe> pipe_group;
unordered_map<int, ComSt> cs_group;
unordered_set <int> iddpipe;
unordered_set <int> idcomst;

ostream& operator<< (ostream& out, unordered_set <int>& par) {
	out << "Exiting id: ";
	for (auto& i : par) {
		out << i << " ";
	}
	out << endl;
	return out;
}

bool check_p_name(Pipe& p, string name) {
	return (p.name.find(name) != string::npos);
}

bool check_p_status(Pipe& p, bool status) {
	return (p.status == status);
}

bool check_cs_name(ComSt& cs, string name) {
	return (cs.name.find(name) != string::npos);
}

bool check_unworking(ComSt& cs, double p) {
	return (cs.get_unused() >= p);
}



void Viewall(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ComSt>& cs_group) {
	for (auto& pipe : pipe_group) {
		cout << pipe.second << endl;
	}
	for (auto& cs : cs_group) {
		cout << cs.second << endl;
	}
}


void search_p(unordered_map <int, Pipe>& pipe_group, vector<int>& id) {
	int x;
	cout << "Search pipe by 1.name 2.status" << endl;
	x = getcorrectnumber(1, 2);
	if (x == 1) {
		string name;
		cout << "Enter the name of pipe: " << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		id = search_p_by_parametr(pipe_group, check_p_name, name);
	}
	else {
		bool k;
		cout << "Enter status of pipe (0 if repairing, 1 if in work): " << endl;
		k = getcorrectnumber(0, 1);
		id = search_p_by_parametr(pipe_group, check_p_status, k);
	}
}
void search_cs(unordered_map <int, ComSt>& cs_group, vector<int>& id) {
	int x;
	cout << "Search CS by 1.name 2.percentage of unused shops" << endl;
	x = getcorrectnumber(1, 2);
	if (x == 1) {
		string name;
		cout << "Enter the name of CS: " << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		id = search_cs_by_parametr(cs_group, check_cs_name, name);

	}
	else {
		double k;
		cout << "Enter the percentage of unused shops" << endl;
		k = getcorrectnumber(0, 100);
		id = search_cs_by_parametr(cs_group, check_unworking, k);
	}

}

void AddPipe() {
	iddpipe.insert(Pipe::max_id);
	Pipe p;
	cin >> p;
	pipe_group.insert({ p.get_id(),p });
}

void AddComSt() {
	idcomst.insert(ComSt::max_idcs);
	ComSt cs;
	cin >> cs;
	cs_group.insert({ cs.get_idc(),cs });
}

void EditPipes() {
	int edit;
	int id1;
	int x;
	if (pipe_group.size() != 0) {
		cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe" << endl;;
		edit = getcorrectnumber(1, 3);
		if (edit == 1) {
			cout << "1.Choose pipe to edit" << endl;
			cout << iddpipe;
			id1 = getcorrectnumber(0, (int)pipe_group.size());
			pipe_group[id1].edit_Pipe();

		}
		if (edit == 2) {
			vector <int> idp;
			cout << "Choose pipes by 1.filter 2.id" << endl;
			x = getcorrectnumber(1, 2);
			if (x == 1) {
				search_p(pipe_group, idp);
				if (idp.size() != 0) {
					cout << "Enter new status (0 if repairing, 1 if works)" << endl;
					bool s;
					s = getcorrectnumber(0, 1);
					for (auto& i : idp)
						pipe_group[i].status = s;
				}
				else
					cout << "There is no pipe to edit";
			
			}


			if (x == 2) {
				unordered_set <int> ids;
				cout << iddpipe;
				cout << "Enter the number of identifiers of pipe you want to edit" << endl;
				int n;
				n = getcorrectnumber(0, Pipe::max_id);
				cout << "Enter idetifiers of pipes" << endl;
				int y;
				for (int i = 0; i < n; i++) {
					y = getcorrectnumber(0, Pipe::max_id - 1);
					if (pipe_group.find(y) != pipe_group.end())
						ids.insert(y);
				}

				cout << "Enter new status (0 if repairing, 1 if works)" << endl;
				bool s;
				s = getcorrectnumber(0, 1);
				for (auto& i : ids)
					pipe_group[i].status = s;
			}
		}
		if (edit == 3) {
			cout << "Enter the id of pipe you want to delete" << endl;
			int n;
			n = getcorrectnumber(0, Pipe::max_id);
			pipe_group.erase(pipe_group.find(n));
			iddpipe.erase(iddpipe.find(n));
			cout << "Pipe was deleted";
		}
	}
	else
		cout << "There is no pipe to edit" << endl;

}

void EditComSt() {
	vector <int> idcs;
	if (cs_group.size() != 0) {
		cout << "1.Edit one CS 2.Edit CSs 3.Delete CS" << endl;
		int edit;
		edit = getcorrectnumber(1, 3);
		if (edit == 1) {
			int id;
			cout << "Choose CS to edit" << endl;
			id = getcorrectnumber(0, (int)cs_group.size());
			cs_group[id].edit_ComSt();
		}
		if (edit == 2) {
			unordered_set <int> idw;
			cout << "Choose  by 1.filter 2.id" << endl;
			int n;
			n = getcorrectnumber(1, 2);
			if (n == 2) {
				cout << "Enter the number of cs you want to edit";
				int y;
				y = getcorrectnumber(0, ComSt::max_idcs);
				cout << "Enter idetifiers of CSs" << endl;
				for (int i = 0; i < y; i++) {
					if (cs_group.find(i) != cs_group.end())
						idw.insert(i);

				}
				for (auto& i : idw)
					cs_group[i].edit_ComSt();

			}
			else {
				search_cs(cs_group, idcs);
				for (auto& i : idcs)
					cs_group[i].edit_ComSt();
			}

		}
		if (edit == 3) {
			cout << "1. identifier of one CS you want to delete 2.delete some CS" << endl;
			int d;
			d = getcorrectnumber(1, 2);
			if (d == 1) {
				cout << "Enter id of CS you want to delete" << endl;
				int n;
				n = getcorrectnumber(0, ComSt::max_idcs);
				cs_group.erase(cs_group.find(n));
			}
			else {
				unordered_set <int> idd;
				cout << "1.delete by filter 2.delete by id" << endl;
				int n;
				n = getcorrectnumber(1, 2);
				if (n == 2) {
					cout << "Enter the number of cs you want to edit";
					int y;
					y = getcorrectnumber(0, ComSt::max_idcs);
					cout << "Enter idetifiers of CSs" << endl;
					for (int i = 0; i < y; i++) {
						if (cs_group.find(i) != cs_group.end())
							idd.insert(i);
					}
					for (auto& i : idd)
						cs_group.erase(cs_group.find(i));
				}
				else {
					search_cs(cs_group, idcs);
					for (auto& i : idcs)
						cs_group.erase(cs_group.find(i));
					for (auto& i : idcomst)
						idcomst.erase(i);
				}

				cout << "CS was deleted";
			}
		}
	}
	else
		cout << "There is no CS to edit" << endl;

}

void Savetofile(){
	string x;
			cout << "Enter the name of your file: " << endl;
			cin >> x;
			ofstream file;
			file.open(x + ".txt");
			if (!file)
				cout << "file is not found" << endl;
			else {
				file << pipe_group.size() << " " << cs_group.size() << endl;
				for (auto pipe : pipe_group)
					pipe.second.save_pipe(file);
				for (auto cs : cs_group)
					cs.second.save_ComSt(file);
			}

}

void Loadfromfile() {
	string x;
	int p1, cs2;
	Pipe newpipe;
	ComSt newcs;
	cout << "Enter the name of your file:" << endl;
	cin >> x;
	ifstream file2;
	file2.open(x + ".txt");
	if (!file2)
		cout << "file is not found";
	else {
		Pipe::max_id = 0;
		ComSt::max_idcs = 0;
		pipe_group.clear();
		cs_group.clear();
		file2 >> p1 >> cs2;
		for (int i = 0; i < p1; i++) {
			newpipe.load_pipe(file2);
			pipe_group.insert({ newpipe.get_id(),newpipe });
			if (Pipe::max_id < newpipe.get_id())
				Pipe::max_id = newpipe.get_id();
		}
		for (int i = 0; i < cs2; i++) {
			newcs.load_ComSt(file2);
			cs_group.insert({ newcs.get_idc(),newcs });
			if (ComSt::max_idcs < newcs.get_idc())
				ComSt::max_idcs = newcs.get_idc();
		}
	}

}

void SearchPipes(){
	vector <int> x;
	if (pipe_group.size() != 0) {
		search_p(pipe_group, x);
		if (x.size() != 0) {
			for (auto& i : x)
				cout << pipe_group[i] << endl;
		}
		else
			cout << "There is no such pipe" << endl;
	}
	else
		cout << "There is no pipe to find" << endl;
}

void SearchComSt() {
	vector <int> x;
	if (cs_group.size() != 0) {
		search_cs(cs_group, x);
		if (x.size() != 0) {
			for (auto& i : x)
				cout << cs_group[i] << endl;
		}
		else
			cout << "There is no such CS";
	}
	else
		cout << "There is no CS to find" << endl;
}

int main() {
	int option = -1;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objects 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 8. Search Pipe 9. Search ComSt 0. Exit\n";
		option = getcorrectnumber(0,9);
		switch (option) {
		case 1: {
			AddPipe();
			break;
		}
		case 2: {
			AddComSt();
			break;
		}
		case 3: {
			Viewall(pipe_group, cs_group);
			break;

		}
		case 4: {
			EditPipes();
			break;
		}
		case 5: {
			EditComSt();
			break;
		}
		case 6: {
			Savetofile();
			break;
			}
		case 7: {
			Loadfromfile();
			break;
		}
		case 8: {
			SearchPipes();
			break;
		}
		case 9: {
			SearchComSt();
			break;
		}
		case 0: {
			return 0;
		}
		default: cout << "Input correct number (1-9)";
			break;
		}

	}
	return 0;
}

