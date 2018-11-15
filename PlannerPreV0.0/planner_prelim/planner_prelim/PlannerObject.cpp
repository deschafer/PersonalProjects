// PlannerObject.cpp : implementation file
//

#include "stdafx.h"
#include "planner_prelim.h"
#include "PlannerObject.h"


// CPlannerObject

CPlannerObject::CPlannerObject(int begYear, int endYear, CPlannerView* view) : m_CurrentYear(nullptr)
{
	// Local vars
	int YearDate = 0;

	// Setting class variables
	m_BegYear = begYear;
	m_EndYear = endYear;
	m_YearCount = endYear - begYear;

	// Getting the date of this year
	time_t Time = time(NULL);
	tm* p_Time = localtime(&Time);

	YearDate = p_Time->tm_year + 1900;
	
	// Now creating the linked list of objects
	for (int i = 0; i < m_YearCount; i++)
	{
		// Adding each day element with the correct inital dimensions
		// View has to be passed in for the cells for each day object
		// This has to dynamically create a CYear object each time
		CYear * object = new CYear(begYear + i, view);

		// Adding this new object to the end of the list
		YearList.EnQueue(object);

		// If the year added is the current year of todays date, then
		// set it as the current year
		if (begYear + i == YearDate) m_CurrentYear = object;
		
	}

	if (m_CurrentYear == nullptr) m_CurrentYear = YearList.ReturnTopNode();
}


// CPlannerObject member functions

void CPlannerObject::IncrementCurrentYear(int x)
{
	for (int i = 0; i < x; i++)
	{
		m_CurrentYear = YearList.Increment(m_CurrentYear);
	}

}




void CPlannerObject::DecrementCurrentYear(int x)
{

	for (int i = 0; i < x; i++)
	{
		m_CurrentYear = YearList.Decrement(m_CurrentYear);
	}

}