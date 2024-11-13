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
	DECLARE_MESSAGE_MAP()

public:
	fs::path m_srcFile, m_dstFolder;

private:
	CDialogEx* m_pMainDlg;
};


