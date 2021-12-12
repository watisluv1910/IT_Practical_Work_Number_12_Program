#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <fstream> // for if/ofstream
#include <time.h> // for srand
#include <vector> // for vector
#include <stdio.h> // for printf
#include <stdlib.h> // for rand, srand
#include <sstream>
#include <utility>

using namespace std;

//function that checks type error or "border crossing"
int initializeInteger(string path = "all", int lowerBound = 0, int upperBound = 0) {
	bool isCorrect = false;
	int integerVariable;
	while (!isCorrect) {
		string stringVariable;
		cin >> stringVariable;
		isCorrect = true;
		for (size_t i = 0; i < 128; i++) {
			if (i < (int)'0' || i > (int)'9') {
				int found = stringVariable.find((char)i);
				if (i != (int)'-') {
					if (found != string::npos) {
						isCorrect = false;
					}
				}
				else {
					if (found != string::npos && ((count(stringVariable.begin(),
						stringVariable.end(), (char)i) > 1)
						|| stringVariable.length() == 1 || found > 0)) {
						isCorrect = false;
					}
				}
			}
		}
		if (isCorrect) {
			integerVariable = stoi(stringVariable);
			if (lowerBound != 0 || upperBound != 0) {
				if (integerVariable < lowerBound
					|| integerVariable > upperBound) {
					cout << "\nInitialization error.\nEnter correct value:\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
					// operator >> will no longer fetch data from the stream 
					// as it is in the wrong format
				}
			}
			else if (path == "allExceptZero" && integerVariable == 0 ||
				path == "negative" && integerVariable >= 0 ||
				path == "notpositive" && integerVariable > 0 ||
				path == "notnegative" && integerVariable < 0 ||
				path == "positive" && integerVariable <= 0) {
				cout << "\nInitialization error.\nEnter correct value:\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				isCorrect = false;
			}
		}
		else {
			cout << "\nInitialization error.\nEnter correct value:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return integerVariable;
}

//function that checks type inconsistencies
string initializeString(int maxlength) {
	bool isCorrect = false;
	while (!isCorrect) {
		string line;
		cin >> line;
		isCorrect = true;
		if (line.length() != maxlength) {
			isCorrect = false;
		}
		for (size_t i = 0; i < 128; i++) {
			if (!(i >= (int)'A' && i <= (int)'Z' || i >= (int)'a' && i <= (int)'z')) {
				if (line.find((char)i) != string::npos) {
					isCorrect = false;
				}
			}
		}
		if (isCorrect) {
			return line;
		}
		else {
			cout << "\nInitialization error.\nEnter correct value:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

char** createArray(int rows, int columns, int path) {
	srand(time(0));
	char** array = new char* [rows];
	for (int i = 0; i < rows; i++) {
		array[i] = new char[columns];
		switch (path) {
		case 1: {
			cout << "\nEnter the next line:\n";
			string line = initializeString(columns);
			for (int j = 0; j < columns; j++) {
				array[i][j] = line[j];
			}
			break;
		}
		case 2: {
			for (int j = 0; j < columns; j++) {
				switch (rand() % 2 + 1) {
				case 1:
					array[i][j] = (char)(rand() % 26 + (int)'A');
					break;
				case 2:
					array[i][j] = (char)(rand() % 26 + (int)'a');
					break;
				}
			}
			break;
		}
		}		
	}
	return array;
}

int** transformArray(int rows, int columns, char** lettersArray) {
	int** encodingsArray = new int* [rows];
	for (int i = 0; i < rows; i++) {
		encodingsArray[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			encodingsArray[i][j] = (int)lettersArray[i][j];
		}   
	}
	return encodingsArray;
}

void bubleSort(int rows, int columns, int** array) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			for (size_t k = 0; k < columns - j; k++) {
				if (array[i][k] < array[i][k + 1]) {
					swap(array[i][k], array[i][k + 1]);
				}
			}
		}
	}
}

void printArray(int rows, int columns, char** lettersArray, int** encodingsArray) {
	cout << "\n|The original array:\t\t\t|The transformed array:\n";
	for (int i = 0; i < rows; i++) {
		cout << "|";
		for (int j = 0; j < columns; j++) {
			cout << lettersArray[i][j] << "\t";
		}
		cout << "|";
		for (int j = 0; j < columns; j++) {
			cout << encodingsArray[i][j] << "\t";
		}
		cout << endl;
	}
}

int main() {
	int path;
	setlocale(LC_ALL, "Russian");
	cout << "Hello!\nPlease, choose how to fill the array:\n"
		"Press <1> and <Enter> bottom, if you want "
		"to enter letters by yourself.\n"
		"Press <2> and <Enter> bottom, if you want "
		"letters to be entered randomly.\n"
		"Press <0> and <Enter> bottom to end the programm.\n"
		"\nEnter the option number:\n";
	path = initializeInteger("all", 0, 2);
	if (path == 0) {
		cout << "\nThe program was interrupted by user.\n";
		return 0;
	}
	int rows = 5, columns = 5;
	char** lettersArray = createArray(rows, columns, path);
	int** encodingsArray = transformArray(rows, columns, lettersArray);
	bubleSort(rows, columns, encodingsArray);
	printArray(rows, columns, lettersArray, encodingsArray);
	return 1;
}
