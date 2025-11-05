#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR between two binary strings
string xorOperation(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to perform Mod-2 Division (CRC calculation)
string mod2Division(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    int n = dividend.length();

    while (pick < n) {
        if (temp[0] == '1')
            temp = xorOperation(divisor, temp) + dividend[pick];
        else
            temp = xorOperation(string(pick, '0'), temp) + dividend[pick];

        pick++;
    }

    // Last n bits
    if (temp[0] == '1')
        temp = xorOperation(divisor, temp);
    else
        temp = xorOperation(string(pick, '0'), temp);

    return temp;
}

// Function to encode data using CRC
string encodeData(string data, string key) {
    int keyLength = key.length();
    string appendedData = data + string(keyLength - 1, '0');
    string remainder = mod2Division(appendedData, key);
    string codeword = data + remainder;
    return codeword;
}

// Function to check for errors at receiver side
bool checkError(string received, string key) {
    string remainder = mod2Division(received, key);
    for (char c : remainder)
        if (c == '1') return true; // error detected
    return false; // no error
}

int main() {
    cout << "=============================\n";
    cout << "Task 1: CRC Calculation\n";
    cout << "=============================\n";
    string data1 = "1101011011";
    string key1 = "10011"; // x^4 + x + 1
    string transmitted1 = encodeData(data1, key1);
    cout << "Original Data: " << data1 << endl;
    cout << "Generator Polynomial: " << key1 << endl;
    cout << "Transmitted Codeword: " << transmitted1 << endl;

    cout << "\n=============================\n";
    cout << "Task 2: CRC Error Detection\n";
    cout << "=============================\n";
    string data2 = "10011101";
    string key2 = "1001"; // x^3 + 1
    string transmitted2 = encodeData(data2, key2);
    cout << "Original Data: " << data2 << endl;
    cout << "Generator Polynomial: " << key2 << endl;
    cout << "Transmitted Codeword: " << transmitted2 << endl;

    // Introduce error (invert 3rd bit)
    string received = transmitted2;
    received[2] = (received[2] == '0') ? '1' : '0';
    cout << "Received Codeword (with error): " << received << endl;

    if (checkError(received, key2))
        cout << "Error Detected at Receiver!" << endl;
    else
        cout << "No Error Detected." << endl;

    return 0;
}
