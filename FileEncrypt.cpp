#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	const int NCHARS = 60;     // Number of characters used

	ifstream keyFile("keyfile.txt");
	ifstream plainFile("plain.txt");
	ofstream cipherFile("cipher.txt");

	if (!keyFile)
	{
		cout << "I cannot open the key file."; return 1;
	}

	if (!plainFile)
	{
		cout << "I cannot open the plain-text file."; return 1;
	}

	if (!cipherFile)
	{
		cout << "I cannot open the cipher-text file."; return 1;
	}

	vector<char> plainChars;
	vector<char> scrambledChars;

	// read the keyfile and populate the two vectors
	
	// There are 60 characters in the plain sequence
	for (int k = 1; k <= NCHARS; k++)
	{
		plainChars.push_back(keyFile.get());
	}

	// Read and discard the new line character that precedes the scrambled sequence
	keyFile.get();
	// There are 60 characters in the scrambled sequence
	for (int k = 1; k <= NCHARS; k++)
	{
		scrambledChars.push_back(keyFile.get());
	}

	// Echo the two sequences to the screen
	cout << "The encryption key is:\n";
	for (char ch : plainChars)
	{
		cout << ch;
	}
	cout << endl;
	for (char ch : scrambledChars)
	{
		cout << ch;
	}
	cout << endl;

	// Build a map that pairs plain (key) with scrambled character (value)
	map<char, char> key;
	for (int k = 0; k < plainChars.size(); k++)
	{
		key.emplace(plainChars[k], scrambledChars[k]);
	}

	// Read the plain-file and encrypt it, writing the result to
	// cipher-text file.
	char ch = plainFile.get();
	while (ch != EOF)
	{
		cipherFile.put(key.at(ch));
		ch = plainFile.get();
	}
	keyFile.close();
	plainFile.close();
	cipherFile.close();

	return 0;
}