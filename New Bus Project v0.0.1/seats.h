#include "bits/stdc++.h"
using namespace std;

// class Seats
class Seats
{
protected:
    int i_SeatNo;

public:
    void CheckSeatAvailabilty();
};

// Seats - CheckSeatAvailability
inline void Seats ::CheckSeatAvailabilty()
{
    int NoLines = 0;
    string line;
    fstream SeatAvailbility;
    SeatAvailbility.open("Seats.txt", ios::in | ios ::out);
    // while (SeatAvailbility.eof())
    // {
    //     getline(SeatAvailbility, line);
    //     NoLines++;
    // }
    i_SeatNo = NoLines;
    if (i_SeatNo == 32)
    {
        cout << "\n\nSeats are not available at the moment.\n\n";
    }
    else
    {
        cout << "\n\n"
             << 32 - i_SeatNo << "  are available.\n\n";
    }
    SeatAvailbility.close();
} // seat availability  function end