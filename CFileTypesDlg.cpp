// CFileTypesDlg.cpp : implementation file
//

#include "pch.h"
#include "Media Transfare.h"
#include "afxdialogex.h"
#include "CFileTypesDlg.h"


// CFileTypesDlg dialog

IMPLEMENT_DYNAMIC(CFileTypesDlg, CDialogEx)

CFileTypesDlg::CFileTypesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_TYPES_DLG, pParent)
	, m_Extension(_T(""))
{

}

CFileTypesDlg::~CFileTypesDlg()
{
}

void CFileTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXT_EDIT, m_Extension);
	DDX_Control(pDX, IDC_EXT_LIST, m_extList);
}


BEGIN_MESSAGE_MAP(CFileTypesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EXT_ADD, &CFileTypesDlg::OnClickedExtAdd)
	ON_BN_CLICKED(IDC_EXT_REMOVE, &CFileTypesDlg::OnClickedExtRemove)
END_MESSAGE_MAP()


// CFileTypesDlg message handlers


void CFileTypesDlg::OnClickedExtAdd()
{
	// TODO: Add your control notification handler code here
}


void CFileTypesDlg::OnClickedExtRemove()
{
	// TODO: Add your control notification handler code here
}
