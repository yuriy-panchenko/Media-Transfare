
// Media Transfare.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#define WM_NEXT_FILE			(WM_APP + 0x0001)

#define WM_NEXT_FILE_FINISHED	(WM_USER + 0x0001)



// CMediaTransfareApp:
// See Media Transfare.cpp for the implementation of this class
//

class CMediaTransfareApp : public CWinApp
{
public:
	CMediaTransfareApp();

	// Overrides
public:
	virtual BOOL InitInstance();

	// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMediaTransfareApp theApp;
