#pragma once


// CNewPlnDialog dialog

class CNewPlnDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPlnDialog)

public:
	CNewPlnDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewPlnDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_ON_NEW_DOCUMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
