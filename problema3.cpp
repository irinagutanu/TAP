#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

ifstream in("subsir.in");
ofstream out("subsir.out");

void readData(vector<int> &v){
	int value, val;
	in >> value;
	for( int i=0; i < value; i++){
		in >> val;
		v.push_back(val);
	}
}

int binarySearchModified(vector<stack<int> > &seq, int &value){
	int left = 0, right = seq.size()-1, mij;
	if( value > seq[right].top()) return -1;
	else if( value <= seq[left].top()) return 0;
	else{

		while(left <= right){
			mij = (left + right)/2;
			if( value == seq[mij].top()) return mij;

			else if(value < seq[mij].top()){
				if(value > seq[mij - 1].top()) return mij;
				else right = mij - 1;
			}
			else if(value > seq[mij].top()){
				if(value < seq[mij+1].top()) return mij+1;
				else left = mij + 1;
			}

			if( value > seq[right].top()) return -1;
			else if( value < seq[left].top()) return left;
		}
	}
}


void BuildSequence(vector<stack<int> > &seq, vector<int> &vect ){

	int elem = vect[0];
	stack<int> interm;
	interm.push(elem);
	seq.push_back(interm);
	
	for( int j=1; j < vect.size(); j++){
		int extras = vect[j];
		int pos = binarySearchModified(seq, extras);
		if(pos != -1){
			seq[pos].push(extras);
		}
		else{
			stack<int> inter;
			inter.push(extras);
			seq.push_back(inter);
		}
	}
}

void printStack(stack<int> s){
	if( s.empty() ) return;
	int top = s.top();
	s.pop();
	printStack(s);
	out << top << " "; 
}

void print(vector<stack<int> > seq){
	for( int i=0; i < seq.size(); i++){
		out << i+1 << ": ";
		printStack(seq[i]);
		out << endl;
	}
}

int LowestValueOnTop(vector<stack<int> > &seq){
	int min = 10000, j=0, lastPoint = 0;

	for( int i=0; i < seq.size() ; i++){
		if( !seq[i].empty()){
			int value = seq[i].top();
			if( value < min ){
				min = value;
				lastPoint = j;
			}
		}
		j++;
	}
	return lastPoint;
}

vector<int> PatienceSort(vector<int> v){
	vector<stack<int> > seq;
	vector<int> finalVector;

	BuildSequence(seq, v);

	int k=0, point;
	while( k < v.size()){
	 	point = LowestValueOnTop(seq);
	 	finalVector.push_back(seq[point].top());
	 	seq[point].pop();
	 	k++;
	}
	return finalVector;
}

int main(){
	vector<stack<int> > seq;
	vector<int> vect;

	readData(vect);
	
	//BuildSequence(seq, vect);

	//print(seq);

	vect = PatienceSort(vect);

	for( int i=0; i<vect.size(); i++){
		out << vect[i] << " ";
	}

	return 0;
}