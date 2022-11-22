#include <iostream>
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


unordered_set <int> search_p(unordered_map <int, Pipe>& pipe_group) {
	int x;
	unordered_set <int> id;
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
	return id;
}
unordered_set<int> search_cs(unordered_map <int, ComSt>& cs_group) {
	int x;
	unordered_set <int> id;
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
	return id;
}

void AddPipe() {
	Pipe p;
	cin >> p;
	pipe_group.insert({ p.get_id(),p });
}

void AddComSt() {
	ComSt cs;
	cin >> cs;
	cs_group.insert({ cs.get_idc(),cs });
}

void EditPipes(unordered_map<int, Pipe>& pipe_group) {
	if (pipe_group.size() != 0) {
		cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe" << endl;;
		int edit = getcorrectnumber(1, 3);
		if (edit == 1) {
			cout << "1.Choose pipe to edit" << endl;
			cout << pipe_group;
			int id = getcorrectnumber(0, INT_MAX);
			if (pipe_group.find(id) != pipe_group.end()) {
				pipe_group[id].edit_Pipe();
				cout << "Pipe was edited" << endl;
		}
			else
				cout << "There is no such pipe";
	}
		if (edit == 2) {
			cout << "Choose pipes by 1.filter 2.id" << endl;
			int x = getcorrectnumber(1, 2);
			if (x == 1) {
				unordered_set <int> id_group;
				int number;
				int id;
				auto idp = search_p(pipe_group);
					if (idp.size() != 0) {
						cout << idp << endl;
						cout << "Choose pipes to edit, 1- all pipes, 2- some pipes" << endl;
						int a = getcorrectnumber(1, 2);
						if (a == 1)
						{
							cout << "Enter new status (0 if repairing, 1 if works)" << endl;
							if (idp.size() != 0) {
								bool s;
								s = getcorrectnumber(0, 1);
								for (auto& i : idp) {
									pipe_group[i].status = s;
								}
							}
						}
						
						else
						{
							cout << "Enter idntifiers of pipes you want to edit" << endl;
							id = -1;
							int i = 0;
							while ((i < (int)idp.size()) || (id != -2)) {
								
								id = getcorrectnumber(-2, INT_MAX);
								if (idp.find(id) != idp.end())
									id_group.insert(id);
								else
								{
									cout << "There is no such pipe" << endl;;
								}
							}
							cout << "Enter new status (0 if repairing, 1 if works)" << endl;
							if (id_group.size() != 0) {
								bool s;
								s = getcorrectnumber(0, 1);
								for (auto& i : id_group) {
									pipe_group[i].status = s;
								}
							}
						}

						/*else
						 {
							cout << "Choose number of identifiers of pipes you want to edit" << endl;
							number = getcorrectnumber(1, (int)idp.size());
							for (int i = 0; id_group.size() < number; i++)
							{
								id = getcorrectnumber(0, INT_MAX);
								if (idp.find(id) != idp.end())
									id_group.insert(id);
								else
								{
									cout << "There is no such pipe" << endl;;
								}

							}

							cout << "Enter new status (0 if repairing, 1 if works)" << endl;
							if (id_group.size() != 0) {
								bool s;
								s = getcorrectnumber(0, 1);
								for (auto& i : id_group) {
									pipe_group[i].status = s;
								}
							}
						}*/
			}

			else {
				cout << "There is no such pipe";

			}
		}


			if (x == 2) {
				unordered_set <int> ids;
				cout << pipe_group;
				cout << "Enter the number of identifiers of pipe you want to edit" << endl;
				int n;
				int id;
				n = getcorrectnumber(1, INT_MAX );
				cout << "Enter idetifiers of pipes" << endl;
				for (int i = 0; ids.size() < n; i++) {
					id = getcorrectnumber(0, Pipe::max_id - 1);
					if (pipe_group.find(id) != pipe_group.end()) {
							ids.insert(id);
					}
					else
					{
						cout << "There is no such pipe" << endl;;
					}
				}
				cout << "Enter new status (0 if repairing, 1 if works)" << endl;
				bool s;
				s = getcorrectnumber(0, 1);
				for (auto& i : ids) {
					for (auto& i : ids)
						pipe_group[i].status = s;
				}
			}
	}
		if (edit == 3) {
			cout << "1. identifier of one pipe you want to delete 2.delete some pipes" << endl;
			int d;
			d = getcorrectnumber(1, 2);
			if (d == 1) {
				cout << pipe_group;
				cout << "Enter id of pipe you want to delete" << endl;
				int n;
				n = getcorrectnumber(0, Pipe::max_id - 1);
				while (pipe_group.find(n) == pipe_group.end()) {
					cout << "There is no such pipe" << endl;
					n = getcorrectnumber(0, Pipe::max_id - 1);
				}
				pipe_group.erase(pipe_group.find(n));
			}

			else {
				unordered_set <int> ids;
				cout << "1.delete by filter 2.delete by id" << endl;
				int action = getcorrectnumber(1, 2);
				if (action == 2) {
					cout << pipe_group;
					cout << "Enter the number of pipe you want to edit" << endl;;
					int n = getcorrectnumber(1, (int)pipe_group.size());
					cout << "Enter idetifiers of pipes" << endl;
					while (ids.size() < n)
					{
						int x = getcorrectnumber(0, Pipe::max_id - 1);
						if (pipe_group.find(x) != pipe_group.end())
							ids.insert(x);
						else
							cout << "There is no such pipe" << endl;
					}

					for (auto& id : ids) {
						pipe_group.erase(pipe_group.find(id));
					}

				}

				else {
					auto idp = search_p(pipe_group);
					if (idp.size() != 0) {
						for (auto& i : idp) {
							pipe_group.erase(pipe_group.find(i));
						}
						cout << "Pipe was deleted";
					}
					else {
						cout << "There is no such pipe";

					}

				}
			}
				
		}
	}



	else
		cout << "There is no pipe to edit" << endl;
	}

void EditComSt(unordered_map<int, ComSt>& cs_group) {
	vector <int> idcs;
	int id;
	if (cs_group.size() != 0) {
		cout << "1.Edit one CS 2.Edit CSs 3.Delete CS" << endl;
		int edit;
		int x;
		edit = getcorrectnumber(1, 3);
		if (edit == 1) {
			int id;
			cout << cs_group;
			cout << "Choose CS to edit" << endl;
			id = getcorrectnumber(0, INT_MAX);
			if (cs_group.find(id) != cs_group.end()) {
				cs_group[id].edit_ComSt();
				cout << "compressor_station was edited";
			}
			else
				cout << "There is no such cs" << endl;
		}
		if (edit == 2) {
			unordered_set <int> idw;
			cout << "Choose by 1.filter 2.id" << endl;
			int n;
			n = getcorrectnumber(1, 2);
			if (n == 2) {
				cout << cs_group;
				cout << "Enter the number of cs you want to edit" << endl;
				int y;
				y = getcorrectnumber(1, INT_MAX);
				cout << "Enter idetifiers of CSs" << endl;
				for (int i = 0; idw.size() < y; i++) {
					cin >> x;
					if (cs_group.find(x) != cs_group.end())
						idw.insert(x);
					else {

						cout << "There is no such compressor_station" << endl;
					}
				}
				for (auto& id : idw)

					cs_group[id].edit_ComSt();
			}

			else {
				unordered_set <int> id_group;
				int number;
				auto idcs = search_cs(cs_group);
				if (idcs.size() != 0) {
					cout << idcs << endl;
					cout << "Choose cs to edit 1- all css, 2- some css" << endl;
					int a = getcorrectnumber(1, 2);
					if (a == 1)
					{
						for (auto& i : idcs)
							cs_group[i].edit_ComSt();
					}
					else {
						cout << "Choose number of identifiers of pipes you want to edit" << endl;
						number = getcorrectnumber(1, (int)idcs.size());
						for (int i = 0; id_group.size() < number; i++) {
							id = getcorrectnumber(0, INT_MAX);
							if (idcs.find(id) != idcs.end())
								id_group.insert(id);
							else
								cout << "There is no such cs" << endl;
						}
						for (auto& i : id_group)
							cs_group[i].edit_ComSt();
					}
				}

				else {
					cout << "There is no such compressor station";

				}

			}
		}
		if (edit == 3) {
			cout << "1. identifier of one compressor station you want to delete 2.delete some CS" << endl;
			int d;
			d = getcorrectnumber(1, 2);
			if (d == 1) {
				cout << cs_group;
				cout << "Enter id of CS you want to delete" << endl;
				int n;
				n = getcorrectnumber(0, ComSt::max_idcs - 1);
				while (cs_group.find(n) == cs_group.end()) {
					cout << "There is no such cs" << endl;
					n = getcorrectnumber(0, ComSt::max_idcs - 1);
				}
				cs_group.erase(cs_group.find(n));

			}
			else {
				unordered_set <int> idd;
				cout << "1.delete by filter 2.delete by id" << endl;
				int n;
				n = getcorrectnumber(1, 2);
				if (n == 2) {
					cout << cs_group;
					cout << "Enter the number of cs you want to delete" << endl;
					int y;
					int x;
					y = getcorrectnumber(1, (int)cs_group.size());
					cout << "Enter idetifiers of CSs" << endl;
					for (int i = 0; i < y; i++) {
						x = getcorrectnumber(0, ComSt::max_idcs);
						if (cs_group.find(x) != cs_group.end())
							idd.insert(x);
						else
						{
							i = i - 1;
							cout << "There is no such CS" << endl;
						}
					}
					for (auto& i : idd) {
						cs_group.erase(cs_group.find(i));
					}
				}
				else {
					auto idcs=search_cs(cs_group);
					if (idcs.size() != 0) {
						for (auto& i : idcs) {
							cs_group.erase(cs_group.find(i));
						}
					}
					else {
						cout << "There is no such cs" << endl;


					}
				}

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
				file.close();
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
		file2.close();
	}

}

void SearchPipes(){
	if (pipe_group.size() != 0) {
		auto x= search_p(pipe_group);
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
		auto x=search_cs(cs_group);
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
			EditPipes(pipe_group);
			break;
		}
		case 5: {
			EditComSt(cs_group);
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

