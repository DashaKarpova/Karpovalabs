#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Pipe
{
	float lenght = 0, diameter = 0;
	int status = -1, change_pipe = 0;
};

struct ComSt
{
	string name = "";
	int workshop = 0, working_ws = -1, change_comst = 0; 
	float effeciency = 0; 
};

void error(int i) { 
	while ((!i)|| (i<=0)) {
		cout << "Error!!! Input numeric value" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> i;
	}
}

string status(int x) {
	if (x == 2)
		return ("Pipe works");
	else if (x == 1)
		return ("Pipe is repairing");
	else
		return ("Unknown");
}

int status_cin(int x){
	while ((x > 2) || (!x) || (x <= 0)) {
		cout << "Error!!! Input numeric value" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> x;
	}
	return x;
}

int workshop_cin(int x, int y) {
	while ((x > y) || (!x) || (x <= 0)) {
		cout << "Error!!! Input numeric value" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> x;
	}
	return x;
}

int main()
{
	int option = -1;
	Pipe p;
	ComSt cs;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objects 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 0. Exit\n";
		cin >> option;
		switch (option) {
		case 1: {
			cout << "\nInput lenght";
			cin >> p.lenght;
			error(int(p.lenght));
			cout << "\nInput diameter";
			cin >> p.diameter;
			error(int(p.diameter));
			cout << "\nChoose status of pipe(1-if repairing, 2 if works)";
			cin >> p.status;
			p.status = status_cin(p.status);
			cout << status(p.status) << endl;
			break;
		}
		case 2: {
			cout << "\nInput name";
			cin >> cs.name;
			cout << "\nNumber_of_workshop";
			cin >> cs.workshop;
			cout << "\nNumber_of_Working_workshop";
			cin >> cs.working_ws;
			cs.working_ws = workshop_cin(cs.working_ws, cs.workshop);
			cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
			cout << "\nEffeciency:" << cs.effeciency << "%" << endl;
			break;
		}
		case 3: {
			cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter:" << p.diameter
				<< "\nStatus:" << status(p.status) << endl;
			cout << "\nComressor Station info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
				<< "\nNumber of working workshops: " << cs.working_ws << "\nEfficiency: " << cs.effeciency << "%" << endl;
			break;

		}
		case 4: {
			if (p.status == -1)
				cout << "\nTHere is no pipe to edit" << endl;
			else {
				cout << "\nInput new status of pipe (1-repairing, 2-working)" << endl;
				cin >> p.status;
				p.status = status_cin(p.status);
				cout << status(p.status) << endl;
			}
			break;
		}
		case 5: {
			if (cs.working_ws == -1)
				cout << "\nThere is Compressor Station to edit" << endl;
			else {
				cout << "\nInput number of working workshops: " << endl;
				cin >> cs.working_ws;
				cs.working_ws = workshop_cin(cs.working_ws, cs.workshop);
				cs.effeciency = float(cs.working_ws) / float(cs.workshop) * 100;
				cout << "\nEfficiency " << cs.effeciency << "%" << endl;

			}
		
		}
		}
	}
	
}

