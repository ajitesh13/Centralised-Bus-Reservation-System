#include "bits/stdc++.h"
#include "reservations.h"
using namespace std;

// class TimeTables
class TimeTables : public Reservations{
    public:
                void Show()const ;
                ~TimeTables ();
};

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