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
 
template <typename T>
T getcorrectnumber(T min, T max) {
	int x;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type number (" << min << "-" << max << "):";
		cin >> x;
	} while (cin.fail() || x<min || x>max);
	return x;
}


template <typename T>
using filter_p = bool (*) (Pipe& p, T par);
template <typename T>
using filter_cs = bool(*) (ComSt& cs, T par);
template <typename T>
vector <int> search_p_by_parametr(unordered_map <int, Pipe>& pipe_group, filter_p<T> f, T par) {
	vector <int> id;
	for (auto& pipe : pipe_group) {
		if (f(pipe.second, par))
			id.push_back(pipe.second.get_id());
	}
	return id;
}

template <typename T>
vector <int> search_cs_by_parametr(unordered_map <int, ComSt>& cs_group, filter_cs<T> f, T par) {
	vector <int> id;
	for (auto& cs : cs_group) {
		if (f(cs.second, par))
			id.push_back(cs.second.get_idd());
	}
	return id;
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

istream& operator>> (istream& in, Pipe& p) {
	cout << "\n Index of pipe" << p.idpipe;
	cout << "\nInput name ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	getline(cin, p.name);
	cout << "\n Input lenght ";
	p.lenght = getcorrectnumber(0.0, DBL_MAX);
	cout << "\n Input diameter ";
	p.diameter = getcorrectnumber(0.0, DBL_MAX);
	cout << "\nChoose status of pipe(0 if repairing, 1 if works)";
	p.status = getcorrectnumber(0,1);
	cout << outputstatus(p.status) << endl;
	return in;
}

istream& operator>>(istream& in, ComSt& cs) {
	cout << "\n Index of ComSt " << cs.idcomst;
	cout << "\nInput name";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(in, cs.name);
	cout << "\nNumber_of_workshop";
	cs.workshop = getcorrectnumber(0, INT_MAX);
	cout << "\nNumber_of_Working_workshop";
	cs.working_ws = getcorrectnumber(0,cs.workshop);
	cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
	cout << "\nEffeciency:" << cs.effeciency << "%" << endl;
	return in;
}

ostream& operator<<(ostream& out, Pipe& p) {
	out<<"\nIndex of pipe: "<<p.idpipe<< "\nPipe info: " << "\nName: " << p.name << "\nLenght: " << p.lenght << "\nDiameter : " << p.diameter
		<< "\nStatus: " << outputstatus(p.status) << endl;
	return out;
}

ostream& operator<< (ostream& out, ComSt& cs) {
	out << "\nIndex of CS: " << cs.idcomst << "\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
		<< "\nNumber of working workshops: " << cs.working_ws << "\nEffeciency: "
		<< cs.effeciency << "%" << endl;
	return out;
}

string outputstatus(bool status) {
	if (status == true)
		return ("Pipe works");
	else 
		return ("Pipe is repairing");
}




void Viewall(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ComSt>& cs_group) {
	for (auto& pipe : pipe_group) {
		cout << pipe.second << endl;
	}
	for (auto& cs : cs_group) {
		cout << cs.second << endl;
	}
}

void Pipe::edit_Pipe() {
	cout << "Status: " << outputstatus(status) << endl;
	cout << "Enter new status(0- repaire, 1- work)" << endl;
	status = getcorrectnumber(0, 1);
	cout << outputstatus(status);
}

void ComSt::edit_ComSt() {
	cout << "Workshops " << workshop << endl;
	cout << "Working workshops " << working_ws << endl;
	cout << "Enter new number of working workshops" << endl;
	working_ws = getcorrectnumber(0, workshop);
}

void Pipe::save_pipe(ofstream& file) {
	file << idpipe << endl << name << endl << lenght << endl << diameter << endl << status << endl;
}

void ComSt::save_ComSt(ofstream& file) {
	file << idcomst << endl << name << endl
		<< workshop << endl << working_ws << endl << effeciency<< endl;
}

void Pipe::load_pipe(ifstream& file2){
	file2 >> idpipe;
	getline(file2, name);
	getline(file2, name);
	file2 >> lenght;
	file2 >> diameter;
	file2 >> status;
}

void ComSt::load_ComSt(ifstream& file2) {
	file2 >> idcomst;
	getline(file2, name);
	getline(file2, name);
	file2 >> workshop;
	file2 >> working_ws;
	file2 >> effeciency;

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



int main() {
	int option = -1;
	unordered_map<int, Pipe> pipe_group;
	unordered_map<int, ComSt> cs_group;
	unordered_set <int> iddp;
	unordered_set <int> iddcs;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objects 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 8. Search Pipe 9. Search ComSt 0. Exit\n";
		option = getcorrectnumber(0,9);
		switch (option) {
		case 1: {
			iddp.insert(Pipe::max_id);
			Pipe p;
			cin >> p;
			pipe_group.insert({ p.get_id(),p });
			cout << iddp.size();
			break;
		}
		case 2: {
			ComSt cs;
			cin >> cs;
			cs_group.insert({ cs.get_idc(),cs });
			break;
		}
		case 3: {
			Viewall(pipe_group, cs_group);
			break;

		}
		case 4: {
			int edit;
			int id1;
			int x;
			Pipe p;
			if (pipe_group.size() != 0) {
				cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe" << endl;;
				edit = getcorrectnumber(1, 3);
				if (edit == 1) {
					cout << "1.Choose pipe to edit" << endl;
					cout<< iddp;
					id1 = getcorrectnumber(0, (int)pipe_group.size());
					pipe_group[id1].edit_Pipe();

				}
				if (edit == 2) {
					vector <int> idp;
					cout << "Choose pipes by 1.filter 2.id" << endl;
					x = getcorrectnumber(1, 2);
					if (x == 1) {
						search_p(pipe_group, idp);
						cout << "Enter new status (0 if repairing, 1 if works)" << endl;
						bool s;
						s = getcorrectnumber(0, 1);
						for (auto& i : idp)
							pipe_group[i].status = s;
					}


					if (x == 2) {
						unordered_set <int> ids;
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
					iddp.erase(iddp.find(n));
					cout << "Pipe was deleted";
				}
			}
			else
				cout << "There is no pipe to edit" << endl;
			break;
		}
		case 5: {
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
						y = getcorrectnumber(0, ComSt::max_idc);
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
						n = getcorrectnumber(0, ComSt::max_idc);
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
							y = getcorrectnumber(0, ComSt::max_idc);
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
							for (auto& i : iddcs)
								iddcs.erase(i);
						}

						cout << "CS was deleted";
					}
				}
			}
			else
				cout << "There is no CS to edit" << endl;
			break;
		}
		case 6: {
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
		case 7: {
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
				ComSt::max_idc = 0;
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
					if (ComSt::max_idc < newcs.get_idc())
						ComSt::max_idc = newcs.get_idc();
				}
			}
		}
		case 8: {
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
			break;
		}
		case 9: {
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
			break;
		}
		case 0: {
			return 0;
		}
		default: cout << "Input correct number (1-7)";
			break;
		}

	}
	return 0;
}

