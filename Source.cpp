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

//function that check type error or "border crossing"
int initializeInteger(string path = "all", int lowerBound = 0, int upperBound = 0) {
	bool isCorrect = false;
	int temporaryVariable;
	while (!isCorrect) {
		string temporaryVariableString;
		cin >> temporaryVariableString;
		isCorrect = true;
		for (size_t i = 0; i < 128; i++) {
			if (i < (int)'0' || i >(int)'9') {
				if (i != (int)'-') {
					if (temporaryVariableString.find((char)i) != string::npos) {
						isCorrect = false;
					}
				}
				else if (temporaryVariableString.find((char)i) != string::npos) {
					if ((count(temporaryVariableString.begin(),
						temporaryVariableString.end(), (char)i) > 1)
						|| temporaryVariableString.length() == 1) {
						isCorrect = false;
					}
				}
			}
		}
		if (isCorrect) {
			temporaryVariable = stoi(temporaryVariableString);
			if (lowerBound != 0 || upperBound != 0) {
				if (temporaryVariable < lowerBound
					|| temporaryVariable > upperBound) {
					cout << "\nInitialization error.\nEnter correct value:\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
					// operator >> will no longer fetch data from the stream 
					// as it is in the wrong format
				}
			}
			else if (path == "allExceptZero" && temporaryVariable == 0 ||
				path == "negative" && temporaryVariable >= 0 ||
				path == "notpositive" && temporaryVariable > 0 ||
				path == "notnegative" && temporaryVariable < 0 ||
				path == "positive" && temporaryVariable <= 0) {
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
	return temporaryVariable;
}

int main() {
	int choosePath;
	setlocale(LC_ALL, "Russian");
	cout << "Hello!\nPlease, choose how to fill the array:\n"
		"Press <1> and <Enter> bottom, if you want "
		"to enter letters by yourself.\n"
		"Press <2> and <Enter> bottom, if you want "
		"letters to be entered randomly.\n"
		"Press <0> and <Enter> bottom to end the programm.\n"
		"\nEnter the option number:\n";
	choosePath = initializeInteger("notnegative");
	while (choosePath > 0) {
		switch (choosePath) {
		case 1:
			break;
		case 2:
			break;
		default:
			cout << "\nIncorrect option choise, try again.\n"
				"Press <1> and <Enter> bottom, if you want "
				"to enter letters by yourself.\n"
				"Press <2> and <Enter> bottom, if you want "
				"letters to be entered randomly.\n"
				"Press <0> and <Enter> bottom to end the programm.\n";
			break;
		}
		cout << "\nEnter the option number:\n";
		choosePath = initializeInteger("notnegative");
	}
	cout << "\nThe program was interrapted by user.\n";
	return 0;
}