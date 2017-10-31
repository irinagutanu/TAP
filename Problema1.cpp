#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 

using namespace std;

ifstream in("acoperire.in");
ofstream out("acoperire.out");

struct interval{
	long long int start, end;
};

void setInterval(interval &i, long long int st, long long int fn){
	i.start = st;
	i.end = fn;
}

bool SortingFunction(interval unit1, interval unit2){
	return unit1.start < unit2.start;
}

void ReadData(vector<interval> &units, interval &unitToCover){
	int numberOfUnits;
	
	in >> unitToCover.start >> unitToCover.end;
	in >> numberOfUnits;

	for( int i=0; i < numberOfUnits; i++){
		long long int st, fn;
		in >> st >> fn;
		interval unit;
		setInterval(unit, st, fn);
		units.push_back(unit);
	}
}

bool GoodInterval(interval &unit, int &leftLimitOfInterval, int& maxUnit){
	if( unit.end > leftLimitOfInterval && 
		unit.end > maxUnit){
		return 1;
	}
	return 0;
}

int FindCover(vector<interval> &units, int &leftLimitOfInterval){
	int maxUnit = -1, found = 0;
	for(unsigned int i=0; i < units.size() && units[i].start <= leftLimitOfInterval; i++){
		if( GoodInterval(units[i], leftLimitOfInterval, maxUnit)){
			found = 1;
			maxUnit = units[i].end;
		}
	}
	leftLimitOfInterval = maxUnit;
	if( found == 0 ) return -1;
	return 1;
}

int Covering(vector<interval> &units, interval &unitToCover){
	int coveringUnits = 0, leftLimitOfInterval = unitToCover.start;
	interval chosenInterval;
	setInterval(chosenInterval, -1000, -1000);
	
	int result = FindCover(units, leftLimitOfInterval);

	if( result == -1) return -1;
	else{
		coveringUnits++;
		while( leftLimitOfInterval < unitToCover.end){
			result = FindCover(units, leftLimitOfInterval);
			if( result == -1) return -1;
			else coveringUnits++;
		}
	}
	return coveringUnits;
}

int main(){
	vector<interval> units;
	interval unitToCover;

	ReadData(units, unitToCover);

	sort(units.begin(), units.end(), SortingFunction);

	int result = Covering(units, unitToCover);

	out << result;
	
	return 0;
}