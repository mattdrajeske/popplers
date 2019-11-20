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

void orderPopplers(Customer& c);
void eatPopplers(Customer& c);

int main() {	
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
	total += first->m_data.m_numPopplers;

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
	
		//increment total number of eaten popplers
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
			cout << " " << tmp.m_name << " was satisfied and got out of line." << endl;
		}	

	

		//remove from front of the line because customer has ordered
		pq->dequeue();

		//change first
		first = pq->m_first;
	}
	
	cout << "A total of " << total << " popplers were eaten." << endl;

	//Section for most eaten popplers------------------------------------
	Customer mostEaten;
	int max = 0;

	QNode<Customer>* cur1 = stats->m_first;
	while(cur1->m_next != NULL){
		if(max < cur1->m_data.m_total){
			mostEaten = cur1->m_data;			
		}				
		cur1 = cur1->m_next;		
		max = mostEaten.m_total;
	}
	if(max < cur1->m_data.m_total){
		mostEaten = cur1->m_data;
	}
	max = mostEaten.m_total;

	cout << "Most popplers eaten: " << max << " by " << mostEaten.m_name << endl;

	//Section for least eaten popplers-----------------------------------
	Customer leastEaten;
	int min = 2147483647;

	QNode<Customer>* cur2 = stats->m_first;
	while(cur2->m_next != NULL){
		if(min > cur2->m_data.m_total){
			leastEaten = cur2->m_data;			
		}				
		cur2 = cur2->m_next;		
		min = leastEaten.m_total;
	}
	if(min > cur2->m_data.m_total){
		leastEaten = cur2->m_data;
	}
	min = leastEaten.m_total;

	cout << "Least popplers eaten: " << min << " by " << leastEaten.m_name << endl;

	/*cout << "A total of " << total << " popplers were eaten." << endl;
	cout << "Max: " << most.m_eaten << endl;
	cout << "Min: " << least.m_eaten << endl;*/

	/*//temporary test--------------------------------
	QNode<Customer>* cur = stats->m_first;
	while(cur->m_next != NULL){
		cout << cur->m_data.m_name << ": " << cur->m_data.m_total << endl;
		cur = cur->m_next;
	}
	cout << cur->m_data.m_name << ": " << cur->m_data.m_total << endl;
	//----------------------------------------------
	*/
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
//@return integer equal to the highest number of popplers
//				eaten in a customer queue
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//@fn leastPopplers
//@brief determines who ate the least popplers in a queue
//@param q queue of customers
//@return integer equal to the lowest number of popplers
//				eaten in a customer queue
/////////////////////////////////////////////////////////
