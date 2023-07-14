#include "HashTableQuad.h"
#include <iostream>
#include <cmath>
#include <random>
using namespace std;

bool HashTableQuad::isPrime(int n) {
    /*
    Runtime: Big Theta(n) runtime of for
    Space: constant
    */
    if (n == 0 || n == 1) { //0 and 1 are not prime numbers
        return false;
    }

    for (int i = 2; i <= n / 2; i++) { //check all possible divisors between 2 and n/2
        if (n % i == 0) { //if n is divisible by i, then it's not a prime number
            return false;
        }
    }

    return true; //if none of the divisors divide n, then n is a prime number
}

HashTableQuad::HashTableQuad(int maxNum, double load)
/*
Runtime: O(n)
Space: size
*/
{
    //initialize member variables
    maxLoad = load;
    numKeys = 0;
    probes = 0;

    //compute the size of the table based on the maximum number and load factor
    size = ceil(double(maxNum) / load);

    //find the next prime number greater than or equal to the size
    while (isPrime(size) == false) {
        size++;
    }

    //initialize the table with size number of elements, all initialized to 0
    for (int i = 0; i < size; i++) {
        table.push_back(0);
    }
}

// This function is a helper function for the insert function that uses quadratic probing to find the correct index to insert an element into the hash table.
// It takes an integer n as input and returns the index to insert it into.
// It also updates the 'probes' counter for the number of probes taken to insert the element.
// It has an average runtime of 1 and a worst-case runtime of the number of elements in the hash table.
// It uses constant space.
int HashTableQuad::Probe(int n)
{
    // Take the modulo of n with the size of the hash table to get the initial probe index.
    long long int ogProbe = n % size;
    int probe = ogProbe;
    // Initialize the number of successful probes and the quadratic probing factor.
    int succProbes = 1;
    long long int i = 1;
    // Loop through the hash table until an empty slot is found or until the entire table has been searched.
    while (table[probe] != 0) {
        // If the current slot already contains the element we are trying to insert, return -1.
        if (table[probe] == n) {
            return -1;
        }
        else {
            // Compute the next probe index using quadratic probing.
            // If we've already tried to probe every slot in the hash table, return -1.
            if (i >= size) {
                return -1;
            }
            probe = (ogProbe + i*i) % size;
            // Increment the quadratic probing factor and the number of successful probes.
            i++;
            succProbes++;
        }
    }
    // Update the 'probes' counter for the number of successful probes taken to insert the element.
    probes += succProbes;
    // Return the index to insert the element into.
    return probe;
}

// This function inserts an integer n into the hash table.
// It first calls the Probe helper function to find the correct index to insert n into.
// If the load factor exceeds the maximum allowed, it calls the rehash function to resize the hash table.
// It has an average runtime of 1 and a worst-case runtime of the number of elements in the hash table.
// It uses constant space.
void HashTableQuad::insert(int n)
{
    // Call the Probe function to find the index to insert n into.
    int probe = Probe(n);
    if (probe != -1) {
        // If the load factor exceeds the maximum allowed, call the rehash function to resize the hash table.
        if (double(numKeys + 1) / double(size) > maxLoad) {
            rehash();
            probe = Probe(n); // the index to insert n into may have changed after rehashing
        }
        // If the index to insert n into is not -1, insert n into the hash table at that index and increment the number of keys in the hash table.
        if (probe != -1) {
            table[probe] = n;
            numKeys++;
        }
    }
}


void HashTableQuad::rehash()
/*
runtime: avg # of elements (n) ; WC is in last for loop, number of elements in old * number of elements in new
space: size of old table (adding another big o of n, so not changing overall space)
*/
{
    std::vector<int> copy(table); // make a copy of the old table
    size = 2 * size; // double the size of the table
    while (isPrime(size) == false) { // if the new size isn't prime, find the next prime
        size++;
    }
    table.resize(size, 0); // create a new, resized table
    for (int i = 0; i < copy.size(); i++) { // set all entries in the new table to 0
        table[i] = 0;
    }
    numKeys = 0; // reset the number of keys in the table to 0
    probes = 0; // reset the number of probes to 0
    for (int i = 0; i < copy.size(); i++) { // insert all keys from the old table into the new table
        if (copy[i] != 0) { // if the entry exists
            insert(copy[i]); // insert the key into the new table
        }
    }
}

bool HashTableQuad::isIn(int n)
/*
runtime: avg is 1; WC # of elements
space: constant
*/
{
    long long int ogProbe = n % size; // calculate the initial probe location
    int probe = ogProbe;
    long long int i = 1;
    while (table[probe] != 0) { // while the probe location is not empty
        if (table[probe] == n) { // if the key is found at the probe location
            return true;
        }
        else { // if the key is not found at the probe location
            if (i >= size) { // if the maximum number of probes has been reached
                return false; // the key is not in the table
            }
            probe = (ogProbe + i * i) % size; // probe again using the quadratic probing formula
            i++;
        }
    }
    return false; // the key is not in the table
}

void HashTableQuad::printKeys()
/*
runtime: avg is n
space: constant
*/
{
    // TODO
    for (int i = 0; i < size; i++) {
        std::cout << table[i] << std::endl;
    }
}

void HashTableQuad::printKeysAndIndexes()
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

int HashTableQuad::getNumKeys() {

    return numKeys;//returns the numkeys factor in the function
}

int HashTableQuad::getTableSize() {

    return size;//returns the table size in the function
}

double HashTableQuad::getMaxLoadFactor() {

    return maxLoad;//returns the max load factor in the function
}

std::vector<double> HashTableQuad::simProbeSuccess()
{
    // Create a vector with 9 elements to store the results for each load factor
    vector<double> result(9);

    // Total number of keys to insert
    const int totalKeys = 1000;

    // Iterate through 9 different load factors (0.1, 0.2, ..., 0.9)
    for (int i = 1; i <= 9; i++) {
        double total = 0;
        double loadFact = double(double(i) / 10.0); // Calculate the load factor for this iteration
        for (int run = 0; run < 100; run++) {
            HashTableQuad HT(totalKeys, loadFact); // Create a new hash table with the current load factor
            // Insert random values into the hash table until it reaches the total number of keys
            while (HT.numKeys < totalKeys) {
                HT.insert((rand() + 1) * (rand() + 1));
            }
            total += double(HT.probes); // Increment the total number of probes made during the insertion process
        }
        // Calculate the average number of probes per key for this load factor
        result[i - 1] = ((total / 100.0) / double(totalKeys));
    }

    return result; // Return the vector of average probe counts for each load factor
}

