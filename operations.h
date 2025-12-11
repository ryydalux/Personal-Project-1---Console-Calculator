#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
//This header file contains all basic operations including managing exponants



void opAdd(vector<string>& equation, int& i, int startIndex, int stopIndex);
void opSub(vector<string>& equation, int& i, int startIndex, int stopIndex);
void opMult(vector<string>& equation, int& i, int startIndex, int stopIndex);
void opDiv(vector<string>& equation, int& i, int startIndex, int stopIndex);
void opExp(vector<string>& equation, int& i);

void opAdd(vector<string>& equation, int& i, int startIndex, int stopIndex) //Performs addition operations
{
	double result;

	result = stod(equation[startIndex]) + stod(equation[stopIndex]);
	equation[i] = to_string(result);

	//Make indexes empty after operation
	equation[startIndex] = " ";
	equation[stopIndex] = " ";

	i = 0; //Reset readEquation loop so we fully re-check equation again
}


void opSub(vector<string>& equation, int& i, int startIndex, int stopIndex)
{
	double result;

	result = stod(equation[startIndex]) - stod(equation[stopIndex]);
	equation[i] = to_string(result);

	//Make indexes empty after operation
	equation[startIndex] = " ";
	equation[stopIndex] = " ";

	i = 0; 
}


void opMult(vector<string>& equation, int& i, int startIndex, int stopIndex)
{
	double result;

	result = stod(equation[startIndex]) * stod(equation[stopIndex]);
	equation[i] = to_string(result);

	//Make indexes empty after operation
	equation[startIndex] = " ";
	equation[stopIndex] = " ";

	i = 0; 
}


void opDiv(vector<string>& equation, int& i, int startIndex, int stopIndex)
{
	double result;

	result = stod(equation[startIndex]) / stod(equation[stopIndex]);
	equation[i] = to_string(result);

	//Make indexes empty after operation
	equation[startIndex] = " ";
	equation[stopIndex] = " ";

	i = 0; 
}


void opExp(vector<string>& equation, int& i)
{
	string fullNumber;
	double base; //Exponant's base
	double exponant; //Exponant number

	for (int search{ i - 1 }; search >= 0; search--) //Looks for exponant's base
	{
		if (equation[search] == " ")
			continue;

		if (equation[search] != "+" && equation[search] != "-" && equation[search] != "*" && equation[search] != "/" && equation[search] != "^")
		{
			fullNumber += equation[search];
			equation[search] = " "; //Pop index as we collect the number
		}
		else
			break;
	}

	base = stod(fullNumber);
	fullNumber = ""; //Reset

	for (int search{ i + 1 }; search < equation.size(); search++) //Looks for exponant
	{
		if (equation[search] == " ")
			continue;

		if (equation[search] != "+" && equation[search] != "-" && equation[search] != "*" && equation[search] != "/" && equation[search] != "^")
		{
			fullNumber += equation[search];
			equation[search] = " ";
		}
		else
			break;
	}

	exponant = stod(fullNumber);
	fullNumber = ""; //Reset

	equation[i] = to_string(pow(base, exponant)); //Operation

	i = 0;
}




