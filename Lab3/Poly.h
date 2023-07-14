#ifndef POLY_H_
#define POLY_H_

#include "PolyNode.h"
#include <vector>
#include <string>

class Poly
{
private:

	PolyNode* HeadPtr = NULL;// Pointer to the head of the polynomial linked list
	int len;// size of the polynomial
    PolyNode* length = 0;//length of the polynomial
    PolyNode *last = new PolyNode(-1, 0, NULL);// Pointer to the last node of the polynomial linked list

public:
	Poly();// Default constructor
	Poly(const std::vector<int>& deg, const std::vector<double>& coeff);// Constructor that takes vectors of degree and coefficient values
	~Poly();// Destructor

	void addMono(int i, double c);// Adds a monomial to the polynomial
	void addPoly(const Poly& p);//Adds another polynomial to the current polynomial
	void multiplyMono(int i, double c);// Multiplies the polynomial by a monomial
	void multiplyPoly(const Poly& p);// Multiplies the polynomial by another polynomial
	void duplicate(Poly& outputPoly);// Duplicates the current polynomial
	int getDegree();// Gets the degree of the polynomial
	int getTermsNo();// Gets the number of terms in the polynomial
	std::string toString();// Converts the polynomial to a string representation
	double evaluate(double x);// Evaluates the polynomial at a given value of x
	PolyNode* getHead() {// Gets a pointer to the head of the polynomial linked list
		return HeadPtr;
	};
};

#endif