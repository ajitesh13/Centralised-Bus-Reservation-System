#include "bits/stdc++.h"
#include "reservations.h"
using namespace std;

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
    payments.open("Payments.txt", ios ::in);
    string line;
    cout << "\n\n-----------------Payment Scheme------------------\n\n";
    while (!payments.eof())
    {
        getline(payments, line);
        cout << line << "\n";
    }
}