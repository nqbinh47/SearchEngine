#include <iostream>
#include "Header/index.h"
using namespace std;
int main()
{
    while (true)
    {
        cout << "\t-------------UPDATE INDEX AND DICTIONARY-------------\n";
        cout << "|-------------------------------------------------|\n"
             << "|      \t*ENTER YOUR CHOICE:                       |\n"
             << "| -1   \tEXIT PROGRAM                              |\n"
             << "|  0   \tADDING FILES TO INDEX AND UPDATING        |\n"
             << "|  1   \tREMOVING FILES FROM INDEX AND UPDATING    |\n"
             << "|  2   \tCLEAR                                     |\n"
             << "|-------------------------------------------------|\n";
        int choice;
        cin >> choice;
        if (choice == -1)
            break;
        if (choice == 0)
        {
            int lchoice;
            string path;
            cout << "|--------------------------INSTRUCTION ADDING FILES----------------------------|\n"
                 << "|      \t*THERE ARE THREE LEVELS:                                               |\n"
                 << "|     \t0 ADD A SINGLE FILE                                                    |\n"
                 << "|          Ex: ..\\File\\VanBanTV_test\\Am nhac\\AN_TN_ (878).txt                  |\n"
                 << "|     \t1 ADD A FOLDER INCLUDING FILES                                         |\n"
                 << "|          Ex: ..\\File\\VanBanTV_test\\Am nhac                                   |\n"
                 << "|     \t2 ADD A FOLDER INCLUDING FOLDERS                                       |\n"
                 << "|          Ex: ..\\File\\VanBanTV_test                                           |\n"
                 << "|------------------------------------------------------------------------------|\n";
            cout << "       *[Choice '1' is my recommendation for a time-saving purpose]*\n";
            cout << "ENTER YOUR CHOICE:     ";
            cin >> lchoice;
            cout << "ENTER YOUR PATH:       ";
            cin >> path;
            if (add_file_to_index(path, lchoice))
            {
                cout << "ADDING SUCCESSFULLY!\n";
            }
            else
            {
                cout << "ERROR! TRY TO ADD AGAIN\n";
            }
        }
        if(choice == 1)
        {
            int lchoice;
            string path;
            cout << "|--------------------------INSTRUCTION REMOVING FILES--------------------------|\n"
                 << "|      \t*THERE ARE THREE LEVELS:                                               |\n"
                 << "|     \t0 ADD A SINGLE FILE                                                    |\n"
                 << "|          Ex: ..\\File\\VanBanTV_test\\Am nhac\\AN_TN_ (878).txt                  |\n"
                 << "|     \t1 ADD A FOLDER INCLUDING FILES                                         |\n"
                 << "|          Ex: ..\\File\\VanBanTV_test\\Am nhac                                   |\n"
                 << "|     \t2 ADD A FOLDER INCLUDING FOLDERS                                       |\n"
                 << "|          Ex: ..\\File\\VanBanTV_test                                           |\n"
                 << "|------------------------------------------------------------------------------|\n";
            cout << "       *[Choice '1' is my recommendation for a time-saving purpose]*\n";
            cout << "ENTER YOUR CHOICE:     ";
            cin >> lchoice;
            cout << "ENTER YOUR PATH:       ";
            cin >> path;
            if (remove_file_from_metadata(path, lchoice))
            {
                cout << "REMOVING SUCCESSFULLY!\n";
            }
            else
            {
                cout << "ERROR! TRY TO REMOVE AGAIN\n";
            }
        }
        if(choice == 2)
        {
            cout << "|--------------------CLEAR ALL DATA INCLUDING INDEX AND DICTIONARY---------|\n"
                 << " STARTING...                                                                \n";
            clear();
            cout << " DONE!                                                                      \n";
        }
    }
}