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

#include "pa7.h"
#include "Data.h"
#include "Stack.h"

template <class T>
class ListNode
{
public:
	ListNode(string line, bool isMaster);
	~ListNode();

	void setDate();

	T getData() const;
	ListNode<T>* getNextPtr() const;

	void setData(const T newData);
	void setNextPtr(ListNode<T>* const newNext);

private:
	T mData; //USES TYPE T FROM THE TEMPLATE, WILL BE DATA LATER
	ListNode<T>* mpNext;
};

/*************************************************************
 * Function: ListNode ()                                     *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/4/22                                *
 * Description: This function acts as the constructor for	 *
 *				 a ListNode and reads in data to the node.   *
 * Input parameters: A string and bool value.	             *
 * Returns: A ListNode.                                      *
 * Preconditions: None.					  .					 *
 * Postconditions: The data is succesfully read in.		     *
 *************************************************************/

template <class T>
ListNode<T>::ListNode(string line, bool isMaster)
{
	string input, first, last, name;
	Data temp;
	stringstream newLine(line); // ?

	getline(newLine, input, ',');

	if (input != "")
	{
		temp.setRecNum(stoi(input));

		getline(newLine, input, ',');
		temp.setIdNum(stoi(input));

		getline(newLine, input, '"');

		getline(newLine, input, '"');
		temp.setName(input);

		getline(newLine, input, ',');
		temp.setEmail(input);

		getline(newLine, input, ',');
		temp.setUnits(input);

		getline(newLine, input, ',');
		temp.setProgram(input);

		getline(newLine, input, ',');
		temp.setLevel(input);

		if (isMaster == true)
		{
			getline(newLine, input, ',');
			temp.setAbsNum(stoi(input));

			Stack<string>* absences = new Stack<string>;
			getline(newLine, input, ',');
			absences->push(input);
			temp.setAbsences(absences);
		}
		else
		{
			Stack<string>* absences = new Stack<string>;
			temp.setAbsences(absences);
		}

		setData(temp);
	}
}

template <class T>
ListNode<T>::~ListNode()
{

}

template <class T>
T ListNode<T>::getData() const
{
	return mData;
}

template <class T>
ListNode<T>* ListNode<T>::getNextPtr() const
{
	return mpNext;
}

template <class T>
void ListNode<T>::setData(const T newData)
{
	mData = newData;
}

template <class T>
void ListNode<T>::setNextPtr(ListNode<T>* const newNext)
{
	mpNext = newNext;
}

/*************************************************************
 * Function: setDate ()		                                 *
 * Date Created: 4/5/22										 *
 * Date Last Modified: 4/5/22                                *
 * Description: This function sets the node's absence date	 *
 *				 to today's date.					         *
 * Input parameters: Nothing.					             *
 * Returns: Nothing.                                         *
 * Preconditions: None.					  .					 *
 * Postconditions: The date is succesfully set.			     *
 *************************************************************/

template <class T>
void ListNode<T>::setDate()
{
	Data temp = mData;

	// retrieved from stackoverflow
	time_t today = time(0);   // get time now
	stringstream date;

	struct tm* now = localtime(&today);

	date << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday;

	temp.setAbsNum(temp.getAbsNum() + 1);
	temp.getAbsences()->push(date.str());

	setData(temp);
}