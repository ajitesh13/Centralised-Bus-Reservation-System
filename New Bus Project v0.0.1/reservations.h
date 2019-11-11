#include "bits/stdc++.h"
#include "seats.h"
#include "passenger.h"
#define UNDERLINE "\033[33;4m"
#define CLOSEUNDERLINE "\033[0m"

using namespace std;
//text bold
ostream &bold_on(ostream &os)
{
    return os << "\e[1m";
}

ostream &bold_off(ostream &os)
{
    return os << "\e[0m";
}

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
    void Show();
    void Show(string, string, string, int, int, int);
    double CalculateFee(double, int);
    ~Reservations();
};
inline Reservations ::Reservations() {}

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
    if (!payments.is_open())
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
inline Payments ::~Payments() {}
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
    double ch, ticket;
    string s1, s2;
    int ot = 0;
    while (PaymentsRead >> s1 >> s2 >> ch)
    {
        if ((str_Dep_St == s1) & (str_Arrival_St == s2))
        {
            i_total = CalculateFee(ch, i_No_Tickets);
            ticket = ch;
            ot = 1;
        }
    }
    if (ot != 1)
    {
        cout << "\tSorry!No bus found on your searched route\n"
             << endl;
    }
    else if (ot >= 0)
    {
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
            cout << bold_on << "\n\t\t***RESERVATION IS SUCCESSFULL!!***\n"
                 << bold_off << endl;
            r2.Show(str_customer_id, str_Dep_St, str_Arrival_St, i_No_Tickets, ticket, i_total);
        }
        else
            cout << "\n\n\t***Confirmation Denied***\n";
    }
}

// modify Reservation function
inline void Reservations ::SearchFile_and_Update() //error
{
    count01 = 0;
    Reservations r1;
    double ch;
    char confirmation;
    int s7;
    ifstream reservationsIn;
    //ifstream seatsIn;
    fstream reservationsOut;
    //fstream seatsOut;
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
        PaymentsRead.open("Timetables.txt", ios ::in);
        string s1, s2, s3, s4, s5, s6;
        while (PaymentsRead >> s1 >> s2 >> ch)
        {
            if ((str_Dep_St == s1) & (str_Arrival_St == s2))
            {
                i_total = CalculateFee(ch, i_No_Tickets);
            }
        }
        reservationsIn.open("Reservations.txt");
        //seatsIn.open("Seats.txt");
        while (reservationsIn >> s1 >> s2 >> s3 >> s4 >> s5)
        {
            reservationsOut.open("temp7.txt", ios ::app);
            if ((s1 == str_customer_id) & (s2 == str_Dep_St) & (s3 == str_Arrival_St))
            {

                reservationsOut << str_customer_id << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                                << "\t" << i_total << "\n";
                cout << "\n\n\t\tRecord found & updated!\n\n";
                cout << "\n\n-------------------------------------------------\n\n";
                count01++;
            }
            else
            {
                reservationsOut << s1 << "\t" << s2 << "\t" << s3 << "\t" << s4 << "\t" << s5 << "\n";
            }
            reservationsOut.close();
        } // end of while - match4
        if (count01 == 0)
        {
            cout << "\n\nRecord  could not be found!\n\n";
            remove("temp7.txt");
        }
        if (count01 != 0)
        {
            remove("Reservations.txt");
            rename("temp7.txt", "Reservations.txt");
        }
        reservationsOut.close();
        r1.Show(str_customer_id, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total);
    }
}
// cancel Resevations1
// inline void Reservations::Deletes()
// {
//     string customer_id, Depst, Arrst, ns, cost;
//     int cntr19=0;
//     cout << "\n\nEnter Your Departure Station: ";
//     cin >> str_Arrival_St;
//     cout << "\n\nEnter Your Arrival Station: ";
//     cin >> str_Dep_St;
//     fstream deleteR;
//     ofstream df;
//     deleteR.open("Reservations.txt", ios::in);

//     while(deleteR >> customer_id >> Depst >> Arrst >> ns >> cost)
//     {

//         df.open("temp15.txt", ios::out | ios::app);
//         if(Depst != str_Dep_St & Arrst != str_Arrival_St)
//         {
//                 df << customer_id << "\t" << Depst << "\t"
//                 << Arrst << "\t" << ns << "\t" << cost << "\n";
//         }
//         else
//         {
//                 cntr19++;
//         }
//         df.close();
//     }
//     deleteR.close();
//     if(cntr19 == 0)
//     {
//         remove("temp15.txt");
//         cout << "\n\nRecord Not Found!\n\n";
//     }
//     else if(cntr19 > 0)
//     {
//         remove("Reservations.txt");
//         rename("temp15.txt", "Reservations.txt");
//         cout << "\n\nreservation Successfully Deleted!\n";
//     }
// }

//cancel Reservations0
inline void Reservations ::Deletes()
{
    int cntr5 = 0;
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
    cout << "\n\n**************************************************************\n"
         << bold_on << "\t\t\t      " << UNDERLINE << "INDIAN ROADWAYS" << CLOSEUNDERLINE << bold_off << "\n\n"
         << "\tCustomer ID :" << customer_id << "\n\n"
         << "\tDep. St. : " << Dept_St << "\n\n"
         << "\tArrival St. : " << Arrival_St << "\n\n"
         << "\tNo. of Tickets :" << No_Tickets << "\n\n"
         << "\tCharge for one ticket : " << Charge << "\n\n"
         << "\t\t*********************************\n"
         << "\n\t\t\tTotal Fare = " << total << endl
         << "\n***************************************************************\n";
}

inline void Reservations ::Show()
{
    int cntr20=0;
    string s1, s2, s3, s4, s5;
    cout << "\n\nEnter your Customer ID:\n\n";
    cin >> str_customer_id;
    cout << "\n\n-------------------------------------------------\n\n";
    cout << "\n\n Depature station\n\n ";
    cin >> str_Dep_St;
    cout << "\n\n Arrival station\n\n ";
    cin >> str_Arrival_St;
    fstream read;
    read.open("Reservations.txt");
    while (read >> s1 >> s2 >> s3 >> s4 >> s5)
    {
        if ((s1 == str_customer_id) & (s2 == str_Dep_St) & (s3 == str_Arrival_St))
        {
            cout << "\n\n**************************************************************\n"
                 << bold_on << "\t\t\t      " << UNDERLINE << "INDIAN ROADWAYS" << CLOSEUNDERLINE << bold_off << "\n\n"
                 << "\tCustomer ID :" << s1 << "\n\n"
                 << "\tDep. St. : " << s2 << "\n\n"
                 << "\tArrival St. : " << s3 << "\n\n"
                 << "\tNo. of Tickets :" << s4 << "\n\n"
                 << "\t\t*********************************\n"
                 << "\n\t\t\tTotal Fare = " << s5 << endl
                 << "\n***************************************************************\n";
                 cntr20++;
        }
    }
    read.close();
    if(cntr20==0)
    {    
            cout << "\n\n\t\t***Record Not Found!!***"<< endl;
    }
    
}

// Reservations Deconstructor
inline Reservations ::~Reservations() {}

// Payments Calculate
inline double Reservations ::CalculateFee(double fee, int nt)
{
    i_total = nt * fee;
    return i_total;
}
