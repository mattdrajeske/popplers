////////////////////////////////////
//Matt Drajeske										//
//CS 1575													//
//Assignment 4										//
////////////////////////////////////

#include <iostream>
#include "popplersqueue.h"
#include "randomengine.h"

using namespace std;

struct Customer{
	string m_name;
	int m_numPopplers;
	//bool m_isHungry;	//condition that will determine if the customer gets back in line
};									//struct that holds the data for each customer

void orderPopplers(Customer& c);
void eatPopplers(Customer& c);

int main() {	
	int numCustomers;	//variable representing the number of customers
	string name;			//variable representing the name of a customers
	int numPopplers;	//variable representing the number of popplers a customer wants

	//queue that represents the line of customers
	PopplersQueue<Customer>* pq = new PopplersQueue<Customer>();
	
	//input for the number of customers that are going to be in line
	cin >> numCustomers;

	//input for the names and number of popplers each customer wants
	//enqueues customers as they are input
	for(int i = 0; i < numCustomers; i++){
		cin >> name >> numPopplers;
		Customer c = {name, numPopplers};
		if(c.m_numPopplers != 0){
			pq->enqueue(c);
		} //if the customer doesn't want any popplers, why would they get in line?
	}

	//node representing the first position in line
	QNode<Customer>* first = pq->m_first;

	//have all the customers in line order
	while(first != NULL){
		//have customers order and eat popplers
		orderPopplers(first->m_data);

		cout << first->m_data.m_name << " ate " << first->m_data.m_numPopplers <<
				 " popplers.";

		eatPopplers(first->m_data);

		//temporary variable
		Customer tmp = {first->m_data.m_name, first->m_data.m_numPopplers};

		//case of customer wanting 1 more poppler
		if(tmp.m_numPopplers == 1){
			cout << " " << tmp.m_name << " wants one more poppler!" << endl;
			pq->enqueue(tmp);
		} //if the customer wants more popplers, they get back in line
		else if(tmp.m_numPopplers != 0){
			cout << " " << tmp.m_name << " wants " << tmp.m_numPopplers << 
						" more popplers!" << endl;
			pq->enqueue(tmp);
		}else{
			cout << " " << tmp.m_name << " was satisfied and got out of line." << endl;
		}	

		//remove from front of the line because customer has ordered
		pq->dequeue();

		//change first
		first = pq->m_first;
	}
	
}

////////////////////////////////////////////////////////
//@fn orderPopplers																		//
//@brief determines how many popplers a customer wants//
//			in one iteration															//									
//@param c customer that is going to eat popplers			//
////////////////////////////////////////////////////////
void orderPopplers(Customer& c){
	int total = 0;

	//case of customer that does not want any popplers
	if(c.m_numPopplers == 0){
		c.m_numPopplers = 0;
	}

	//variable to hold the number of boxes the customer wants
	int numBoxes;

	//if the customer wants a multiple of 5 popplers
	if(c.m_numPopplers % 5 == 0){
		numBoxes = c.m_numPopplers/5;
	}
	else{
		numBoxes = (c.m_numPopplers/5) + 1;
	}

	//the number of popplers that the customer ate
	c.m_numPopplers = numBoxes*5;
}

////////////////////////////////////////////////////////
//@fn eatPopplers																			//
//@brief have customers eat their popplers with 1/6		//
//				chance that they will get back in line			//
//@param c customer at the front of the line					//
////////////////////////////////////////////////////////
void eatPopplers(Customer& c){
	randomEngine rand;	//random engine 
	int count = 0;			//counter for the number of popplers a customer will want in the next iteration

	//loop through each poppler eaten to see if the customer will get back in line
	for(int i = 0; i < c.m_numPopplers; i++){
		int diceroll = rand.rollD(6);
		if(diceroll == 6){
			//c.m_isHungry = true;
			count++;
		}
	}
	c.m_numPopplers = count;
}
	