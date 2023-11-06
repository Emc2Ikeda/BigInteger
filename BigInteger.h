// Name: BigInteger.h
// Date: 11/2/22
// Author: Ema Ikeda
// Description: h file for BigInteger class

#ifndef BIGINT
#define BIGINT
#include "DoublyLinkedList.h"
#include <string>

class BigInteger
{
private:
	DoublyLinkedList<int> intString; // series of Node<int>
	void flipSign(); // flip sign of BigInteger for operator + and -
	void truncate(); // delete leading 0's for operator-
	bool compare(BigInteger&);
public:
	BigInteger();
	BigInteger(std::string); // parameterized constructor w/ determined string 
	BigInteger(const BigInteger& other); // copy constructor
	~BigInteger();
	bool isNegative(); // check if BigInteger is negative
	int getLength() const; // returns the length of bigInteger

	BigInteger operator+(BigInteger&);
	BigInteger operator-(BigInteger&);
	bool operator<=(BigInteger&);
	bool operator>=(BigInteger&);
	bool operator==(BigInteger&);
	bool operator>(BigInteger&);
	bool operator<(BigInteger&);
	// makes BigInteger1=BigInteger2
	void operator=(BigInteger&);

	friend ostream& operator<<(ostream& out, const BigInteger&);

	friend ifstream& operator>>(ifstream& in, BigInteger&);
};

// Print BigInteger by calling DLL::operator<<
ostream& operator<<(ostream& out, const BigInteger& other) {
	out << other.intString;
	return out;
};

// Call DLL::operator>> to make intString equal to the line in test.txt
ifstream& operator>>(ifstream& in, BigInteger& other) {
	std::string line;
	getline(in, line, '\n');
	// make intString equal to line
	for (char lineChar: line) {
      int digit = lineChar - '0';
      other.intString.insertLast(digit);
   	}
	return in;
};

#endif