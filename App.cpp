#include<iostream>
#include<fstream>
#include<string>
#include"PQ.h"
#include"PQ.cpp"
using namespace std;

//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 7
//File: App.cpp

//Data class that contains the data of each entry
class Data {
public:
	string Date;				//Date of Exchange holder
	double ExchangeRate;		//Exchange rate holder
	double ExchangeRateVsAve;	//Exchange rate - Average rate
	

	//Operators Overloading
	//Comparing variables of type data based on their change from the average
	bool operator>(const Data& b) {
		return(ExchangeRateVsAve > b.ExchangeRateVsAve);
	}

	bool operator<(const Data& b) {
		return(ExchangeRateVsAve < b.ExchangeRateVsAve);
	}

	bool operator>= (const Data& b) {
		return(ExchangeRateVsAve >= b.ExchangeRateVsAve);
	}
	
	bool operator<= (const Data& b) {
		return(ExchangeRateVsAve <= b.ExchangeRateVsAve);
	}

	bool operator==(const Data& b) {
		return(ExchangeRateVsAve == b.ExchangeRateVsAve);
	}


};

//Global input file stream that opens USD-EGP text file
ifstream input("USD-EGP.txt");

//Functions prototype
void GetInput(double A[], string Dates[]);
double GetAverage(double A[], int size);
void PopulateQ(PQ<Data>& Q, double A[], string Dates[], int size, double average);
void MaxSubArray(Data data[], int size, Data& start, Data& end);
void PopulateArray(Data data[], double A[], string Dates[], int size, double average);
void start(PQ<Data>& Qmin, PQ<Data>& Qmax, double& Average, double A[], string Dates[], int size);


void main() {

	int size = 102;									//Number of entries in the file
	Data ItemTemp;									//Temporary data variable to insert as item 0 in the priority Q
	ItemTemp.Date = "";
	ItemTemp.ExchangeRateVsAve = -INFINITY;
	PQ<Data> Qmin(Min, size, ItemTemp);				//Minimum priority Q

	ItemTemp.Date = "";
	ItemTemp.ExchangeRateVsAve = INFINITY;
	PQ<Data> Qmax(Max, size, ItemTemp);				//Maximum priority Q


	double* A = new double[size];					//Array "A" that will hold the values for exchange rates 
	string* Dates = new string[size];				//Array "Dates" that will hold the dates of exchange

	GetInput(A, Dates);								//Takes the data from the given file
	double M = GetAverage(A, size);					//Gets the Average and store it into M

	PopulateQ(Qmin, A, Dates, size, M);				//Populates the Minimum and maximum heap
	PopulateQ(Qmax, A, Dates, size, M);


	start(Qmin, Qmax, M, A, Dates, size);			//Starts the program


}

void start(PQ<Data>& Qmin, PQ<Data>& Qmax, double& Average, double A[], string Dates[], int size) {
	int command = 0;						//Holds the choice of the user for a process
	string dummy, FileName;
	Data ItemTemp;							//Used as a temporary holder for any removed element from a prority queue
	Data data[102], start, end;				//Variables for the 4th option 

	cout << "Welcome To the Rate Exchange" << endl;

	while (command != 6) { //Exit case

		cout << endl << endl << "You Can:" << endl << endl;
		cout << "\t1- List all days and exchange rates ascendingly (based on exchange rates).";
		cout << "\n\t2- List all days and exchange rates descendingly (based on exchange rates).\n\t";
		cout << "3- Output the highest and lowest exchange rate days.\n\t";
		cout << "4- Output the start and end days of the contiguous period over which the sum of price changes is maximum.\n\t";
		cout << "5- Output the Average.\n\t6- Exit the program\n\n";
		cout << "Please Enter your Choice [1,2,3,4,5,6]" << endl;
		cin >> command;
		getline(cin, dummy);		//Dummy to get rid of the (cin) leftovers
		if (cin.fail()) {			//Check if the input does not suite the type int
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			command = 0;
		}


		switch (command) {
		case 1:
			cout << "Date\t\tExchange Rate\t\tExchange Rate vs Average" << endl;

			//Loop through the whole queue removing elements and displaying them
			while (!Qmin.isempty()) {
				ItemTemp = Qmin.remove();
				cout << ItemTemp.Date << "\t\t" << ItemTemp.ExchangeRate << "\t\t" << ItemTemp.ExchangeRateVsAve << endl;
			}

			//Repopulate the Queue
			PopulateQ(Qmin, A, Dates, size, Average);
			break;

		case 2:
			cout << "Date\t\tExchange Rate\t\tExchange Rate vs Average" << endl;

			//Loop through the whole queue removing elements and displaying them
			while (!Qmax.isempty()) {
				ItemTemp = Qmax.remove();
				cout << ItemTemp.Date << "\t\t" << ItemTemp.ExchangeRate << "\t\t" << ItemTemp.ExchangeRateVsAve << endl;
			}

			//Repopulate the Queue
			PopulateQ(Qmax, A, Dates, size, Average);
			break;

		case 3:
			//Peak at the top max item and display it
			ItemTemp = Qmax.Peak();
			cout << "Highest Exchange Rate Day is (" << ItemTemp.Date << ") at a rate of (" << ItemTemp.ExchangeRate << ") that is (" << ItemTemp.ExchangeRateVsAve << ") from the average rate" << endl;
			
			//Peak at the top min item and display it
			ItemTemp = Qmin.Peak();
			cout << "Lowest Exchange Rate Day is (" << ItemTemp.Date << ") at a rate of (" << ItemTemp.ExchangeRate << ") that is (" << ItemTemp.ExchangeRateVsAve << ") from the average rate" << endl;
			break;

		case 4:
			PopulateArray(data, A, Dates, size, Average);		//Populate the array data
			MaxSubArray(data, size, start, end);				//Find the start and end points needed

			cout << "Start Date: " << start.Date << endl;		//Display the dates of these points
			cout << "End Date: " << end.Date << endl;
			break;

		case 5:
			cout << "Average Rate is: " << Average << endl;		//Display the Average
			break;

		default:
			cout << "Invalid Input! Please Try Again" << endl;	//Invalid input
		}

	}
}


//Gets the data from a given file and stores them in a string and double type array respectively
void GetInput(double A[], string Dates[]) {

	//If you were unable to open the file throw an error
	if (input.fail()) {
		cout << "Could not open the file! Please make sure of the destination and try again" << endl;
		input.close();
		return;
	}

	string word;							//Temporary variable to hold the inputed strings from the file
	int i = 0;
	while (!input.eof()) {
		getline(input, word, '\t');			//Takes the string in the first column of a row (i) 
		Dates[i] = word;					//Stores it as an element number (i) in the Dates array
		getline(input, word, '\n');			//Takes the string in the second column of a row (i)
		A[i] = atof(word.c_str());			//stores it as an element number (i) in the A array after converting it to a float
		i++;
	}

	input.close();
}

//Takes in a double type array and its size and returns the average and returns the average of its elements 
double GetAverage(double A[], int size) {
	double sum = 0;

	for (int i = 0; i < size; i++)
		sum += A[i];

	return (sum / double(size));
	
}

//Populates a given priority Queue with data
void PopulateQ(PQ<Data>& Q, double A[], string Dates[], int size, double average) {
	Data entry;										//Temporary holder for the data before pushing it to the queue
	for (int i = 0; i < size; i++) {
		entry.Date = Dates[i];						//Store the date
		entry.ExchangeRate = A[i];					//Store the Exchange rate
		entry.ExchangeRateVsAve = A[i] - average;	//Store the change from the Average
		
		Q.insert(entry);							//Insert it to the Queue
	}
}

//Populates a given Data type array with data
void PopulateArray(Data data[], double A[], string Dates[], int size, double average) {
	Data entry;										//Temporary holder for the data before pushing it to the queue
	for (int i = 0; i < size; i++) {
		entry.Date = Dates[i];						//Store the date
		entry.ExchangeRate = A[i];					//Store the Exchange rate
		entry.ExchangeRateVsAve = A[i] - average;	//Store the change from the Average

		data[i] = entry;							//Insert it to the array
	}
}

//Finds the start and end days of the contiguous period over which the sum of price changes is maximum
void MaxSubArray(Data data[], int size, Data& start, Data& end) {
	double Max= -INFINITY, MaxEnding = 0;			//Max holds the maximum sum, MaxEnding is the current subarray of numbers
	int s = 0;										//s holds the starting point of a new subarray

	for (int i = 0; i < size; i++) {
		MaxEnding += data[i].ExchangeRateVsAve;		//add the next number in the array to the current subarray run

		if (Max < MaxEnding) {						
			Max = MaxEnding;						//if the current subarray run is higher than the highest recorded one
			start = data[s];						//then set the start to the start of the subarray
			end = data[i];							//and the end to the current element in the loop
		}

		if (MaxEnding < 0) {
			MaxEnding = 0;							//if the current subarray run falls under 0 then reset the run
			s = i + 1;								//and set the start to the next element in the loop
		}
	}

}