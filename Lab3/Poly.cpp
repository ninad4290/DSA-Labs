#include "Poly.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;



Poly::Poly() //Time complexity= theta(1) , space complexity= theta(1)
{
	HeadPtr = new PolyNode(-1, 0, NULL); //This statement initializes a new polynomial with a single dummy node which contains degree -1 and coefficient 0, and points to NULL
	len = 0; //sets value of size to zero
}



Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)//Time complexity= theta(n) , space complexity= theta(n)
{
    for (int i = deg.size(); i > 0; i--){ //creates a linked list. The for loop iterates over the deg vector in a reverse order.
    	PolyNode *newNode = new	PolyNode (deg[i-1], coeff[i-1], HeadPtr);// This statement creates a new Polynode object that stores the degree and coefficients and moves next
    	HeadPtr = newNode;//HeadPtr points to the first object in the linked list
    }
    len = deg.size(); // It assigns the value of the len to the input deg vector
    PolyNode *BPtr = HeadPtr; // This line creates a new pointer and assigns it the value of the current head pointer HeadPtr
    HeadPtr = new PolyNode (-1, 0, BPtr);//This line creates a new head node with a degree of -1 and coefficient of 0, and links it to the previous head node using the backup pointer BPtr

}




Poly::~Poly()//Time complexity= theta(n) , space complexity= theta(1)
{
    PolyNode* temporaryVar;//pointer to hold a reference to a node
    while (HeadPtr -> next){ //while loop checks if there is a next node in the linked list
    	temporaryVar = HeadPtr -> next; //tempVar is assigned the reference to the next node
    	HeadPtr -> next = temporaryVar -> next;//the next node of HeadPtr is assigned to the next node of the temporaryVar
    	free(temporaryVar);//deallocates the memory allocated to node being deleted
	}
}






void Poly::addPoly(const Poly& p) //Time complexity= theta(n^2) , space complexity= theta(n)
{
	PolyNode *Node = p.HeadPtr->next;//pointer to the first node
    while(Node){
    	addMono(Node->deg, Node->coeff); //adds a new node to the current object's linked list with the same degree and coefficient values.
    	Node = Node->next;//Node pointer is updated to the next node in the Poly object
    }
}

void Poly::addMono(int i, double c) { // This function adds a monomial (a term of the form c*x^i) to the polynomial.
	// The input is the degree i and coefficient c of the monomial to add.
	// Time complexity is theta(n), where n is the number of terms in the polynomial.
	// Space complexity is theta(1), because only a constant amount of memory is used.

    if(c==0){	//This if statement checks if the coefficient we're adding by is zero.
        return;
    }

    if(getTermsNo()==0){    // If the polynomial is empty, we add the monomial as the first term.
        HeadPtr->next = new PolyNode(i,c,NULL);
        return;
    }

    // We iterate over the terms of the polynomial to find where to insert the new monomial.
    PolyNode *prev = HeadPtr;// Pointer to the previous term in the polynomial.

    for(PolyNode *thisnode = HeadPtr->next; thisnode != NULL; thisnode = thisnode->next){

            if(i == thisnode->deg){ //when the input degree is the same as this term degree
                if (thisnode->coeff + c == 0){// If the sum of the coefficients is zero, we remove the term.
                    prev->next = thisnode->next;
                    len--;
                }
                else{// Otherwise, we update the coefficient of the existing term.
                    thisnode->coeff = thisnode->coeff + c;
                    len++;
                }
                return;
            }
            // If the degree of the new monomial is greater than the degree of the current term, we insert the new term before it.
            else if(i > thisnode->deg){
                prev->next = new PolyNode(i,c,thisnode);
                len++;
                return;
            }
            // If we reach the end of the polynomial without finding a term with degree greater than the new monomial, we add it as the last term.
            else if (thisnode->next == NULL && i < thisnode->deg){    //new smallest degree
                thisnode->next = new PolyNode(i,c,NULL);
                len++;
                return;
            }
            // Update the pointer to the previous term.
            prev = thisnode;
        }



}




void Poly::multiplyMono(int i, double c)          //Time complexity= theta(n) , space complexity= theta(1)
{
    if (c == 0)                       //This if statement checks if the cefficient we're multiplying by is zero.
    {
        HeadPtr->next = NULL;            //This statement makes the list empty if the if statement is true because anything times zero is zero.
    }
    PolyNode* ptr = HeadPtr->next;       //This statement intruduces a pointer and makes it point to the first node in the list.
    while (ptr)                       //This while loop iterates through each node in the in the list.
    {
        ptr->coeff *= c;              //This statement multiplies the coefficient of the node the pointer is pointing to by the coefficient of the monomial (ex. 2x^2 * 3x -> 2*3=6).
        ptr->deg += i;                //This statement adds the degree of the node the pointer is pointing to, to the degree of the monomial (x^2 * x = x^3).
        ptr = ptr->next;              //This statement moves the pointer to the next node for the next iteration of the while loop.
    }
}



void Poly::multiplyPoly(const Poly& p)          //Time complexity= theta(n^3) the while loop runs n times and calls the addPoly method each time, which has a time complexity of n^2 so n*n^2=n^3.
{                                               //space complexity= theta(n) space complexity for duplicate function and addPoly is theta(n) so n+n = theta(n)
    if (getDegree() == -1)                      //This if statement checks if the degree of the list is -1 (i.e.if the list is empty).
    {
        return;                                 //This statement returns nothing if the list is empty.
    }

    PolyNode* polynomial_head = p.HeadPtr;         //This statement introduces a pointer pinting to the head of the polynomial we're multiplying our list by.
    Poly* initial = new Poly();                 //This statement creates a new, empty list, initialt.
    Poly* node_mult = new Poly();               //This statement creates a new, empty list, node_mult.
    Poly* mult_result= new Poly();              //This statement creates a new, empty list, mult_result.
    duplicate(*initial);                        //This statement duplicates our initial list/polynomial into the 'initial' list we created.

    while (polynomial_head->next != NULL)       //This while loop iterates through each node in the polynomial.
    {
        initial->duplicate(*node_mult);              //This statement duplicates the initial list into the list 'node_mult'.
        node_mult->multiplyMono(polynomial_head->next->deg, polynomial_head->next->coeff);   //This statement calls the MultiplyMono and multiplys each node in the polynomial by all the nodes of our initial list/polynomial which we duplicated into 'initial' list.
        mult_result->addPoly(*node_mult);                                                    //This statement adds the value of the multiplication of this node of the polynomial into the list that will be carrying the multiplication result.
        polynomial_head = polynomial_head->next;                                             //This statement moves the head of the polynomial into the next node.
    }
    mult_result->duplicate(*this);              //This statement duplicates the result of the multiplication into our original list/polynomial.
}



void Poly::duplicate(Poly& outputPoly)          //Time complexity= theta(n) , space complexity= theta(n)
{
    PolyNode* head_ptr = HeadPtr;
    PolyNode* new_list_ptr = outputPoly.HeadPtr;

    if (HeadPtr->next == NULL)             //This if statement checks if the list is empty.
    {
        outputPoly.HeadPtr->next = NULL;   //This statement makes the duplicate list also empty if the original list is empty.
    }

    while (head_ptr->next != NULL)      //This while loop iterates through each node in the original list.
    {
        if (new_list_ptr->next != NULL)                         //This if statement checks if the node in the duplicat list is not the last node.
        {
            new_list_ptr->next->coeff = head_ptr->next->coeff;  //This statement assigns the coefficient of the node in the duplicate list to the coeffiecient of the node in the original list.
            new_list_ptr->next->deg = head_ptr->next->deg;      //This statement assigns the degree of the node in the duplicate list to the degree of the node in the original list.
        }
        else      //This else statement will run if the if statement condition was not met (i.e. this is the last node in the duplicate list)
        {
            new_list_ptr->next = new PolyNode(head_ptr->next->deg, head_ptr->next->coeff, NULL);            //This statement creates a new node in the duplicate list pointing to null/being the last node with the same coefficient and degree as the node in the original list.
        }
        head_ptr = head_ptr->next;                              //This statement moves the pointer to the next node in the original list.
        new_list_ptr = new_list_ptr->next;                      //This statement moves the other pointer to the next node in the duplicate list.
    }
}
int Poly::getDegree()                //Time complexity= theta(1) , space complexity= theta(1)
{
    if (HeadPtr->next == NULL)          //This if statement checks if the list is empty.
    {
        return -1;                   //This statement returns -1 if the list is empty.
    }
    int degree = HeadPtr->next->deg;    //This statement returns the degree of the first node in the list, which would be carrying the highest degree, being the degree of the polynomial.
    return degree;                   //This statement returns the degree of the first node if the list is not empty.
}



int Poly::getTermsNo()            //Time complexity= theta(n) , space complexity= theta(1)
{
    PolyNode* head_ptr;           //This statement creates a pointer pointing to the head node of the linked list.
    int TermsNo = 0;              //This statement introduces the variable count which will carry the number of terms in the list.
    for (head_ptr = HeadPtr->next; head_ptr != NULL; head_ptr = head_ptr->next)          //This for loop iterates through each node in the list.
    {
        TermsNo++;                //This statement adds one to TermsNo, indicationg the counting of one extra node.
    }
    return TermsNo;               //This statement returns the number of terms/ nodes in the list.
}



double Poly::evaluate(double x)         //Time complexity= theta(n) , space complexity= theta(1)
{
    PolyNode* head_ptr = this->HeadPtr;            //This statement creates a pointer pointing to the head node of the linked list.
    double result = 0;                         //This statement introduces the variable "total", which will hold the result of the evaluation.

    while (head_ptr->next != NULL)                                      //This while loop iterates through each node in the list.
    {
        result+= head_ptr->next->coeff * pow(x, head_ptr->next->deg);   //This statement evaluates the expression at that node (ex. if coefficient is 3, degree is 2, and the input of the method,x, is 4, then this would evaluate 3x^2= 3*4^2= 48)and adds the result to the total.
        head_ptr = head_ptr->next;
    }

    return result;          //This statement returns the result of the evaluation.
}



std::string Poly::toString()            //Time complexity= theta(n) , space complexity= theta(1)
{
    std::string str = "degree=" + std::to_string(this->getDegree()) + "; ";

    PolyNode* head_ptr = this->HeadPtr;

    while (head_ptr->next != NULL)
    {
        str = str + "a(" + std::to_string(head_ptr->next->deg) + ")=" + std::to_string(head_ptr->next->coeff) + "; ";
        head_ptr = head_ptr->next;
    }

    return str;
}
