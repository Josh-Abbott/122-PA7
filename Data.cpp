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

#include "Data.h"

int Data::getAbsNum() const
{
	return absencesNum;
}

void Data::setAbsNum(int num)
{
	absencesNum = num;
}

int Data::getRecNum() const
{
	return recordNum;
}

void Data::setRecNum(int num)
{
	recordNum = num;
}

int Data::getIdNum() const
{
	return idNum;
}

void Data::setIdNum(int num)
{
	idNum = num;
}

string Data::getName() const
{
	return name;
}

void Data::setName(string newName)
{
	name = newName;
}

string Data::getEmail() const
{
	return email;
}

void Data::setEmail(string newEmail)
{
	email = newEmail;
}

string Data::getUnits() const
{
	return units;
}

void Data::setUnits(string newUnits)
{
	units = newUnits;
}

string Data::getProgram() const
{
	return program;
}

void Data::setProgram(string newProgram)
{
	program = newProgram;
}

string Data::getLevel() const
{
	return level;
}

void Data::setLevel(string newLevel)
{
	level = newLevel;
}

Stack<string>* Data::getAbsences() const
{
	return absences;
}

void Data::setAbsences(Stack<string>* newStack)
{
	absences = newStack;
}