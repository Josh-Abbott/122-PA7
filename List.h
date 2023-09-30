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

#include "Node.h"
#include "Stack.h"
#include "Data.h"

template <class T>
class List
{
public:
	List();
	~List();
	ListNode<T>* getHeadPtr() const;
	void setHeadPtr(T newData);
	bool insertAtFront(ListNode<T>* newData);
	bool isEmpty();

	void loadList(ifstream& infile, bool isMaster);
	void writeMaster(ostream& outfile);
	void markAbsences();
	void generateReport(int option, int amount, ostream& report);
	void editAbsences();

private:
	ListNode<T>* mpHead;

	ListNode<T>* makeNode(const T newData);
	void destroyList();
	void destroyList(ListNode<T>* const pMem);
};

template <class T>
List<T>::List()
{
	mpHead = nullptr;
}

template <class T>
List<T>::~List()
{
	destroyList();
}

template <class T>
ListNode<T>* List<T>::getHeadPtr() const
{
	return mpHead;
}

/*************************************************************
 * Function: insertAtFront ()                                *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/4/22                                *
 * Description: This function inserts a ListNode at the 	 *
 *				 front of the list.						     *
 * Input parameters: A ListNode.				             *
 * Returns: A success value.                                 *
 * Preconditions: None.					  .					 *
 * Postconditions: The node is inserted succesfully.	     *
 *************************************************************/

template <class T>
bool List<T>::insertAtFront(ListNode<T>* newData)
{
	bool success = false;

	if (newData != nullptr)
	{
		success = true;
		newData->setNextPtr(mpHead);
		mpHead = newData;
	}

	return success;
}

template <class T>
bool List<T>::isEmpty()
{
	return (mpHead == nullptr);
}

template <class T>
void List<T>::setHeadPtr(T newData)
{
	mpHead = makeNode<T>(newData);
}

/*************************************************************
 * Function: makeNode ()									 *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/4/22                                *
 * Description: This function creates a new node in memory	 *
 * Input parameters: A variable of type T.		             *
 * Returns: A ListNode.                                      *
 * Preconditions: None.					  .					 *
 * Postconditions: A new node is created and returned.	     *
 *************************************************************/

template <class T>
ListNode<T>* List<T>::makeNode(const T newData)
{
	ListNode<T>* pMem = new ListNode<T>(newData);
	return pMem;
}

/*************************************************************
 * Function: destroyList ()                                  *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/4/22                                *
 * Description: This function recursively deletes the list   *
 *				 in memory.								     *
 * Input parameters: A ListNode.				             *
 * Returns: Nothing.                                         *
 * Preconditions: None.					  .					 *
 * Postconditions: The list is destroyed.				     *
 *************************************************************/

template <class T>
void List<T>::destroyList(ListNode<T>* const pMem)
{
	if (pMem != nullptr)
	{
		destroyList(pMem->getNextPtr());
		delete pMem;
	}
}

template <class T>
void List<T>::destroyList()
{
	destroyList(mpHead);
}

/*************************************************************
 * Function: loadList ()                                     *
 * Date Created: 4/5/22										 *
 * Date Last Modified: 4/5/22                                *
 * Description: This function reads in a file, creates a 	 *
 *				 new node, and inserts it at front.			 *
 * Input parameters: An ifstream and bool value.	         *
 * Returns: Nothing.                                         *
 * Preconditions: None.					  .					 *
 * Postconditions: The list is loaded in succesfully.	     *
 *************************************************************/

template <class T>
void List<T>::loadList(ifstream& infile, bool isMaster)
{
	string line;

	while (!infile.eof())
	{
		getline(infile, line);
		ListNode<T>* pNew = new ListNode<T>(line, isMaster);
		insertAtFront(pNew);
	}
}

/*************************************************************
 * Function: writeMaster ()                                  *
 * Date Created: 4/5/22										 *
 * Date Last Modified: 4/5/22                                *
 * Description: This function writes the list's contents	 *
 *				 to a file.								     *
 * Input parameters: An ostream file.			             *
 * Returns: Nothing.		                                 *
 * Preconditions: None.					  .					 *
 * Postconditions: The data is succesfully written.		     *
 *************************************************************/

template <class T>
void List<T>::writeMaster(ostream& outfile)
{
	ListNode<Data>* pTemp = mpHead;

	pTemp = pTemp->getNextPtr();

	while (pTemp != nullptr) // loop thru list to print to file (DONT FORGET ABOUT TIME)
	{
		Stack<string>* stackTemp = pTemp->getData().getAbsences();
		string item;
		string absences = "";

		for (int i = 0; i < pTemp->getData().getAbsNum(); i++)
		{
			absences += stackTemp->pop();
		}

		stringstream line;
		line << to_string(pTemp->getData().getRecNum()) << ",";
		line << to_string(pTemp->getData().getIdNum()) << ",";

		line << "\"" << pTemp->getData().getName() << "\"";
		line << pTemp->getData().getEmail() << ",";
		line << pTemp->getData().getUnits() << ",";
		line << pTemp->getData().getProgram() << ",";
		line << pTemp->getData().getLevel() << ",";
		line << to_string(pTemp->getData().getAbsNum()) << ",";
		line << absences;

		outfile << line.str() << endl;

		pTemp = pTemp->getNextPtr();
	}
}

/*************************************************************
 * Function: markAbsences ()                                 *
 * Date Created: 4/6/22										 *
 * Date Last Modified: 4/6/22                                *
 * Description: This function loops through the list and	 *
 *				 prompts the user if they are absent.	     *
 * Input parameters: Nothing.					             *
 * Returns: Nothing.	                                     *
 * Preconditions: None.					  .					 *
 * Postconditions: The absences are succesfully marked.	     *
 *************************************************************/

template <class T>
void List<T>::markAbsences()
{
	ListNode<Data>* pTemp = mpHead;

	int menu_choice = 0, choice;

	while (pTemp != nullptr) // loop thru list
	{
		menu_choice = 0;
		while (menu_choice == 0)
		{
			system("cls");
			cout << "Student: " << pTemp->getData().getName() << endl;
			cout << "Is this student absent today?" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			cin >> choice;

			switch (choice)
			{
			case 1: // yes
			{
				pTemp->setDate();
				menu_choice = 1;
				break;
			}
			case 2: // no
			{
				menu_choice = 1;
				break;
			}
			}
			pTemp = pTemp->getNextPtr();
		}
	}
}

/*************************************************************
 * Function: generateReport ()                               *
 * Date Created: 4/6/22										 *
 * Date Last Modified: 4/6/22                                *
 * Description: This function generates a report of the  	 *
 *				 list's contents and writes it to a file.    *
 * Input parameters: Two ints and an ostream file.	         *
 * Returns: Nothing.                                         *
 * Preconditions: None.					  .					 *
 * Postconditions: The report is succesfully generated.	     *
 *************************************************************/

template <class T>
void List<T>::generateReport(int option, int amount, ostream& report)
{
	if (option == 1) // generate all students
	{
		ListNode<Data>* pTemp = mpHead->getNextPtr();

		while (pTemp != nullptr)
		{
			report << pTemp->getData().getName() << endl << pTemp->getData().getAbsences()->peek() << endl << endl;

			pTemp = pTemp->getNextPtr();
		}
	}
	else if (option == 2) // generate over an amount
	{
		ListNode<Data>* pTemp = mpHead->getNextPtr();

		while (pTemp != nullptr)
		{
			if (pTemp->getData().getAbsNum() >= amount)
			{
				report << pTemp->getData().getName() << endl;
			}
			pTemp = pTemp->getNextPtr();
		}
	}
}

/*************************************************************
 * Function: editAbsences ()                                 *
 * Date Created: 4/7/22										 *
 * Date Last Modified: 4/7/22                                *
 * Description: This function prompts the user for a student *
 *				 ID that they would like to edit.		     *
 * Input parameters: Nothing.					             *
 * Returns: Nothing.                                         *
 * Preconditions: None.					  .					 *
 * Postconditions: The absences are succesfully edited.	     *
 *************************************************************/

template <class T>
void List<T>::editAbsences()
{
	ListNode<Data>* pTemp = mpHead;
	int studentChange, choice;
	bool success = false;

	cout << "Please enter the student ID you would like to edit: " << endl;
	cin >> studentChange;

	while (pTemp != nullptr)
	{
		if (pTemp->getData().getIdNum() == studentChange)
		{
			success = true;

			int menu_choice = 0;

			while (menu_choice == 0)
			{
				cout << "Student: " << pTemp->getData().getName() << endl;
				cout << "Is this student absent today?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;
				cin >> choice;

				switch (choice)
				{
				case 1: // yes
				{
					pTemp->setDate();
					menu_choice = 1;
					break;
				}
				case 2: // no
				{
					menu_choice = 1;
					break;
				}
				}
			}

			break;
		}
		pTemp = pTemp->getNextPtr();
	}

	if (success == true)
	{
		cout << "Student's absences were succesfully edited!" << endl;
	}
	else
	{
		cout << "A student matching that ID could not be found!" << endl;
	}
}