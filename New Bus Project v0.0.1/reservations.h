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
    Reservations(string customer_id, string DeptSt, string ArrivalSt, int NoTickets);
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
    cout << "\n\n";
    if (! payments.is_open())
    {
        cout << "Unable to open payment records!!" << endl;
    }
    while (!payments.eof())
    {
        getline(payments, line);
        cout << line << endl;
    }
    payments.close();
}
inline Payments :: ~Payments(){}
// Reservations constructor
inline Reservations ::Reservations(string customer_id, string DeptSt, string ArrivalSt, int NoTickets)
{
    Reservations r2;
    str_customer_id = customer_id;
    str_Dep_St = DeptSt;
    str_Arrival_St = ArrivalSt;
    i_No_Tickets = NoTickets;
    ifstream PaymentsRead;
    PaymentsRead.open("Timetables.txt");
    double ch,ticket;
    string s1, s2;
    int ot=0;
    while (PaymentsRead >> s1 >> s2 >> ch)
    {
        if ((str_Dep_St == s1) & (str_Arrival_St == s2))
        {
            i_total = CalculateFee(ch, i_No_Tickets);
            ticket=ch;
            ot=1;
        }
    }
    if(ot!=1){
        cout<<"\tSorry!No bus found on your searched route\n"<<endl;
    }
    else if (ot>=0){
    char confirmation;
    cout << "\n\nConfirm the Reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        fstream Reservations;
        fstream Seats;
        string line;
        Reservations.open("Reservations.txt", ios ::app | ios ::out | ios ::ate | ios ::in);
        Seats.open("Seat.txt", ios ::app | ios ::out | ios ::ate | ios ::in);
        Seats << str_customer_id << "\t" << i_No_Tickets << "\n";
        Reservations << str_customer_id << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                     << "\t" << i_total << "\n";
        Reservations.close();
        r2.CheckSeatAvailabilty(DeptSt, ArrivalSt, NoTickets);
        cout<<"\n\t\t***RESERVATION IS SUCCESSFUL!!***\n"<<endl;
        r2.Show(str_customer_id, str_Dep_St, str_Arrival_St, i_No_Tickets, ticket, i_total);
    }
    else
        cout << "\n\n\t***Confirmation Denied***\n";
    }
}

// modify Reservation function
inline void Reservations ::SearchFile_and_Update() //error
{
    Reservations r1;
    double ch;
    char confirmation;
    int s7;
    ifstream reservationsIn; 
    ifstream seatsIn;       
    fstream reservationsOut;
    fstream seatsOut;
    cout << "\n\nConfirm the You wants to modify reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        // TimeTables T1;
        Payments P1;
        // T1.Show();
        P1.Show();
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\nEnter your Customer ID:\n\n";
        cin >> str_customer_id;
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
            if (s1 == str_customer_id)
            {
                while (seatsIn >> s6 >> s7)
                {
                    seatsOut.open("temp8.txt", ios ::app);
                    if (s6 == str_customer_id)
                    {
                        seatsOut << str_customer_id << "\t" << i_No_Tickets << "\n";
                        reservationsOut << str_customer_id << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
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
            cout<<"File successfully renamed";
        else
            cout<<"Error renaming file";
    }
    seatsOut.close();
    reservationsOut.close();
    cout << "\n\nDone!\n\n";
    r1.Show(str_customer_id, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total);
}

// cancel Reservations
inline void Reservations ::Deletes()
{
    int cntr5=0;
    char confirmation;
    string customer_id, dept, arr;
    int nt, tot;
    ifstream ResIn; 
    ofstream ResOut;
    cout << "\n\nConfirm to Cancel The Reservations of your Customer ID (y/n): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\nEnter your Customer ID :\n\n";
        cin >> str_customer_id;
        cout << "\n\n-------------------------------------------------\n\n";
        ResIn.open("Reservations.txt");
        ResOut.open("temp5.txt", ios ::app);
        while (ResIn >> customer_id >> dept >> arr >> nt >> tot)
        {
            if (customer_id != str_customer_id)
            {
                ResOut << customer_id << "\t" << dept << "\t" << arr << "\t" << nt << "\t" << tot << "\n";
                cntr5++;
            }
        }
    }
    ResOut.close();
    if (cntr5 == 0)
    {
        cout << "\n\nRecord  could not be found!\n\n";
        remove("temp5.txt");
    }
    else if (cntr5 > 0)
    {
        remove("Reservations.txt");
        rename("temp5.txt", "Reservations.txt");
        cout << "\n\n\t***Your Reservation Cancelled Successfully!!***\n\n";
    }
    ResIn.close();
}

// Reservations - Show
inline void Reservations ::Show(string customer_id, string Dept_St, string Arrival_St, int No_Tickets, int Charge, int total)
{
    cout <<"\n\n**************************************************************\n"
         << "\tCustomer ID :" << customer_id << "\n\n"
         << "\tDep. St. : " << Dept_St << "\n\n"
         << "\tArrival St. : " << Arrival_St << "\n\n"
         << "\tNo. of Tickets :" << No_Tickets << "\n\n"
         << "\tCharge for one ticket : " << Charge << "\n\n"
         << "\t\t*********************************\n"
         << "\n\t\t\tTotal Fare = " << total << endl
         <<"\n**************************************************************\n";
}      

// Reservations Deconstructor
inline Reservations ::~Reservations() {}

// Payments Calculate
inline double Reservations ::CalculateFee(double fee, int nt)
{
    i_total = nt * fee;
    return i_total;
}
