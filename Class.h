#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

double convv(string time) {
	int hour = stoi(time.substr(0, 2));
	int minute = stoi(time.substr(3, 2));
	string period = time.substr(6, 2);
	
	

	string military_time;

	if (period == "pm" && hour >= 1 && hour != 12) {
		hour += 12;
	}
	else if (hour == 12 && period == "am") {
		hour = 0;
	}
	return hour + (minute * (1.0 / 60.0));
}

struct Professor {

	Professor() {
		start_time = 0;
		end_time = 0;
		RMP_overall = 0;
	}
	string name;
	string class_name;
	string days;
	double start_time; // military time
	double end_time;
	double RMP_overall;
};

class Class
{
public:
	Class(string class_name) : class_name(class_name) {};
	void insert(string prof, string days_, string time, double RMP) {
		double start = convv(time.substr(0,8));
		double end = convv(time.substr(9, 8));
		
		professors.push_back(new Professor);
		professors.back()->name = prof;
		professors.back()->class_name = class_name;
		professors.back()->days = days_;
		professors.back()->start_time = start;
		professors.back()->end_time = end;
		professors.back()->RMP_overall = RMP;
	}

	void print() {
		cout << class_name << ": " << endl;
		for (const auto& x : professors) {
			cout << x->name;
			cout << ", " << x->start_time << "-" << x->end_time << ", " << x->days << ", " << x->RMP_overall << endl;
			cout << fixed << setprecision(2);
		}
		cout << endl;
	}
	vector<Professor* > professors;
	string class_name;
};




