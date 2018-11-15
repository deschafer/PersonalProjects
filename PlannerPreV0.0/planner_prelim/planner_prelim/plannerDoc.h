
// plannerDoc.h : interface of the CPlannerDoc class
//


#pragma once


class CPlannerDoc : public CDocument
{
protected: // create from serialization only
	CPlannerDoc();
	DECLARE_DYNCREATE(CPlannerDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPlannerDoc();

	int GetMonthRequest() { return m_MonthRequest; }
	void ResetMonthRequest() { m_MonthRequest = 0; }

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int m_MonthRequest;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnNextMonth();
	afx_msg void OnPrevMonth();
};
