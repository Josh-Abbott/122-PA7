/****************************************************************************************************************
 * Programmer: Josh Abbott																						*
 * Class: CptS 122; Lab Section 10																				*
 * Programming Assignment: 7																					*
 * Date: 4/7/22																									*
 *																												*
 * Description: This program allows for the user to import a csv or .txt file full of student information		*
 *              to mark if they are absent or not and generate a report.										*
 *																												*
 * Relevant Formulas: Refer to each function definition.														*
 *																												*
 * Format of record in input files (classList.csv & master.txt):												*
 *	Record, ID, "Last,First", Email, Units, Program, Level, Absence Number, Absence Date						*
 *																												*
 ***************************************************************************************************************/

#pragma once

#include "Stack.h"

class Data
{
public:
	Stack<string>* getAbsences() const;
	void setAbsences(Stack<string>* newStack);
	int getAbsNum() const;
	void setAbsNum(int num);
	int getRecNum() const;
	void setRecNum(int num);
	int getIdNum() const;
	void setIdNum(int num);
	string getName() const;
	void setName(string newName);
	string getEmail() const;
	void setEmail(string newEmail);
	string getUnits() const;
	void setUnits(string newUnits);
	string getProgram() const;
	void setProgram(string newProgram);
	string getLevel() const;
	void setLevel(string newLevel);

private:
	Stack<string>* absences;
	int absencesNum;
	int recordNum;
	int idNum;
	string name;
	string email;
	string units;
	string program;
	string level;
};
