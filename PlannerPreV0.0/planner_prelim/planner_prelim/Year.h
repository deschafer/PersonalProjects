#pragma once
#include "Month.h"
//#include "planner.h"

class CPlannerView;
// CYear command target

class CYear //: public CObject
{
protected:

	int m_YearDate;			// The date of this year, like 2018
	bool m_LeapYear;		// Indicator variable if this is a leap year
	int m_CurrMonthCounter;

	bool IsLeapYear();		// Returns true if this year is a leap year
	int FindBegDate(int day, int month, int year);
	CMonth m_Months[12];	// Array of the twelve months within a year
	CMonth *m_CurrentMonth;	// Ptr to current month

public:
	
	// Returns the current month from today's date
	CMonth* CurrentMonth() { return &m_Months[m_CurrMonthCounter]; };
	int ReturnYearDate() { return m_YearDate; }
	CMonth MonthX(int x) { return m_Months[x]; }

	bool MoveMonth(int x);
	void SetCurrentMonth(int x);

	// CTOR for a CYear object
	CYear(int YearDate, CPlannerView* view);

	CYear() {};
	virtual ~CYear() {};
};


