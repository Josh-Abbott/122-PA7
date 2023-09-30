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

template <class T>
class Stack
{
public:
	Stack(int newSize = -1);
	~Stack();

	int getCurSize();
	void setCurSize(int newSize);

	bool push(T newItem);
	T pop();
	T peek();

	bool isEmpty();

private:
	int curSize;
	T data[100];

};

template <class T>
Stack<T>::Stack(int newSize)
{
	curSize = newSize; // set to -1 instead of 0 cause 0 is a valid size
}

template <class T>
Stack<T>::~Stack()
{
	delete[] data;
}

/*************************************************************
 * Function: push ()	                                     *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/4/22                                *
 * Description: This function pushes an item to the stack. 	 *
 * Input parameters: A variable of type T.		             *
 * Returns: A success value.                                 *
 * Preconditions: None.					  .					 *
 * Postconditions: The item is pushed to the stack.		     *
 *************************************************************/

template <class T>
bool Stack<T>::push(T newItem)
{
	if (getCurSize() < 100)
	{
		setCurSize(getCurSize() + 1);
		data[getCurSize()] = newItem;
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
 * Function: pop ()		                                     *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/4/22                                *
 * Description: This function pops/removes a value from the	 *
 *				 stack and returns it.					     *
 * Input parameters: Nothing.					             *
 * Returns: A variable of type T.                            *
 * Preconditions: None.					  .					 *
 * Postconditions: The item is popped and returned.		     *
 *************************************************************/

template <class T>
T Stack<T>::pop()
{
	T temp = peek(); // keep hold of pop item to return

	data[getCurSize()] = "";
	setCurSize(getCurSize() - 1);
	return temp;
}

/*************************************************************
 * Function: peek ()	                                     *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/5/22                                *
 * Description: This function peeks into the stack and	 	 *
 *				 returns what is on the top.			     *
 * Input parameters: Nothing.					             *
 * Returns: A variable of type T.                            *
 * Preconditions: None.					  .					 *
 * Postconditions: The correct variable is returned.	     *
 *************************************************************/

template <class T>
T Stack<T>::peek()
{
	if (getCurSize() == -1)
	{
		return "";
	}
	else
	{
		return data[getCurSize()];
	}
}

template <class T>
bool Stack<T>::isEmpty()
{
	return curSize == -1;
}

template <class T>
int Stack<T>::getCurSize()
{
	return curSize;
}

template <class T>
void Stack<T>::setCurSize(int newSize)
{
	this->curSize = newSize;
}