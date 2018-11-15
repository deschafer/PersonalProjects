// NewPlnDialog.cpp : implementation file
//

#include "stdafx.h"
#include "planner_prelim.h"
#include "NewPlnDialog.h"
#include "afxdialogex.h"


// CNewPlnDialog dialog

IMPLEMENT_DYNAMIC(CNewPlnDialog, CDialogEx)

CNewPlnDialog::CNewPlnDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ID_ON_NEW_DOCUMENT, pParent)
{

}

CNewPlnDialog::~CNewPlnDialog()
{
}

void CNewPlnDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewPlnDialog, CDialogEx)
END_MESSAGE_MAP()


// CNewPlnDialog message handlers
