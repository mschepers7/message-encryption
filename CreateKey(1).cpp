#include <random>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//const int NCHARS = 60;

int main()
{
    vector<char> plainChars;  // Original permutation of characters
    vector<char> scrambled;   // Scrambled permutation of characters
    ifstream keyInputFile;    // File used to read in the key
    ofstream keyOutputFile;   // File used to output the key

    // Create seeded random number generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randy(seed);    

    // Create two vectors that contain all characters in plain text order
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        plainChars.push_back(ch);
        scrambled.push_back(ch);
    }

    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        plainChars.push_back(ch);
        scrambled.push_back(ch);
    }

    // Adding special characters
    string specialChars = "!,.?#@";
    for (char ch : specialChars)
    {
        plainChars.push_back(ch);
        scrambled.push_back(ch);
    }
    
    // Adding space and newline characters to support encoding/decoding of text with spaces and newlines
    plainChars.push_back(' ');
    plainChars.push_back('\n');
    scrambled.push_back(' ');
    scrambled.push_back('\n');

    // Scramble the scrambled vector
    shuffle(scrambled.begin(), scrambled.end(), randy);

    // Store the two vectors in a file named keyFile.txt
    keyOutputFile.open("keyfile.txt");
    for (char ch : plainChars)
    {
        keyOutputFile << ch;
    }
    keyOutputFile << endl;

    for (char ch : scrambled)
    {
        keyOutputFile << ch;
    }
    keyOutputFile << endl;
    keyOutputFile.close();

    // Read the two vectors  from the key file and echo their contents to the screen
    keyInputFile.open("keyfile.txt");
    cout << "The plain text sequence and the scrambled sequence are:\n";

    char ch = keyInputFile.get();
    while (ch != EOF)
    {
        cout << ch; 
        ch = keyInputFile.get();
    }    
    return 0;
}
