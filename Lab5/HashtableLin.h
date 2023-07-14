#ifndef HASHTABLELIN_H_ // header guard to prevent multiple includes
#define HASHTABLELIN_H_

#include <vector>

class HashTableLin // class definition
{
private:
	// private member variables
	std::vector<int> table; // vector to store hash table
	int size; // current size of hash table
	int numKeys; // number of keys currently in hash table
	double maxL; // maximum load factor allowed
	int probes; // total number of probes made during operations

	// private member functions
	bool isPrime(int n); // helper function to check if a number is prime
	int Probe(int n); // helper function to perform linear probing

public:
	// public member functions
	HashTableLin(int maxNum, double load); // constructor to initialize hash table with maximum number of elements and maximum load factor

	void insert(int n); // function to insert a key into the hash table
	bool isIn(int n); // function to check if a key is present in the hash table
	void printKeys(); // function to print all the keys in the hash table
	void printKeysAndIndexes(); // function to print all the keys and their indexes in the hash table
	int getNumKeys(); // function to get the current number of keys in the hash table
	int getTableSize(); // function to get the current size of the hash table
	double getMaxLoadFactor(); // function to get the maximum load factor allowed

	// static member functions
	static std::vector<double> simProbeSuccess(); // function to simulate the average number of probes for a successful search
	static std::vector<double> simProbeUnsuccess(); // function to simulate the average number of probes for an unsuccessful search (bonus)

	// getter function for the table member variable
	std::vector<int> getTable() {
		return table;
	};

private:
	// private member functions
	void rehash(); // helper function to rehash the table when load factor is exceeded
};

#endif

