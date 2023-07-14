#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>




class HugeInteger
{
private:



	HugeInteger absoluteAddition(const HugeInteger& num1, const HugeInteger& num2);
	int absoluteValue(const HugeInteger& h);
	HugeInteger absoluteSubtraction(const HugeInteger& num1, const HugeInteger& num2);
	std::vector<int> revdigits;
	bool PositivNum;

public:

	// Required methods



	HugeInteger(const std::string& val);
	HugeInteger(int n);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
	HugeInteger() {
		    revdigits = {};
		    PositivNum = true;
	}
	int whichIsBigger(const HugeInteger& h);




};

#endif /* HUGEINTEGER_H_ */