////////////////////////////////////
//Matt Drajeske										
//CS 1575													
//Assignment 4										
////////////////////////////////////

#include <iostream>
#include "popplersqueue.h"
#include "randomengine.h"

using namespace std;

struct Customer{
	string m_name;			//name of customer
	int m_numPopplers;	//number of popplers that they want
	int m_eaten;				//number of popplers that they ate in one iteration
	int m_total;				//total number of popplers that they ate
};										//struct that holds the data for each customer

void orderPopplers(Customer&);
void eatPopplers(Customer&);
void mostPopplers(PopplersQueue<Customer>*&);
void leastPopplers(PopplersQueue<Customer>*&);


int main(){	
	int numCustomers;	//variable representing the number of customers
	string name;			//variable representing the name of a customers
	int numPopplers;	//variable representing the number of popplers a customer wants

	//queue that represents the line of customers
	PopplersQueue<Customer>* pq = new PopplersQueue<Customer>();

	//to determine who ate the most popplers
	PopplersQueue<Customer>* stats = new PopplersQueue<Customer>();
	
	//input for the number of customers that are going to be in line
	cin >> numCustomers;

	//input for the names and number of popplers each customer wants
	//enqueues customers as they are input
	for(int i = 0; i < numCustomers; i++){
		cin >> name >> numPopplers;
		Customer c = {name, numPopplers, 0, 0};
		if(c.m_numPopplers != 0){
			pq->enqueue(c);
		} //if the customer doesn't want any popplers, why would they get in line?
	}

	int total = 0;		//total number of popplers eaten

	//node representing the first position in line
	QNode<Customer>* first = pq->m_first;

	//have all the customers in line order
	while(first != NULL){
		//have customers order and eat popplers
		orderPopplers(first->m_data);

		cout << first->m_data.m_name << " ate " << first->m_data.m_eaten <<
				 " popplers.";

		eatPopplers(first->m_data);

		//temporary variable
		Customer tmp = {first->m_data.m_name, first->m_data.m_numPopplers, first->m_data.m_eaten, 
										first->m_data.m_total};
	
		total += tmp.m_eaten;

		//case of customer wanting 1 more poppler
		if(tmp.m_numPopplers == 1){
			cout << " " << tmp.m_name << " wants one more poppler!" << endl;
			pq->enqueue(tmp);
		} 
		//if the customer wants more popplers, they get back in line
		else if(tmp.m_numPopplers != 0){
			cout << " " << tmp.m_name << " wants " << tmp.m_numPopplers << 
						" more popplers!" << endl;
			
			pq->enqueue(tmp);
		}
		//if customer is satisfied
		else{
			Customer stat = {tmp.m_name, tmp.m_numPopplers, tmp.m_eaten, tmp.m_total};
			stats->enqueue(stat);
			cout << " " << tmp.m_name << " was satisfied after eating " << tmp.m_total 
					<< " popplers." << endl;
		}	

	

		//remove from front of the line because customer has ordered
		pq->dequeue();

		//change first
		first = pq->m_first;
	}
	
	cout << "\nA total of " << total << " popplers were eaten." << endl;
	mostPopplers(stats);
	leastPopplers(stats);
}

////////////////////////////////////////////////////////
//@fn orderPopplers																		
//@brief determines how many popplers a customer wants
//			in one iteration																				
//@param c customer that is going to eat popplers			
////////////////////////////////////////////////////////
void orderPopplers(Customer& c){
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
	c.m_eaten = numBoxes*5;
}

////////////////////////////////////////////////////////
//@fn eatPopplers																			
//@brief have customers eat their popplers with 1/6		
//				chance that they will get back in line			
//@param c customer at the front of the line					
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
	c.m_total += c.m_eaten;
}

/////////////////////////////////////////////////////////
//@fn mostPopplers
//@brief determines who ate the most popplers in a queue
//@param q queue of customers
/////////////////////////////////////////////////////////
void mostPopplers(PopplersQueue<Customer>*& q){
	Customer mostEaten;
	int max = 0;

	QNode<Customer>* cur = q->m_first;
	while(cur->m_next != NULL){
		if(max < cur->m_data.m_total){
			mostEaten = cur->m_data;			
		}				
		cur = cur->m_next;		
		max = mostEaten.m_total;
	}
	if(max < cur->m_data.m_total){
		mostEaten = cur->m_data;
	}
	max = mostEaten.m_total;

	cout << mostEaten.m_name << " ate the most popplers: " << max << endl;
}

/////////////////////////////////////////////////////////
//@fn leastPopplers
//@brief determines who ate the least popplers in a queue
//@param q queue of customers
/////////////////////////////////////////////////////////
void leastPopplers(PopplersQueue<Customer>*& q){
	Customer leastEaten;
	int min = 2147483647;

	QNode<Customer>* cur = q->m_first;
	while(cur->m_next != NULL){
		if(min > cur->m_data.m_total){
			leastEaten = cur->m_data;			
		}				
		cur = cur->m_next;		
		min = leastEaten.m_total;
	}
	if(min > cur->m_data.m_total){
		leastEaten = cur->m_data;
	}
	min = leastEaten.m_total;

	cout << leastEaten.m_name << " ate the fewest popplers: " << min << endl;
}