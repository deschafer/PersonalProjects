#pragma once
#include "LLNode.h"
#include "Year.h"

class CLLNode_Year :
	public CLLNode
{

protected:
	struct Node { //Simple Linked List struct

		CYear *Object;
		Node *next;
	};
	Node* p_Head;
public:
	// Default CTOR and DTOR
	CLLNode_Year() { p_Head = nullptr; };
	~CLLNode_Year() {};


	CYear* Increment(CYear* CurrYearPtr);
	CYear* Decrement(CYear* CurrYearPtr);
	void EnQueue(CYear* YearObject);	// Adds a new node to the end of the list
	CYear* ReturnTopNode() { return p_Head->Object;}
	CYear* ReturnYearThatMatches(int YearDate);
};

