#include <bits/stdc++.h>
using namespace std;
int count01;

// class Passenger
class Passenger
{
    string str_City, str_ContactNumber, str_UserName, str_Password, str_name;

protected:
    string str_customer_id;

public:
    Passenger() {}
    Passenger(string name, string customer_id, string City, string ContactNumber, string Username, string Password);
    bool Login();
    void SearchFile_and_Update();
    void Deletes();
    ~Passenger();
};
inline Passenger :: ~Passenger(){}

// Passenger constructor
inline Passenger ::Passenger(string name, string customer_id, string City, string ContactNumber, string Username, string Password)
{
    str_name = name;
    str_customer_id = customer_id;
    str_City = City;
    str_ContactNumber = ContactNumber;
    str_UserName = Username;
    str_Password = Password;
    fstream registration;
    registration.open("Passenger.txt", ios::app | ios::out | ios::ate);
    registration << str_customer_id << "\t" << str_name << "\t" << str_City << "\t" << str_ContactNumber << "\t" << str_UserName
                 << "\t" << str_Password << "\n";
    registration.close();
}

// Delete record function
inline void Passenger::Deletes()
{
    string customer_id, name, city, username, password, cn;
    cout << "\n\nEnter your Customer ID to delete the record :\n\n";
    cin >> str_customer_id;
    fstream deleteF;
    ofstream df;
    deleteF.open("Passenger.txt", ios::in);
    while (deleteF >> customer_id >> name >> city >> cn >> username >> password)
    {
        df.open("temp2.txt", ios ::out | ios :: app);
        if (customer_id != str_customer_id)
        {
            df << customer_id << "\t" << name << "\t" << city << "\t"
               << cn << "\t" << username
               << "\t" << password << "\n";
        }
        else
        {
            count01++;
        }
        df.close();
    } // end of while
    deleteF.close();
    if (count01 == 0)
    {
        remove("temp2.txt");
        cout << "\n\nRecord not found\n\n";
    }
    if (count01 > 0)
    {
        remove("Passenger.txt");
        rename("temp2.txt", "Passenger.txt");
        cout<<"Deleted account successfully!!\n";
    }
} //end of function DeleteRecord

// Search file and update
inline void Passenger ::SearchFile_and_Update()
{
    count01 = 0;
    string customer_id, name, city, username, password, cn;
    cout << "\n\n-------------------------------------------------\n\n";
    cout << "\n\nEnter your Customer ID :\n\n";
    cin >> str_customer_id;
    ifstream PassengerIn;
    ofstream writeFile;
    PassengerIn.open("Passenger.txt");
    while (PassengerIn >> customer_id >> name >> city >> cn >> username >> password)
    {
        writeFile.open("temp1.txt", ios ::app);
        if (customer_id == str_customer_id)
        {
            cout << "\n\nRecord found!\n\n";
            cout << "\n\n-------------------------------------------------\n\n";
            cout << "\n\nNew Passenger Name:\n\n ";
            cin >> str_name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\nNew Passenger City:\n\n "; //address change to city
            cin >> str_City;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
             contact:
                cout << "\n\nNew Passenger : Contact No\n\n ";
                getline(cin,str_ContactNumber);
                if (str_ContactNumber.size() > 10 || str_ContactNumber.size() < 10)
                {
                    cout << "\n\t\t!!!!Please Enter Valid Contact Number:!!!!" << endl;
                    goto contact;
                }
            cout << "\n\nNew Passenger : UserName \n\n ";
            cin >> str_UserName;
            cout << "\n\nNew Passenger : Password\n\n ";
            cin >> str_Password;
            writeFile << str_customer_id << "\t" << str_name << "\t" << str_City << "\t"
                      << str_ContactNumber << "\t" << str_UserName
                      << "\t" << str_Password << "\n";
            count01++;
        }
        else 
        {
            writeFile << customer_id << "\t" << name << "\t" << city << "\t"
                      << cn << "\t" << username
                      << "\t" << password << "\n";
        }
        writeFile.close();
    } // end of while
    PassengerIn.close();
    if (count01 == 0)
    {
        cout << "\n\nRecord  could not be found!\n\n";
        remove("temp1.txt");
    }
    if (count01 > 0)
    {
        remove("Passenger.txt");
        rename("temp1.txt", "Passenger.txt");
        cout<<"MODIFIED SUCCESSFULLY!!\n";
    }
}

// Login
inline bool Passenger ::Login()
{
    long long x=0; //to detect correct username and password for login
    string username01, password01;
    cout << "==============================================================================="
         << "\n\n\t\t\t\tLogin Screen\n\n"
         << "Enter your UserName:\n\n";
    cin >> username01;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\nEnter your Password:\n\n";
    cin >> password01;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ifstream matchup;
    matchup.open("Passenger.txt", ios::in);
    string s1, s2, s3, s4, s5, s6;
    while (matchup >> s1 >> s2 >> s3 >> s4 >> s5 >> s6)
    {
        if (username01==s5 && password01==s6)
        {
            x++;
        }
    }matchup.close(); //end of while
    if(x>0){
        cout << "\n\nLogged in Successfully!!\n\n";
        return true;
    }
    else{
        cout<< "\n\nLog in Failed!\n\n";
        return false;
    }
}

