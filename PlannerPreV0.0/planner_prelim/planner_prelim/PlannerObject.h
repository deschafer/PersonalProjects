#pragma once
#include "LLNode_Year.h"
// CPlannerObject command target


// This is the main object file, 
// it will contain all the information that will be saved from a user
class CPlannerObject// : public CObject
{
protected:

	// Will contain a dynamic list/array of year objects
	
	int m_BegYear;		// First year of this planner's year range
	int m_EndYear;		// Last year of this planner's year range
	int m_YearCount;	// The range of years for this planner
	CYear *m_CurrentYear;	// The current year of this planner object
	CLLNode_Year YearList;	// The list structure containing the years of this structure



public:
	// Default CTOR should not be used
	CPlannerObject() {};
	CPlannerObject(int begYear, int endYear, CPlannerView* view);
	virtual ~CPlannerObject() {};

	void IncrementCurrentYear(int x);
	void DecrementCurrentYear(int x);

	CYear* ReturnCurrentYear() { return m_CurrentYear; }
	CMonth* ReturnCurrentMonth() { return YearList.ReturnTopNode()->CurrentMonth(); }
	CYear* ReturnYearThatMatches(int YearDate) { return YearList.ReturnYearThatMatches(YearDate); }

};


