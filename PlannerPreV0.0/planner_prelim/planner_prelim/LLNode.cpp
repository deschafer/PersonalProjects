#include "stdafx.h"
#include "LLNode.h"
#include "Month.h"

//
// EnQueue()
// Adds a new CDay object to the end of the linked list structure
//
void CLLNode::EnQueue(CDay DayObject) { // adds actor name to the end of the linked list

	// Local Vars
	Node* p_Aux;

	// Creating new node
	p_Aux = new Node;
	p_Aux->Object = DayObject;
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

//
// ResetSizes()
// Edits the sizes of all the nodes in the linked list
//
void CLLNode::ResetSizes(CMonth* month)
{
	// Local Variables
	Node* p_Current;
	CRect *CurrentRect;
	int WidthPortion;
	int HeightPortion;
	int rows;
	int columns;
	int widthCt = 0;
	int HeightCt = 0;
	int BegCell = month->ReturnBegDate();
	int topPortion = 0;

	// Get the dimension information needed
	month->ReturnDimensions(WidthPortion, HeightPortion, rows, columns, topPortion);

	// Set to the head pointer for this list object
	p_Current = p_Head;

	// Loop to reset sizes of all days within this loop
	for (int i = 0, widthCt = BegCell; (p_Current != NULL) && (i < month->m_NumberDays); i++)
	{
		// Moving to the next row of cells
		if ((((widthCt % columns) == 0) && widthCt > 0))
		{
			widthCt = 0;
			HeightCt += 1;
		}

		// Getting current cell rectangle object
		CurrentRect = &(p_Current->Object.m_Cell);

		// Modifying the dimensions of this object
		CurrentRect->SetRect(CPoint(widthCt * WidthPortion, (HeightCt * HeightPortion) + topPortion),
							 CPoint((widthCt + 1) * WidthPortion, (HeightCt + 1) * HeightPortion + topPortion));

		// Getting next node in list
		p_Current = p_Current->next;
		// Incrementing width counter
		widthCt++;
	}
}
