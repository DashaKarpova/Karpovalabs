#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<float.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//создание классов (труба и компрессорная станция)
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
	int get_id(){ return idpipe; }

private:
	double lenght = 0, diameter = 0;
	int idpipe = 0;

};

class ComSt
{public:
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
private:
	int workshop, working_ws, idcomst;
	double effeciency;
	
};

int Pipe::max_id = 0;
int ComSt::max_idc = 0;


//проверка 
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

//операторы ввода и вывода

istream& operator>> (istream& in, Pipe& p) {
	cout << "\n Index of pipe" << p.idpipe;
	cout << "\nInput name ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	getline(in, p.name);
	cout << "\n Input lenght ";
	p.lenght = getcorrectnumber(0.0, DBL_MAX);
	cout << "\n Input diameter ";
	p.diameter = getcorrectnumber(0.0, DBL_MAX);
	cout << "\nChoose status of pipe(0 if repairing, 1 if works)";
	p.status = getcorrectnumber(0,1);
	outputstatus(p.status);

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
//проверка статуса
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

int main() {
	int option = -1;
	ComSt cs;
	unordered_map<int, Pipe> pipe_group;
	unordered_map<int, ComSt> cs_group;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objects 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 0. Exit\n";
		option = getcorrectnumber(0,7);
		switch (option) {
		case 1: {
			Pipe p;
			cin >> p;
			pipe_group.insert({ p.get_id(),p });
			break;
		}
		case 2: {
			ComSt cs;
			cin >> cs;
			cs_group.insert({ cs.get_idc(), cs });
			break;
		}
		case 3: {
			Viewall(pipe_group, cs_group);
			break;

		}
		case 4: {
			Editpipe(p);
			break;
		}
		case 5: {
			EditCS(cs);
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
		case 0: {
			return 0;
		}
		default: cout << "Input correct number (1-7)";
			break;
		}

	}
}

