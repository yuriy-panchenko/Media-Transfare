
// Media TransfareDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Media Transfare.h"
#include "Media TransfareDlg.h"
#include "afxdialogex.h"
#include "CFileTypesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PRS_SETTINGS	_T("Settings")
#define	PRE_AUTO_RENAME	_T("AutoRename")
#define	PRE_IGNORE_DUPLICATES	_T("IgnoreDuplicates")
#define	PRE_SEARCH_SUBFOLDER	_T("SearchSubFolders")
#define	PRE_IGNORE_FILES_LESS	_T("IgnoreFileLess")
#define	PRE_REMOVE_COPIED	_T("RemoveCopied")
//#define	PRE_SORT_BY_YEAR	_T("SortByYear")
//#define	PRE_SORT_BY_MONTH	_T("SortByMonth")

#define	PRE_IGNORE_SIZE	_T("FileLessSize")
#define	PRE_IGNORE_TYPE	_T("FileLessType")
#define	PRE_SOURCE_PATH	_T("SourecPath")
#define	PRE_DESTINATION_PATH	_T("DestinationPath")

#define FILE_EXTENSION_LIST	_T("ExtList.bin")

#ifdef _DEBUG
#define _DEBUG_TEST
#endif // _DEBUG

void CMediaTransfareDlg::InsertComas(CString& str)
{
	auto index{ str.GetLength() - 3 };
	while (index > 0)
	{
		str.Insert(index, _T(','));
		index -= 3;
	}
}

CString CMediaTransfareDlg::ReadableFormat(size_t len)
{
	//	0 bytes, 1 KB, 2 MB, 3 GB, 4 TB

	int curr_range{ 0 };
	auto db{ (double)len };

	do
	{
		if (len < 999)
			break;

		db = (double)len;
		db /= 1024;
		len >>= 10;
		++curr_range;
	} while (curr_range < 4);

	CString ret;

	switch (curr_range)
	{
	case 0:ret.Format(_T("%.0f bytes"), db); break;
	case 1:ret.Format(_T("%.2f KB"), db); break;
	case 2:ret.Format(_T("%.2f MB"), db); break;
	case 3:ret.Format(_T("%.2f GB"), db); break;
	default:ret.Format(_T("%.2f TB"), db); break;
	}

	return ret;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMediaTransfareDlg dialog



CMediaTransfareDlg::CMediaTransfareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEDIA_TRANSFARE_DIALOG, pParent)
	, m_bAutoRename(FALSE)
	, m_srcPath(_T(""))
	, m_dstPath(_T(""))
	, m_bIgnoreDuplicates(FALSE)
	, m_dstInfo1(_T(""))
	, m_dstInfo2(_T(""))
	, m_dstInfo3(_T(""))
	, m_srcInfo1(_T(""))
	, m_srcInfo2(_T(""))
	, m_srcInfo3(_T(""))
	, m_bSearchSubFolders(FALSE)
	, m_bIgnoreFilesLess(FALSE)
	, m_iIgnoreSize(0)
	, m_iIgnoreSizeType(0)
	, m_bRemoveCopied(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

#ifdef _DEBUG_TEST
	m_srcPath = _T("D:\\Temp\\Test\\src");
	m_dstPath = _T("D:\\Temp\\Test\\dst");
#endif // _DEBUG_TEST

}

void CMediaTransfareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AUTO_RENAME, m_bAutoRename);
	DDX_Text(pDX, IDC_BROWSE_DST, m_dstPath);
	DDX_Text(pDX, IDC_BROWSE_SRC, m_srcPath);
	DDX_Check(pDX, IDC_IGNORE_DUPLICATES, m_bIgnoreDuplicates);
	DDX_Text(pDX, IDC_INFO_DST_1, m_dstInfo1);
	DDX_Text(pDX, IDC_INFO_DST_2, m_dstInfo2);
	DDX_Text(pDX, IDC_INFO_DST_3, m_dstInfo3);
	DDX_Text(pDX, IDC_INFO_SRC_1, m_srcInfo1);
	DDX_Text(pDX, IDC_INFO_SRC_2, m_srcInfo2);
	DDX_Text(pDX, IDC_INFO_SRC_3, m_srcInfo3);
	DDX_Check(pDX, IDC_SEARCH_SUB_FOLDERS, m_bSearchSubFolders);
	DDX_Check(pDX, IDC_IGNORE_FILES_LESS, m_bIgnoreFilesLess);
	DDX_Text(pDX, IDC_IGNORE_SIZE, m_iIgnoreSize);
	DDX_CBIndex(pDX, IDC_IGNORE_SIZE_COMBO, m_iIgnoreSizeType);
	DDX_Check(pDX, IDC_REMOVE_COPIED, m_bRemoveCopied);
	//DDX_Check(pDX, IDC_SORT_BY_MONTH, m_bSortByMonth);
	//DDX_Check(pDX, IDC_SORT_BY_YEAR, m_bSortByYear);
}

BEGIN_MESSAGE_MAP(CMediaTransfareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE_TYPES, &CMediaTransfareDlg::OnClickedFileTypes)
	ON_BN_CLICKED(IDOK, &CMediaTransfareDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_BROWSE_SRC, &CMediaTransfareDlg::OnChangeBrowseSrc)
	ON_EN_CHANGE(IDC_BROWSE_DST, &CMediaTransfareDlg::OnChangeBrowseDst)
	ON_BN_CLICKED(IDC_IGNORE_FILES_LESS, &CMediaTransfareDlg::OnBnClickedIgnoreFilesLess)
	ON_WM_DESTROY()
	//ON_BN_CLICKED(IDC_SORT_BY_YEAR, &CMediaTransfareDlg::OnBnClickedSortByYear)
	ON_BN_CLICKED(IDC_SEARCH_SUB_FOLDERS, &CMediaTransfareDlg::OnBnClickedSearchSubFolders)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CMediaTransfareDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMediaTransfareDlg message handlers

BOOL CMediaTransfareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CFile file;
	if (file.Open(FILE_EXTENSION_LIST, CFile::modeRead | CFile::shareDenyNone))
	{
		CArchive ar{ &file, CArchive::load };
		m_Extensions.Serialize(ar);
	}

	//m_srcPath = theApp.GetProfileString(PRS_SETTINGS, PRE_SOURCE_PATH);
	//m_dstPath = theApp.GetProfileString(PRS_SETTINGS, PRE_DESTINATION_PATH);

	m_bAutoRename = theApp.GetProfileInt(PRS_SETTINGS, PRE_AUTO_RENAME, TRUE);
	m_bIgnoreDuplicates = theApp.GetProfileInt(PRS_SETTINGS, PRE_IGNORE_DUPLICATES, TRUE);
	m_bSearchSubFolders = theApp.GetProfileInt(PRS_SETTINGS, PRE_SEARCH_SUBFOLDER, TRUE);
	m_bRemoveCopied = theApp.GetProfileInt(PRS_SETTINGS, PRE_REMOVE_COPIED, TRUE);
	//m_bSortByYear = theApp.GetProfileInt(PRS_SETTINGS, PRE_SORT_BY_YEAR, FALSE);
	//m_bSortByMonth = theApp.GetProfileInt(PRS_SETTINGS, PRE_SORT_BY_MONTH, FALSE);

	m_bIgnoreFilesLess = theApp.GetProfileInt(PRS_SETTINGS, PRE_IGNORE_FILES_LESS, TRUE);
	m_iIgnoreSize = theApp.GetProfileInt(PRS_SETTINGS, PRE_IGNORE_SIZE, 200);
	m_iIgnoreSizeType = theApp.GetProfileInt(PRS_SETTINGS, PRE_IGNORE_TYPE, 1);

	UpdateData(FALSE);
#ifdef _DEBUG_TEST
	OnChangeBrowseSrc();
	OnChangeBrowseDst();
#endif // _DEBUG_TEST
	UpdateControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMediaTransfareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMediaTransfareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMediaTransfareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMediaTransfareDlg::OnClickedFileTypes()
{
	CFileTypesDlg dlg{ m_Extensions, this };

	if (dlg.DoModal() == IDOK)
	{
		m_Extensions.Copy(dlg.GetExensions());

		CFile file;
		if (file.Open(FILE_EXTENSION_LIST, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive))
		{
			CArchive ar{ &file, CArchive::store };
			m_Extensions.Serialize(ar);
		}
	}
}

void CMediaTransfareDlg::OnChangeBrowseSrc()
{
	if (UpdateData())
	{
		UpdateControls();

		if (!m_srcPath.IsEmpty())
			if (auto pThread = ::AfxBeginThread(CollectSourceFiles, this))
				::WaitForSingleObject(*pThread, INFINITE);

		m_srcInfo1.Format(_T("Found %d media files"), m_srcFiles.GetSize());

		size_t total_size{};

		for (INT_PTR i = 0; i < m_srcFiles.GetSize(); ++i)
			total_size += m_srcFiles[i].m_size;

		m_srcInfo2.Format(_T("%I64u"), total_size);
		InsertComas(m_srcInfo2);
		m_srcInfo2 = _T("TotalSize = ") + ReadableFormat(total_size) + _T(" (") + m_srcInfo2 + _T(" bytes)");

		UpdateData(FALSE);
	}
}

void CMediaTransfareDlg::OnChangeBrowseDst()
{
	if (UpdateData())
		UpdateControls();

	if (!m_dstPath.IsEmpty())
		if (auto pThread = ::AfxBeginThread(CollectDestinationFiles, this))
			::WaitForSingleObject(*pThread, INFINITE);

	m_dstInfo1.Format(_T("Found %d media files"), m_dstFiles.GetSize());

	size_t total_size{};

	for (INT_PTR i = 0; i < m_dstFiles.GetSize(); ++i)
		total_size += m_dstFiles[i].m_size;

	m_dstInfo2.Format(_T("%I64u"), total_size);
	InsertComas(m_dstInfo2);
	m_dstInfo2 = _T("TotalSize = ") + ReadableFormat(total_size) + _T(" (") + m_dstInfo2 + _T(" bytes)");

	UpdateData(FALSE);
}


void CMediaTransfareDlg::UpdateControls()
{
	GetDlgItem(IDOK)->EnableWindow(!m_srcPath.IsEmpty() && !m_dstPath.IsEmpty() && (m_srcPath != m_dstPath) && !m_srcFiles.IsEmpty());
	GetDlgItem(IDC_IGNORE_SIZE)->EnableWindow(m_bIgnoreFilesLess);
	GetDlgItem(IDC_IGNORE_SIZE_COMBO)->EnableWindow(m_bIgnoreFilesLess);
	//GetDlgItem(IDC_SORT_BY_MONTH)->EnableWindow(m_bSortByYear);
}

void CMediaTransfareDlg::EnableControls(BOOL bEnable)
{
	GetDlgItem(IDC_BROWSE_SRC)->EnableWindow(bEnable);
	GetDlgItem(IDC_BROWSE_DST)->EnableWindow(bEnable);
	GetDlgItem(IDC_AUTO_RENAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_SEARCH_SUB_FOLDERS)->EnableWindow(bEnable);
	GetDlgItem(IDC_IGNORE_DUPLICATES)->EnableWindow(bEnable);
	GetDlgItem(IDC_REMOVE_COPIED)->EnableWindow(bEnable);
	GetDlgItem(IDC_IGNORE_FILES_LESS)->EnableWindow(bEnable);
	GetDlgItem(IDC_IGNORE_SIZE)->EnableWindow(bEnable);
	GetDlgItem(IDC_IGNORE_SIZE_COMBO)->EnableWindow(bEnable);
	GetDlgItem(IDC_FILE_TYPES)->EnableWindow(bEnable);
	GetDlgItem(IDOK)->EnableWindow(bEnable);
}

void CMediaTransfareDlg::OnBnClickedIgnoreFilesLess()
{
	if (UpdateData())
		UpdateControls();
}


void CMediaTransfareDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (UpdateData())
	{
		//theApp.WriteProfileString(PRS_SETTINGS, PRE_SOURCE_PATH, m_srcPath);
		//theApp.WriteProfileString(PRS_SETTINGS, PRE_DESTINATION_PATH, m_dstPath);

		theApp.WriteProfileInt(PRS_SETTINGS, PRE_AUTO_RENAME, m_bAutoRename);
		theApp.WriteProfileInt(PRS_SETTINGS, PRE_IGNORE_DUPLICATES, m_bIgnoreDuplicates);
		theApp.WriteProfileInt(PRS_SETTINGS, PRE_SEARCH_SUBFOLDER, m_bSearchSubFolders);
		theApp.WriteProfileInt(PRS_SETTINGS, PRE_REMOVE_COPIED, m_bRemoveCopied);
		//theApp.WriteProfileInt(PRS_SETTINGS, PRE_SORT_BY_YEAR, m_bSortByYear);
		//theApp.WriteProfileInt(PRS_SETTINGS, PRE_SORT_BY_MONTH, m_bSortByMonth);

		theApp.WriteProfileInt(PRS_SETTINGS, PRE_IGNORE_FILES_LESS, m_bIgnoreFilesLess);
		theApp.WriteProfileInt(PRS_SETTINGS, PRE_IGNORE_SIZE, m_iIgnoreSize);
		theApp.WriteProfileInt(PRS_SETTINGS, PRE_IGNORE_TYPE, m_iIgnoreSizeType);
	}
}

//	AFX_THREADPROC

void CMediaTransfareDlg::LoadFolderFiles(CMediaTransfareDlg* pDlg, const fs::path& dir, BOOL bLoadSubFolders, CArray<CFileStatus>& info)
{
	CFileStatus status;

	for (const auto& entry : fs::directory_iterator{ dir })
	{
		const auto& file_path{ entry.path() };
		if (CFile::GetStatus(file_path.c_str(), status))
		{
			switch (status.m_attribute)
			{
			case CFile::Attribute::directory:
				if (bLoadSubFolders)
					LoadFolderFiles(pDlg, status.m_szFullName, TRUE, info);
				break;

			case CFile::Attribute::device:
			case CFile::Attribute::volume:
				break;

			default:
			{
				if (pDlg->IsAcceptableExtension(CString(fs::path{ status.m_szFullName }.extension().c_str()).MakeLower()))
					info.Add(status);
			}
			break;
			}

		}
		else
		{
		}
	}
}

UINT CMediaTransfareDlg::CollectSourceFiles(LPVOID pData)
{
	auto pDlg = static_cast<CMediaTransfareDlg*>(pData);

	CArray<CFileStatus> info;
	LoadFolderFiles(pDlg, pDlg->m_srcPath.GetString(), pDlg->m_bSearchSubFolders, info);

	pDlg->m_srcFiles.Copy(info);

	return 0;
}

UINT CMediaTransfareDlg::CollectDestinationFiles(LPVOID pData)
{
	auto pDlg = static_cast<CMediaTransfareDlg*>(pData);

	CArray<CFileStatus> info;
	LoadFolderFiles(pDlg, pDlg->m_dstPath.GetString(), FALSE, info);

	pDlg->m_dstFiles.Copy(info);

	return 0;
}

BOOL CMediaTransfareDlg::IsAcceptableExtension(const CString& ext)
{
	for (INT_PTR i = 0; i < m_Extensions.GetSize(); ++i)
		if (m_Extensions[i] == ext)
			return TRUE;

	return FALSE;
}

void CMediaTransfareDlg::OnBnClickedSortByYear()
{
	if (UpdateData())
		UpdateControls();
}


void CMediaTransfareDlg::OnBnClickedSearchSubFolders()
{
	if (UpdateData() && !m_srcPath.IsEmpty())
		OnChangeBrowseSrc();
}


void CMediaTransfareDlg::OnClose()
{
	//if (!IsBusy())
	CDialogEx::OnClose();
}


void CMediaTransfareDlg::OnBnClickedCancel()
{
	//if (IsBusy())
	//{
	//	ShutDownWorkingThreads();
	//	EnableControls();
	//	UpdateControls();
	//	GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
	//}
	//else
	CDialogEx::OnCancel();
}

void CMediaTransfareDlg::OnBnClickedOk()
{
	BeginWaitCursor();
	if (UpdateData())
	{
	}
	EndWaitCursor();
}