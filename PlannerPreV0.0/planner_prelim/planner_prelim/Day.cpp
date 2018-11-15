// Day.cpp : implementation file
//

#include "stdafx.h"
#include "planner_prelim.h"
#include "Day.h"


// CDay

CDay::CDay(const int DayNumber, CPoint TopLeft, CPoint BottomRight) : m_Cell(TopLeft, BottomRight)
{
	this->m_DayNumber = DayNumber;
}

CDay::CDay(const int DayNumber)
{

	this->m_DayNumber = DayNumber;


}

CDay::~CDay()
{
}



// CDay member functions

void CDay::Initilize(int DayNumber)
{

	this->m_DayNumber = DayNumber;

}
