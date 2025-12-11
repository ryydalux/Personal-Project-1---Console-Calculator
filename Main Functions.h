#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "operations.h"
#include "parentheses.h"
using namespace std;
//This header file contains all the main logic used by the program (reading the equation and checking for order of priority)

void search_startIndex(vector<string>& equation, int i, int& startIndex);
void search_stopIndex(vector<string>& equation, int i, int& stopIndex);

void check_MultDiv(vector<string> equation, bool& hasMultDiv);
void check_Exp(vector<string> equation, bool& hasExp);
void check_Par(vector<string> equation, bool& hasPar);


void getEquation(vector<string>& equation, string userInput, int inputSize) //Collects input data and stores it into a string array
{

	string fullNumber;

	for (int i{0}; i < inputSize; i++) //stores numbers into index, then store operator, vice versa
	{
		fullNumber = ""; //Reset

		while (userInput[i] != '+' && userInput[i] != '-' && userInput[i] != '*' && userInput[i] != '/' && userInput[i] != '^' && userInput[i] != '(' && userInput[i] != ')' && i < inputSize)
		{

			if (userInput[i] == '0')
				fullNumber += "0";
			else if (userInput[i] == '1')
				fullNumber += "1";
			else if (userInput[i] == '2')
				fullNumber += "2";
			else if (userInput[i] == '3')
				fullNumber += "3";
			else if (userInput[i] == '4')
				fullNumber += "4";
			else if (userInput[i] == '5')
				fullNumber += "5";
			else if (userInput[i] == '6')
				fullNumber += "6";
			else if (userInput[i] == '7')
				fullNumber += "7";
			else if (userInput[i] == '8')
				fullNumber += "8";
			else if (userInput[i] == '9')
				fullNumber += "9";
			else if (userInput[i] == '.') //Decimal Support
				fullNumber += ".";

			i++;
		}

		if (fullNumber != "" && fullNumber != " ") //Unless no number was detected, pushback fullNumber into equation.
			equation.push_back(fullNumber);

		
		if (userInput[i] == '+')
		{
			equation.push_back("+");
			continue;
		}
		if (userInput[i] == '-')
		{
			equation.push_back("-");
			continue;
		}
		if (userInput[i] == '*')
		{
			equation.push_back("*");
			continue;
		}
		if (userInput[i] == '/')
		{
			equation.push_back("/");
			continue;
		}
		if (userInput[i] == '^')
		{
			equation.push_back("^");
			continue;
		}
		if (userInput[i] == '(')
		{
			equation.push_back("(");
			continue;
		}
		if (userInput[i] == ')')
		{
			equation.push_back(")");
			continue;
		}
		
			
	}
}


void readEquation(vector<string>& equation) //Reads the line and checks for operators ( ) ^ * / + -
{
	//Variables used for * / + - operators
	int startIndex; //Index where last number seen
	int stopIndex; //Index where next number seen after operator symbol

	//Variables used to regulate order of priority (P-E-MD-AS)
	bool hasMultDiv;
	bool hasExp;
	bool hasPar;


	for (int i{ 0 }; i < equation.size(); i++)
	{
		//Skip to next index if empty
		if (equation[i] == " " || equation[i] == "")
		{
			continue;
		}

		if (equation[i] == "(")
		{
			opPar(equation, i);
		}

		check_Par(equation, hasPar);

		if (hasPar == false)
		{

			if (equation[i] == "^")
			{
				opExp(equation, i);
			}

			check_Exp(equation, hasExp);

			if (hasExp == false)
			{

				if (equation[i] == "*")
				{
					search_startIndex(equation, i, startIndex);
					search_stopIndex(equation, i, stopIndex);

					opMult(equation, i, startIndex, stopIndex);
				}

				if (equation[i] == "/")
				{
					search_startIndex(equation, i, startIndex);
					search_stopIndex(equation, i, stopIndex);

					opDiv(equation, i, startIndex, stopIndex);
				}

				check_MultDiv(equation, hasMultDiv); //Checks if equation still has a * or / 

				if (hasMultDiv == false)
				{
					if (equation[i] == "+")
					{
						search_startIndex(equation, i, startIndex);
						search_stopIndex(equation, i, stopIndex);

						opAdd(equation, i, startIndex, stopIndex);
					}

					if (equation[i] == "-")
					{
						search_startIndex(equation, i, startIndex);
						search_stopIndex(equation, i, stopIndex);

						opSub(equation, i, startIndex, stopIndex);
					}
				}
			}
		}
	}
}


void search_startIndex(vector<string>& equation, int i, int& startIndex) //Finds index of the closest number to the left of operator
{
	i--; //Decrement to not read operator

	for (int search{ i }; search >= 0; search--)
	{
		if (equation[search] == " ")
			continue;

		if (equation[search] != "+" && equation[search] != "-" && equation[search] != "*" && equation[search] != "/")
		{
			startIndex = search;
			break;
		}
	}
}


void search_stopIndex(vector<string>& equation, int i, int& stopIndex) //Finds index of the closest number to the right of operator
{
	i++; //Increment to not read operator

	for (int search{ i }; search < equation.size(); search++)
	{
		if (equation[search] == " ")
			continue;

		if (equation[search] != "+" && equation[search] != "-" && equation[search] != "*" && equation[search] != "/")
		{
			stopIndex = search;
			break;
		}
	}
}


void check_MultDiv(vector<string> equation, bool& hasMultDiv)
{
	hasMultDiv = false; //Reset

	for (string check : equation)
	{
		if (check == "*" || check == "/")
			hasMultDiv = true;
	}
}

void check_Exp(vector<string> equation, bool& hasExp)
{
	hasExp = false; //Reset

	for (string check : equation)
	{
		if (check == "^")
			hasExp = true;
	}
}

void check_Par(vector<string> equation, bool& hasPar)
{
	hasPar = false; //Reset

	for (string check : equation)
	{
		if (check == "(" || check == ")")
			hasPar = true;
	}
}