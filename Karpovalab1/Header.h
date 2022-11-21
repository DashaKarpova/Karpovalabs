#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<float.h>
#include "Pipe.h"
#include "ComSt.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
T getcorrectnumber(T min, T max) {
	int x;
	while ((cin >> x).fail() || (x < min) || (x > max)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type number (" << min << "-" << max << "):";
	}
	return x;
}

template <typename T>
ostream& operator<< (ostream& out, unordered_map <int, T>& p) {
	out << "Exiting id: ";
	for (auto& [i, obj] : p) {
		cout << i << " ";
	}
	out << endl;
	return out;
}

template <typename T>
ostream& operator<< (ostream& out, unordered_set<int, T>& p) {
	out << "Exiting id: ";
	for (auto& i : p) {
		cout << i << " ";
	}
	out << endl;
	return out;
}

template <typename T>
using filter_p = bool (*) (Pipe& p, T par);

template <typename T>
using filter_cs = bool(*) (ComSt& cs, T par);

template <typename T>
unordered_set <int> search_p_by_parametr(unordered_map <int, Pipe>& pipe_group, filter_p<T> f, T par) {
	unordered_set <int> id;
	for (auto& pipe : pipe_group) {
		if (f(pipe.second, par))
			id.insert(pipe.second.get_id());
	}
	return id;
}



template <typename T>
unordered_set <int> search_cs_by_parametr(unordered_map <int, ComSt>& cs_group, filter_cs<T> f, T par) {
	unordered_set <int> id;
	for (auto& cs : cs_group) {
		if (f(cs.second, par))
			id.insert(cs.second.get_idc());
	}
	return id;
}

