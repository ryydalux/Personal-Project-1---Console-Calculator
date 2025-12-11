#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Main Functions.h"
#include "operations.h"
using namespace std;
//This header file contains all operations related to managing parentheses.

double readEquation_inPar(vector<string> equation_inPar);
void search_startIndex(vector<string>& equation, int i, int& startIndex);
void search_stopIndex(vector<string>& equation, int i, int& stopIndex);

void check_MultDiv(vector<string> equation, bool& hasMultDiv);
void check_Exp(vector<string> equation, bool& hasExp);
void check_Par(vector<string> equation, bool& hasPar);


void opPar(vector<string>& equation, int& i)
{

	int openParenthesis{ i }; //Index where the open parenthesis is
	int closeParenthesis;//Index where the close parenthesis is

	vector<string> equation_inPar{}; //Equation that is currently inbetween the parentheses being tracked


	//Check if equation has inner parenthesis
	for (int search{ openParenthesis }; search < equation.size(); search++)
	{
		if (equation[search] == "(")
			openParenthesis = search;

		if (equation[search] == ")")
			break;
		
	}

	equation[openParenthesis] = " "; //Pop index of ( after it's confirmed its the most inner ( found

	//Finds closest ) index + stores everything into equation_inPar
	for (int search{ openParenthesis + 1 }; search < equation.size(); search++)
	{
		if (equation[search] == ")")
		{
			closeParenthesis = search;
			equation[search] = " ";
			break;
		}

		equation_inPar.push_back(equation[search]);
		equation[search] = " ";
	}
	
	//Checks if parenthesis has an exponant
	double par_Exponant{ 1 };

	if ((closeParenthesis + 2) < equation.size())
	{
		if (equation[closeParenthesis + 1] == "^")
		{
			par_Exponant = stod(equation[closeParenthesis + 2]);

			//Pop indexes
			equation[closeParenthesis + 1] = " ";
			equation[closeParenthesis + 2] = " ";
		}
	}



	//Checks if parenthesis has a distributor
	string fullNumber{ "" };
	double distributor{ 1 };
	int atIndex{ openParenthesis - 1 }; //Will initialize search variable in for loop


	if (!(atIndex < 0)) //If equation STARTS with (, dont look for distributor
	{
		if (equation[atIndex] == "*") //Skip * symbol if user input 2 * (numbers)
		{
			equation[atIndex] = " ";
			atIndex--;
		}

		for (int search{ atIndex }; search >= 0; search--)
		{
			if (equation[search] != "+" && equation[search] != "-" && equation[search] != "*" && equation[search] != "/" && equation[search] != "^" && equation[search] != "(")
			{
				fullNumber += equation[search];
				equation[search] = " ";
			}
			else
				break;
		}
	}

	if (fullNumber != "")
		distributor = stod(fullNumber);




	//Perform operations within equation_inPar
	double result_inPar; //Result of the equation inbetween parenthesis

	result_inPar = readEquation_inPar(equation_inPar);

	//Apply exponant and distributor to result_inPar
	result_inPar = pow(result_inPar, par_Exponant);
	result_inPar *= distributor;

	//Place result found back in original equation
	equation[openParenthesis] = to_string(result_inPar);


	i = 0;
}



double readEquation_inPar(vector<string> equation_inPar) //Finds the result within the parenthesis
{
	//Variables used for * / + - operators
	int startIndex; //Index where last number seen
	int stopIndex; //Index where next number seen after operator symbol

	//Variables used to regulate order of priority (P-E-MD-AS)
	bool hasMultDiv;
	bool hasExp;


	for (int i{ 0 }; i < equation_inPar.size(); i++)
	{
		//Skip to next index if empty
		if (equation_inPar[i] == " " || equation_inPar[i] == "")
			continue;
		
			if (equation_inPar[i] == "^")
			{
				opExp(equation_inPar, i);
			}

			check_Exp(equation_inPar, hasExp);

			if (hasExp == false)
			{

				if (equation_inPar[i] == "*")
				{
					search_startIndex(equation_inPar, i, startIndex);
					search_stopIndex(equation_inPar, i, stopIndex);

					opMult(equation_inPar, i, startIndex, stopIndex);
				}

				if (equation_inPar[i] == "/")
				{
					search_startIndex(equation_inPar, i, startIndex);
					search_stopIndex(equation_inPar, i, stopIndex);

					opDiv(equation_inPar, i, startIndex, stopIndex);
				}

				check_MultDiv(equation_inPar, hasMultDiv); //Checks if equation still has a * or / 

				if (hasMultDiv == false)
				{
					if (equation_inPar[i] == "+")
					{
						search_startIndex(equation_inPar, i, startIndex);
						search_stopIndex(equation_inPar, i, stopIndex);

						opAdd(equation_inPar, i, startIndex, stopIndex);
					}

					if (equation_inPar[i] == "-")
					{
						search_startIndex(equation_inPar, i, startIndex);
						search_stopIndex(equation_inPar, i, stopIndex);

						opSub(equation_inPar, i, startIndex, stopIndex);
					}
				}
			}
	
	}

	//Return result found
	string result;

	for (string check : equation_inPar)
	{
		if (check != " " || check != "")
			result += check;
	}
	
	return stod(result);
}