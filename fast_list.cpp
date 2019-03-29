/*********************************************************************
* fast_list class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/

#include "shape.h"
#include "fast_list.h"


//####################################################################
//####################################################################
//####################################################################


lkList::~lkList(){
	Node* tmp;
	while(tail!=nullptr){
		tmp=tail->next;
		delete tail;
		tail=tmp;
	}
}

//====================================================================

void lkList::insert(Node* nd){
	
	if(head){
		counter++;
		head->next=nd;
		nd->prev=head;
		head=nd;
	}
	else{
		counter++;
		tail=head=nd;
	}
}

//====================================================================

void lkList::print()const{
	Node* tmp=tail;
	while(tmp!=nullptr){
		//cout<<tmp->id<<" : ";
		if(tmp==tmp->next){
			break;
		}
		tmp=tmp->next;
	}
	cout<<endl;
}

//====================================================================

//####################################################################
//####################################################################
//####################################################################


void relLink::insert(Shape* shape, bool chg){
	Node* tmp;

	if(chg){	
		tmp=A.insert(shape);
		tmp->ab=true;
	}
	else{
		tmp=B.insert(shape);
		tmp->ab=false;
	}
	//ShapeIndex[shape]=tmp;
		//*

	int id;
	if(ShapeIndexB.size()){
		id=ShapeIndexB[ShapeIndexB.size()-1];
		shape->setID(id);
		ShapeIndexB.pop_back();
		ShapeIndexA[id]=tmp;
	}
	else{
		id=ShapeIndexA.size();
		shape->setID(id);
		ShapeIndexA.push_back(tmp);
	}
	/**/
}

//====================================================================

void relLink::swap2(Shape* shape, bool chg){
	/*
	if(ShapeIndex[shape]->ab!=(bool)chg){
		if(ShapeIndex[shape]->ab==false){
			ShapeIndex[shape]->ab=true;
			B.remove(ShapeIndex[shape]);
			A.insert(ShapeIndex[shape]);
		}
		else if(ShapeIndex[shape]->ab==true){
			ShapeIndex[shape]->ab=false;
			A.remove(ShapeIndex[shape]);
			B.insert(ShapeIndex[shape]);
		}
	}
	*/
}

//====================================================================

void relLink::swap(Shape* shape, bool chg){
	
	if(ShapeIndexA[shape->getID()]->ab!=(bool)chg){
		Node* tmp=ShapeIndexA[shape->getID()];
		if(tmp->ab==false){
			tmp->ab=true;
			B.remove(tmp);
			A.insert(tmp);
		}
		else if(tmp->ab==true){
			tmp->ab=false;
			A.remove(tmp);
			B.insert(tmp);
		}
	}
}

//####################################################################
//####################################################################
//####################################################################
