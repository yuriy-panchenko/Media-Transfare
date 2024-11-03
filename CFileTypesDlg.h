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

	afx_msg void OnClickedExtAdd();
	afx_msg void OnClickedExtRemove();
	afx_msg void OnEnChangeExtEdit();
	afx_msg void OnLbnSelchangeExtList();
	DECLARE_MESSAGE_MAP()

private:
	void UpdateControls();
	BOOL Exist(const CString&)const;

private:
	CString m_Extension;
	CListBox m_extList;
};
