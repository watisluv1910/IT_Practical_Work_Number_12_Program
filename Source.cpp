#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#define NOMINMAX
#include <windows.h>
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

// function that checks type error or "border crossing":
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
					// operator >> will no longer fetch data from the stream 
					// as it is in the wrong format:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
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

// function that checks type inconsistencies:
string initializeString(int maxlength) {
	bool isCorrect = false;
	while (!isCorrect) {
		string line;
		cin >> line;
		isCorrect = true;
		// the letters combination length can't be more 
		// than the number of columns in array (5 according to the task):
		if (line.length() != maxlength) {
			isCorrect = false;
		}
		// check for unsuitable symbols (all except english alphabet):
		for (size_t i = 0; i < 128; i++) {
			if (!(i >= (int)'A' && i <= (int)'Z' || i >= (int)'a' && i <= (int)'z')) {
				// if unsuitable symbol was found:
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
			// operator >> will no longer fetch data from the stream 
			// as it is in the wrong format:
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}
	}
}

// function that creates 2-dimentional dynamic char array 
// with the way user've chosen:
char** createArray(int rows, int columns, int path) {
	srand(time(0)); // system time dependent randomizing
	char** array = new char* [rows]; // creating the main array
	for (int i = 0; i < rows; i++) {
		array[i] = new char[columns]; // creating subarrays
		switch (path) {
		case 1: { // user input
			cout << "\nEnter the line:\n";
			string line = initializeString(columns);
			for (int j = 0; j < columns; j++) {
				array[i][j] = line[j];
			}
			break;
		}
		case 2: { // filling by random number
			for (int j = 0; j < columns; j++) {
				switch (rand() % 2 + 1) { // random choise of letter case:
				case 1: // uppercase
					array[i][j] = (char)(rand() % 26 + (int)'A');
					break;
				case 2: // lowercase
					array[i][j] = (char)(rand() % 26 + (int)'a');
					break;
				}
			}
			break;
		}
		}		
	}
	return array; // returning a pointer to the array
}

// function that sorts each subarray in descending order:
void bubleSort(int length, int* array) {
	for (int i = 0; i < length; i++) {
		for (size_t j = 0; j < length - i; j++) {
			if (array[j] < array[j + 1]) {
				swap(array[j], array[j + 1]);
			}
		}
	}
}

// function that creates 2-dimentional dynamic integer array 
// with letters transformed to ASCII code:
int** transformArray(int rows, int columns, char** lettersArray) {
	int** encodingsArray = new int* [rows];
	for (int i = 0; i < rows; i++) {
		encodingsArray[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			encodingsArray[i][j] = (int)lettersArray[i][j];
		}
		bubleSort(columns, encodingsArray[i]); // sorting the subarray
	}
	return encodingsArray; // returning a pointer to the transformed array
}

// function that performs arrays outout in console:
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
	// for correct recognition of russian letters in console:
	setlocale(LC_ALL, "Russian"); 
	// special commands (ctrl-c, ctrl-break) treatment:
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = ENABLE_PROCESSED_INPUT;
	SetConsoleMode(hOut, dwMode);
	// introduction part:
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
	// the value of rows and columns could be changed in code or 
	// entered from console through the <initializeInteger> function:
	int rows = 5, columns = 5;
	char** lettersArray = createArray(rows, columns, path);
	int** encodingsArray = transformArray(rows, columns, lettersArray);
	printArray(rows, columns, lettersArray, encodingsArray);
	return 1;
}
