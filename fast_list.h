/*********************************************************************
* fast_list class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef FAST_LIST_H
#define FAST_LIST_H

#include "shape.h"

using namespace std;

struct Node
{
	bool ab=false;
	Node* next=nullptr;
	Node* prev=nullptr;
	Shape* shape=nullptr;
	Node(Shape* sp){
		shape=sp;
	};
};

//####################################################################
//####################################################################
//####################################################################


class lkList
{
	private:
		int counter=0;
		Node* tail=nullptr;
		Node* head=nullptr;

	public:
		~lkList();
		lkList();
		lkList(Shape*);
		void insert(Node*);
		Node* insert(Shape*);
		void remove(Node*);
		void print() const;
		int getCounter() const;
		Node* getTail() const;
};

//====================================================================

inline lkList::lkList(){}

inline Node* lkList::getTail() const{
	return tail;
}

inline int lkList::getCounter() const{
	return counter;
}


inline lkList::lkList(Shape* sp){
	counter++;	
	insert(new Node(sp));
}


inline Node* lkList::insert(Shape* sp){
	Node* tmp=new Node(sp);
	insert(tmp);
	return tmp;
}

inline void lkList::remove(Node* nd){
	if(nd->prev){
		nd->prev->next=nd->next;
	}
	else{//if(nd==tail){ the only node tha prev = nullptr is tail
		tail=tail->next;
	}
	
	if(nd->next){
		nd->next->prev=nd->prev;
	}
	else{//if(nd==head){ The only node that next=nullptr is head
		head=head->prev;
	}
	
	nd->prev=nd->next=nullptr;
	counter--;	
}

//####################################################################
//####################################################################
//####################################################################

class relLink
{
	private:
		std::vector<Node*> ShapeIndexA;
		std::vector<int> ShapeIndexB;// the index of deleted (as future option) is added to this vector
		double threshold=0;
		lkList A; // list of the shapes that are in the view of the camera
		lkList B; // list of out-of-view shapes (shapes not in the view of the camera)

	public:
		relLink();
		void setThreshold(double);
		void insert(Shape*, bool);
		void swap2(Shape*, bool);
		void swap(Shape*, bool);
		void print(bool=true);
		void getTotal() const;
		Node* getTail();
};

//====================================================================


inline void relLink::getTotal() const{
	cout<<"A :"<<A.getCounter()<<endl;
	cout<<"B :"<<B.getCounter()<<endl;
}

inline void relLink::setThreshold(double _threshold){
	if(threshold==0){
		threshold=_threshold;
	}
}

inline relLink::relLink()
	:A(), B()
{}

inline void relLink::print(bool a){
	if(a){
		A.print();
	}
	else{
		B.print();
	}
}

inline Node* relLink::getTail(){
	return A.getTail();
}


#endif