#include "bits/stdc++.h"
using namespace std;

// class Seats
class Seats
{
protected:
    int i_SeatNo;

public:
    void CheckSeatAvailabilty(string DepSt, string ArrSt, int nt);
};

// Seats - CheckSeatAvailability
inline void Seats ::CheckSeatAvailabilty(string DepSt, string ArrSt, int nt)
{
    
    //int NoLines = 0;
    //string line;
    int seats, cntr=0;
    ifstream SeatAvailbility;
    ofstream seat_update;
    string s1, s2;
    SeatAvailbility.open("seat_available.txt");
    while ( SeatAvailbility >> s1 >> s2 >> seats)
    {
        seat_update.open("temp11.txt", ios::app);
        if ((s1 == DepSt) & (s2 == ArrSt))
        {
            seats = seats - nt;

            if(seats < 0)
            {
                cout << "\n\n\n****SORRY! THIS RESERVATION IS NOT POSSIBLE****\n\n\n" << endl;
                exit(1);
            }
 
            
            seat_update << DepSt << "\t" << ArrSt << "\t" << seats << "\n";
            cntr++;
        }
        else
        {
            seat_update << s1 << "\t" << s2 << "\t" << seats << "\n";
        }
        seat_update.close();
    }
    SeatAvailbility.close();
    if (cntr == 0)
    {
        remove("temp11.txt");
    }
    if (cntr > 0)
    {
        remove("seat_available.txt");
        rename("temp11.txt", "seat_available.txt");
        cout << "\n\n***YOUR RESERVATION IS SUCCESSFULL!***\n";
    }

} 