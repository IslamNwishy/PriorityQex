#include "PQ.h"
using namespace std;

//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 7
//File: PQ.cpp

template<class Type>
PQ<Type>::PQ(h_type heap, int size, Type item) {
	heapType = heap;			//set the heaptype to the given one
	MaxSize = size;				//set the maximum size to the given one
	a = new Type[MaxSize + 1];	//create the array of a size Max+1 that will act as the queue
	itemMinOrMax = item;		//set the smallest or largest value (depending on the heaptype) that can be added to the queue
	a[0] = itemMinOrMax;		//reserve the first slot in the array to the smallest or largest value that can be added to the queue
	N = 0;						//set N to 0
}

template<class Type>
PQ<Type>::~PQ() {
	//Destroy the array
	delete []a;
}

template<class Type>
bool PQ<Type>::insert(Type item) {
	if (N+1 > MaxSize)				//if the array is full return false
		return false;

	a[++N] = item;					//increment to point at the next slot (rightmost empty leaf) and store the given item 
	UpHeap(N);						//adjust the heap upwards
	return true;
}

template<class Type>
Type PQ<Type>::remove() {
	
	Type temp = a[1];				//store the first element in temporary variable temp
	a[1] = a[N--];					//replace the first element with the last one
	DownHeap(1);					//adjust the heap downwards

	return temp;
}

template<class Type>
bool PQ<Type>::isempty() {
	return(N == 0);
}

template<class Type>
Type PQ<Type>::Peak() {
	return a[1];
}

template<class Type>
void PQ<Type>::UpHeap(int k) {
	Type temp = a[k];

	if (heapType == Min) {						//In case of a Minimum heap
		while (a[k/2] >= temp) {
			a[k] = a[k / 2];
			k /= 2;
		}
		a[k] = temp;
	}

	else {
		while (a[k/2] <= temp) {				//In case of a Maximum heap
			a[k] = a[k / 2];
			k /= 2;
		}
		a[k] = temp;
	}
}

template<class Type>
void PQ<Type>::DownHeap(int k) {
	int j = 2 * k;
	Type temp = a[k];

	if (heapType == Min) {						//In case of a Minimum heap
		while (j <= N) {
			if (j<N && a[j]>a[j + 1])
				j++;
			if (temp <= a[j])
				break;
			a[j / 2] = a[j];
			j *= 2;
		}
		a[j / 2] = temp;
	}

	else {
		while (j <= N) {						//In case of a Maximum heap
			if (j<N && a[j]<a[j + 1])
				j++;
			if (temp >= a[j])
				break;
			a[j / 2] = a[j];
			j *= 2;
		}

		a[j / 2] = temp;
	}
}