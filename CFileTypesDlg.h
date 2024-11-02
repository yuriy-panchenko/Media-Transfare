#pragma once
#include "afxdialogex.h"


// CFileTypesDlg dialog

class CFileTypesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileTypesDlg)

public:
	CFileTypesDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFileTypesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_TYPES_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_Extension;
	CListBox m_extList;
public:
	afx_msg void OnClickedExtAdd();
	afx_msg void OnClickedExtRemove();
};
