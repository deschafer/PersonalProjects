
// plannerDoc.cpp : implementation of the CPlannerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "planner_prelim.h"
#endif

#include "plannerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlannerDoc

IMPLEMENT_DYNCREATE(CPlannerDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlannerDoc, CDocument)
	//ON_COMMAND(ID_NEXT_MONTH, &CPlannerDoc::OnNextMonth)
	//ON_COMMAND(ID_PREV_MONTH, &CPlannerDoc::OnPrevMonth)
END_MESSAGE_MAP()


// CPlannerDoc construction/destruction

CPlannerDoc::CPlannerDoc() : m_MonthRequest(0)
{
	// TODO: add one-time construction code here

}

CPlannerDoc::~CPlannerDoc()
{
}

BOOL CPlannerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPlannerDoc serialization

void CPlannerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPlannerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPlannerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPlannerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPlannerDoc diagnostics

#ifdef _DEBUG
void CPlannerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlannerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPlannerDoc commands

/*
void CPlannerDoc::OnNextMonth()
{
	m_MonthRequest++;
}


void CPlannerDoc::OnPrevMonth()
{
	m_MonthRequest--;
}
*/