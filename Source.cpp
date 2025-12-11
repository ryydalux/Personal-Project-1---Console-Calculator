#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

#include "Main Functions.h"
#include "operations.h"
using namespace std;

//User only needs to type numbers and the operator inbetween.
//After calculation is done, user can continue calculating with the resulting number or enter a specific key to reset to beginning.
//Pay attention to basic math rules, if user tries to divide by zero, error or if user tries to square root a negative, error. Etc..

int main()
{
	//Obtain input
	string input;
	
	getline(cin, input);


	//Find size of input
	int inputSize{ 0 };

	for (char check : input)
		inputSize++;


	//Transfer input into array for more flexibility
	vector<string> equation{};

	getEquation(equation, input, inputSize);

	readEquation(equation);


	
	//Print equation
	for (string check : equation) 
	{
		if (check == "inf") //If user tries to divide by 0
		{
			cout << "\nERROR 2" << endl;
			break;
		}

		if (check == " " || check == "")
			continue;
		else
			cout << endl << endl << setprecision(1) << fixed << stod(check);
	}
	
	cout << endl;
}