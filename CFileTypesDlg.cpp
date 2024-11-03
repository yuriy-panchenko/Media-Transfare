// CFileTypesDlg.cpp : implementation file
//

#include "pch.h"
#include "Media Transfare.h"
#include "afxdialogex.h"
#include "CFileTypesDlg.h"
#include "Media TransfareDlg.h"

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
	ON_EN_CHANGE(IDC_EXT_EDIT, &CFileTypesDlg::OnEnChangeExtEdit)
	ON_LBN_SELCHANGE(IDC_EXT_LIST, &CFileTypesDlg::OnLbnSelchangeExtList)
END_MESSAGE_MAP()


// CFileTypesDlg message handlers


void CFileTypesDlg::OnClickedExtAdd()
{
	if (UpdateData())
	{
		if (!Exist(m_Extension))
		{
			m_extList.AddString(m_Extension.MakeLower());
			m_Extension.Empty();
			UpdateData(FALSE);
			UpdateControls();
		}
	}
}


void CFileTypesDlg::OnClickedExtRemove()
{
	// TODO: Add your control notification handler code here
}


void CFileTypesDlg::OnEnChangeExtEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CFileTypesDlg::OnLbnSelchangeExtList()
{
	// TODO: Add your control notification handler code here
}

void CFileTypesDlg::UpdateControls()
{
	GetDlgItem(IDC_EXT_ADD)->EnableWindow(!m_Extension.IsEmpty());
	GetDlgItem(IDC_EXT_REMOVE)->EnableWindow(m_extList.GetCurSel() > -1);
}

BOOL CFileTypesDlg::Exist(const CString& ext) const
{
	return static_cast<CMediaTransfareDlg*>(GetParent())->IsAcceptableExtension(ext);
}
