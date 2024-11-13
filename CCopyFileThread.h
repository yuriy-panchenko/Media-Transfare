#pragma once

// CCopyFileThread

class CCopyFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CCopyFileThread)

protected:
	CCopyFileThread();           // protected constructor used by dynamic creation
	virtual ~CCopyFileThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	afx_msg void OnNextFile(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

public:
	fs::path m_dstFolder, m_srcFolder;
	CFileStatus m_fileStatus;

private:
	CDialogEx* m_pMainDlg;
};


