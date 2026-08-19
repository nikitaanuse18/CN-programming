#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string received;

    cout << "Enter Received Code Word: ";
    cin >> received;

    int n = received.length();

    vector<int> code(n + 1);

    int index = 0;

    for (int i = n; i >= 1; i--)
    {
        code[i] = received[index] - '0';
        index++;
    }

    int r = 0;

    while ((1 << r) < n + 1)
    {
        r++;
    }

    int errorPosition = 0;

    for (int i = 0; i < r; i++)
    {
        int parityPosition = 1 << i;
        int parity = 0;

        for (int j = 1; j <= n; j++)
        {
            if ((j & parityPosition) != 0)
            {
                parity ^= code[j];
            }
        }

        if (parity != 0)
        {
            errorPosition += parityPosition;
        }
    }

    if (errorPosition == 0)
    {
        cout << "\nNo Error" << endl;
    }
    else if (errorPosition > n)
    {
        cout << "\nError Cannot Be Corrected" << endl;
    }
    else
    {
        cout << "\nError at position: " << errorPosition << endl;

        code[errorPosition] = !code[errorPosition];

        cout << "Corrected Code Word: ";

        for (int i = n; i >= 1; i--)
        {
            cout << code[i];
        }

        cout << endl;
    }

    string data = "";

    for (int i = n; i >= 1; i--)
    {
        if ((i & (i - 1)) != 0)
        {
            data += char(code[i] + '0');
        }
    }

    cout << "Data Word: " << data << endl;

    return 0;
}
\\Enter Data Word: 1011001

Data Word       : 1011001
Redundant Bits  : 4
Total Bits      : 11
R1              : 0
R2              : 1
R4              : 1
R8              : 0
Code Word       : 10101001110
@nikitaanuse18 ➜ /workspaces/CN-programming (main) $ g++ receiver.cpp
@nikitaanuse18 ➜ /workspaces/CN-programming (main) $ ./a.out
Enter Received Code Word: 10101101110

Error at position: 6
Corrected Code Word: 10101001110
Data Word: 1011001