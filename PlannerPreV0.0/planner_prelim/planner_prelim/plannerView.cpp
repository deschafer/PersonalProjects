
// plannerView.cpp : implementation of the CPlannerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "planner_prelim.h"
#endif

#include "plannerDoc.h"
#include "planner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlannerView

IMPLEMENT_DYNCREATE(CPlannerView, CView)

BEGIN_MESSAGE_MAP(CPlannerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlannerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_NEXT_MONTH, &CPlannerView::OnNextMonth)
	ON_COMMAND(ID_PREV_MONTH, &CPlannerView::OnPrevMonth)
	ON_COMMAND(ID_YEAR_PLUS, &CPlannerView::OnYearPlus)
	ON_COMMAND(ID_YEAR_MINUS, &CPlannerView::OnYearMinus)
END_MESSAGE_MAP()

// CPlannerView construction/destruction

CPlannerView::CPlannerView() : m_Rows(5), m_Columns(7), m_Height(0),
m_Width(0), m_SizeChanged(1), m_CurrentMonth(), m_TopBarSize(60),
m_DaysComplete(0), m_MonthsComplete(0), m_Year(nullptr), m_Planner(2018, 2028, this)
{


}

CPlannerView::~CPlannerView()
{
}

BOOL CPlannerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlannerView drawing

void CPlannerView::OnDraw(CDC* pDC)
{
	CPlannerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawLayout(pDC);

}

// CPlannerView Initialization

//
// InitilizeWndVariables()
// Gets the client window dimensions and sets the appropriate vars in the class
//
void CPlannerView::InitilizeWndVariables()
{
	// Local Variables
	CRect rect;

	// Gets the current year
	m_Year = m_Planner.ReturnCurrentYear();

	// Gets the current month
	m_CurrentMonth = m_Year->CurrentMonth();

	// Check if this month is valid for a 6 row display
	if (m_CurrentMonth->IsSixRowDisplay())
	{
		m_Rows = 6;
	}
	else
	{
		m_Rows = 5;
	}

	// Gets the current client dimensions of this view object
	this->GetClientRect(&rect);

	// Sets appropriate variables to these dimensions
	m_Height = rect.Height();
	m_Width = rect.Width();

	// Sets the appropriate dimensions for each row or column based
	// on the total number of rows or columns set
	m_HeightPortion = (m_Height - m_TopBarSize) / m_Rows;
	m_WidthPortion = m_Width / m_Columns;

	// Set the indicator variable back to false
	m_SizeChanged = false;

	// Sets the array of month strings
	if (!m_MonthsComplete)
	{
		m_MonthStrings[0] = "January";
		m_MonthStrings[1] = "February";
		m_MonthStrings[2] = "March";
		m_MonthStrings[3] = "April";
		m_MonthStrings[4] = "May";
		m_MonthStrings[5] = "June";
		m_MonthStrings[6] = "July";
		m_MonthStrings[7] = "August";
		m_MonthStrings[8] = "September";
		m_MonthStrings[9] = "October";
		m_MonthStrings[10] = "November";
		m_MonthStrings[11] = "December";
		m_MonthsComplete = 1;
	}
	// Sets the array of day strings
	if (!m_DaysComplete)
	{
		m_DayStrings[0] = "Sunday";
		m_DayStrings[1] = "Monday";
		m_DayStrings[2] = "Tuesday";
		m_DayStrings[3] = "Wednesday";
		m_DayStrings[4] = "Thursday";
		m_DayStrings[5] = "Friday";
		m_DayStrings[6] = "Saturday";
		m_DaysComplete = 1;
	}

}

//
// DrawLayout()
// Draws the Month style layout for this view
//
void CPlannerView::DrawLayout(CDC* pDC)
{
	// Local Vars

	// Initialize variables if not already
	if (m_Width == 0 || m_Height == 0 || m_SizeChanged)
	{
		InitilizeWndVariables();
		m_CurrentMonth->ResetCells(m_WidthPortion, m_HeightPortion);
	}

	// Sets the default color for the background
	FillBackground(pDC);

	// Drawing the month section of the UI
	DrawMonthSection(pDC);

	// Drawing the top bar/ days of the week section of the UI
	DrawTopBarSection(pDC);

	// Draws the rows and columns for the main layout of the month view
	DrawGrid(pDC);

	// Draws the contents of each cell
	DrawCells(pDC);
}

//
// FillBackground()
// Draws Fills the background with the default color
//
void CPlannerView::FillBackground(CDC* pDC)
{
	// Local Variables
	CRect EnclosingRect(CPoint(0, 0), CPoint(m_Width, m_Height));
	CBrush NewBrush;

	// Creating the new brush
	NewBrush.CreateSolidBrush(RGB(180, 180, 180));

	// Filling the client area
	pDC->FillRect(EnclosingRect, &NewBrush);

	// Deleting the brush object
	NewBrush.DeleteObject();
}

//
// DrawTopBarSection()
// Draws the lower section of the client area topbar.
//
void CPlannerView::DrawTopBarSection(CDC* pDC)
{
	// Local Variables
	int FontSize = 22;
	CFont font;
	CRect EnclosingRect(CPoint(0, 37), CPoint(m_Width, m_TopBarSize));
	CBrush NewBrush;

	// Set the background mode as transparent so text will
	// appear accordingly
	pDC->SetBkMode(TRANSPARENT);

	// Drawing the top bar section
	pDC->MoveTo(0, m_TopBarSize);
	pDC->LineTo(m_Width, m_TopBarSize);

	// Create the font
	VERIFY(font.CreateFont(
		FontSize,                  // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Cambria")));           // lpszFacename

	// Save the default font, and set the new font
	CFont* def_font = pDC->SelectObject(&font);

	// Create the new brush
	NewBrush.CreateSolidBrush(RGB(140, 120, 120));

	// Set the color of the text 
	pDC->SetTextColor(RGB(50, 50, 50));

	// Color in the rectangle for this section of the topbar
	pDC->FillRect(EnclosingRect, &NewBrush);

	// Drawing each day of the week's text
	for (int i = 0; i < 7; i++)
	{
		pDC->TextOutW(m_WidthPortion * i + (m_WidthPortion / 50), 37, m_DayStrings[i]);
	}

	// Selecting the old object
	pDC->SelectObject(def_font);

	// Deleting objects
	font.DeleteObject();
	NewBrush.DeleteObject();

}

void CPlannerView::DrawMonthSection(CDC* pDC)
{
	// Local variables
	int FontSize = 38;
	CFont font;
	CString YearDate;
	CRect EnclosingRect(CPoint(0, 0), CPoint(m_Width, 37));
	CBrush NewBrush; 

	// Set the background mode as transparent so text will
	// appear accordingly
	pDC->SetBkMode(TRANSPARENT);

	// Formatting the year date into this string
	YearDate.Format(L"%d", m_Year->ReturnYearDate());

	VERIFY(font.CreateFont(
		FontSize,                  // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Calibri")));           // lpszFacename

								   
	// Save the default font, and set the new font
	CFont* def_font = pDC->SelectObject(&font);

	// Save the default font, and set the new font
	NewBrush.CreateSolidBrush(RGB(82, 95, 120));

	// Color in the rectangle for this section of the topbar
	pDC->FillRect(EnclosingRect, &NewBrush);

	// Set the color of the text 
	pDC->SetTextColor(RGB(50, 50, 50));
	
	// Draw the current month text
	pDC->TextOutW(5, 0, m_MonthStrings[m_CurrentMonth->ReturnMonthType()]);
	// Draw the current year date text
	pDC->TextOutW(pDC->GetTextExtent(m_MonthStrings[m_CurrentMonth->ReturnMonthType()]).cx + 25, 0, YearDate);
	// Select default font
	pDC->SelectObject(def_font);

	// Delete the font object.
	font.DeleteObject();
	NewBrush.DeleteObject();

	// Draws the last line for this section
	pDC->MoveTo(0, 35);
	pDC->LineTo(m_Width, 35);


}

void CPlannerView::DrawGrid(CDC* pDC)
{

	// Draws rows based on amount of rows and current
	// dimensions of client area
	for (int height = m_HeightPortion + m_TopBarSize; height < m_Height - 10; height += m_HeightPortion)
	{
		pDC->MoveTo(0, height);
		pDC->LineTo(m_Width, height);
	}
	// Draws columns based on amount of colomns and current
	// dimensions of client area
	for (int width = m_WidthPortion; width < m_Width - 10; width += m_WidthPortion)
	{

		pDC->MoveTo(width, m_TopBarSize);
		pDC->LineTo(width, m_Height);

	}

}

void CPlannerView::DrawCells(CDC* pDC)
{
	// Local Variables
	CLLNode* Curr;
	CRect EnclosingRect;
	CString string;
	CLLNode* NodeTemp;
	CFont font;
	CBrush NewBrush;

	// Creating the font objecy
	VERIFY(font.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Calibri")));           // lpszFacename

	// Traversing the head of the list of days within the month object
	Curr = m_CurrentMonth->GetList();
	Curr->m_AuxPtr = Curr->GetHead();

	// Getting each cell's dimensions
	EnclosingRect = Curr->m_AuxPtr->Object.m_Cell;

	// Printing each cell

	// First selecting new font
	CFont* def_font = pDC->SelectObject(&font);

	// Then creating new brush and selecting background mode for styling
	NewBrush.CreateSolidBrush(RGB(221, 221, 235));
	pDC->SetBkMode(TRANSPARENT);

	// Traversing the linked list structure of each month, 
	// and drawing the contents of each cell.
	for (int i = 0; i < m_CurrentMonth->m_NumberDays; i++)
	{
		// Sets CString object format
		string.Format(L"%u.", Curr->m_AuxPtr->Object.GetNumber());
		// Writes the number of this day to the corner of this cell

		// Deflate with respect to pen width
		EnclosingRect.DeflateRect(1, 1);
		// Fill in this rectangle with NewBrush's color
		pDC->FillRect(EnclosingRect, &NewBrush);
		// Reset the rectangles size
		EnclosingRect.InflateRect(1, 1);
		// Finally drawing the text
		pDC->TextOutW(EnclosingRect.TopLeft().x + 5, EnclosingRect.TopLeft().y + 5, string);

		// Moves to next node
		Curr->m_AuxPtr = Curr->m_AuxPtr->next;
		// Check if nullptr
		if (Curr->m_AuxPtr == nullptr) break;

		// Set the rectangle as the next cell's rectangle
		EnclosingRect = Curr->m_AuxPtr->Object.m_Cell;
	}

	// Resetting the font
	pDC->SelectObject(def_font);

	// Deleting the objects
	font.DeleteObject();
	NewBrush.DeleteObject();


}

// CPlannerView printing


void CPlannerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlannerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlannerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlannerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlannerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlannerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlannerView diagnostics

#ifdef _DEBUG
void CPlannerView::AssertValid() const
{
	CView::AssertValid();
}

void CPlannerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlannerDoc* CPlannerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlannerDoc)));
	return (CPlannerDoc*)m_pDocument;
}
#endif //_DEBUG

void CPlannerView::MoveMonth(int query)
{

	AfxMessageBox(_T("Bad Element ffssdfe"), MB_OK);

	m_Year->MoveMonth(query);
}

// CPlannerView message handlers in PLANNER.cpp

