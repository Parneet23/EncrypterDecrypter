#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//Expecting user to add the complete path of file and the digit with how much character users wants to change the message.
//Program is performing both encryption and decryption using Caesar Cipher Algorithm.
bool isAlphabet(char ch) {
	if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')) 
		return  true;
	return false;
}
bool isUpper(char ch) {
	if(ch >= 'A' && ch <= 'Z')
		return true;
	return false;
}
string deconvertLine(string strInput, int decryptedDigit) {
	for(int i=0; i<strInput.length(); i++) {
		if(!isAlphabet(strInput[i]))
			continue;
		if((isUpper(strInput[i]) && strInput[i]-decryptedDigit < 'A') || (!isUpper(strInput[i]) && strInput[i]-decryptedDigit < 'a')) {
		   int diff, remaining;
		    if(isUpper(strInput[i])) {
		    	diff=strInput[i]-'A';
			remaining=decryptedDigit-diff-1;
			strInput[i]='Z'-remaining;
		    }
		    else {
			diff=strInput[i]-'a';
			remaining=decryptedDigit-diff-1;
			strInput[i]='z'-remaining;
		    }
		}
		else {
			strInput[i]=strInput[i]-decryptedDigit;
		}
	}
	strInput+="\n";
	return strInput;
}
string convertLine(string strInput, int encryptedDigit) {
	for(int i=0; i<strInput.length(); i++) {
		if(!isAlphabet(strInput[i]))
			continue;
		if((isUpper(strInput[i]) && strInput[i]+encryptedDigit > 'Z') || (!isUpper(strInput[i]) && strInput[i]+encryptedDigit > 'z')) {
		   int diff, remaining;
		    if(isUpper(strInput[i])) {
			diff='Z'-strInput[i];
			remaining=encryptedDigit-diff-1;
			strInput[i]='A'+remaining;
		    }
		    else {
			diff='z'-strInput[i];
			remaining=encryptedDigit-diff-1;
			strInput[i]='a'+remaining;
		    }
		}
		else {
			strInput[i]=strInput[i]+encryptedDigit;
		} 	
	}
	strInput+="\n";
	return strInput;
}
void fileDecrypter(string filename, int decryptedDigit) {
	ifstream infile;
	string decString="";
	infile.open(filename);
	if(!infile.is_open()) {
		cout << "File does not exist or some issue in opening file\n";
		return;
	}
	ofstream outfile;
	string output="";
	while(getline(infile, decString)) {
		output += deconvertLine(decString, decryptedDigit);
	}
	outfile.open(filename);
	outfile << output;
	infile.close();
	outfile.close();
}
void fileEncrypter(string filename, int encryptedDigit) {
	ifstream infile;
	string encString="";
	infile.open(filename);
	if(!infile.is_open()) {
		cout << "File does not exist or some issue in opening file\n";
		return;
	}
	ofstream outfile;
	string output="";
	while(getline(infile, encString)) {
		output += convertLine(encString, encryptedDigit);
	}
	outfile.open(filename);
	outfile << output;
	infile.close();
	outfile.close();
}
int main() {
	cout << "Enter complete path of file which you want to encrypt\n";
	string filename;
	cin >> filename;
	cout << "Enter the encryption shift number\n";
	int encryptedDigit;
	cin >> encryptedDigit;
	int number;
	cout << "Enter 1 number for encrypt and any other number for decrypt\n";
	cin >> number;
	if(number == 1)
		fileEncrypter(filename, encryptedDigit);
	else 
		fileDecrypter(filename, encryptedDigit);
}