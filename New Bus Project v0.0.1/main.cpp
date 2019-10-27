#include "bits/stdc++.h"
#include "iostream"
#include "fstream"
#include "cstdio"
// #include "timetables.h"
// #include "payments.h"
//#include "passenger.h"
//#include "seats.h"
#include "reservations.h"
using namespace std;
//int count01 ;
int main()
{
    int mainchoice, subChoiceOne , nt ;
    string name, NIC,  City, Password,  UserName, ContactNumber, DepSt, ArrSt;
    try{
        mainMenu :
                system("COLOR 70");
            cout << "\n\n Welcome to SPRPTA Bus Ticket Reservation System \n\n" ;
            cout << "\n\n  1.Customer\n\n"
                 << "  2.Reservation\n\n"
                 << "  3.Exit\n\n"
                 << "\n\n Enter your choice :" ;
            try{
            cin >> mainchoice ;
            if ((mainchoice !=1) & (mainchoice != 2) & (mainchoice != 3 )){
                throw 11 ;
            }
        }
        catch(int x){
            perror("\n\n Please select a Relevant Number from the menu \n\n" );
            return main() ;
        }
            switch(mainchoice){
                case 1:{
                            subMenu :
                                        system("CLS");
                            cout << "-------------------------------------------------\n\n"
                                    <<  "\n\n1.Register\n\n"
                                    << "2.Modify\n\n"
                                    << "3.Remove Account\n\n"
                                    << "\n\nEnter your choice :" ;
                    try{
                            cin >> subChoiceOne ;
          if ((subChoiceOne !=1) & (subChoiceOne != 2) & (subChoiceOne != 3 )){
                throw 12 ;
            }
                    }
            catch(int y){
                perror( "\n\nError - Please select a Relevant Number from the menu \n\n") ;
                goto mainMenu ;
                system("CLS");
        }
                            switch(subChoiceOne){
                          case 1: {
                                    system("CLS");
                                     cout << "-------------------------------------------------\n\n"
                                          << "Please fill in this information for the Registration";
                                     cout << "\n\nPassenger Name:\n\n "  ;
                                     cin >> name ;
                                     cout << "\n\nPassenger NIC:\n\n " ;
                                     cin >> NIC ;
                                    cout << "\n\nPassenger City:\n\n " ;
                                    cin >> City ;
                                    cout << "\n\nPassenger : Contact No\n\n " ;
                                    cin >> ContactNumber ;
                                    cout << "\n\nPassenger : UserName \n\n " ;
                                    cin >> UserName ;
                                    cout << "\n\nPassenger : Password\n\n " ;
                                    cin >> Password ;
                                    //make the password protective
                        Passenger P1(name, NIC,  City, ContactNumber , UserName, Password );
                        cout << "\n\nPress any key to move to the sub Menu.\n\n" ;
                        system("PAUSE") ;
                        system("CLS");
                        goto subMenu ;
                        system("CLS");
                        }; // Sub  choice first case
                                break ;
                        case 2:{
                                    system("CLS");
                                    Passenger P2 ;
                                    P2.Login() ;
                                    P2.SearchFile_and_Update() ;
                                    cout << "Press any key to move to the sub Menu.\n\n" ;
                                    system("PAUSE") ;
                                    goto subMenu ;
                                    system("CLS");
                        } ;
                                break ;
                        case 3:{
                                system("CLS");
                                Passenger P3 ;
                                P3.Login() ;
                                P3.Deletes() ;
                                cout << "Press any key to move to the sub Menu.\n\n" ;
                                system("PAUSE") ;
                                goto subMenu ;
                                system("CLS");
                       };
                                break ;
                            }//sub switch one
                };//main choice first case
                    break ;
        case 2:{
                        system("CLS");
                        int subChoice2 ;
                        cout << "-------------------------------------------------\n\n"
                             <<  "\n\n1.Make a Reservation\n\n"
                             << "2.Modify Reservation\n\n"
                             << "3.Cancel Reservation\n\n"
                             << "\n\nEnter your choice :" ;
                         cin >> subChoice2 ;
                    switch(subChoice2){
                         case 1:{
                                    system("CLS");
                                    Reservations R2 ;
                                    R2.Login() ;
                                    char check ;
                                    system("CLS");
                                    cout << "\n\nCheck seat availabilty(Y/N) ?\n" ;
                                    cin >> check ;
                                    check = tolower(check);
                                    if(check == 'y'){
                                       TimeTables T1 ;
                                       Payments P1 ;
                                       R2.CheckSeatAvailabilty();
                                       T1.Show();
                                       P1.Show();
                                    cout << "\n\n Passenger NIC:\n\n "  ;
                                    cin >> NIC ;
                                    cout << "\n\n Depature station\n\n " ;
                                    cin >> DepSt ;
                                    cout << "\n\n Arrival station\n\n " ;
                                    cin >> ArrSt ;
                                    cout << "\n\nNo. of Tickets\n\n " ;
                                    cin >> nt ;
                                    Reservations R2(NIC,DepSt, ArrSt, nt);
                                    }
                                    goto mainMenu ;
                                };
                                    break ;
                            case 2:{
                                         system("CLS");
                                         Reservations R3 ;
                                         R3.Login() ;
                                         R3.SearchFile_and_Update() ;
                                         cout << "Press any key to move to the main Menu.\n\n" ;
                                         system("PAUSE") ;
                                         goto mainMenu ;
                                         system("CLS");
                                        };
                                        break ;
                            case 3:{
                                              system("CLS");
                                              Reservations R4 ;
                                              R4.Login() ;
                                              R4.Deletes() ;
                                              cout << "Press any key to move to the main Menu.\n\n" ;
                                              system("PAUSE") ;
                                              goto mainMenu ;
                                              system("CLS");
                                            };
                                        break ;
                    } // second sub switch end
                    //main switch case 2 ;
                };
                    break ;
        case 3:{
                    system("CLS");
                    exit(0);
                };
                    break ;
    } // main switch end
    }
    catch(...){
        perror ("\n\nUnexpected Error occoured, Program is terminating\n\n") ;
         exit(0);
    }
return 0;
 }