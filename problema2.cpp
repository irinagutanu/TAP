#include <iostream>
#include <stdlib.h>
#include <fstream>
#define Max 10000
using namespace std;

ifstream in("deadline.in");
ofstream out("deadline.out");

struct date{
	int lenght, deadline;
};

int compare(const void *a, const void *b){
	struct date t1 = *(date*) a;
	struct date t2 = *(date*) b;
	if( t1.deadline < t2.deadline) return -1;
	if( t1.deadline == t2.deadline) return 0;
	return 1;
}

void readInfo(struct date (&activity)[Max], int &numberActivities){
	in >> numberActivities;
	for( int i=0; i<numberActivities; i++){
		in >> activity[i].lenght >> activity[i].deadline;
	}
}

int main(){
	struct date activity[Max];
	int numberActivities;
	readInfo(activity, numberActivities);
	
	qsort(activity, numberActivities, sizeof(date), compare);
	int start = 0, delay = 0, wholedelay = 0;
	for( int i=0; i<numberActivities; i++){
		out << "Activitatea "<< i <<":   "<< activity[i].lenght <<"-" <<activity[i].deadline << endl;
		out << "Intervalul ["<< start << ", "<< start+activity[i].lenght <<")" << endl;
		delay = start + activity[i].lenght - activity[i].deadline;
		if(delay < 0){
			out << "Intarziere: "<< 0 << endl;
		}
		else{
			out << "Intarziere: "<< delay << endl;
			wholedelay = wholedelay + delay;
		}
		start = start+activity[i].lenght;
	}
	out << endl;
	out << "Intarziere totala: " << wholedelay << endl;
	return 0;
}