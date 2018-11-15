#pragma once
#include <memory>


#include "Day.h"
#include "LLNode.h"

// Month types
enum class MonthType {JAN = 31, FEB = 28, MAR = 31, APR = 30, MAY = 31, JUN = 30, JUL = 31, AUG = 31, SEP = 30, OCT = 31, NOV = 30, DEC = 31};

// CMonth command target
class CMonth //: public CObject
{
protected:
	
	int m_WidthPortion;		
	int m_HeightPortion;
	unsigned m_Rows;
	unsigned m_Columns;
	int m_TopSize;
	int m_BegDay;
	int m_MonthType;		// Holds the type of this month (0 = JAN, ..., 11 = DEC)

	CDay m_TempDay;				
	CDay* CreateDayObject(const int dayNumber);	// CTOR for a month object

	CLLNode list_Days;			// List containing day objects

public:

	CMonth() {};
	virtual ~CMonth() {};

	// Holds the number of days for this month
	int m_NumberDays;
	
	// Returns the LL class for the list of day objects
	CLLNode* GetList() { return &list_Days; }
	int ReturnMonthType() { return m_MonthType; }
	bool IsSixRowDisplay();

	// CTORs
	CMonth(int NumberDays);
	CMonth(int NumberDays, unsigned rows, unsigned columns);
	CMonth(int NumberDays, int WidthPortion, int HeightPortion, unsigned rows, unsigned columns, int topSize);
	CMonth(int NumberDays, int WidthPortion, int HeightPortion, unsigned rows, unsigned columns, int topSize, int BegDate);
	CMonth(int NumberDays, int WidthPortion, int HeightPortion, unsigned rows, unsigned columns, int topSize, int BegDate, int MonthType);

	// Returns the current dimension information
	void ReturnDimensions(int &WidthPortion, int &HeightPortion, int &Rows, int &Columns, int &topSize);
	int ReturnBegDate() { return m_BegDay; }
	// Function called to reset the cell dimensions of each day object
	void ResetCells(int widthPortion, int heightPortion);
};



