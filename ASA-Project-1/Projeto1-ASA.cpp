#include <cstdio>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using std::vector;

int rows;
int columns;
map<string, unsigned long long> answers;
map<string, unsigned long long>::iterator it;


vector<int> getVector(){
	int column;
	scanf("%d\n%d",&rows,&columns);
	vector<int> _mainVector(rows);

	for(int iter = 0 ; iter < rows; iter++){
		scanf("%d",&column);
		_mainVector[iter] = column;
	}
	return _mainVector;
}

bool checkVector(vector<int> vector){
	if (rows == 0 || columns == 0 || vector[rows-1] == 0) {return false;}
	return true;
}


int getStarterPoint(vector<int> vetor){
	int maxRow = 0;
	for (int iter = 0; iter < rows ; iter++){
		if (vetor[iter] >= vetor[maxRow]) {maxRow = iter;}
	}
	return maxRow;
}

bool squareFits(vector<int> vector,int squareSize,int startRow){
	if (squareSize > startRow+1 || vector[startRow] < squareSize) {return false;}

	if (startRow == 0 && squareSize == 1) {return true;}

	for (int j=1; j < squareSize; j++){
		if (vector[startRow] != vector[startRow-j]) {return false;}
	}
	return true;
}

vector<int> removeSquare(vector<int> vector, int squareSize, int startRow) {
	for (int iter=0; iter < squareSize; iter++) {
		vector[startRow-iter] -= squareSize;
	}
	return vector;
}

unsigned long long matrixSolver(vector<int> vector){
	int startRow = getStarterPoint(vector);
	unsigned long long combinations = 0;
	string vectorKey = "";
	if (vector[startRow] <= 0) {return 1;}

	for (int j = 0; j<rows; j++) {vectorKey += to_string(vector[j]) ;}

	if ((it = answers.find(vectorKey)) != answers.end()) {return it->second;}


	for (int iter = 1 ; iter <=vector[startRow]; iter++) {
		if (squareFits(vector,iter,startRow)) {combinations += matrixSolver(removeSquare(vector, iter, startRow));}
	}
	answers.insert({vectorKey,combinations});
	return combinations;
}

int main(){
	vector<int> mainVector = getVector();
	if (checkVector(mainVector)) {
		printf("%lld\n",matrixSolver(mainVector));
	}
	else {printf("0\n");}
	return 0;
}