#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//создание структур (труба и компрессорная станция)
struct Pipe
{
	float lenght = 0, diameter = 0;
	int status = -1, change_pipe = 0;
};

struct ComSt
{
	string name = "";
	double workshop = 0, working_ws = -1, change_comst = 0; 
	float effeciency = 0; 
};

//ошибка при вводе значений
float error(float i) { 
	while ((((cin>>i).fail())||(cin.peek() != '\n'))||(i<=0)) {
		cout << "Error!!! Input numeric value>0" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		
	}
	return i;
}

//проверка 
int check_option(int x) {
	while (((cin >> x).fail()) || (cin.peek() != '\n')) {
		cout << "Input correct number(0-7)" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}
//проверка статуса
void status(bool status) {
	if (status == true)
		cout<<"\nPipe works";
	else 
		cout<<"\nPipe is repairing";
}

bool status_cin(bool checkstatus) {
	while (((cin >> checkstatus).fail()) || (cin.peek() != '\n'))
	{
		cout << "Error!\nInput one of the predefined states:\n 0.In repair\n 1.In work\n ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return checkstatus;
}

//Проверка цехов
int integervalue(int x) {
	while ((((cin >> x).fail()) || (cin.peek() != '\n')) ||(x / trunc(x) != 1)||(x<=0)) {
		cout << "Error!!! Input integer value" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}

int workshop_cin(int x, int y) {
	while ((((cin>>x).fail())||(cin.peek()!='\n')) || (x > y) || (x <= 0)) {
		cout << "Error!!! Input numeric value" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}



void Addpipe(Pipe& p)
{
	cout << "\nInput lenght";
	p.lenght=error(p.lenght);
	cout << "\nInput diameter";
	p.diameter = error(p.diameter);
	cout << "\nChoose status of pipe(1-if repairing, 2 if works)";
	p.status = status_cin(p.status);
	 status(p.status);
}

void AddCS(ComSt& cs) {
	cout << "\nInput name";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, cs.name);
	cout << "\nNumber_of_workshop";
	cs.workshop = integervalue(cs.workshop);
	cout << "\nNumber_of_Working_workshop";
	cs.working_ws = workshop_cin(cs.working_ws, cs.workshop);
	cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
	cout << "\nEffeciency:" << cs.effeciency << "%" << endl;
}

void Viewall(Pipe& p, ComSt& cs) {
	cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter:" << p.diameter
		<< "\nStatus:"; status(p.status);
	cout << "\nComressor Station info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
		<< "\nNumber of working workshops: " << cs.working_ws << "\nEfficiency: " << cs.effeciency << "%" << endl;
}

void Editpipe(Pipe& p) {
	if (p.status==-1)
		cout << "\nTHere is no pipe to edit" << endl;
	else {
		cout << "\nInput new status of pipe (0-repairing, 1-working)" << endl;
		p.status = status_cin(p.status);
		status(p.status);
	}
}

void EditCS(ComSt& cs) {
	if (cs.working_ws == -1)
		cout << "\nThere is Compressor Station to edit" << endl;
	else {
		cout << "\nInput number of working workshops: " << endl;
		cs.working_ws = integervalue(cs.working_ws);
		cs.working_ws = workshop_cin(cs.working_ws, cs.workshop);
		cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
		cout << "\nEfficiency " << cs.effeciency << "%" << endl;
	}
}

void savetofile(Pipe& p, ComSt& cs) {
	ofstream file;
	file.open("Data.txt", ios::in);
	if (file.is_open()) {
		file << p.lenght << endl
			<< p.diameter << endl
			<< p.status << endl
			<< cs.name << endl
			<< cs.workshop << endl
			<< cs.working_ws << endl
			<< cs.effeciency <<"%"<< endl;
		file.close();
	}
}
void loadfromfile(Pipe& p, ComSt& cs) {
	ifstream file2;
	string line;
	file2.open("Data.txt");
	if (file2.is_open()) {
		getline(file2, line);
		p.lenght = stoi(line);
		getline(file2, line);
		p.diameter = stoi(line);
		getline(file2, line);
		p.status = stoi(line);
		getline(file2, line);
		cs.name = line;
		getline(file2, line);
		cs.workshop = stoi(line);
		getline(file2, line);
		cs.working_ws = stoi(line);
		getline(file2, line);
		cs.effeciency = stod(line);
	}
	else
		cout << "file doesn't exist";
}
int main() {
	int option = -1;
	Pipe p;
	ComSt cs;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objects 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 0. Exit\n";
		option = check_option(option);
		switch (option) {
		case 1: {
			Addpipe(p);
			break;
		}
		case 2: {
			AddCS(cs);
			break;
		}
		case 3: {
			Viewall(p, cs);
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
			savetofile(p, cs);
			break;
		}
		case 7: {
			loadfromfile(p, cs);
			cout << "Information was loaded from file" << endl;
			break;
		}
		case 0: {
			return 0;
		}
		default: cout << "Input correct number (1-7)";
			break;
		}

	}
}

