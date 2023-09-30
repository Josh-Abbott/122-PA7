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

#include "Menu.h"

 /*************************************************************
  * Function: displayMenu ()                                  *
  * Date Created: 4/4/22									  *
  * Date Last Modified: 4/4/22                                *
  * Description: This function displays the menu options.	  *
  * Input parameters: Nothing.					              *
  * Returns: Nothing.	                                      *
  * Preconditions: None.					  .			      *
  * Postconditions: The options are displayed succesfully.    *
  *************************************************************/

void Menu::displayMenu()
{
	cout << "-*- ATTENDANCE TRACKER -*-" << endl;
	cout << "1. Import course list" << endl;
	cout << "2. Load master list" << endl;
	cout << "3. Store master list" << endl;
	cout << "4. Mark absences" << endl;
	cout << "5. Edit absences" << endl;
	cout << "6. Generate report" << endl;
	cout << "7. Exit" << endl;
}

/*************************************************************
 * Function: startMenu ()                                    *
 * Date Created: 4/4/22										 *
 * Date Last Modified: 4/7/22                                *
 * Description: This function starts the menu and runs the	 *
 *				 selection process for the program.		     *
 * Input parameters: Nothing.					             *
 * Returns: Nothing.	                                     *
 * Preconditions: None.					  .					 *
 * Postconditions: The operations are performed succesfully. *
 *************************************************************/

void Menu::startMenu()
{
	int choice = 0, menu_loop = 0, menu_loop2 = 0;
	bool loaded = false;
	bool imported = false;

	ifstream infileC;
	ifstream infileM;
	ofstream outfile;
	ofstream report;

	List<Data> recordsList;

	while (menu_loop == 0)
	{
		system("cls");
		displayMenu();
		cin >> choice;

		switch (choice)
		{
		case 1: // import course list
			infileC.open("classList.csv");
			if (infileC.good() && loaded == false && imported == false) // checking if it actually exists & is an option
			{
				recordsList.loadList(infileC, false);
				imported = true;
				cout << "Course list succesfully imported!" << endl;
			}
			else
			{
				cout << "Course list could not be imported!" << endl;
			}
			infileC.close();
			system("pause");
			break;
		case 2: // load master list
			infileM.open("master.txt");
			if (infileM.good() && loaded == false && imported == false) // checking if it actually exists & is an option
			{
				recordsList.loadList(infileM, true);
				loaded = true;
				cout << "Master list succesfully loaded!" << endl;
			}
			else
			{
				cout << "Master list could not be loaded!" << endl;
			}
			infileM.close();
			system("pause");
			break;
		case 3: // store master list
			outfile.open("master.txt");
			if (loaded == true || imported == true)
			{
				if (outfile.good()) // checking if it actually exists & is an option
				{
					recordsList.writeMaster(outfile);
					cout << "Master list was succesfully stored!" << endl;
				}
				else
				{
					cout << "Master list could not be stored to!" << endl;
				}
			}
			else
			{
				cout << "Data needs to be imported or loaded to be stored!" << endl;
			}
			system("pause");
			break;
		case 4: // mark absences
			if (imported == true)
			{
				recordsList.markAbsences();
				cout << "The absences have succesfully been marked!" << endl;
			}
			else
			{
				cout << "You need to import data first!" << endl;
			}
			system("pause");
			break;
		case 5: // edit (bonus)!!!
			if (imported == true || loaded == true)
			{
				recordsList.editAbsences();
			}
			else
			{
				cout << "You need to import data first!" << endl;
			}

			system("pause");
			break;
		case 6: // generate report (options)
			if (loaded == true || imported == true)
			{
				menu_loop2 = 0;
				report.open("report.txt");
				if (report.good())
				{
					while (menu_loop2 == 0)
					{
						system("cls");
						cout << "1. Generate report for all students" << endl;
						cout << "2. Generate report for students over an amount" << endl;
						cin >> choice;

						switch (choice)
						{
						case 1: // generate report for all students; showing only the most recent absence (use peek)

							recordsList.generateReport(1, 0, report);
							menu_loop2 = 1;
							break;
						case 2: // generate report for students with absences that match or exceed a number entered

							int amount;
							cout << "Please enter a minimum absence amount: " << endl;
							cin >> amount;

							recordsList.generateReport(2, amount, report);
							menu_loop2 = 1;
							break;
						}
					}
				}
				cout << "Succesfully generated report.txt" << endl;
			}
			else
			{
				cout << "You need to load or import data before generating!" << endl;
			}			
			system("pause");
			break;
		case 7: // exit
			menu_loop = 1;
			cout << "Thank you for using this application!" << endl;
			break;
		}
	}
}