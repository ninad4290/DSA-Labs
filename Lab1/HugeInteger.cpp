#include "HugeInteger.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;

HugeInteger::HugeInteger(const std::string& val) {
	
	int i;

	if (val[0] == '-') { //if the first element of string val contains a negative before it
		negative = true; //the boolean with name negative is true
	}

	else {
		negative = false; //otherwise the boolean negative is false
	}

	int size = 0;
	for (size = 0; val[size] != '\0'; size++) { //for loop that starts at size=0 and iterates through loop as long as position size in string val does not reach an empty character
		if ((negative) && (val[size] == '-')) { //if the element is negative, and position size in string val is a minus sign
			continue; //continue
		}

		else if (!(val[size] >= 48 && val[size] <= 57)) { //if the position size is NOT in between ASCII characters 48 and 57 (between 1 and 9)
			throw("error"); //throw an error

		}
	}

	if (size == 0) { //if the size of the string is 0
		throw("error"); //throw an error
	}

	for (i = 0; i < size; i++) { //for loop to start at i=0 and iterate through all the values in the string as long as it is less than the string size
		if (!(i == 0 && negative)) { //if i is NOT equal to 0 and it is NOT negative
			large.push_back(val[i] - 48); //append the value to the beginning of vector large
		}

	}

}


HugeInteger::HugeInteger(int n) {
	
	srand(time(0)); //generate random as time goes on
	if (n <= 0) { //if n is less than or equal to zero
		throw("error"); //throw an error
	}

	else {

		int num = 1 + (rand() % 9); //generate the random number with the first digit being anything other than 0
		large.push_back(num); //append the number to the end of vector large
		negative = rand() % 2; //generates a 0 or 1 boolean value
		for (int i = 1; i < n; i++) { //for loop starting at i=1, and iterating as long as i is less than n digits (runs n times)
			num = rand() % 10; //generate random number from 0 through 9
			large.push_back(num); //append the number to the end of vector large

		}

	}


}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	
	int carry = 0;
	int s = 0;
	string sum = "";
	int i = 0;
	int j = 0;

	if (large.size() >= h.large.size()) { //if the vector size is larger or equal to the second vector
		i = large.size() - 1; //set i to be the vector size - 1 which reads back to front of the vector
		j = h.large.size() - 1; //set j to be the vector size - 1 to read from the back to the front of the vector

		while (j >= 0) { //while j is greater than 0
			s = large[i] + h.large[j] + carry; //s is element from large + element from j + carry
			sum = to_string((s % 10)) + sum; //get the sum
			carry = s / 10; //gets the carry

			i--; //move back in the vector
			j--; //move back in the vector
		}

		while (i >= 0) {
				s = large[i] + carry;
				sum = to_string((s % 10)) + sum;
				carry = s / 10;

				i--;
		}

	}
	else {
		i = h.large.size() - 1;
		j = large.size() - 1;

		while (j >= 0) {
			s = h.large[i] + large[j] + carry;
			sum = to_string((s % 10)) + sum;
			carry = s / 10;

			i--;
			j--;
		}
		while (i >= 0) {
			s = h.large[i] + carry;
			sum = to_string((s % 10)) + sum;
			carry = s / 10;
			i--;
		}
	}
	if (carry)
		sum = "1" + sum;

	return HugeInteger(sum);

}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	
	return HugeInteger("");
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	
	return 0;
}

std::string HugeInteger::toString() {
	

	string str = ""; //initialize an empty string called str
	if (negative) { //if it was negative
		str += "-"; //add a minus sign to the string

	}
	for (auto i = large.begin(); i != large.end(); i++) { //for loop starting at the first pointer of vector large and iterating as long as it is not the last pointer
		str += to_string(*i); //pointer pointing two elements in vector large
	}

	return str;

}