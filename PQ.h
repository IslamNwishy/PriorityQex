#ifndef PQ_H
#define PQ_H
#include<iostream>
using namespace std;

//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 7
//File: PQ.h

//enum that describes the heap type (either minimum or maximum)
enum h_type {Min,Max};

template<class Type>
class PQ {
public:
	PQ(h_type heap = Min, int size = 11, Type item = NULL);	//Constructor
	~PQ();													//Destructor

	//Public Member Functions
	bool insert(Type);					//Insert an Element into the heap
	Type remove();						//Remove and return an element
	bool isempty();						//Returns true if the Queue is empty (not counting a[0])
	Type Peak();						//Returns the top element in the queue without removing it


private:
	h_type heapType;
	Type* a;							//Pointer to the storage array
	int MaxSize;						//Maximum size of the heap
	int N;								//index to the last element in the array
	Type itemMinOrMax;					//Min item or max item to be stored in a[0] based on the heap type of the queue (Max or Min)

	//Heap adjusment functions
	void UpHeap(int);
	void DownHeap(int);

};
#endif // !PQ_H
