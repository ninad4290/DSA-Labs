#include "HugeInteger.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;




HugeInteger::HugeInteger(const std::string& val){
	// TODO
	PositivNum=true;
		int Stop;

		if (val[0]=='-' && val.size()>1 && '1'<=val[1] && '9'>=val[1]) { 
		    PositivNum=false;
		    Stop=1;
		}
		else if ('1'<=val[0] && '9'>=val[0] && val.size()>1) {
		    Stop=0;
		}

		else if ('0'<=val[0] && val.size()==1) {
		    Stop=0;
		}

		else {
		    throw std::invalid_argument("Input is invalid, Please enter a acceptable integer.");
		}

		for (int i=val.size()-1; i>=Stop; i--) {

		    if ('0'<=val[i] && '9'>=val[i]) { 
		        int diff = val[i]-'0';
		        revdigits.push_back(diff);
		    }
		    else { 
		        throw std::invalid_argument("Input contains characters other than integers.");
		    }

		}

}



HugeInteger::HugeInteger(int n) {
	if (n<=0) {
		    throw std::invalid_argument("Cannot create an integer with zero numbers.");
		}

		else {
		    
	    	if (rand()%2 == 0) {
	    	    PositivNum = true;
	    	}
	    	else {
	    	    PositivNum = false;
	    	}



	    	for (int i=0; i<n; i++) {
	    	    if (i==n-1) {
	    	        revdigits.push_back(rand()%9+1); 
	    	    }
	    	    else { 
	    	        revdigits.push_back(rand()%10);
	    	    }
	    	}
		}

}
HugeInteger HugeInteger::absoluteAddition(const HugeInteger& num1, const HugeInteger& num2) { 
	// TODO
	int largesize;
	int smallsize;

	int count = 0;

	int bigger = 0; 

	HugeInteger IntSum; 

	
    if (num1.revdigits.size()>=num2.revdigits.size()) {
        largesize = num1.revdigits.size();
        smallsize = num2.revdigits.size();
        bigger = 0; 
    }

    else {
        largesize = num2.revdigits.size();
        smallsize = num1.revdigits.size();
        bigger = 1; 
    }

    for (int i=0; i<smallsize; i++) {
	    int tempVar = num1.revdigits[i]+num2.revdigits[i]+count;

	    count=tempVar/10; //
	    tempVar=tempVar%10; 

	    IntSum.revdigits.push_back(tempVar); 

	}


	for (int j=smallsize; j<largesize; j++) {

	    if (bigger==0) { 
	        int tempVar = num1.revdigits[j]+count;

    	    count=tempVar/10;
    	    tempVar=tempVar%10; 

    	    IntSum.revdigits.push_back(tempVar);
	    }
	    else {
	        int tempVar = num2.revdigits[j]+count;

    	    count=tempVar/10; 
    	    tempVar=tempVar%10; 

    	    IntSum.revdigits.push_back(tempVar);
	    }
	}


	if (count!=0) {
	    IntSum.revdigits.push_back(count);
	}

	
	return IntSum;
}