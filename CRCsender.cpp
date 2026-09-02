#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string ip;
    int octet[4];
    char dot;

    cout << "Enter IP address: ";
    cin >> ip;

    // Count dots
    int dots = 0;

    for (char ch : ip)
    {
        if (ch == '.')
            dots++;
    }

    // Check exactly 3 dots
    if (dots != 3)
    {
        cout << "Invalid IP address";
        return 0;
    }

    // Convert string into integers
    stringstream ss(ip);

    for (int i = 0; i < 4; i++)
    {
        ss >> octet[i];

        if (i < 3)
            ss >> dot;
    }

    // Check each octet
    for (int i = 0; i < 4; i++)
    {
        if (octet[i] < 0 || octet[i] > 255)
        {
            cout << "Invalid IP address";
            return 0;
        }
    }

    cout << "Valid IP address" << endl;

    // Class A
    if (octet[0] >= 1 && octet[0] <= 126)
    {
        cout << "Class: A" << endl;

        cout << "Net ID: "
             << octet[0] << ".0.0.0" << endl;

        cout << "Host ID: "
             << octet[3] << endl;
    }

    // Class B
    else if (octet[0] >= 128 && octet[0] <= 191)
    {
        cout << "Class: B" << endl;

        cout << "Net ID: "
             << octet[0] << "."
             << octet[1] << ".0.0" << endl;

        cout << "Host ID: "
             << octet[3] << endl;
    }

    // Class C
    else if (octet[0] >= 192 && octet[0] <= 223)
    {
        cout << "Class: C" << endl;

        cout << "Net ID: "
             << octet[0] << "."
             << octet[1] << "."
             << octet[2] << ".0" << endl;

        cout << "Host ID: "
             << octet[3] << endl;
    }

    // Class D
    else if (octet[0] >= 224 && octet[0] <= 239)
    {
        cout << "Class: D" << endl;
        cout << "Net ID: Not applicable" << endl;
        cout << "Host ID: Not applicable" << endl;
    }

    // Class E
    else if (octet[0] >= 240 && octet[0] <= 255)
    {
        cout << "Class: E" << endl;
        cout << "Net ID: Not applicable" << endl;
        cout << "Host ID: Not applicable" << endl;
    }

    else
    {
        cout << "Invalid IP address";
    }

    return 0;
}


//OUTPUT
//Enter IP address: 192.168.1.1
//Valid IP address
//Class: C
//Net ID: 192.168.1.0
//Host ID: 1