// Year.cpp : implementation file
//



#include <chrono>
#include <ctime>

#include "stdafx.h"
#include "planner_prelim.h"
#include "Year.h"
#include "planner.h"


CYear::CYear(int YearDate, CPlannerView* view) : m_CurrMonthCounter(0)
{
	// Local variables
	int Correction = 0;
	int MonthToday = 0;
	time_t _Time = time(NULL);
	tm * TimeOut = localtime(&_Time);
	MonthToday = TimeOut->tm_mon;

	m_YearDate = YearDate;

	// Determines if this object is a leap year
	(IsLeapYear()) ? m_LeapYear = 1, Correction = 1 : m_LeapYear = 0;
	
	// Initializing the months
	m_Months[0] = CMonth((int)MonthType::JAN, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 1, YearDate), 0);
	m_Months[1] = CMonth((int)MonthType::FEB + Correction, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 2, YearDate), 1);
	m_Months[2] = CMonth((int)MonthType::MAR, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 3, YearDate), 2);
	m_Months[3] = CMonth((int)MonthType::APR, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 4, YearDate), 3);
	m_Months[4] = CMonth((int)MonthType::MAY, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 5, YearDate), 4);
	m_Months[5] = CMonth((int)MonthType::JUN, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 6, YearDate), 5);
	m_Months[6] = CMonth((int)MonthType::JUL, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 7, YearDate), 6);
	m_Months[7] = CMonth((int)MonthType::AUG, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 8, YearDate), 7);
	m_Months[8] = CMonth((int)MonthType::SEP, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 9, YearDate), 8);
	m_Months[9] = CMonth((int)MonthType::OCT, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 10, YearDate), 9);
	m_Months[10] = CMonth((int)MonthType::NOV, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 11, YearDate), 10);
	m_Months[11] = CMonth((int)MonthType::DEC, view->ReturnWidthPortion(),
		view->ReturnHeightPortion(), view->ReturnRows(), view->ReturnColumns(), view->ReturnTopSize(), FindBegDate(1, 12, YearDate), 11);

	m_CurrentMonth = &(m_Months[MonthToday]);
	m_CurrMonthCounter = MonthToday;

}


// CYear member functions

//
// IsLeapYear()
// Returns a bool variable indicating whether this is a leap year
//
bool CYear::IsLeapYear()
{
	int YearDifference = 0;

	// Sets reference point at year 2000

	YearDifference = m_YearDate - 2000;

	return ((m_YearDate % 4) == 0) ? 1 : 0;
}



int CYear::FindBegDate(int day, int month, int year)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;
	return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}


bool CYear::MoveMonth(int x)
{
	// Local Variables
	int temp = 0;

	// If not within range, or at the end of the year
	if ((m_CurrMonthCounter + x) < 0 || (m_CurrMonthCounter + x) > 11)
	{
		return 0;
	}

	// Adds the additional month change and resets the current month
	m_CurrMonthCounter += x;
	m_CurrentMonth = &m_Months[m_CurrMonthCounter];

	// return true to indicate that it was successful
	return 1;
}

void CYear::SetCurrentMonth(int x)
{

	m_CurrMonthCounter = x;

}