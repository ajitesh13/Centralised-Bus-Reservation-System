#include <bits/stdc++.h>
#include "reservations.h"
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
using namespace std;
string gen_id();

int main()
{
    int mainchoice, subChoiceOne, nt;
    string name, customer_id, City, Password, UserName, ContactNumber, DepSt, ArrSt;
    try
    {
    mainMenu:
        cout << "\n\n\t\t\t   " << UNDERLINE <<bold_on<< "WELCOME TO INDIAN ROADWAYS"<<bold_off << CLOSEUNDERLINE << "\n\n";
        cout << "\n\n\t\t\t\t1.Customer\n\n"
             << "\t\t\t\t2.Reservation\n\n"
             << "\t\t\t\t3.Exit\n\n"
             << "Enter your choice :";
        try
        {
            cin >> mainchoice;
            if ((mainchoice != 1) & (mainchoice != 2) & (mainchoice != 3))
            {
                throw 11;
            }
        }
        catch (int x)
        {
            cout << "\n\n Please select a Relevant Number from the menu \n\n";
            return main();
        }
        switch (mainchoice)
        {
        case 1:
        {
        subMenu:

            cout << "============================================================================================\n"
                 << "\n\n\t\t\t\t1.Register\n\n"
                 << "\t\t\t\t2.Modify\n\n"
                 << "\t\t\t\t3.Remove Account\n\n"
                 << "\t\t\t\t4.Go Back to Main Menu\n\n"
                 << "Enter your choice :";
            try
            {
                cin >> subChoiceOne;
                if ((subChoiceOne != 1) & (subChoiceOne != 2) & (subChoiceOne != 3) & (subChoiceOne != 4))
                {
                    throw 12;
                }
            }
            catch (int y)
            {
                cout << "\n\nError - Please select a Relevant Number from the menu \n\n";
                goto subMenu;
            }
            switch (subChoiceOne)
            {
            case 1:
            {

                cout << "========================================================================================\n";
                cout << "\t\t\t" << UNDERLINE <<bold_on<< "REGISTER HERE!!"<<bold_off << CLOSEUNDERLINE << "\n\n";
                cout << "\t(Please fill in this information for the Registration)\n";
                cout << "Note: All entries in the form should be of one word and should not contain spaces.";
                cout << "\n\nPassenger Name:\n\n";
                cin >> name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\nPassenger City:\n\n ";
                cin >> City;
                cout << "\n\nPassenger : Contact No\n\n ";
                cin >> ContactNumber;
                cout << "\n\nPassenger : UserName \n\n ";
                cin >> UserName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\nPassenger : Password\n\n ";
                cin >> Password;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                //make the password protective
                customer_id = (gen_id());
                cout << "\nYour Customer ID is: " <<bold_on<< customer_id<< bold_off << endl;
                cout << "Remember this for login and other future purposes.\n"<< endl;
                Passenger P1(name, customer_id, City, ContactNumber, UserName, Password);
                goto mainMenu;

            }; // Sub  choice first case
            break;
            case 2:
            {

                Passenger P2;
                if (P2.Login())
                {
                    P2.SearchFile_and_Update();
                }
                goto subMenu;
            };
            break;
            case 3:
            {
                Passenger P3;
                if (!P3.Login())
                {
                    goto subMenu;
                }
                P3.Deletes();
                goto subMenu;
            };
            break;
            case 4:
                goto mainMenu;
                break;
            } //sub switch one
        };    //main choice first case
        break;
        case 2:
        {
        subMenu2:
            int subChoice2;
            cout << "================================================================================"
                 << "\n\n\t\t\t\t1.Make a Reservation\n\n"
                 << "\t\t\t\t2.Modify Reservation\n\n"
                 << "\t\t\t\t3.Cancel Reservation\n\n"
                 << "\t\t\t\t4.Show Reservation\n\n"
                 << "\t\t\t\t5.Go Back to Main Menu"
                 << "\n\nEnter your choice :";
            try
            {
                cin >> subChoice2;
                if ((subChoice2 != 1) & (subChoice2 != 2) & (subChoice2 != 3) & (subChoice2 != 4) & (subChoice2 != 5))
                {
                    throw 13;
                }
            }
            catch (int y)
            {
                cout << "\n\nError - Please select a Relevant Number from the menu \n\n";
                goto subMenu2;
            }
            switch (subChoice2)
            {
            case 1:
            {
                Reservations R2;
                if (!R2.Login())
                {
                    cout << "Try Again!!" << endl;
                    goto subMenu2;
                }
                char check = 'y';
                if (check == 'y')
                {
                    Payments Pa1;
                    cout << "\nPassenger Customer ID:\n\n";
                    cin >> customer_id;
                    Pa1.Show();
                    string search1, search2;
                    cout << "\n\n Enter Your Depature station\n\n ";
                    cin >> DepSt;
                    cout << "\n\n Enter Your Arrival station\n\n ";
                    cin >> ArrSt;
                    cout << "\n\nNo. of Tickets\n\n ";
                    cin >> nt;
                    Reservations R2(customer_id, DepSt, ArrSt, nt);
                    goto mainMenu;
                }
            };
            break;
            case 2:
            {
                Reservations R3;
                if (!R3.Login())
                {
                    goto subMenu2;
                }
                R3.SearchFile_and_Update();
                cout << "Moving to Main Menu...\n\n";
                goto subMenu2;
            };
            break;
            case 3:
            {
                Reservations R4;
                if (!R4.Login())
                {
                    goto subMenu2;
                }
                R4.Deletes();
                cout << "Moving to the Main Menu...\n\n";
                goto mainMenu;
            };
            break;
                case 4:
                {
                    Reservations myr;
                    myr.Login();

                    myr.Show();
                    goto mainMenu;
                }
                break;
            case 5:
                goto mainMenu;
                break;
            } // second sub switch end  
        };
        break;
        case 3:
        {
            cout << "\n\nThanks for Using Our Service! Hope to see you again!\n\n";
            exit(0);
        };
        break;
        } // main switch end
    }
    catch (...)
    {
        cout << "\n\nUnexpected Error occoured, Program is terminating!!\n\n";
        exit(0);
    }
    return 0;
}

//generates a unique customer_id
string gen_id(){
    long long x =190000;
    string line;
    /* Creating input filestream */ 
    ifstream file("Passenger.txt");
    string s1, s2, s3, s4, s5, s6, id;
    while (file >>  s1 >> s2 >> s3 >> s4 >> s5 >> s6){
        x = stoll(s1);
    }
    id = to_string(x+1);
    return id;
}