#include <iostream>
#include <fstream>
#include <cstdlib>
#define MAX 1001
using namespace std;

ifstream in("acoperire.in");
ofstream out("acoperire.out");

struct interval{
	long long int left, right;
};

int compare(const void *a, const void *b){
	struct interval t1 = *(interval*) a;
	struct interval t2 = *(interval*) b;
	if( t1.left < t2.left) return -1;
	if( t1.left == t2.left) return 0;
	return 1;
}

void readInfo(struct interval (&intervale)[MAX], struct interval &intervalPrincipal, int &total){
	long long int nr1, nr2;
	in >> nr1 >> nr2;
	intervalPrincipal.left = nr1;
	intervalPrincipal.right = nr2;
	in >> total;
	for( int i=0; i<total; i++){
		in >> nr1 >> nr2;
		intervale[i].left = nr1;
		intervale[i].right = nr2;
	}
}

void lateEnd( struct interval &intervalCurent, struct interval i){
	if( i.right > intervalCurent.right ){
		intervalCurent.left = i.left;
		intervalCurent.right = i.right;
	}
}

void findInterval(struct interval (&intervale)[MAX], struct interval &intervalPrincipal, int &total){
	int contor=0, j=0;
	struct interval intervalCurent;
	intervalCurent.left = -1;
	intervalCurent.right = -1;
	int maxLeft = intervalPrincipal.left;

	for( int i=0; i < total && intervale[i].left <= maxLeft; i++){
		if( intervale[i].right >= maxLeft){
			lateEnd(intervalCurent, intervale[i]);
			j = i;
		}
	}
	if( intervalCurent.left == -1){
		out << -1;
		return;
	}
	else{
		out << intervalCurent.left << "-" << intervalCurent.right << endl;
		maxLeft = intervalCurent.right;
		contor++;
	}
	int i=j+1;
	while( maxLeft <= intervalPrincipal.right){
		for( i ; i < total && intervale[i].left <= maxLeft; i++){
			if(  intervale[i].right >= maxLeft ){
				lateEnd(intervalCurent, intervale[i]);
				j = i;
			}
		}
		if( intervalCurent.left == antLeft){
			out << -1;
			maxLeft = 20001;
			return;
		}
		else{
			out << intervalCurent.left << "-" << intervalCurent.right << endl;
			maxLeft = intervalCurent.right;
			contor++;
		}
	}
	out << contor << endl;
}

int main(){
	struct interval intervale[MAX];
	struct interval intervalPrincipal;
	int total;
	readInfo(intervale, intervalPrincipal, total);

	qsort(intervale, total, sizeof(interval), compare);

	findInterval(intervale, intervalPrincipal, total);

	return 0;
}
