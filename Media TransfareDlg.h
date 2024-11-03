
// Media TransfareDlg.h : header file
//

#pragma once


// CMediaTransfareDlg dialog
class CMediaTransfareDlg : public CDialogEx
{
// Construction
public:
	CMediaTransfareDlg(CWnd* pParent = nullptr);	// standard constructor
	BOOL IsAcceptableExtension(const CString& ext);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIA_TRANSFARE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedFileTypes();
	afx_msg void OnBnClickedOk();
	afx_msg void OnChangeBrowseSrc();
	afx_msg void OnChangeBrowseDst();
	afx_msg void OnBnClickedIgnoreFilesLess();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

private:
	void UpdateControls();
	
	static UINT CALLBACK CollectSourceFiles(LPVOID);
	static void LoadFolderFiles(CMediaTransfareDlg* pDlg, const std::filesystem::path& dir, BOOL bLoadSubFolders, CArray<CFileStatus>& info);

private:
	BOOL m_bAutoRename;
	CString m_srcPath;
	CString m_dstPath;
	BOOL m_bIgnoreDuplicates;
	CString m_dstInfo1;
	CString m_dstInfo2;
	CString m_dstInfo3;
	CString m_srcInfo1;
	CString m_srcInfo2;
	CString m_srcInfo3;
	BOOL m_bSearchSubFolders;
	BOOL m_bIgnoreFilesLess;
	int m_iIgnoreSize;
	int m_iIgnoreSizeType;
	BOOL m_bRemoveCopied;
	
	CArray<CFileStatus> m_srcFiles, m_dstFiles;
	CStringArray m_Exensions;
	CMutex m_Mutex;
	BOOL m_bSortByMonth;
	BOOL m_bSortByYear;
};
