#include "bits/stdc++.h"
#include "seats.h"
#include "passenger.h"
#define UNDERLINE "\033[33;4m"
#define CLOSEUNDERLINE "\033[0m"

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
    Reservations(int customer_id, string DeptSt, string ArrivalSt, int NoTickets);
    void SearchFile_and_Update(int);
    // ModifyReservation Function
    void Deletes(int);
    // cancel reservation function
    void Show(int);
    void Show(int, string, string, int, int, int);
    double CalculateFee(double, int);
    ~Reservations();
};
 Reservations ::Reservations() {}

// class Payments
class Payments : public Reservations
{
public:
    void Show() const;
    ~Payments();
};

// payments - show
 void Payments ::Show() const
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
 Payments ::~Payments() {}
// Reservations constructor
 Reservations ::Reservations(int customer_id, string DeptSt, string ArrivalSt, int NoTickets)
{
    int n;
    Reservations r2;
    str_Dep_St = DeptSt;
    str_Arrival_St = ArrivalSt;
    i_No_Tickets = NoTickets;
    ifstream PaymentsRead;
    PaymentsRead.open("Timetables.txt");
    double ch, ticket;
    string s1, s2, s3, s4;
    int ot = 0;
    while (PaymentsRead >> s1 >> s2 >> ch >> s3 >> s4)
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
        cout << "\t\tSorry!! No bus found on your searched route\n"
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
            string line;

            n = r2.CheckSeatAvailabilty(DeptSt, ArrivalSt, NoTickets);
            if (n == 1)
            {
                Reservations.open("Reservations.txt", ios ::app | ios ::out | ios ::ate | ios ::in);
                Reservations << customer_id << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                             << "\t" << i_total << "\n";
                Reservations.close();
                cout << bold_on << "\n\t\t\t***RESERVATION IS SUCCESSFUL!!***\n"
                     << bold_off << endl;
                r2.Show(customer_id, str_Dep_St, str_Arrival_St, i_No_Tickets, ticket, i_total);
            }
        }
        else
            cout << "\n\n\t\t***Confirmation Denied***\n";
    }
}

// modify Reservation function
 void Reservations ::SearchFile_and_Update(int log_customerid)
{
    int new_ticket_no;
    count01 = 0;
    Reservations r1;
    double ch;
    char confirmation;
    ifstream reservationsIn;
    fstream reservationsOut;
    cout << "\n\nConfirm that you want to modify reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {

        Payments P1;
        P1.Show();
        // cout << "\n\nEnter your Customer ID:\n\n";
        // cin >> str_customer_id;
        cout << "\n\n--------------------------------------------------------------------------------\n\n";
        cout << "\n\nDeparture station\n\n ";
        cin >> str_Dep_St;
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n Arrival station\n\n ";
        cin >> str_Arrival_St;
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\nEnter New  No. of Tickets\n\n ";
        cin >> i_No_Tickets; //new no of tickets
        fstream PaymentsRead;

        PaymentsRead.open("Timetables.txt", ios ::in);
        string s1, s2, s3, s4, s5, s6, s7, s8;
        while (PaymentsRead >> s1 >> s2 >> ch >> s7 >> s8)
        {
            if ((str_Dep_St == s1) & (str_Arrival_St == s2))
            {
                i_total = CalculateFee(ch, i_No_Tickets);
            }
        }
        reservationsIn.open("Reservations.txt");
        int s10;
        while (reservationsIn >> s10 >> s2 >> s3 >> s4 >> s5)
        {
            reservationsOut.open("temp7.txt", ios ::app);
            if ((s10 == log_customerid) & (s2 == str_Dep_St) & (s3 == str_Arrival_St))
            {
                new_ticket_no = i_No_Tickets - stoi(s4);
                int n = CheckSeatAvailabilty(str_Dep_St, str_Arrival_St, new_ticket_no);
                if (n == 1)
                {
                    reservationsOut << log_customerid << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                                    << "\t" << i_total << "\n";
                    cout << "\n\t\tRecord found & updated!\n\n";
                    cout << "\n-------------------------------------------------\n";
                    count01++;
                }
            }
            else
            {
                reservationsOut << s10 << "\t" << s2 << "\t" << s3 << "\t" << s4 << "\t" << s5 << "\n";
            }
            reservationsOut.close();
        } // end of while
        if (count01 == 0)
        {
            cout << "\n\n\t\tSorry, Record could not be found!\n\n";
            remove("temp7.txt");
        }
        else if (count01 != 0)
        {
            remove("Reservations.txt");
            rename("temp7.txt", "Reservations.txt");
            r1.Show(log_customerid, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total);
        }
        reservationsOut.close();
    }
    else
    {
        cout << "\n\t\t***Confirmation Denied!!***\n"
             << endl;
    }
}

//cancel Reservations0
 void Reservations ::Deletes(int log_customerid)
{
    int cntr5 = 0;
    char confirmation;
    int customer_id;
    string dept, arr;
    int nt, tot;
    ifstream ResIn;
    ofstream ResOut;
    cout << "\n\nConfirm to "<<bold_on<< "Cancel"<<bold_off<<" the Reservation of your Customer ID (y/n): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        cout << "\n\n--------------------------------------------------------------------------------\n\n";
        // cout << "\n\nEnter your Customer ID :\n\n";
        // cin >> str_customer_id;
        cout << "\n\nDepature station\n\n ";
        cin >> str_Dep_St;
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n Arrival station\n\n ";
        cin >> str_Arrival_St;
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n-------------------------------------------------\n\n";
        ResIn.open("Reservations.txt");
        ResOut.open("temp5.txt", ios ::app);
        while (ResIn >> customer_id >> dept >> arr >> nt >> tot)
        {
            if ((customer_id == log_customerid) & (dept == str_Dep_St) & (arr == str_Arrival_St))
            {
                int n = CheckSeatAvailabilty(str_Dep_St, str_Arrival_St, -nt);
            }
            else
            {
                ResOut << customer_id << "\t" << dept << "\t" << arr << "\t" << nt << "\t" << tot << "\n";
                cntr5++;
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
            cout << "\n\n\t\t***Your Reservation Cancelled Successfully!!***\n\n\n";
        }
        ResIn.close();
    }
    else
    {
        cout << "\n\t\t***Confirmation Denied!!***" << endl;
    }
}

// Reservations  Show
 void Reservations ::Show(int customer_id, string Dept_St, string Arrival_St, int No_Tickets, int Charge, int total)
{
    string s6, s7, s8, s9, s10;
    string deptime, arrtime;
    fstream time;
    time.open("Timetables.txt");
    while (time >> s6 >> s7 >> s8 >> s9 >> s10)
    {
        if ((s6 == Dept_St) & (s7 == Arrival_St))
        {
            deptime = s9;
            arrtime = s10;
        }
    }
    cout << "\n\n\t**************************************************************\n"
         << bold_on << "\t\t\t\t      " << UNDERLINE << "INDIAN ROADWAYS" << CLOSEUNDERLINE << bold_off << "\n\n"
         << "\t\tCustomer ID :" << customer_id << "\n\n"
         << "\t\tDep. St. : " 
         << left<< setw(20)<< Dept_St<< "\t" << "Departure Time: " << deptime << "\n\n"
         << "\t\tArrival St. : " 
         << left<< setw(17)<< Arrival_St << "\t" << "Arrival Time: " << arrtime << "\n\n"
         << "\t\tNo. of Tickets :" << No_Tickets << "\n\n"
         << "\t\tCharge for one ticket : " << Charge << "\n\n"
         << "\t\t\t---------------------------------\n"
         << bold_on<< "\n\t\t\t\tTotal Fare = " << total <<bold_off<< "\n"
         << "\n\t***************************************************************\n";
}

 void Reservations ::Show(int log_customerid)
{
    int cntr20 = 0;
    int s1; 
    string s2, s3, s4, s5;
    string s6, s7, s8, s9, s10;
    string deptime, arrtime;
    // cout << "\n\nEnter your Customer ID:\n\n";
    // cin >> str_customer_id;
    cout << "\n\n-----------------------------------------------------------------------------------\n\n";
    cout << "\n\n Depature station\n\n ";
    cin >> str_Dep_St;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\n Arrival station\n\n ";
    cin >> str_Arrival_St;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    fstream read;
    read.open("Reservations.txt");
    fstream time;
    time.open("Timetables.txt");
    while (time >> s6 >> s7 >> s8 >> s9 >> s10)
    {
        if ((s6 == str_Dep_St) & (s7 == str_Arrival_St))
        {
            deptime = s9;
            arrtime = s10;
        }
    }
    while (read >> s1 >> s2 >> s3 >> s4 >> s5)
    {
        if ((s1 == log_customerid) & (s2 == str_Dep_St) & (s3 == str_Arrival_St))
        {
            cout << "\n\n\t**********************************************************************\n"
                 << bold_on << "\t\t\t\t    " << UNDERLINE << "INDIAN ROADWAYS" << CLOSEUNDERLINE << bold_off << "\n\n"
                 << "\t\tCustomer ID :" << s1 << "\n\n"
                 << "\t\tDep. St. : " 
                 << left<< setw(20)<< s2 << "\t" << "Departure Time: " << deptime << "\n\n"
                 << "\t\tArrival St. : " 
                 << left<< setw(17)<<s3 << "\t" << "Arrival Time: " << arrtime << "\n\n"
                 << "\t\tNo. of Tickets :" << s4 << "\n\n"
                 << "\t\t\t---------------------------------\n"
                 << bold_on<<"\n\t\t\t\tTotal Fare = " << s5 <<bold_off<< "\n"
                 << "\n\t***********************************************************************\n";
            cntr20++;
        }
    }
    read.close();
    if (cntr20 == 0)
    {
        cout << "\n\n\t\t***Record Not Found!!***" << endl;
    }
}

// Reservations Destructor
 Reservations ::~Reservations() {}

// Payments Calculate
 double Reservations ::CalculateFee(double fee, int nt)
{
    i_total = nt * fee;
    return i_total;
}
