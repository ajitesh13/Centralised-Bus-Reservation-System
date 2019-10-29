#include "bits/stdc++.h"
#include "seats.h"
#include "passenger.h"

using namespace std;


// class Reservations
class Reservations : public Passenger, public Seats
{
protected:
    string str_Arrival_St, str_Dep_St;
    int i_No_Tickets, i_Charge;
    double i_total;

public:
    Reservations();
    // to make a reservation
    Reservations(string NIC, string DeptSt, string ArrivalSt, int NoTickets);
    void SearchFile_and_Update();
    // ModifyReservation Function
    void Deletes();
    // cancel reservation function
    void Show(string, string, string, int, int, int);
    double CalculateFee(double, int);
    ~Reservations();
};
inline Reservations :: Reservations(){}

// class Payments
class Payments : public Reservations
{
public:
    void Show() const;
    ~Payments();
};

// payments - show
inline void Payments ::Show() const
{
    fstream payments;
    payments.open("Payments.txt", ios::in);
    string line;
    cout << "\n\n-----------------Payment Scheme------------------\n\n";
    while (!payments.eof())
    {
        getline(payments, line);
        cout << line << "\n";
    }
}
inline Payments :: ~Payments(){}

// class TimeTables
class TimeTables : public Reservations
{
public:
    void Show() const;
    ~TimeTables();
};


// timetables - Show
inline void TimeTables ::Show() const
{
    string line2;
    ifstream timetable("Timetables.txt");
    cout << "\n\n----------------TimeTable-------------------------\n\n";
    while (!timetable.eof())
    {
        getline(timetable, line2);
        cout << line2 << "\n\n";
    }
}
inline TimeTables :: ~TimeTables(){}

// Reservations constructor
inline Reservations ::Reservations(string NIC, string DeptSt, string ArrivalSt, int NoTickets)
{
    Reservations r2;
    str_NIC = NIC;
    str_Dep_St = DeptSt;
    str_Arrival_St = ArrivalSt;
    i_No_Tickets = NoTickets;
    ifstream PaymentsRead;
    PaymentsRead.open("Payments.txt");
    double ch;
    string s1, s2;
    while (PaymentsRead >> s1 >> s2 >> ch)
    {
        if ((str_Dep_St == s1) & (str_Arrival_St == s2))
        {
            i_total = CalculateFee(ch, i_No_Tickets);
        }
    }
    char confirmation;
    cout << "\n\nConfirm the Reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        fstream Reservations;
        fstream Seats;
        string line;
        Reservations.open("Reservations.txt", ios::app | ios::out | ios::ate);
        Seats.open("Seat.txt", ios ::app | ios ::out | ios ::ate | ios ::in);
        Seats << str_NIC << "\t" << i_No_Tickets << "\n";
        Reservations << str_NIC << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                     << "\t" << i_total << "\n";
        Reservations.close();
    }
    else
    {
        cout << "\n\nConfirmation denied and exiting from the program \n";
        exit(0);
    }
    r2.Show(str_NIC, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total);
}

// modify Reservation function
inline void Reservations ::SearchFile_and_Update()
{
    Reservations r1;
    double ch;
    char confirmation;
    int s7;
    ifstream reservationsIn; //SEARCH
    ifstream seatsIn;        //search
    fstream reservationsOut;
    fstream seatsOut;
    cout << "\n\nConfirm the You wants to modify reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    //system("CLS");
    if (confirmation == 'y')
    {
        TimeTables T1;
        Payments P1;
        T1.Show();
        P1.Show();
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\nEnter new your NIC :\n\n";
        cin >> str_NIC;
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\n New Depature station\n\n ";
        cin >> str_Dep_St;
        cout << "\n\n New Arrival station\n\n ";
        cin >> str_Arrival_St;
        cout << "\n\nNew  No. of Tickets\n\n ";
        cin >> i_No_Tickets;
        fstream PaymentsRead;
        PaymentsRead.open("Payments.txt", ios ::in);
        string s1, s2, s3, s4, s5, s6;
        while (PaymentsRead >> s1 >> s2 >> ch)
        {
            if ((str_Dep_St == s1) & (str_Arrival_St == s2))
            {
                cout << ch;
                i_total = CalculateFee(ch, i_No_Tickets);
            }
        }
        cout << ch;
        reservationsIn.open("Reservations.txt");
        seatsIn.open("Seats.txt");
        while (reservationsIn >> s1 >> s2 >> s3 >> s4 >> s5)
        {
            reservationsOut.open("temp7.txt", ios ::app);
            if (s1 == str_NIC)
            {
                while (seatsIn >> s6 >> s7)
                {
                    seatsOut.open("temp8.txt", ios ::app);
                    if (s6 == str_NIC)
                    {
                        seatsOut << str_NIC << "\t" << i_No_Tickets << "\n";
                        reservationsOut << str_NIC << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                                        << "\t" << i_total << "\n";
                        cout << "\n\nRecord found & updated!\n\n";
                        cout << "\n\n-------------------------------------------------\n\n";
                        count01++;
                    }
                    else
                    {
                        seatsOut << s6 << "\t" << s7 << "\n";
                        reservationsOut << s1 << "\t" << s2 << "\t" << s3 << "\t" << s4 << "\t"
                                        << s5 << "\n";
                    }
                    seatsOut.close();
                    reservationsOut.close();
                } // end of while - match4
            }// end of outer if
        }// end of outer while
    }// end of confirmation if
    if (count01 == 0)
    {
        cout << "\n\nRecord  could not be found!\n\n";
        remove("temp7.txt");
        remove("temp8.txt");
    }
    if (count01 != 0)
    {
        remove("Reservations.txt");
        int r = rename("temp7.txt", "Reservations.txt");
        remove("Seats.txt");
        int r2 = rename("temp8.txt", "Seats.txt");
        if ((r == 0) & (r2 == 0))
            puts("File successfully renamed");
        else
            perror("Error renaming file");
    }
    seatsOut.close();
    reservationsOut.close();
    cout << "\n\nDone!\n\n";
    r1.Show(str_NIC, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total);
}

// cancel Reservations
inline void Reservations ::Deletes()
{
    char confirmation;
    string nic, nic2, dept, arr, s8;
    int nt, ch, tot, sn;
    ifstream ResIn;  //reservations
    ifstream SeatIn; //seats
    fstream ResOut;
    fstream SeatOut;
    cout << "\n\nConfirm to Cancel the Reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\nEnter your NIC :\n\n";
        cin >> str_NIC;
        cout << "\n\n-------------------------------------------------\n\n";
        ResIn.open("Reservations.txt");
        SeatIn.open("Seats.txt");
        while (ResIn >> nic >> dept >> arr >> nt >> ch >> tot)
        {
            ResOut.open("temp5.txt", ios ::app | ios ::out);
            if (nic != str_NIC)
            {
                while (SeatIn >> nic2 >> sn)
                {
                    SeatOut.open("temp6.txt", ios ::app | ios ::out);
                    if (nic2 != str_NIC)
                    {
                        SeatOut << nic2 << "\t" << nt << "\n";
                        ResOut << nic << "\t" << dept << "\t" << arr << "\t" << nt << "\t" << ch
                               << tot << "\n";
                    }
                    else
                    {
                        count01++;
                    }
                }// end of while - match4
            }// end of outer if
        }// end of outer while
    }// end of confirmation if
    ResOut.close();
    SeatOut.close();
    if (count01 == 0)
    {
        cout << "\n\nRecord  could not be found!\n\n";
        remove("temp5.txt");
        remove("temp6.txt");
    }
    if (count01 > 0)
    {
        remove("Reservations.txt");
        rename("temp5.txt", "Reservations.txt");
        remove("Seats.txt");
        rename("temp6.txt", "Seats.txt");
    }
    ResIn.close();
    cout << "\n\nDone!\n\n";
}

// Reservations - Show
inline void Reservations ::Show(string NIC, string Dept_St, string Arrival_St, int No_Tickets, int Charge, int total)
{
    //system("CLS");
    cout << "\n\nNIC :" << NIC << "\n"
         << "\n\nDep. St. :" << Dept_St << "\t\t"
         << "Arrival St. :" << Arrival_St << "\n\n"
         << "No_Tickets :" << No_Tickets << "\t"
         << "Charge for one ticket :" << Charge << "\t"
         << "total = " << total << "\n\n";
}

// Reservations Deconstructor
inline Reservations ::~Reservations() {}

// Payments Calculate
inline double Reservations ::CalculateFee(double fee, int nt)
{
    i_total = nt * fee;
    return i_total;
}
