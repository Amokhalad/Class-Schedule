#include <iostream>
#include <vector>
#include <string>
#include "Class.h"
using namespace std;
void insert_classes(Class* A, Class* B, Class* C);
void all_possible_schedule(Class* A, Class* B, Class* C, vector<vector<Professor*>> * schedules);
bool compare(Professor* A, Professor* B);
void print_schedules(vector<vector<Professor*>>* schedules);
void score(vector<vector<Professor*>>* schedules);
vector<vector<Professor*>>* max_RMP(vector<vector<Professor*>>* schedules);
void print_schedule(vector<Professor*> schedule);
void run(vector<vector<Professor*>>* schedules);

int main() {
	Class* ClassA = new Class("Math 1D");
	Class* ClassB = new Class("Math 2A");
	Class* ClassC = new Class("Math 2B");
	vector<vector<Professor*>>* schedules = new vector<vector<Professor*>>;

	insert_classes(ClassA, ClassB, ClassC);
	all_possible_schedule(ClassA, ClassB, ClassC, schedules);
	run(schedules);
}
void run(vector<vector<Professor*>>* schedules) {
	vector<vector<Professor*>>* optimal_schedules = new vector<vector<Professor*>>;
	optimal_schedules = max_RMP(schedules);
	print_schedules(optimal_schedules);
}

vector<vector<Professor*>>* max_RMP(vector<vector<Professor*>>* schedules) {
	double RMP_sum = 0;
	double Max_RMP = 0;
	vector<vector<Professor*>>* optimal_schedules = new vector<vector<Professor*>>;

	for (int i = 0; i < schedules->size(); ++i) {
		RMP_sum = 0;
		for (int j = 0; j < (*schedules)[i].size(); ++j) {
			RMP_sum += (*schedules)[i][j]->RMP_overall;
		}
		if (Max_RMP <= RMP_sum) {
			Max_RMP = RMP_sum;
		}
	}
	for (int i = 0; i < schedules->size(); ++i) {
		RMP_sum = 0;
		for (int j = 0; j < (*schedules)[i].size(); ++j) {
			RMP_sum += (*schedules)[i][j]->RMP_overall;
		}
		if (Max_RMP == RMP_sum) {
			optimal_schedules->push_back((*schedules)[i]);
		}
	}
	return optimal_schedules;
}
void all_possible_schedule(Class* A, Class* B, Class* C, vector<vector<Professor*>> * schedules) {
	vector<Professor* > A_prof = A->professors;
	vector<Professor* > B_prof = B->professors;
	vector<Professor* > C_prof = C->professors;
	vector<Professor* > Professors;
	
	for (int a = 0; a < A_prof.size(); ++a) {
		for (int b = 0; b < B_prof.size(); ++b) {
			for (int c = 0; c < C_prof.size(); ++c) {
				if (compare(A_prof[a], B_prof[b])) {
					if (compare(A_prof[a], C_prof[c])) {
						if (compare(B_prof[b], C_prof[c])) {
							vector<Professor* > Professors = { A_prof[a], B_prof[b] , C_prof[c] };
							schedules->push_back(Professors);
						}
					}
				}
			}
		}
	}
}

void print_schedules(vector<vector<Professor*>>* schedules) {

	for (int i = 0; i < schedules->size(); ++i) {
		int rmp_sum = 0;
		cout << "Schedule " << i + 1 << ":" << endl;
		for (int j = 0; j < (*schedules)[i].size(); ++j) {
			cout << fixed << setprecision(2);
			cout << (*schedules)[i][j]->class_name << ": " << (*schedules)[i][j]->name << ", " << (*schedules)[i][j]->start_time << "-" << (*schedules)[i][j]->end_time << ", " << (*schedules)[i][j]->days << endl;
			rmp_sum += (*schedules)[i][j]->RMP_overall;
		}
		cout << rmp_sum << endl;
		cout << endl;
	}
}

void print_schedule(vector<Professor*> schedule) {
	for (int i = 0; i < schedule.size(); ++i) {
		cout << fixed << setprecision(2);
		cout << schedule[i]->class_name << ": " << schedule[i]->name << ", " << schedule[i]->start_time << "-" << schedule[i]->end_time << ", " << schedule[i]->days << endl;
	}
}
bool compare(Professor* A, Professor* B) {
	bool same_days = false;

	for (int i = 0; i < A->days.length(); ++i) {
		for (int j = 0; j < B->days.length(); ++j) {
			if (A->days[i] == B->days[j]) {
				same_days = true;
				break;
			}
		}
	}

	if (!same_days) {
		return true;
	}
	
	double difference = abs(A->start_time - B->start_time);
	return A->start_time + difference > A->end_time;
}

void insert_classes(Class * A, Class * B, Class * C) {
	string prof = "Marc";
	string days = "TR";
	string time = "09:35 am-11:50 am";
	double RMP = 3.2;
	
	A->insert(prof, days, time, RMP);
	

	prof = "Shobha";
	days = "MW";
	time = "01:30 pm-03:45 pm";
    RMP = 3.1;
	A->insert(prof, days, time, RMP);
	

	prof = "Young";
	days = "TR";
	time = "01:30 pm-03:45 pm";
	RMP = 3;
	A->insert(prof, days, time, RMP);

	prof = "Jody";
	time = "09:35 am-11:50 am";
	days = "R";
	RMP = 3.1;
	B->insert(prof, days, time, RMP);

	prof = "Young";
	time = "01:30 pm-03:45 pm";
	days = "MW";
	RMP = 3;
	B->insert(prof, days, time, RMP);
	
	prof = "Young";
	time = "06:00 pm-08:15 pm";
	days = "TR";
	RMP = 3;

	B->insert(prof, days, time, RMP);

	
	prof = "Jeffrey";
	time = "07:30 am-09:45 am";
	days = "TR";
	RMP = 3.8;
	C->insert(prof, days, time, RMP);

	prof = "Jeffrey";
	time = "09:35 am-11:50 am";
	days = "MW";
	RMP = 3.8;
	C->insert(prof, days, time, RMP);

	prof = "Young";
	time = "06:00 pm-08:15 pm";
	days = "MW";
	RMP = 3;
	C->insert(prof, days, time, RMP);
}