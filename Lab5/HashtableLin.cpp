#include "HashTableLin.h"
#include <iostream>
#include <cmath>
#include <random>
using namespace std;




bool HashTableLin::isPrime(int n) {
	/*
	runtime:  theta(n)
	space: constant
	*/
    // check if the input number is 0 or 1, which are not considered prime
    if (n == 0 || n == 1) {
        return false;
    }

    // loop through all numbers from 2 to n/2 and check if n is divisible by any of them
    // if n is divisible by any of these numbers, it is not prime
    for (int i=2; i <= n/2; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    // if n is not divisible by any numbers from 2 to n/2, it is prime
    return true;
}


HashTableLin::HashTableLin(int maxNum, double load)
/*
	runtime:  theta(n)
	space: size
	*/
{// set the maximum load factor and initialize the number of keys and probes to 0
maxL = load;
numKeys = 0;
probes = 0;

// calculate the size of the table as maxNum/load and round up to the nearest integer
size = ceil(double(maxNum)/load);

// make sure that the size of the table is a prime number by incrementing it until a prime is found
while (isPrime(size) == false) {
    size++;
}

// initialize the table with zeros
for (int i = 0; i < size; i++) {
    table.push_back(0);
}
}

int HashTableLin::Probe(int n) {
	/*
	runtime: avg is theta(1);
	space: constant
	*/
    // initialize probe as n mod size
    int probe = n % size;
    // initialize succProbes to 1
    int succProbes = 1;

    // iterate while the value at the probe is not 0
    while (table[probe]!=0) {
        // if the value at the probe is n, return -1 to indicate that the value is already in the table
        if (table[probe] == n) {
            return -1;
        }
        else {
            // increment the probe by 1 and wrap around to the beginning if necessary
            probe=(probe+1)%size;
            // increment the number of successful probes by 1
            succProbes++;
        }
    }
    // increment the total number of probes by the number of successful probes
    probes += succProbes;
    // return the index at which the value can be inserted
    return probe;
}


void HashTableLin::insert(int n)
/*
runtime: avg is theta(1);
space: constant unless rehash
*/
{
    int probe = Probe(n); // get the initial probe index for the element
    if (probe != -1) { // check if element was found, -1 indicates it was found
        if (double(numKeys+1)/double(size) > maxL) { // check if rehash is needed to maintain max load factor
            rehash(); // if needed, increase size of the hash table and rehash all elements
            probe = Probe(n); // recalculate the probe index for the element after rehashing
        }
        table[probe] = n; // insert element at the calculated probe index
        numKeys++; // increment the number of keys in the hash table
    }
}



void HashTableLin::rehash()
/*
runtime: avg # of elements (n) ; WC is in last for loop, number of elements in old * number of elements in new
space: size of old table (adding another big o of n, so not changing overall space)
*/
{
    // Make a copy of the current table
    std::vector<int> copy(table);

    // Double the size of the table and find the next prime number greater than the new size
    size = 2 * size;
    while (isPrime(size) == false) {
        size++;
    }

    // Resize the table to the new size and set all values to 0
    table.resize(size, 0);
    for (int i = 0; i < copy.size(); i++) {
           table[i] = 0;
       }

    // Reset the number of keys and probes
    numKeys = 0;
    probes = 0;

    // Re-insert all the elements from the copy into the new table
    for (int i = 0; i < copy.size(); i++) {
        if (copy[i] != 0) { //if the entry exists
           insert(copy[i]);
        }
    }
}


bool HashTableLin::isIn(int n)
/*
runtime: avg is 1; WC # of elements
space: constant
*/
{
    // TODO, change following code after completing this function
    int probe = n % size;
    while (table[probe] != 0) {
        if (table[probe] == n) {
            return true;
        }
        else{
            probe = (probe + 1) % size;
        }
    }
    return false;
}

void HashTableLin::printKeys()
/*
runtime: avg is n
space: constant
*/
{

    for (int i = 0; i < size; i++) {
        std::cout << table[i] << std::endl;//outputs yhe keys
    }
}

void HashTableLin::printKeysAndIndexes()
/*
runtime: avg is n
space: constant
*/
{
    // TODO
    for (int i = 0; i < size; i++) {
        std::cout << i << ", " << table[i] << std::endl;
    }
}

int HashTableLin::getNumKeys() {
	
    return numKeys;//returns the numkeys factor in the function
}

int HashTableLin::getTableSize() {
	
    return size;//returns the table size in the function
}

double HashTableLin::getMaxLoadFactor() {
	
    return maxL;//returns the max load factor in the function
}

std::vector<double> HashTableLin::simProbeSuccess()
{
    // create a vector with 9 elements to store the result
    vector<double> result(9);
    // initialize a variable to keep track of the total number of probes
    double total = 0;
    // set the total number of keys to 1000
    const int allKeys = 1000;

    // loop through 9 load factors from 0.1 to 0.9
    for (int i = 1; i <= 9; i++) {
        total = 0;
        // calculate the load factor as the current index divided by 10.0
        double loadFac = double(double(i)/10.0);

        // run the experiment 100 times
        for (int run = 0; run < 100; run++) {
            // create a new hash table with totalKeys and loadFact
            HashTableLin HT(allKeys, loadFac);

            // insert random values into the hash table until it reaches totalKeys
            while (HT.numKeys < allKeys) {
                HT.insert((rand()+1) * (rand()+1));
            }

            // update the total number of probes
            total += double(HT.probes);
        }

        // calculate the average number of probes per insertion and store it in the result vector
        result[i - 1] = ((total / 100.0) / double(allKeys));
    }

    // return the result vector
    return result;
}
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    
    vector<double> result(9);// create a vector with 9 elements to store the result
    return result;// return the result vector
}
