#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR
string xorOperation(string a, string b)
{
    string result = "";

    for (int i = 1; i < b.length(); i++)
    {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }

    return result;
}

// Function to calculate CRC
string calculateCRC(string data, string generator)
{
    int genLength = generator.length();

    string temp = data.substr(0, genLength);

    for (int i = genLength; i < data.length(); i++)
    {
        if (temp[0] == '1')
            temp = xorOperation(temp, generator);
        else
            temp = xorOperation(temp, string(genLength, '0'));

        temp += data[i];
    }

    // Final XOR
    if (temp[0] == '1')
        temp = xorOperation(temp, generator);
    else
        temp = xorOperation(temp, string(genLength, '0'));

    return temp;
}

int main()
{
    string receivedData, generator;

    cout << "========== RECEIVER SIDE ==========\n\n";

    cout << "Enter Received Data: ";
    cin >> receivedData;

    cout << "Enter Generator: ";
    cin >> generator;

    // Number of extra zero bits
    int extraZeros = generator.length() - 1;

    // Calculate remainder
    string remainder = calculateCRC(receivedData, generator);

    cout << "\n----------- OUTPUT -----------\n";

    cout << "Received Data         : "
         << receivedData << endl;

    cout << "Generator             : "
         << generator << endl;

    cout << "Number of Extra 0 Bits: "
         << extraZeros << endl;

    cout << "CRC Remainder         : "
         << remainder << endl;

    // Check for error
    bool error = false;

    for (char bit : remainder)
    {
        if (bit != '0')
        {
            error = true;
            break;
        }
    }

    if (error)
    {
        cout << "\nResult: ERROR DETECTED!" << endl;
        cout << "Data is corrupted." << endl;
    }
    else
    {
        cout << "\nResult: NO ERROR" << endl;
        cout << "Data received successfully." << endl;
    }

    cout << "\n===================================\n";

    return 0;
}

//----------- OUTPUT -----------
//Received Data         : 1000101
//Generator             : 1011
//Number of Extra 0 Bits: 3
//CRC Remainder         : 000

//Result: NO ERROR
//Data received successfully.
