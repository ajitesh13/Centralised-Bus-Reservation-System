#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstdio>
//#include <conio.h>
//#include <curses.h>
#include <cstdlib>
#include <stdio.h>
using namespace std;
int count01 ;
// class Passenger
class Passenger
 {
                string    str_City, str_ContactNumber, str_UserName, str_Password, str_name ;
            protected:
                string   str_NIC ;
            public:
                Passenger(){}
                Passenger(string name, string NIC, string City, string ContactNumber, string Username, string Password) ;
                void Login();
                void SearchFile_and_Update() ;
                void Deletes() ;
                ~Passenger() ;
};
// class Seats
class Seats{
        protected:
            int i_SeatNo ;
        public:
            void CheckSeatAvailabilty() ;
};
// class Reservations
class Reservations : public Passenger,public Seats{
protected :
        string str_Arrival_St, str_Dep_St ;
        int  i_No_Tickets, i_Charge ;
        double i_total ;
    public:
                Reservations();
                // to make a reservation
                Reservations(string NIC, string DeptSt, string ArrivalSt, int NoTickets );
                void SearchFile_and_Update();
                // ModifyReservation Function
                void Deletes();
                // cancel reservation function
                void Show(string, string, string, int, int, int);
                double  CalculateFee(double, int) ;
                ~Reservations();
};
// class TimeTables
class TimeTables : public Reservations{
    public:
                void Show()const ;
                ~TimeTables ();
};
// class Payments
class Payments: public Reservations{
    public :
                void Show()const ;
                ~Payments();
};
// payments - show
inline void Payments :: Show()const{
                    fstream payments ;
                    payments.open("Payments.txt",ios :: in)  ;
                    string line ;
                    cout << "\n\n-----------------Payment Scheme------------------\n\n" ;
                    while(!payments.eof()){
                            getline(payments,line);
                            cout << line << "\n" ;
                    }
}
// timetables - Show
inline void TimeTables :: Show()const{
                    string line2 ;
                    ifstream timetable("Timetables.txt") ;
                    cout << "\n\n----------------TimeTable-------------------------\n\n" ;
                    while(!timetable.eof()){
                            getline(timetable,line2) ;
                            cout << line2 << "\n\n" ;
                    }
}
// Reservations constructor
inline Reservations :: Reservations(string NIC, string DeptSt, string ArrivalSt, int NoTickets ){
                        Reservations  r2 ;
                        str_NIC = NIC ;
                        str_Dep_St = DeptSt ;
                        str_Arrival_St = ArrivalSt ;
                        i_No_Tickets = NoTickets ;
                        ifstream PaymentsRead ;
                        PaymentsRead.open("Payments.txt") ;
                        double  ch ;
                        string s1,s2 ;
                        while(PaymentsRead >> s1 >> s2 >> ch){
                                if((str_Dep_St == s1) & (str_Arrival_St == s2)){
                                    i_total = CalculateFee(ch, i_No_Tickets);
                                }
                        }
                        char confirmation ;
                            cout << "\n\nConfirm the Reservation(Y/N): \n\n" ;
                            cin >> confirmation ;
                            confirmation = tolower(confirmation);
                        if(confirmation == 'y'){
                                fstream Reservations ;
                                fstream Seats ;
                                string line ;
                                Reservations.open("Reservations.txt", ios::app | ios:: out | ios::ate);
                                Seats.open("Seat.txt", ios :: app | ios :: out | ios :: ate | ios :: in);
                                Seats <<  str_NIC << "\t" << i_No_Tickets <<"\n" ;
                                Reservations << str_NIC <<"\t"<< str_Dep_St <<"\t"<< str_Arrival_St <<"\t"<< i_No_Tickets
                                            << "\t" << i_total <<"\n";
                                Reservations.close();
                        }
                        else{
                                cout << "\n\nConfirmation denied and exiting from the program \n" ;
                                exit(0) ;
                        }
                                r2.Show(str_NIC, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total  ) ;
}
// modify Reservation function
inline void Reservations :: SearchFile_and_Update(){
                                Reservations  r1 ;
                                double ch;
                                char confirmation ;
                                int   s7;
                                    ifstream reservationsIn ; //SEARCH
                                    ifstream  seatsIn; //search
                                    fstream  reservationsOut ;
                                    fstream seatsOut ;
                                    cout << "\n\nConfirm the You wants to modify reservation(Y/N): \n\n" ;
                                    cin >> confirmation ;
                                    confirmation = tolower(confirmation) ;
                                    system("CLS");
                        if(confirmation == 'y'){
                                    TimeTables T1 ;
                                    Payments P1 ;
                                    T1.Show();
                                    P1.Show() ;
                                    cout << "\n\n-------------------------------------------------\n\n" ;
                                    cout <<"\n\nEnter new your NIC :\n\n" ;
                                    cin >> str_NIC ;
                                     cout << "\n\n-------------------------------------------------\n\n" ;
                                    cout << "\n\n New Depature station\n\n " ;
                                    cin >> str_Dep_St ;
                                    cout << "\n\n New Arrival station\n\n " ;
                                    cin >> str_Arrival_St ;
                                    cout << "\n\nNew  No. of Tickets\n\n " ;
                                    cin >> i_No_Tickets ;
                                    fstream PaymentsRead ;
                                    PaymentsRead.open("Payments.txt", ios :: in) ;
                                    string s1,s2,s3,s4,s5,s6 ;
                                        while(PaymentsRead >> s1 >> s2 >> ch){
                                                if((str_Dep_St == s1) & (str_Arrival_St == s2)){
                                                        cout << ch ;
                                                        i_total = CalculateFee(ch, i_No_Tickets);
                                                }
                                        } cout << ch ;
                        reservationsIn.open("Reservations.txt");
                        seatsIn.open("Seats.txt") ;
                                while(reservationsIn >> s1 >> s2 >> s3 >> s4 >> s5){
                                    reservationsOut.open("temp7.txt",ios :: app) ;
                                        if(s1 == str_NIC){
                                            while(seatsIn >> s6 >> s7){
                                                seatsOut.open("temp8.txt",ios :: app) ;
                                                    if(s6 == str_NIC){
                                                            seatsOut <<  str_NIC << "\t" << i_No_Tickets << "\n";
                                                            reservationsOut << str_NIC <<"\t"<< str_Dep_St <<"\t"<< str_Arrival_St <<"\t"<< i_No_Tickets
                                                                       << "\t" << i_total    << "\n";
                                                            cout << "\n\nRecord found & updated!\n\n" ;
                                                            cout << "\n\n-------------------------------------------------\n\n" ;
                                                                    count01 ++ ;
                                                    }
                                                    else {
                                                            seatsOut << s6 << "\t" <<  s7 << "\n";
                                                            reservationsOut << s1 <<"\t"<< s2 <<"\t"<< s3  <<"\t"<< s4<<"\t"
                                                                            << s5 <<"\n";
                                                        }
                                                        seatsOut.close();
                                                        reservationsOut.close();
                                    } // end of while - match4
                                } // end of outer if
                            } // end of outer while
                        }// end of confirmation if
                                     if(count01 == 0){
                                                cout << "\n\nRecord  could not be found!\n\n" ;
                                                remove("temp7.txt") ;
                                                remove("temp8.txt") ;
                                                }
                                    if(count01 != 0){
                                                remove("Reservations.txt");
                                                int r = rename("temp7.txt","Reservations.txt");
                                                remove("Seats.txt");
                                                int r2 =  rename("temp8.txt","Seats.txt");
                                                    if ( (r == 0) & (r2 == 0) )
                                                            puts ( "File successfully renamed" );
                                                    else
                                                            perror( "Error renaming file" );
                                            }
                                                seatsOut.close() ;
                                                reservationsOut.close();
                                                cout << "\n\nDone!\n\n" ;
                                            r1.Show(str_NIC, str_Dep_St, str_Arrival_St, i_No_Tickets,ch, i_total  ) ;
}
// cancel Reservations
inline void Reservations :: Deletes(){
                                char confirmation ;
                                string  nic, nic2, dept, arr, s8;
                                int nt, ch, tot,sn;
                                ifstream ResIn ; //reservations
                                ifstream SeatIn ; //seats
                                fstream ResOut ;
                                fstream SeatOut ;
                                    cout << "\n\nConfirm to Cancel the Reservation(Y/N): \n\n" ;
                                    cin >> confirmation ;
                                    confirmation = tolower(confirmation) ;
                        if(confirmation == 'y'){
                                    cout << "\n\n-------------------------------------------------\n\n" ;
                                    cout <<"\n\nEnter your NIC :\n\n" ;
                                    cin >> str_NIC ;
                                     cout << "\n\n-------------------------------------------------\n\n" ;
                            ResIn.open("Reservations.txt");
                            SeatIn.open("Seats.txt") ;
                                while(ResIn >> nic >> dept >> arr >> nt >> ch >> tot){
                                    ResOut.open("temp5.txt",ios :: app | ios :: out) ;
                                        if(nic != str_NIC){
                                            while(SeatIn >> nic2 >> sn){
                                                SeatOut.open("temp6.txt",ios :: app | ios :: out) ;
                                                    if(nic2 != str_NIC){
                                                            SeatOut <<  nic2 << "\t" << nt << "\n";
                                                            ResOut << nic <<"\t"<< dept <<"\t"<< arr <<"\t"<< nt <<"\t"<< ch
                                                                       << tot  << "\n";
                                                    }
                                                    else {
                                                            count01 ++ ;
                                    }
                                    } // end of while - match4
                                        } // end of outer if
                                } // end of outer while
                        }// end of confirmation if
                                        ResOut.close();
                                        SeatOut.close();
                                     if(count01 == 0){
                                                cout << "\n\nRecord  could not be found!\n\n" ;
                                                remove("temp5.txt") ;
                                                remove("temp6.txt") ;
                                                }
                                    if(count01 > 0){
                                                remove("Reservations.txt");
                                                rename("temp5.txt","Reservations.txt");
                                                remove("Seats.txt");
                                                rename("temp6.txt","Seats.txt");
                                            }
                                                ResIn.close() ;
                                                cout << "\n\nDone!\n\n" ;
}
// Reservations - Show
inline void Reservations :: Show(string NIC, string Dept_St, string Arrival_St, int No_Tickets, int Charge, int total ){
                        system("CLS") ;
                  cout <<"\n\nNIC :" << NIC  << "\n"
                       <<"\n\nDep. St. :" << Dept_St << "\t\t"
                       <<"Arrival St. :" << Arrival_St <<"\n\n"
                       <<"No_Tickets :" << No_Tickets <<"\t"
                       <<"Charge for one ticket :" << Charge <<"\t"
                       << "total = " << total <<"\n\n" ;
}
// Reservations Deconstructor
inline Reservations :: ~Reservations(){}
// Payments Calculate
inline double Reservations :: CalculateFee(double fee, int nt)
{
   i_total = nt * fee ;
   return i_total ;
}
// Seats - CheckSeatAvailability
 inline void  Seats ::  CheckSeatAvailabilty(){
                    int  NoLines = 0 ;
                    string line ;
                    ifstream SeatAvailbility ;
                    SeatAvailbility.open("Seats.txt");
                    while(SeatAvailbility.eof()){
                            getline(SeatAvailbility,line) ;
                            NoLines ++;
                    }
                    i_SeatNo = NoLines  ;
                            if(i_SeatNo == 32 ){
                            cout <<"\n\nSeats are not available at the moment.\n\n" ;
                            }
                            else
                            {
                            cout <<"\n\n" << 32 - i_SeatNo << "  are available.\n\n" ;
                            }
                    SeatAvailbility.close();
                } // seat availability  function end
// Delete record function
inline void Passenger ::  Deletes(){
                    string   nic, name, city, username, password , cn;
                     cout <<"\n\nEnter your NIC to delete the record :\n\n" ;
                     cin >> str_NIC ;
                        fstream deleteF ;
                        ofstream df ;
                        deleteF.open("Passenger.txt", ios::in | ios :: out);
                            while(deleteF >> nic >> name >> city >> cn >>username >> password){
                                    df.open("temp2.txt",ios :: ate ) ;
                                        if(nic != str_NIC){
                                            df    << nic <<"\t"<< name <<"\t"<< city <<"\t"
                                                      << cn <<"\t"<< username
                                                      <<"\t"  << password << "\n";
                                        }
                                        else {
                                               count01 ++ ;
                                        }
                                            df.close() ;
                                }// end of while
                                  deleteF.close() ;
                                if(count01 == 0){
                                                remove("temp2.txt") ;
                                                cout << "\n\nRecord not found\n\n" ;
                                                }
                                            if(count01 > 0){
                                                remove("Passenger.txt");
                                                rename("temp2.txt","Passenger.txt");
                                            }
                                        cout << "\n\nDone!\n\n" ;
            }//end of function DeleteRecord
// Search file and update
inline void Passenger :: SearchFile_and_Update(){
                      string   nic, name, city, username, password , cn;
                                    cout << "\n\n-------------------------------------------------\n\n" ;
                                    cout <<"\n\nEnter your NIC :\n\n" ;
                                    cin >> str_NIC ;
                        ifstream PassengerIn ;
                        ofstream writeFile ;
                        PassengerIn.open("Passenger.txt");
                                while(PassengerIn >> nic >> name >> city >> cn >>username >> password){
                                    writeFile.open("temp1.txt",ios :: app ) ;
                                        if(nic == str_NIC){
                                            cout << "\n\nRecord found!\n\n" ;
                                            cout << "\n\n-------------------------------------------------\n\n" ;
                                            cout << "\n\nNew Passenger Name:\n\n "  ;
                                            cin >> str_name ;
                                            cout << "\n\nNew Passenger City:\n\n " ;//address change to city
                                            cin >> str_City ;
                                            cout << "\n\nNew Passenger : Contact No\n\n " ;
                                            cin >> str_ContactNumber ;
                                            cout << "\n\nNew Passenger : UserName \n\n " ;
                                            cin >> str_UserName ;
                                            cout << "\n\nNew Passenger : Password\n\n " ;
                                            cin >> str_Password ;
                                            writeFile << str_NIC <<"\t"<< str_name <<"\t"<< str_City <<"\t"
                                                      << str_ContactNumber <<"\t"<< str_UserName
                                                      <<"\t"  << str_Password << "\n";
                                            count01 ++ ;
                                    }
                                    else{
                                            writeFile << nic <<"\t"<< name <<"\t"<< city <<"\t"
                                                      << cn <<"\t"<< username
                                                      <<"\t"  << password << "\n";
                                    }
                                        writeFile.close();
                                }// end of while
                                  PassengerIn.close() ;
                                if(count01 == 0){
                                                cout << "\n\nRecord  could not be found!\n\n" ;
                                                remove("temp1.txt") ;
                                                }
                                    if(count01 > 0){
                                                remove("Passenger.txt");
                                            rename("temp1.txt","Passenger.txt");
                                            }
                                                cout << "\n\nDone!\n\n" ;
            }
// Login
 inline void Passenger :: Login()
            {
                    string username01, password01 ;
                            cout <<"-------------------------------------------"
                                 << "\n\nLogin Screen\n\n"
                                 << "\n\nEnter your UserName:\n\n" ;
                            cin >> username01 ;
                            cout << "\n\nEnter your Password:\n\n" ;
                            //system("COLOR 6E") ;
                            cin >> password01 ;
                            ifstream matchup ;
                            matchup.open("Passenger.txt", ios::in );
                    string s1,s2, s3, s4, s5, s6 ;
                    while(matchup >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 ){
                           if(s5 == username01 && s6 == password01 ){
                                cout <<"\n\nLogged in Successfully.\n\n";
                           }
                            ///////
                        } //end of while
            }
// Passenger constructor
 inline Passenger ::   Passenger(string name, string NIC, string City, string ContactNumber, string Username, string Password){
                    str_name = name ;
                    str_NIC = NIC ;
                    str_City = City ;
                    str_ContactNumber = ContactNumber ;
                    str_UserName = Username ;
                    str_Password = Password ;
                fstream registration ;
                registration.open("Passenger.txt", ios::app | ios:: out | ios::ate);
                registration << str_NIC <<"\t"<< str_name <<"\t"<< str_City <<"\t"<< str_ContactNumber <<"\t"<< str_UserName
                             <<"\t"  << str_Password << "\n";
                registration.close();
            }
// Passenger deconstructor
inline Passenger :: ~Passenger(){}
inline TimeTables :: ~TimeTables(){}
inline Payments :: ~Payments(){}
// Reservations constructor
inline Reservations :: Reservations(){}
/*************************************************************************************************************************************/
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