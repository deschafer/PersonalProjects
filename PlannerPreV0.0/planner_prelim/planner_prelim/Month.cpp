// Month.cpp : implementation file
//

#include "stdafx.h"
#include "planner_prelim.h"
#include "Month.h"
#include "Day.h"

// CMonth

CMonth::CMonth(int NumberDays)
{
	// Local Variables
	CRect Temp;

	m_NumberDays = NumberDays;


	for (int i = 0; i < NumberDays; i++)
	{
		//Temp.TopLeft = ();
		

		list_Days.EnQueue(CDay(i));

	}

}

CMonth::CMonth(int NumberDays, unsigned Rows, unsigned Columns)
{

	m_NumberDays = NumberDays;
	m_Columns = Columns;
	m_Rows = Rows;
}

CMonth::CMonth(int NumberDays, int WidthPortion, int HeightPortion, unsigned Rows, unsigned Columns, int topSize)
{
	// Local Variables
	CRect Temp;
	unsigned TotalHeight = HeightPortion * Columns;

	// Setting appropriate variables
	m_NumberDays = NumberDays;
	m_Rows = Rows;
	m_Columns = Columns;
	m_WidthPortion = WidthPortion;
	m_HeightPortion = HeightPortion;
	m_TopSize = topSize;

	// Draws columns based on amount of colomns and current
	// dimensions of client area
	

	// This is creating the initial list of m_NumberDays day objects,
	// so the loop in within this function.
	// For modifying this list, the loop will be present in the CDay class methods.
	for (int i = 0; i < m_NumberDays; i++)
	{
		// Adding each day element with the correct inital dimensions
		list_Days.EnQueue(CDay(i + 1, CPoint(0, i*WidthPortion), CPoint(HeightPortion, i*WidthPortion)));
	}

}

CMonth::CMonth(int NumberDays, int WidthPortion, int HeightPortion, unsigned Rows, unsigned Columns, int topSize, int BegDate)
{
	// Local Variables
	CRect Temp;
	unsigned TotalHeight = HeightPortion * Columns;

	// Setting appropriate variables
	m_NumberDays = NumberDays;
	m_Rows = Rows;
	m_Columns = Columns;
	m_WidthPortion = WidthPortion;
	m_HeightPortion = HeightPortion;
	m_TopSize = topSize;
	m_BegDay = BegDate;

	// Draws columns based on amount of colomns and current
	// dimensions of client area


	// This is creating the initial list of m_NumberDays day objects,
	// so the loop in within this function.
	// For modifying this list, the loop will be present in the CDay class methods.
	for (int i = 0; i < m_NumberDays; i++)
	{
		// Adding each day element with the correct inital dimensions
		list_Days.EnQueue(CDay(i + 1, CPoint(0, i*WidthPortion), CPoint(HeightPortion, i*WidthPortion)));
	}

}

CMonth::CMonth(int NumberDays, int WidthPortion, int HeightPortion, unsigned Rows, unsigned Columns, int topSize, int BegDate, int MonthType)
{
	// Local Variables
	CRect Temp;
	unsigned TotalHeight = HeightPortion * Columns;

	// Setting appropriate variables
	m_NumberDays = NumberDays;
	m_Rows = Rows;
	m_Columns = Columns;
	m_WidthPortion = WidthPortion;
	m_HeightPortion = HeightPortion;
	m_TopSize = topSize;
	m_BegDay = BegDate;
	m_MonthType = MonthType;

	// Draws columns based on amount of colomns and current
	// dimensions of client area


	// This is creating the initial list of m_NumberDays day objects,
	// so the loop in within this function.
	// For modifying this list, the loop will be present in the CDay class methods.
	for (int i = 0; i < m_NumberDays; i++)
	{
		// Adding each day element with the correct inital dimensions
		list_Days.EnQueue(CDay(i + 1, CPoint(0, i*WidthPortion), CPoint(HeightPortion, i*WidthPortion)));
	}

}

// This function needs to reset sizes of all the day objects within this month object
void CMonth::ResetCells(int widthPortion, int heightPortion)
{
	m_HeightPortion = heightPortion;
	m_WidthPortion = widthPortion;

	// Passes this object to the linked list class
	list_Days.ResetSizes(this);


}


CDay* CMonth::CreateDayObject(const int dayNumber)
{

	return new CDay(dayNumber);
}


void CMonth::ReturnDimensions(int &WidthPortion, int &HeightPortion, int &Rows, int &Columns, int &topSize)
{
	WidthPortion = m_WidthPortion;
	HeightPortion = m_HeightPortion;
	Rows = m_Rows;
	Columns = m_Columns;
	topSize = m_TopSize;
}

bool CMonth::IsSixRowDisplay()
{
	// If a 31-day month, and first day is a sat or Fri, then 6 rows are needed
	if (m_NumberDays == 31 && (m_BegDay == 6 || m_BegDay == 5)) return 1;
	// If a 30-day month, and first day is fri, then 6 rows are needed
	else if (m_NumberDays == 30 && m_BegDay == 6) return 1;
	// Otherwise, the default number of 5 rows will be just fine
	else return 0;

}

// CMonth member functions