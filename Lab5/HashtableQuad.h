#ifndef HASHTABLEQUAD_H_ // If the symbol HASHTABLEQUAD_H_ is not defined, execute the following code.
#define HASHTABLEQUAD_H_ // Define the symbol HASHTABLEQUAD_H_

#include <vector> // Include the vector library.

class HashTableQuad // Define the HashTableQuad class.
{
private:
	// Declare private member variables.
	std::vector<int> table; // A vector to hold the hash table.
	int size; // The size of the hash table.
	int numKeys; // The number of keys in the hash table.
	double maxLoad; // The maximum load factor of the hash table.
	int probes; // The number of probes for the last operation.

	// Declare private member functions.
	bool isPrime(int n); // A function to determine whether a number is prime.
	int Probe(int n); // A function to probe the hash table.

public:
	// Declare public member functions.
	HashTableQuad(int maxNum, double load); // A constructor for the HashTableQuad class.
	void insert(int n); // A function to insert a key into the hash table.
	bool isIn(int n); // A function to determine whether a key is in the hash table.
	void printKeys(); // A function to print the keys in the hash table.
	void printKeysAndIndexes(); // A function to print the keys and their indexes in the hash table.
	int getNumKeys(); // A function to get the number of keys in the hash table.
	int getTableSize(); // A function to get the size of the hash table.
	double getMaxLoadFactor(); // A function to get the maximum load factor of the hash table.
	static std::vector<double> simProbeSuccess(); // A static function to simulate probe success.

	// Declare a public member function to get the hash table.
	std::vector<int> getTable() {
		return table;
	};

private:
	// Declare private member functions.
	void rehash(); // A function to rehash the hash table.
};

#endif // End of the conditional compilation directive.
