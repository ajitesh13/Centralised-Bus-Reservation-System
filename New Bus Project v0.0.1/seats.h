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
    int seats;
    fstream SeatAvailbility;
    string s1, s2;
    SeatAvailbility.open("seat_available.txt");
    while ( SeatAvailbility >> s1 >> s2 >> seats)
    {
        if ((DepSt == s1) & (ArrSt == s2))
        {
            seats = seats - nt;
            SeatAvailbility << DepSt << "\t" << ArrSt << "\t" << seats << "\n";

            
        }
    }
    

    //  while (SeatAvailbility.eof())
    //  {
    //      getline(SeatAvailbility, line);
    //      NoLines++;
    //  }
    // i_SeatNo = NoLines;
    // if (i_SeatNo == 32)
    // {
    //     cout << "\n\nSeats are not available at the moment.\n\n";
    // }
    // else
    // {
    //     cout << "\n\n" << 32 - i_SeatNo << "  are available.\n\n";
    // }
    SeatAvailbility.close();
} // seat availability  function end