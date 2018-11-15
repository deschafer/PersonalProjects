#include "stdafx.h"
#include "planner.h"


void CPlannerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_SizeChanged = 1;
}


void CPlannerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CString string;
	
	CString str;
	str.Format(L"my string %d", m_CurrentMonth->m_NumberDays);
	AfxMessageBox(str);

	CView::OnLButtonDown(nFlags, point);
}


void CPlannerView::OnNextMonth()
{
	// Local Vars
	bool error = 0;
	bool NoChange = 0;
	int PrevMonthDate = -1;

	m_SizeChanged = 1;
	error = m_Year->MoveMonth(1);
	if (!error)
	{
		PrevMonthDate = m_Year->ReturnYearDate();

		m_Planner.IncrementCurrentYear(1);
		m_Year = m_Planner.ReturnCurrentYear();
		if (PrevMonthDate != m_Year->ReturnYearDate()) m_Year->SetCurrentMonth(0);
		else
		{
			NoChange = 1;
		}
	}
	if (!NoChange) InvalidateRect(nullptr);
}


void CPlannerView::OnPrevMonth()
{
	// Local Vars
	bool error = 0;
	bool NoChange = 0;
	int PrevYearDate = -1;

	m_SizeChanged = 1;
	error = m_Year->MoveMonth(-1);
	if (!error)
	{
		PrevYearDate = m_Year->ReturnYearDate();

		m_Planner.DecrementCurrentYear(1);
		m_Year = m_Planner.ReturnCurrentYear();
		if(PrevYearDate != m_Year->ReturnYearDate()) m_Year->SetCurrentMonth(11);
		else
		{
			NoChange = 1;
		}
	}
	if(!NoChange) InvalidateRect(nullptr);
}


void CPlannerView::OnYearPlus()
{
	// Local Vars
	int PrevYearDate = -1;

	m_SizeChanged = 1;

	PrevYearDate = m_Year->ReturnYearDate();

	m_Planner.IncrementCurrentYear(1);
	m_Year = m_Planner.ReturnCurrentYear();

	if (PrevYearDate != m_Year->ReturnYearDate()) InvalidateRect(nullptr);

}


void CPlannerView::OnYearMinus()
{
	// Local Vars
	int PrevYearDate = -1;

	m_SizeChanged = 1;

	PrevYearDate = m_Year->ReturnYearDate();

	m_Planner.DecrementCurrentYear(1);
	m_Year = m_Planner.ReturnCurrentYear();

	if (PrevYearDate != m_Year->ReturnYearDate()) InvalidateRect(nullptr);

}
