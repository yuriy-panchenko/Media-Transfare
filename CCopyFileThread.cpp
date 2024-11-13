// CCopyFileThread.cpp : implementation file
//

#include "pch.h"
#include "Media Transfare.h"
#include "CCopyFileThread.h"
#include "Media TransfareDlg.h"

// CCopyFileThread

IMPLEMENT_DYNCREATE(CCopyFileThread, CWinThread)

CCopyFileThread::CCopyFileThread()
{
	m_pMainDlg = (CMediaTransfareDlg*)theApp.GetMainWnd();
}

CCopyFileThread::~CCopyFileThread()
{
}

BOOL CCopyFileThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CCopyFileThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCopyFileThread, CWinThread)
END_MESSAGE_MAP()


// CCopyFileThread message handlers
