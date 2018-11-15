#include "stdafx.h"
#include "LLNode_Year.h"

// Adds a new node to the end of the list
void CLLNode_Year::EnQueue(CYear *YearObject)
{
	// Local Vars
	Node* p_Aux;

	// Creating new node
	p_Aux = new Node;
	p_Aux->Object = YearObject;
	p_Aux->next = nullptr;

	if (p_Head == nullptr) { // If empty list

		p_Head = p_Aux;
		return;
	}
	// Otherwise, traverse and add to end of the list.
	Node *p_Traverse = p_Head;
	while (p_Traverse->next != nullptr)
		p_Traverse = p_Traverse->next;
	p_Traverse->next = p_Aux;
}


CYear* CLLNode_Year::ReturnYearThatMatches(int YearDate)
{


	Node *p_Traverse = p_Head;
	while (p_Traverse->next != nullptr)
	{
		

		if (YearDate == p_Traverse->Object->ReturnYearDate())
		{
			return p_Traverse->Object;
			break;
		}

		p_Traverse = p_Traverse->next;
	}

		
	
}

CYear* CLLNode_Year::Increment(CYear* CurrYearPtr)
{
	// Local Variables
	Node *p_Traverse = p_Head;

	while (p_Traverse->next != nullptr)
	{


		if (CurrYearPtr->ReturnYearDate() == p_Traverse->Object->ReturnYearDate())
		{
			return p_Traverse->next->Object;
			break;
		}

		p_Traverse = p_Traverse->next;
	}

	return CurrYearPtr;

}

CYear* CLLNode_Year::Decrement(CYear* CurrYearPtr)
{
	// Local Variables
	Node *p_Traverse = p_Head;
	Node *prev = nullptr;

	while (p_Traverse->next != nullptr)
	{
		prev = p_Traverse;

		if (CurrYearPtr->ReturnYearDate() == p_Traverse->next->Object->ReturnYearDate())
		{
			return prev->Object;
			break;
		}

		p_Traverse = p_Traverse->next;
	}

	return CurrYearPtr;

}