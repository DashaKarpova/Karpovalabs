#include <iostream>
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

void f(int i) {
	cout << "Error!!! Input numeric value" << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cin >> i;
}

int main()
{
	int option = -1;
	Pipe p;
	ComSt cs;

	while (option) {
		cout << "\nChoose Option:\n 1.Add pipe 2. Add compressor station 3.View all objets 4. Edit pipe 5. Edit Comressor Station 6. Save 7. Load 0. Exit\n";
		cin >> option;
		if (option == 1) {
			cout << "\nInput lenght ";
			cin >> p.lenght;
			if (!p.lenght) {
				do {
					f(p.lenght);
				} while (!p.lenght);
			}
			cout << "\nInput diameter ";
			cin >> p.diameter;
			if (!p.diameter) {
				do {
					f(p.diameter);
				} while (!p.diameter);

			}
			cout << "\nInput status of pipe (1-repairing, 2-working)";
			cin >> p.status;
			if ((p.status > 2) || (p.status < 0) || (!p.status)) {
				do {
					f(p.status);
				} while ((p.status > 2) || (p.status < 0) || (!p.status));

			}
		}		if (p.status == 1) {
			cout << "\nPipe is repairing\n" << endl;
		}
		else {
			cout << "\nPipe is working\n" << endl;
		}

	}
}

