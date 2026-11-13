
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// 1. CHARACTER COUNT
string characterCount(vector<string> packets)
{
    string result = "";

    for(string p : packets)
    {
        result += to_string(p.length() + 1) + p;
    }

    return result;
}

vector<string> decodeCount(string s)
{
    vector<string> packets;
    int i = 0;

    while(i < s.length())
    {
        int size = s[i] - '0';

        packets.push_back(s.substr(i + 1, size - 1));

        i += size;
    }

    return packets;
}

// 2. CHARACTER STUFFING
string characterStuff(string msg)
{
    string result = "FLAG ";

    stringstream ss(msg);
    string word;

    while(ss >> word)
    {
        if(word == "FLAG" || word == "ESC")
            result += "ESC ";

        result += word + " ";
    }

    result += "FLAG";

    return result;
}

string characterDestuff(string msg)
{
    stringstream ss(msg);
    string word, result = "";

    ss >> word; // Skip starting FLAG

    vector<string> tokens;

    while(ss >> word)
        tokens.push_back(word);

    for(int i = 0; i < tokens.size() - 1; i++)
    {
        if(tokens[i] == "ESC")
            i++;

        result += tokens[i] + " ";
    }

    return result;
}

// 3. BIT STUFFING
string bitStuff(string s)
{
    string result = "01111110";
    int ones = 0;

    for(char ch : s)
    {
        result += ch;

        if(ch == '1')
        {
            ones++;

            if(ones == 5)
            {
                result += '0';
                ones = 0;
            }
        }
        else
        {
            ones = 0;
        }
    }

    result += "01111110";

    return result;
}

string bitDestuff(string s)
{
    string result = "";
    int ones = 0;

    for(int i = 8; i < s.length() - 8; i++)
    {
        result += s[i];

        if(s[i] == '1')
        {
            ones++;

            if(ones == 5)
            {
                i++; // Skip stuffed 0
                ones = 0;
            }
        }
        else
        {
            ones = 0;
        }
    }

    return result;
}

int main()
{
    // CHARACTER COUNT
    cout << "1. CHARACTER COUNT\n";

    int n;
    cout << "Enter number of frames: ";
    cin >> n;

    vector<string> packets(n);

    cout << "Enter frames:\n";

    for(int i = 0; i < n; i++)
        cin >> packets[i];

    string s = characterCount(packets);

    cout << "Transmitted stream: " << s << endl;

    vector<string> received = decodeCount(s);

    cout << "Received frames: ";

    for(string p : received)
        cout << p << " ";

    // CHARACTER STUFFING
    cout << "\n\n2. CHARACTER STUFFING\n";

    string msg;
    cout << "Enter data: ";
    cin.ignore();

    getline(cin, msg);

    string f = characterStuff(msg);

    cout << "Stuffed frame: " << f << endl;
    cout << "After de-stuffing: " << characterDestuff(f) << endl;

    // BIT STUFFING
    cout << "\n3. BIT STUFFING\n";

    string bits;
    cout << "Enter bit string: ";
    cin >> bits;

    f = bitStuff(bits);

    cout << "Stuffed frame: " << f << endl;
    cout << "After de-stuffing: " << bitDestuff(f) << endl;

    return 0;
}
