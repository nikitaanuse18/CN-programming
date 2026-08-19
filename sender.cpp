#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Calculate number of redundant bits
int getRedundantBits(int m)
{
    int r = 0;

    while ((1 << r) < (m + r + 1))
    {
        r++;
    }

    return r;
}

// Check whether a position is a power of 2
bool isParityPosition(int position)
{
    return (position & (position - 1)) == 0;
}

// Generate Hamming Code
vector<int> generateHammingCode(string data, int r)
{
    int m = data.length();
    int totalBits = m + r;

    // Index 0 is not used
    vector<int> code(totalBits + 1, 0);

    int dataIndex = 0;

    /*
       Teacher's format:

       Data is written from D(totalBits) towards D1.

       Example for 1011001:

       D11 D10 D9 R8 D7 D6 D5 R4 D3 R2 R1
        1   0   1  R8  1  0  0  R4  1 R2 R1
    */

    for (int position = totalBits; position >= 1; position--)
    {
        if (!isParityPosition(position))
        {
            code[position] = data[dataIndex] - '0';
            dataIndex++;
        }
    }

    // Calculate parity bits using EVEN parity
    for (int i = 0; i < r; i++)
    {
        int parityPosition = 1 << i;
        int parity = 0;

        for (int position = 1; position <= totalBits; position++)
        {
            if ((position & parityPosition) != 0)
            {
                parity ^= code[position];
            }
        }

        code[parityPosition] = parity;
    }

    return code;
}

int main()
{
    string data;

    cout << "Enter Data Word: ";
    cin >> data;

    int m = data.length();

    // Calculate redundant bits
    int r = getRedundantBits(m);

    // Generate Hamming code
    vector<int> code = generateHammingCode(data, r);

    int totalBits = m + r;

    cout << "\nData Word       : " << data << endl;
    cout << "Redundant Bits  : " << r << endl;
    cout << "Total Bits      : " << totalBits << endl;

    // Display redundant bits
    for (int i = 0; i < r; i++)
    {
        int position = 1 << i;

        cout << "R" << position
             << "              : " << code[position] << endl;
    }

    // Display final codeword in teacher's format
    cout << "Code Word       : ";

    for (int position = totalBits; position >= 1; position--)
    {
        cout << code[position];
    }

    cout << endl;

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