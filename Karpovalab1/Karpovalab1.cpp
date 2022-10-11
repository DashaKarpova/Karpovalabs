#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//создание структур (труба и компрессорная станция)
struct Pipe
{
	int lenght = 0, diameter = 0;
	int status = -1, change_pipe = 0;
};

struct ComSt
{
	string name = "";
	int workshop = 0, working_ws = -1, change_comst = 0; 
	float effeciency = 0; 
};

//ошибка при вводе значений
int checkintegervalue() { 
	int i;
	while ((((cin>>i).fail())||(cin.peek() != '\n'))||(i<=0)) {
		cout << "Error!!! Input numeric value without gap" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		
	}
	return i;
}

//проверка 
int check_option() {
	int x;
	while (((cin >> x).fail()) || (cin.peek() != '\n')) {
		cout << "Input correct number(0-7)" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}
//проверка статуса
void outputstatus(bool status) {
	if (status == true)
		cout<<"\nPipe works";
	else 
		cout<<"\nPipe is repairing";
}

bool status() {
	bool checkstatus;
	while (((cin >> checkstatus).fail()) || (cin.peek() != '\n'))
	{
		cout << "Error!\nInput one of the predefined states:\n 0.In repair\n 1.In work\n ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return checkstatus;
}

//Проверка цехов


int correctworkingws( int max) {
	int workshop;
	while ((((cin>>workshop).fail())||(cin.peek()!='\n')) || (workshop > max) || (workshop < 0)) {
		cout << "Error!!! Input numeric value" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return workshop;
}



void Addpipe(Pipe& p)
{
	cout << "\nInput lenght";
	p.lenght= checkintegervalue();
	cout << "\nInput diameter";
	p.diameter = checkintegervalue();
	cout << "\nChoose status of pipe(0 if repairing, 1 if works)";
	p.status = status();
	 outputstatus(p.status);
}

void AddCS(ComSt& cs) {
	cout << "\nInput name";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, cs.name);
	cout << "\nNumber_of_workshop";
	cs.workshop = checkintegervalue();
	cout << "\nNumber_of_Working_workshop";
	cs.working_ws = correctworkingws(cs.workshop);
	cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
	cout << "\nEffeciency:" << cs.effeciency << "%" << endl;
}

void Viewall(Pipe& p, ComSt& cs) {
	if (p.status != -1) {
		cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter:" << p.diameter
			<< "\nStatus:"; outputstatus(p.status);
	}
	else {
		cout << "\nPipe info: There is no pipe";
	}
	if (cs.workshop != 0) {
		cout << "\nComressor Station info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
			<< "\nNumber of working workshops: " << cs.working_ws << "\nEfficiency: " << cs.effeciency << "%" << endl;
	}
	else {
		cout << "\nCompressor Station info: There is no Comressor Station";
	}
}

void Editpipe(Pipe& p) {
	if (p.status==-1)
		cout << "\nTHere is no pipe to edit" << endl;
	else {
		cout << "\nInput new status of pipe (0-repairing, 1-working)" << endl;
		p.status = status();
		outputstatus(p.status);
	}
}

void EditCS(ComSt& cs) {
	if (cs.working_ws == -1)
		cout << "\nThere is no Compressor Station to edit" << endl;
	else {
		cout << "\nInput number of working workshops: " << endl;
		cs.working_ws = correctworkingws(cs.workshop);
		cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
		cout << "\nEfficiency " << cs.effeciency << "%" << endl;
	}
}

void savetofile(Pipe& p, ComSt& cs) {
	ofstream file;
	file.open("Data.txt");
	file << (p.status != -1) << endl;
	file << (cs.workshop > 0) << endl;
	if (file.is_open()) {
		if (p.status != -1) {
			file << p.lenght << endl
				<< p.diameter << endl
				<< p.status << endl;
		}
		if (cs.workshop > 0) {
			file << cs.name << endl
				<< cs.workshop << endl
				<< cs.working_ws << endl
				<< cs.effeciency << "%" << endl;
		}
		file.close();
	}
}
void loadfromfile(Pipe& p, ComSt& cs) {
	ifstream file2;
	string line;
	int amountpipe;
	int amountcs;
	file2.open("Data.txt");
	if (file2.is_open()) {
		file2 >> amountpipe >> amountcs;
		if (amountpipe < 1 && amountcs < 1) {
			cout << "\nFile doesn't have data" << endl;
		}
		if (amountpipe > 0 && amountcs == 0) {
	
			file2 >> p.lenght >> p.diameter >> p.status;
			if (amountpipe == 0 && amountcs > 0) {

				file2.ignore();
				getline(file2, cs.name);
				file2 >> cs.workshop >> cs.working_ws >> cs.effeciency;
			}
			else {

				file2 >> p.lenght >> p.diameter >> p.status;
				file2.ignore();
				getline(file2, cs.name);
				file2 >> cs.workshop >> cs.working_ws >> cs.effeciency;
			}
		}
	}
}
int main() {
	int option = -1;
	Pipe p;
	ComSt cs;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objects 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 0. Exit\n";
		option = check_option();
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

