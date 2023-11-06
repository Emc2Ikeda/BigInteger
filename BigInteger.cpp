// Name: BigInteger.cpp
// Date: 11/2/22
// Author: Ema Ikeda
// Description: cpp file for BigInteger class

#include "BigInteger.h"

// default constructor
BigInteger::BigInteger() {
}

// parameterized constructor with known string
BigInteger::BigInteger(std::string str)
{
	int digit;
	bool negSign = str.at(0) == '-'; // flag that triggers if str(0) is negative.
	if (negSign == true) { 
		// start loop from str[1], then multiply intString's first node by -1 if there is a negative sign
		for (int i=1; i < str.length(); i++) {
			// convert each char to int, then add to dll
			digit = str.at(i) - '0';
			// if digit is not int, go to IllegalArgumentException
			intString.insertLast(digit);
		}
		intString.getFirst()->data *= -1;
	} else {
		// if there is no negative sign, start from str[0]
		for (int i = 0; i < str.length(); i++) {
			digit = str.at(i) - '0';
			intString.insertLast(digit);
		}
	}
}

BigInteger::~BigInteger() {
	intString.clear();
}

// copy constructor
// debug
BigInteger::BigInteger(const BigInteger& other) {
	intString = other.intString;
	// call copy constructor of dll
	// destroy intString
	// // fill all elements of other.intstring to this
	// intString.clear();
	
	// // fill 
	// intString = other.intString;
}

// check if BigInteger is negative
bool BigInteger::isNegative() {
	// if the first node is < 0, return true
	return intString.getFirst()->data < 0;
}

bool BigInteger::compare(BigInteger& other) {
	bool meetsCondition = false;
	Node<int>* cursor = intString.getFirst(); // make it point to intString.first when Node<T>*'s are protected
	Node<int>* otherCursor = other.intString.getFirst();
	// Starting from the highest digit, traverse down the list. 
	//If one of the digit in this is greater than that of other, return true
	while (cursor != NULL) {
		if (cursor->data > otherCursor->data) {
			meetsCondition = true;
			break;
		}
		// both cursors move to the next node
		cursor = cursor->next;
		otherCursor = otherCursor->next;
	}
	return meetsCondition;
}

int BigInteger::getLength() const {
	return intString.getLength();
}

void BigInteger::flipSign() {
	intString.getFirst()->data *= -1;
}

BigInteger BigInteger::operator+(BigInteger& other) {
	// if this and other's sign is different call operator-
	if (isNegative() && !other.isNegative()) {
		flipSign();
		other - *this;
	} else if (!isNegative() && other.isNegative()) {
		other.flipSign();
		*this - other;
	}

	// make copy of this and other to leave this or other unaffected
	BigInteger x = *this; // copy of this
	BigInteger y = other;
	Node<int>* otherCursor = y.intString.getLast();
	Node<int>* cursor = x.intString.getLast();
	// iterate backwards to add from the lowest digit
	// if one of the bigInt is shorter than the other and both bigInt's are negative, 
	//change its first node to positive
	if (x.isNegative() && y.isNegative()) {
		if (x.getLength() < y.getLength()) {
			x.flipSign();
		} else if (x.getLength() > y.getLength()) {
			y.flipSign();
		}
	}

	while (cursor != NULL && otherCursor != NULL) {
		cursor->data += otherCursor->data;
		// add 1 to next digit if sum > 9 and change digit to sum % 10
		if (cursor->data > 9) {
			cursor->data %= 10;
			// if the first node is negative, subtract by 1 instead
			if (x.isNegative() && cursor->prev->prev == NULL) {
				cursor->prev->data -= 1;
			} else if (cursor->prev == NULL) {
				if (cursor->data < 0) {
					cursor->data *= -1;
				}
				x.intString.insertFirst(1);
			} else {	
				cursor->prev->data += 1;
			}
		}
		cursor = cursor->prev;
		otherCursor = otherCursor->prev;
	}
	
	// add missing digits from other to intString if other had more digits than this
	if (otherCursor != NULL) {
		while (otherCursor != NULL) {
			x.intString.insertFirst(otherCursor->data);
			otherCursor = otherCursor->prev;
		}
	}
	BigInteger result = x;
	return result;
}

//Subtract elements in this with that of other. Use borrowing during subtraction
BigInteger BigInteger::operator-(BigInteger& other) {
	// if this < 0 and other > 0, call operator+
	if (isNegative() && !other.isNegative()) {
		other.flipSign();
		other + *this;
		return *this;
	} else if (!isNegative() && other.isNegative()) {
		other.flipSign();
		*this + other;
		return *this;
	}

	BigInteger x = *this; // copy of this and other
	BigInteger y = other;

	bool negative = x.isNegative(); // Use to carry over negative sign if result was negative
	// If this < other, switch values of this and other and make the result negative
	if (x < y) {
		BigInteger temp = x;
		x = y;
		y = temp;
		negative = true;
	}
	Node<int>* otherCursor = y.intString.getLast();
	Node<int>* cursor = x.intString.getLast();

	if (x.isNegative() && y.isNegative()) {
		if (x.getLength() < y.getLength()) {
			x.flipSign();
		} else if (x.getLength() > y.getLength()) {
			y.flipSign();
		}
	}
	// iterate backwards to add from the lowest digit
	while (cursor != NULL && otherCursor != NULL) {
		cursor->data -= otherCursor->data;
		// add 10 to current digit and subtract 1 from next digit if difference < 0
		if (cursor->data < 0) {
			cursor->data += 10;
			cursor->prev->data -= 1;
		}
		cursor = cursor->prev;
		otherCursor = otherCursor->prev;
	}

	if (otherCursor != NULL) {
		while (otherCursor != NULL) {
			x.intString.insertFirst(otherCursor->data);
			otherCursor = otherCursor->prev;
		}
		if (x.intString.getFirst()->data == 0) { // trim 0 and keep negative sign if it is negative
			x.intString.deleteFirst();
		}
	}

	x.truncate();

	if (negative) { // carry over negative sign if result was negative
		x.flipSign();
	}

	BigInteger result = x;
	return result;
}

// BigInteger BigInteger::operator-(BigInteger& other) {
// // if this < 0 and other > 0, call operator+
// if (isNegative() && !other.isNegative()) {
// 	other.flipSign();
// 	other + *this;
// 	return *this;
// } else if (!isNegative() && other.isNegative()) {
// 	other.flipSign();
// 	*this + other;
// 	return *this;
// }

// bool negative = isNegative(); // Use to carry over negative sign if result was negative
// // If this < other, switch values of this and other and make the result negative
// if (*this < other) {
// 	BigInteger temp = *this;
// 	*this = other;
// 	other = temp;
// 	negative = true;
// }
// Node<int>* otherCursor = other.intString.getLast();
// Node<int>* cursor = intString.getLast();

// if (isNegative() && other.isNegative()) {
// 	if (getLength() < other.getLength()) {
// 		flipSign();
// 	} else if (getLength() > other.getLength()) {
// 		other.flipSign();
// 	}
// }

// Truncate leading zero's, but if result contained only 0's, keep one zero.
void BigInteger::truncate() {
	int leadingDigit = intString.getFirst()->data;
	if (getLength() <= 1) { // don't truncate if BigInt is shorter than 1 digit
		return;
	} else if (leadingDigit != 0) {
		return;
	} else {
		Node<int>* cursor = intString.getFirst();
		while (cursor->data != 0 || intString.getLength() > 1) {
			intString.deleteFirst();
			cursor = cursor->next;
		}
	}
}

bool BigInteger::operator<=(BigInteger& other)
{
	bool isLessThanOrEqual;
	// check if this and other has same sign. If this is negative and other is positive, return false
	//if other is negative and this is positive, return true
	if (isNegative() && !other.isNegative()) { // this < 0 and other > 0
		isLessThanOrEqual = true;
	}
	else if (!isNegative() && other.isNegative()) { // this > 0 and other < 0
		isLessThanOrEqual = false;
	}
	else { // this and other has the same sign
		if ((*this < other) || (*this == other)) {
			isLessThanOrEqual = true;
		}
	}

	// if all nodes have the same data, return true
	return isLessThanOrEqual;
}

bool BigInteger::operator>=(BigInteger& other) {
	DoublyLinkedList<int> otherIntString = other.intString;
	bool isGreaterThanOrEqual = false;

	// check if this and other has same sign. If this is negative and other is positive, return false
	//if other is negative and this is positive, return true
	if (isNegative() && !other.isNegative()) { // this < 0 and other > 0
		isGreaterThanOrEqual = false;
	}
	else if (!isNegative() && other.isNegative()) { // this > 0 and other < 0
		isGreaterThanOrEqual = true;
	}
	else { // this and other has the same sign
		if (intString.getLength() > otherIntString.getLength()) { // EX: "100" >= "10"
			isGreaterThanOrEqual = true;
		} 
		else if (intString.getLength() < otherIntString.getLength()) { // EX: "10" <= "100"
			isGreaterThanOrEqual = false;
		}
		else {
			if ((*this > other) || (*this == other)) {
				isGreaterThanOrEqual = true;
			}
		}
	}
	return isGreaterThanOrEqual;
}

// check if this is equal to other by traversing all the nodes in both this and other.
//if length of this and other does not match, assume that this!= other, so return false
bool BigInteger::operator==(BigInteger& other) {
	// if length is unequal, return false
	if (getLength() != other.getLength()) {
		return false;
	}
	Node<int>* cursor = intString.getFirst(); // make it point to intString.first when Node<T>*'s are protected
	Node<int>* otherCursor = other.intString.getFirst();
	while (cursor != NULL) {
		// if any of the nodes are not the same, return false
		if (cursor->data != otherCursor->data) {
			return false;
		}
		// both cursors move to the next node
		cursor = cursor->next;
		otherCursor = otherCursor->next;
	}
	return true;
}

// check if this > other by comparing their lengths, whether they are negative, 
//and the value of the nodes
bool BigInteger::operator>(BigInteger& other) {
	// Return true if this > other. Return false otherwise
	bool isGreaterThan = false;

	//Case when this > 0 and other > 0. Return true if:
	//1. If this is longer than other, return true
	//2. If this's length is equal to other...
	if (!isNegative() && !other.isNegative()) {
		//If this's length is greater than other's length, assume that this > other
		if (getLength() > other.getLength()) {
			isGreaterThan = true;		
		} else if (this->getLength() == other.getLength()) {
			
			// traverse both this and other and compare data
			Node<int>* cursor = intString.getFirst(); // make it point to intString.first when Node<T>*'s are protected
			Node<int>* otherCursor = other.intString.getFirst();
			// Starting from the highest digit, traverse down the list. 
			//If one of the digit in this is greater than that of other, return true
			while (cursor != NULL) {
				if (cursor->data > otherCursor->data) {
					isGreaterThan = true;
					break;
				} else if (cursor->data < otherCursor->data) {
					break;
				}
				// both cursors move to the next node
				cursor = cursor->next;
				otherCursor = otherCursor->next;
			}
		}
	//If this < 0 and other > 0, then this < other
	} else if (!isNegative() && other.isNegative()) {
		isGreaterThan = true;
	// If both this and other < 0, return true if: 
	//1. this's length is less than other's
	} else if (isNegative() && other.isNegative()) {
				//If this's length is greater than other's length, assume that this > other
		if (getLength() < other.getLength()) {
			isGreaterThan = true;
		} else if (this->getLength() == other.getLength()) {
			isGreaterThan = compare(other);
		}
	}
	return isGreaterThan;
}

bool BigInteger::operator<(BigInteger& other) {
	bool isLessThan = false;

	//When this > 0 and other > 0. Return true if:
	//1. If this has less digits than other, return true
	//2. If this has the same number of digits as other, compare value of each digits, starting from the highest digit.
	//If the this's current digit is less than other's current digit, return true.
	if (!isNegative() && !other.isNegative()) {
		if (getLength() < other.getLength()) {
			isLessThan = true;		
		} else if (this->getLength() == other.getLength()) {
			// traverse both this and other and compare data
			Node<int>* cursor = intString.getFirst(); // make it point to intString.first when Node<T>*'s are protected
			Node<int>* otherCursor = other.intString.getFirst();
			// Starting from the highest digit, traverse down the list. 
			//If one of the digit in this is greater than that of other, return true
			while (cursor != NULL) {
				if (cursor->data < otherCursor->data) {
					isLessThan = true;
					break;
				} else if (cursor->data > otherCursor->data) {
					break;
				}
				// both cursors move to the next node
				cursor = cursor->next;
				otherCursor = otherCursor->next;
			}
		}
	//If this < 0 and other > 0, then this < other
	} else if (isNegative() && !other.isNegative()) {
		isLessThan = true;
	// If both this and other < 0, return true if: 
	//1. this's length is less than other's
	} else if (isNegative() && other.isNegative()) {
		//When this < 0 and other < 0. Return true if:
		//1. If this has more digits than other, return true
		//2. If this has the same number of digits as other, compare value of each digits, starting from the highest digit.
		//If the this's current digit is greater than other's current digit, return true.

		if (getLength() > other.getLength()) {
			isLessThan = true;
		} else if (this->getLength() == other.getLength()) {
			Node<int>* cursor = intString.getFirst(); // make it point to intString.first when Node<T>*'s are protected
			Node<int>* otherCursor = other.intString.getFirst();
			// Starting from the highest digit, traverse down the list. 
			//If one of the digit in this is greater than that of other, return true
			// Check if this.intString's first node is less than that of other.intString's first node
			if (cursor->data < otherCursor->data) {
				isLessThan = true;
				return isLessThan;
			} else if (cursor->data > otherCursor->data) {
				isLessThan = false;
				return isLessThan;
			}

			// After checking the first node, start the while loop from the next node
			cursor = cursor->next;
			otherCursor = otherCursor->next;

			while (cursor != NULL) {
				if (cursor->data > otherCursor->data) {
					isLessThan = true;
					break;
				}
				cursor = cursor->next;
				otherCursor = otherCursor->next;
			}
		}
	}
	return isLessThan;
}

// makes BigInteger1=BigInteger2
void BigInteger::operator=(BigInteger& other) {
	// flush this, then replace intString with other.intString
	intString.clear();
	Node<int>* cursor = other.intString.getFirst();
	while (cursor != NULL) {
		intString.insertLast(cursor->data);
		cursor = cursor->next;
	}
	// return *this;
}
