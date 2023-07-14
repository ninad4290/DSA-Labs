

#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_

#include <iostream>


template <typename E>
class ArrayStack {
    private:
        int capacity;
        E* items;
        int topIndex = -1;

    public:
            ArrayStack() : ArrayStack(100) {}
        ArrayStack(int n){
            items = new E[n];
            capacity = n;
        }
        ~ArrayStack() {
            delete [] items;
        }


        bool isEmpty() {
            return (topIndex<0);
        }
        void push(const E& e) {
            if (topIndex == capacity-1) {
                E* newArray = new E[2*capacity];
                for (int i=0; i<capacity; i++) {
                    newArray[i]=items[i];
                }
                delete[] items;
                items=newArray;
                capacity *= 2;
            }
            topIndex++;
            items[topIndex]=e;
        }
        E pop() {
            if (isEmpty()==true) {

                throw std::underflow_error("Stack is empty");
            }
            else {
                E tempE = items[topIndex];
                topIndex--;
                return tempE;
            }
        }
        E top() {
            if (isEmpty()==true) {
                throw std::underflow_error("Stack is empty");

            }
            else {
                return items[topIndex];
            }
            return items[topIndex];
        }

        void printStack() {
            for (int i=0; i<=topIndex; i++) {
                std::cout<<items[i]<<std::endl;
            }
        }

};



#endif