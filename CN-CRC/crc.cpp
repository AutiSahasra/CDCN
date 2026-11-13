#include <iostream>
#include <string>
using namespace std;

int main()
{
    string word, data = "";
    string generator = "10011";

    cout << "Enter a word: ";
    cin >> word;

    // Convert word to binary
    for (char c : word)
    {
        for (int j = 7; j >= 0; j--)
        {
            if (c & (1 << j))
                data += "1";
            else
                data += "0";
        }
    }

    cout << "\nData in binary : " << data << endl;
    cout << "Generator      : " << generator << endl;

    // Append zeros
    string temp = data + "0000";

    // CRC division using XOR
    for (int i = 0; i <= temp.length() - generator.length(); i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < generator.length(); j++)
            {
                if (temp[i + j] == generator[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }

    // Get CRC remainder
    string crc = temp.substr(temp.length() - 4);

    cout << "CRC Remainder  : " << crc << endl;
    cout << "Transmitted Data: " << data + crc << endl;

    return 0;
}