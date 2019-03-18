
// HttpSourceViewerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "HttpSourceViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHttpSourceViewerDlg �Ի���

CHttpSourceViewerDlg* CHttpSourceViewerDlg::m_pThis = NULL;

CHttpSourceViewerDlg::CHttpSourceViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpSourceViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pThis = this;
}

void CHttpSourceViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_urlEdit);
	DDX_Control(pDX, IDC_TAB_MAIN, m_mainTab);
	DDX_Control(pDX, IDC_STATIC_HTML_REQ_PROGRESS, m_htmlReqProgress);
}

BEGIN_MESSAGE_MAP(CHttpSourceViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_PASTE, &CHttpSourceViewerDlg::OnBnClickedButtonPaste)
	ON_BN_CLICKED(ID_BUTTON_CLEAR, &CHttpSourceViewerDlg::OnBnClickedButtonClear)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CHttpSourceViewerDlg::OnSelchangeTabMain)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CHttpSourceViewerDlg::OnTcnSelchangeTabMain)
ON_BN_CLICKED(ID_BUTTON_GO, &CHttpSourceViewerDlg::OnBnClickedButtonGo)
END_MESSAGE_MAP()


// CHttpSourceViewerDlg ��Ϣ��������

BOOL CHttpSourceViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ����Ӷ���ĳ�ʼ������
	InitTabControl();
	m_urlEdit.SetWindowTextW(TEXT("http://www.5566.net"));
	m_htmlReqProgress.SetRange(0, 100);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHttpSourceViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHttpSourceViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHttpSourceViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHttpSourceViewerDlg::OnBnClickedButtonPaste()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	m_urlEdit.Paste();
}


void CHttpSourceViewerDlg::OnBnClickedButtonClear()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	m_urlEdit.SetWindowTextW(TEXT(""));
}


void CHttpSourceViewerDlg::InitTabControl()
{
	// ����3��Tabҳ��
	m_mainTab.InsertItem(0, TEXT("HTML ͷ"));
	m_mainTab.InsertItem(1, TEXT("HTML ����"));
	m_mainTab.InsertItem(2, TEXT("��ȡ����"));

	// �����Ի��򣬲��ҽ�IDC_TAB_MAIN�ؼ���Ϊ������
	m_tabHtmlHead.Create(IDD_DIALOG_TAB_HTML_HEAD, GetDlgItem(IDC_TAB_MAIN));
	m_tabHtmlBody.Create(IDD_DIALOG_TAB_HTML_BODY, GetDlgItem(IDC_TAB_MAIN));
	m_tabHtmlGet.Create(IDD_DIALOG_TAB_HTML_GET, GetDlgItem(IDC_TAB_MAIN));

	// �ƶ�ÿ��Tabҳ�浽���ʵ�λ��
	MoveSubTab();

	// �ֱ��������غ���ʾ
	m_tabHtmlHead.ShowWindow(true);
	m_tabHtmlBody.ShowWindow(false);
	m_tabHtmlGet.ShowWindow(false);

	// ����Ĭ�ϵ�ѡ�
	m_mainTab.SetCurSel(0);
}


// �ƶ�ÿ��Tabҳ�浽���ʵ�λ��
void CHttpSourceViewerDlg::MoveSubTab()
{
	static bool isFirstTime = true;

	if (isFirstTime)
	{
		// ���IDC_TAB_MAIN�Ŀͻ�����С
		CRect rectClient;
		m_mainTab.GetClientRect(&rectClient);
		
		// �����ӶԻ����ڸ������е�λ��
		rectClient.top += 30;
		rectClient.bottom -= 10;
		rectClient.left += 10;
		rectClient.right -= 10;

		// �����ӶԻ���ߴ粢�ƶ���ָ��λ��
		m_tabHtmlHead.MoveWindow(&rectClient);
		m_tabHtmlBody.MoveWindow(&rectClient);
		m_tabHtmlGet.MoveWindow(&rectClient);
	}
	isFirstTime = false;
}

void CHttpSourceViewerDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
		int CurSel = m_mainTab.GetCurSel();
		switch (CurSel)
		{
		case 0:
			m_tabHtmlHead.ShowWindow(true);
			m_tabHtmlBody.ShowWindow(false);
			m_tabHtmlGet.ShowWindow(false);
			break;
		case 1:
			m_tabHtmlHead.ShowWindow(false);
			m_tabHtmlBody.ShowWindow(true);
			m_tabHtmlGet.ShowWindow(false);
			break;
		case 2:
			m_tabHtmlHead.ShowWindow(false);
			m_tabHtmlBody.ShowWindow(false);
			m_tabHtmlGet.ShowWindow(true);
			break;
		default:
			break;
		}

		*pResult = 0;
}


void CHttpSourceViewerDlg::OnBnClickedButtonGo()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	ProcessHttpRequest();
}


// ��ȡURL��ַ��Ȼ��������񣬷���HTMLͷ������
bool CHttpSourceViewerDlg::ProcessHttpRequest()
{
	// ��ȡ��Ҫ�����URL��ַ
	CString strUrl;
	m_urlEdit.GetWindowTextW(strUrl);

	// ����HTTP�ͻ��ˣ���������
	WinHttpClient client(strUrl.GetBuffer(), &CHttpSourceViewerDlg::HtmlRequestProgress);
	// Send http request, a GET request by default.
	client.SendHttpRequest();

	//�ռ����������ص�Httpͷ��HTML����
	// The response header.
	wstring httpResponseHeader = client.GetResponseHeader();

	// The response content.
	wstring httpResponseContent = client.GetResponseContent();

	//��Httpͷ��Html������ʾ��Tab��ǩҳ���ı�����
	// Set URL.
	m_tabHtmlHead.m_htmlHeadEdit.SetWindowTextW(httpResponseHeader.c_str());
	m_tabHtmlBody.m_htmlBodyEdit.SetWindowTextW(httpResponseContent.c_str());

	return true;
}


bool CHttpSourceViewerDlg::HtmlRequestProgress(double progress)
{
	m_pThis->m_htmlReqProgress.SetPos( static_cast<int>(progress) );
	return true;
}