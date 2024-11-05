// CFileTypesDlg.cpp : implementation file
//

#include "pch.h"
#include "Media Transfare.h"
#include "afxdialogex.h"
#include "CFileTypesDlg.h"
#include "Media TransfareDlg.h"

// CFileTypesDlg dialog

IMPLEMENT_DYNAMIC(CFileTypesDlg, CDialogEx)

CFileTypesDlg::CFileTypesDlg(const CStringArray& ext, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_TYPES_DLG, pParent)
	, m_Extension(_T(""))
{
	m_Extensions.Copy(ext);
}

CFileTypesDlg::~CFileTypesDlg()
{
}

const CStringArray& CFileTypesDlg::GetExensions() const
{
	return m_Extensions;
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
	ON_BN_CLICKED(IDOK, &CFileTypesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileTypesDlg message handlers


void CFileTypesDlg::OnClickedExtAdd()
{
	if (UpdateData())
	{
		if (m_Extension[0] != _T('.'))
			m_Extension.Insert(0, _T('.'));

		if (!Exist(m_Extension))
		{
			m_extList.AddString(m_Extension.MakeLower());
			m_Extension.Empty();
			UpdateData(FALSE);
			UpdateControls();
			GetDlgItem(IDOK)->EnableWindow();
		}
	}
}

/*
3gp
bmp
gif
jpeg
jpg
mp4
png
webp
*/

void CFileTypesDlg::OnClickedExtRemove()
{
	const auto iSel{ m_extList.GetCurSel() };
	ASSERT(iSel > -1);
	CString str;
	m_extList.GetText(iSel, str);
	const auto iIndex{ FindExtension(str) };
	ASSERT(iIndex > -1);
	
	m_extList.DeleteString(iSel);
	m_Extensions.RemoveAt(iIndex);
	GetDlgItem(IDOK)->EnableWindow();
}


void CFileTypesDlg::OnEnChangeExtEdit()
{
	if (UpdateData())
		UpdateControls();
}


void CFileTypesDlg::OnLbnSelchangeExtList()
{
	UpdateControls();
}

void CFileTypesDlg::UpdateControls()
{
	GetDlgItem(IDC_EXT_ADD)->EnableWindow(!m_Extension.IsEmpty());
	GetDlgItem(IDC_EXT_REMOVE)->EnableWindow(m_extList.GetCurSel() > -1);
}

BOOL CFileTypesDlg::Exist(const CString& ext) const
{
	return FindExtension(ext) > -1;
}

INT_PTR CFileTypesDlg::FindExtension(const CString& ext) const
{
	for (INT_PTR i = 0; i < m_Extensions.GetSize(); ++i)
		if (m_Extensions[i] == ext)
			return i;

	return -1;
}

BOOL CFileTypesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (INT_PTR i = 0; i < m_Extensions.GetSize(); ++i)
		m_extList.AddString(m_Extensions[i]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFileTypesDlg::OnBnClickedOk()
{
	m_Extensions.RemoveAll();
	CString str;

	for (int i = 0; i < m_extList.GetCount(); ++i)
	{
		m_extList.GetText(i, str);
		m_Extensions.Add(str);
	}

	CDialogEx::OnOK();
}
