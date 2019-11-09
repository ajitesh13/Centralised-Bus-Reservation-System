#include "bits/stdc++.h"
#include "reservations.h"
#include "string.h"
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
using namespace std;
int main()
{
    int mainchoice, subChoiceOne, nt;
    string name, NIC, City, Password, UserName, ContactNumber, DepSt, ArrSt;
    try
    {
    mainMenu:
        cout<<"\n\n\t" <<UNDERLINE<< "Welcome to Indian Roadways(Dept. of Bus & Public Transport)"<<CLOSEUNDERLINE<<"\n\n";
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
            perror("\n\n Please select a Relevant Number from the menu \n\n");
            return main();
        }
        switch (mainchoice)
        {
        case 1:
        {
        subMenu:
            //system("CLS");
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
                perror("\n\nError - Please select a Relevant Number from the menu \n\n");
                goto mainMenu;
                //system("CLS");
            }
            switch (subChoiceOne)
            {
            case 1:
            {
                //system("CLS");
                cout << "========================================================================================\n";
                cout<<"\t\t\t"<<UNDERLINE<<"REGISTER HERE!!"<<CLOSEUNDERLINE<<"\n";
                cout<< "\t(Please fill in this information for the Registration)\n";
                cout<<"Note: All entries in the form should be of one word and should not contain spaces.";
                cout << "\n\nPassenger Name:\n\n";
                cin >> name;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\nPassenger NIC:\n\n ";
                cin >> NIC;
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
                Passenger P1(name, NIC, City, ContactNumber, UserName, Password);
                //cout << "\n\nPress any key to move to the sub Menu.\n\n";
                //system("PAUSE");
                //getchar();
                //system("CLS");
                goto subMenu;
                //system("CLS");
            }; // Sub  choice first case
            break;
            case 2:
            {
                //system("CLS");
                Passenger P2;
                if(P2.Login())
                {
                    P2.SearchFile_and_Update();
                }
                    
                cout << "Press any key to move to the sub Menu.\n\n";
                getchar();
                //system("PAUSE");
                goto subMenu;
                //system("CLS");
            };
            break;
            case 3:
            {
                //system("CLS");
                Passenger P3;
                if(!P3.Login())
                {
                    goto subMenu;
                }
                P3.Deletes();
                cout << "Press any key to move to the sub Menu.\n\n";
                //system("PAUSE");
                goto subMenu;
                //system("CLS");
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
            //system("CLS");
            int subChoice2;
            cout << "================================================================================"
                 << "\n\n\t\t\t\t1.Make a Reservation\n\n"
                 << "\t\t\t\t2.Modify Reservation\n\n"
                 << "\t\t\t\t3.Cancel Reservation\n\n"
                 << "\t\t\t\t4.Show Reservation\n\n"
                 <<"\t\t\t\t5.Go Back to Main Menu"
                 << "\n\nEnter your choice :";
            cin >> subChoice2;
            switch (subChoice2)
            {
            case 1:
            {
                //system("CLS");
                Reservations R2;
                if(!R2.Login()){
                    cout<<"Try Again!!"<<endl;
                    //system("PAUSE");
                    goto mainMenu;
                }
                char check='y';
                //system("CLS");

                // cout << "\n\nCheck seat availabilty(Y/N) ?\n"; 
                 //cin>> check;
                // cin.ignore();

                 //check = tolower(check);
                if (check == 'y')
                {
                    TimeTables T1;
                    Payments Pa1;
                    
                    //T1.Show();
                    
                    //Pa1.Show();
                    cout << "\n\n Passenger NIC:\n\n ";
                    cin >> NIC;
                    string search1, search2;
                

                    
                    cout << "\n\n Enter Your Depature station\n\n ";
                    cin >> DepSt;
                    cout << "\n\n Enter Your Arrival station\n\n ";
                    cin >> ArrSt;
                    cout << "\n\nNo. of Tickets\n\n ";
                    cin >> nt;
                    Reservations R2(NIC, DepSt, ArrSt, nt);
                    R2.CheckSeatAvailabilty(DepSt, ArrSt, nt);
                    
                }
                else{
                    //system("PAUSE");
                    goto mainMenu;
                }
            };
            break;
            case 2:
            {
                //system("CLS");
                Reservations R3;
                if(!R3.Login()){
                    //system("PAUSE");
                    goto mainMenu;
                }
                R3.SearchFile_and_Update();
                cout << "Moving to Main Menu...\n\n";
                //system("PAUSE");
                goto mainMenu;
                //system("CLS");
            };
            break;
            case 3:
            {
                //system("CLS");
                Reservations R4;
                if(!R4.Login()){
                    goto mainMenu;
                }
                R4.Deletes();
                cout << "Moving to the Main Menu...\n\n";
                //system("PAUSE");
                goto mainMenu;
                //system("CLS");
            };
            break;
            // case 4:
            // {
            //     Reservations myr;
            //     myr.Login();

            //     myr.Show();
            //     goto mainMenu;
            // }
            break;
             case 5:
              goto mainMenu;
              break;
             }// second sub switch end    //main switch case 2 ;
        };
        break;
        case 3:
        {
            //system("CLS");
            exit(0);
        };
        break;
        } // main switch end
    }
    catch (...)
    {
        perror("\n\nUnexpected Error occoured, Program is terminating!!\n\n");
        exit(0);
    }
    return 0;
}
