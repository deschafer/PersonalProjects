
// planner.h : interface of the CPlannerView class
//

#pragma once
#include "plannerDoc.h"
#include "Month.h"
#include "Year.h"
#include "PlannerObject.h"



class CPlannerView : public CView
{
protected: // create from serialization only
	CPlannerView();
	DECLARE_DYNCREATE(CPlannerView)

	// Attributes
public:
	CPlannerDoc* GetDocument() const;

	// Operations
public:
	void InitilizeWndVariables();
	void DrawLayout(CDC* pDC);
protected:
	void MoveMonth(int query);
	void FillBackground(CDC* pDC);
	void DrawMonthSection(CDC* pDC);
	void DrawTopBarSection(CDC* pDC);
	void DrawGrid(CDC* pDC);
	void DrawCells(CDC* pDC);

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CPlannerView();
	int ReturnRows() { return m_Rows; }						// Returns the number of rows
	int ReturnColumns() { return m_Columns; }				// Returns number of columns
	int ReturnWidthPortion() { return m_WidthPortion; }		// Returns the width of each cell
	int ReturnHeightPortion() { return m_HeightPortion; }	// Returns the height of each cell
	int ReturnTopSize() { return m_TopBarSize; }			// Returns the size of the top portion of the client area
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_Width;			// To store the total width of this client area
	int m_Height;			// To store the total height of this client area
	int m_HeightPortion;	// To store the section size for each row
	int m_WidthPortion;		// To Store the section size for each column
	int m_TopBarSize;		// The size of the top bar in this view
	unsigned m_Rows;		// Stores the count of the number of rows
	unsigned m_Columns;		// Stores the count of the number of columns
	bool m_SizeChanged;		// Indicator variable for whether size has been changed of window
	bool m_DaysComplete;	// Indicates whether the m_DayStrings array has been initialized
	bool m_MonthsComplete;  // Indicated whether the m_MonthStrings array has been initialized
	CMonth *m_CurrentMonth;	// The current month object
	CString m_DayStrings[7];	// Array that holds the CString types for each of the days of the week
	CString m_MonthStrings[12];	// Array that holds the CString types for each of the twelve months
	CYear *m_Year;			// The current year object
	CPlannerObject m_Planner;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNextMonth();
	afx_msg void OnPrevMonth();
	afx_msg void OnYearPlus();
	afx_msg void OnYearMinus();
};

#ifndef _DEBUG  // debug version in plannerView.cpp
inline CPlannerDoc* CPlannerView::GetDocument() const
   { return reinterpret_cast<CPlannerDoc*>(m_pDocument); }
#endif

