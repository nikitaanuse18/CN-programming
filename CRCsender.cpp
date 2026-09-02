#include <iostream>
#include <string>
using namespace std;
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
    if (temp[0] == '1')
        temp = xorOperation(temp, generator);
    else
        temp = xorOperation(temp, string(genLength, '0'));

    return temp;
}

int main()
{
    string data, generator;

    cout << "========== SENDER SIDE ==========\n\n";

    cout << "Enter Data Bits: ";
    cin >> data;

    cout << "Enter Generator: ";
    cin >> generator;
    int extraZeros = generator.length() - 1;
    string dataWithZeros = data + string(extraZeros, '0');
    string crc = calculateCRC(dataWithZeros, generator);
    string transmittedData = data + crc;

    cout << "\n----------- OUTPUT -----------\n";

    cout << "Data Bits              : " << data << endl;
    cout << "Generator              : " << generator << endl;

    cout << "Number of Extra 0 Bits : "
         << extraZeros << endl;

    cout << "Data + Extra 0 Bits    : "
         << dataWithZeros << endl;

    cout << "CRC Remainder          : "
         << crc << endl;

    cout << "Transmitted Data       : "
         << transmittedData << endl;

    cout << "\n=================================\n";

    return 0;
}

//----------- OUTPUT -----------
//Data Bits              : 10101010
//Generator              : 1010101010
//Number of Extra 0 Bits : 9
//Data + Extra 0 Bits    : 10101010000000000
//CRC Remainder          : 100000000
//Transmitted Data       : 10101010100000000
