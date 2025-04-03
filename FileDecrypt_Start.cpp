
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	const int NCHARS = 60;     

	ifstream keyFile("keyfile.txt");
	ifstream cipherFile("cipher.txt");
	ofstream decryptedFile("decrypted.txt");
	
	if (!keyFile)
	{
		cout << "I cannot open the key file."; return 1;
	}

	if (!decryptedFile)
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

	// There are 28 characters in the plain sequence
	for (int k = 1; k <= NCHARS; k++)
	{
		plainChars.push_back(keyFile.get());
	}
	// Read and discard the new line character that precedes the scrambled sequence
	keyFile.get();
	// There are 28 characters in the scrambled sequence
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
	cout << endl << endl;

	
	map<char, char> key;
	for (int k = 0; k < plainChars.size(); k++)
	{
		key[scrambledChars[k]] = plainChars[k];
	}
	
	
	// Read the cipher file and decrypt it, writing the result to
	// plain-text file.
	cout << "The decrypted message is: \n" << endl;
	
	

	char ch = cipherFile.get(); // Read a character from the cipher file
	while (ch != EOF)
	{
		

		char plainCh = key.at(ch); 
		decryptedFile.put(plainCh); 

		
		cout << plainCh;
		ch = cipherFile.get(); 
	}

	cout << endl << endl;
	keyFile.close();
	decryptedFile.close();
	cipherFile.close();
	

	return 0;
}


