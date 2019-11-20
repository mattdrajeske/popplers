////////////////////////////////////
//Matt Drajeske										//
//CS 1575													//
//Assignment 4										//
////////////////////////////////////

#include "abstractqueue.h"

using namespace std;

//Class used to store info about the node
template<class T>
class QNode{
public:
	//member variables	
	//number of popplers the QNode originally wants
	QNode<T>* m_next;				//the next QNode in line
	T m_data;
	
	// Purpose: Default constructor
  // Postconditions: next pointer set to NULL
  // ---INLINE---
  QNode<T>() : m_next(NULL) {}
	
	// Purpose: Auxiliary constructor, construct from parameters
  // Postconditions: data and next pointer set to parameters
  // ---INLINE---
  QNode<T>(const T& x, QNode<T>* c) 
             : m_data(x), m_next(c) {}

};

//Class used to define a whole line of QNodes
template<class T>
class PopplersQueue : public virtual AbstractQueue<T>
{
public:
	//member variables
	QNode<T>* m_first;	//pointer to the first QNode in line
	QNode<T>* m_last;		//pointer to the last QNode in line
	QNode<T> m_dummy; 	//for error handling
	int m_size;					//length of the line*/

	//default constructor
	PopplersQueue(){
		m_first = NULL;
		m_last = NULL;
		int m_size = 0;
	}

	//returns whether the line of QNodes is empty
	virtual bool isEmpty() const{
		return m_first == NULL;
	}

	//returns the front of the queue, or the first QNode in line
	//template<typename T>
	virtual const T& front() const throw (Oops){
		Oops err("Queue is empty");
		try{
			if(isEmpty()){
				throw err;
			}
			return m_first->m_data;
		}
		catch(Oops e){
			cout << err.getMsg() << "\n";		
			return m_dummy.m_data;
		}
	}

	//returns the QNode at the back of the line
	//template<typename T>
	virtual const T& back() const throw (Oops){
		Oops err("Queue is empty");
		try{
			if(isEmpty()){
				throw err;
			}			
			QNode<T>* current = m_first;
			while(current->m_next != NULL){
				current = current->m_next;
			}
			//m_last = current;
			return current->m_data;
		}
		catch(Oops e){
			cout << err.getMsg() << "\n";		
			return m_dummy.m_data;
		}
	}

	//adds a QNode to the line
	//template<typename T>
	virtual void enqueue(const T& x){
		if(isEmpty()){
			QNode<T>* newnode = new QNode<T>(x, NULL);
			m_first = newnode;
		}
		else{
			QNode<T>* current = m_first;
			while(current->m_next != NULL){
				current = current->m_next;
			}
			current->m_next = new QNode<T>(x, NULL);
		}
		m_size++;
	}		
	

	//removes a QNode from the line
	virtual void dequeue(){
		if(isEmpty()){
			return;
		}
		QNode<T>* temp = m_first->m_next;
		delete m_first;
		m_first = temp;
		m_size--;
	}

	//removes all QNodes from the queue
	virtual void clear(){
		if(!isEmpty()){
			QNode<T>* current = m_first;
			while(current->m_next != NULL){
				QNode<T>* next = current->m_next;
				delete current;
				current = next;
			}
			m_first = NULL;
			m_last = NULL;
			m_size = 0;
		}
	}

	//destructor
	virtual ~PopplersQueue(){
		if(!isEmpty()){
			QNode<T>* current = m_first;
			while(current->m_next != NULL){
				QNode<T>* next = current->m_next;
				delete current;
				current = next;
			}
		}
	}
};
