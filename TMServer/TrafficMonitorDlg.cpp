
// TrafficMonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TrafficMonitorDlg.h"
#include "afxdialogex.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
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


// CTrafficMonitorDlg �Ի���



CTrafficMonitorDlg::CTrafficMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAFFICMONITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, serveList);
	DDX_Control(pDX, IDC_EDIT2, Edit_carNum);
	DDX_Control(pDX, IDC_EDIT3, Edit_time);
	DDX_Control(pDX, IDC_EDIT4, Edit_path);
	DDX_Control(pDX, IDC_EDIT1, edit_find);
}

BEGIN_MESSAGE_MAP(CTrafficMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTrafficMonitorDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTrafficMonitorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON4, &CTrafficMonitorDlg::OnBnClickedUpdate)
	ON_BN_CLICKED(IDC_BUTTON1, &CTrafficMonitorDlg::OnBnClickedFind)
	ON_BN_CLICKED(IDC_BUTTON5, &CTrafficMonitorDlg::OnBnClickedShowAll)
END_MESSAGE_MAP()


// CTrafficMonitorDlg ��Ϣ�������

BOOL CTrafficMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	plateDao.set_gszFile("database.db");
	plateDao.init();
	
	server = new Server("127.0.0.1", 50084);
	int init_success = server->init();
	if (init_success == 0)
	{
		// ��������ʼ���ɹ�����ʼ����
		server->serve();
	}
	else
	{
		// ��������ʼ��ʧ��
		MessageBox(_T("��������ʼ��ʧ�ܣ�"));
		return FALSE;
	}
	
	CRect rect;
	serveList.GetClientRect(&rect);
	serveList.SetExtendedStyle(serveList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	serveList.InsertColumn(0, _T("���ƺ�"), LVCFMT_CENTER, rect.Width() / 3, 0);
	serveList.InsertColumn(1, _T("�ϴ�����"), LVCFMT_CENTER, rect.Width() /3 , 1);
	serveList.InsertColumn(2, _T("ͼƬ��ַ"), LVCFMT_CENTER, rect.Width() / 3, 2);
	CString ptime;
	int i = 0;
	for (auto iplate = plates.cbegin(); iplate != plates.cend(); ++iplate, ++i)//������ʾ����ѯ��������
	{
		ptime.Format(_T("%ld"), (*iplate)->get_time());
		serveList.InsertItem(i, (CString)(*iplate)->get_number().c_str());
		serveList.SetItemText(i, 1, ptime);
		serveList.SetItemText(i, 2, (CString)(*iplate)->get_path().c_str());
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

CTrafficMonitorDlg::~CTrafficMonitorDlg()
{
	plateDao.release();
}

void CTrafficMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTrafficMonitorDlg::OnPaint()
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
HCURSOR CTrafficMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTrafficMonitorDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NMLISTVIEW *pnml = (NMLISTVIEW*)pNMHDR;
	
	if (-1 != pnml->iItem)
	{
		NowID = pnml->iItem;
		this->SetDlgItemTextW(IDC_EDIT2, serveList.GetItemText(pnml->iItem, 0));
		this->SetDlgItemTextW(IDC_EDIT3, serveList.GetItemText(pnml->iItem, 1));
		this->SetDlgItemTextW(IDC_EDIT4, serveList.GetItemText(pnml->iItem, 2));
		//����ѡ���е����ݸ�plate��ֵ
		plate = *plates[NowID];
	}
	*pResult = 0;
}


void CTrafficMonitorDlg::OnBnClickedDelete()
{
	if (NowID ==-1)
	{
		MessageBox(_T("��ѡ��Ҫɾ���ļ�¼"));
		return;
	}
	//���ݿ���ɾ��
	if (plateDao.remove(plate) != 0)
	{
		MessageBox(_T("ɾ��ʧ��"));
		return;
	}
	//����ɾ��
	serveList.DeleteItem(NowID);
	//ɾ�������������
	for (std::vector<Plate*>::iterator iter = plates.begin(); iter != plates.end();)
	{
		if (**iter==plate)
			iter = plates.erase(iter);
		else
			iter++;
	}
	this->SetDlgItemTextW(IDC_EDIT2,NULL);
	this->SetDlgItemTextW(IDC_EDIT3, NULL);
	this->SetDlgItemTextW(IDC_EDIT4,NULL);
	NowID=-1;
	
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTrafficMonitorDlg::OnBnClickedUpdate()//����ĳ����Ϣ
{
	USES_CONVERSION;//Unicode���ַ�ת��˵������ͬ
	CString carNum, time, path;//��������ĳ�����Ϣ
	Edit_carNum.GetWindowText(carNum);
	Edit_time.GetWindowText(time);
	Edit_path.GetWindowText(path);
	plate.set_number(W2A(carNum));
	plate.set_time(_ttol(time));
	plate.set_path(W2A(path));
	if (carNum.GetLength() == 0 || time.GetLength() == 0 || path.GetLength() == 0) 
	{
		MessageBox(_T("�޸�����"));
		return;
	}
	plateDao.update(plate);//�������ݿ�����

	////���޸ĺ�ĳ�����Ϣ��ʾ���б���
	*plates[NowID] = plate;
	serveList.SetItemText(NowID, 0,carNum);
	serveList.SetItemText(NowID, 1, time);
	serveList.SetItemText(NowID, 2, path);
	NowID = -1;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTrafficMonitorDlg::OnBnClickedFind()
{
	USES_CONVERSION;
	CString info;
	edit_find.GetWindowText(info);//��ȡҪ��ѯ����Ϣ
	plates.swap(plateDao.findByNumber(W2A(info)));
	if (plates.size() == 0)//���û�з���ֵ����ѯ������Ƿ�Ϊ����
	{
		plates = plateDao.findByTime(W2A(info));//�������ڲ�ѯ
		if (plates.size() == 0)//���û�鵽����ʾNot Found
		{
			MessageBox(_T("Not Found"));
			return;
		}
	}
	serveList.DeleteAllItems();//�鵽�ˣ�����������б���
	CString ptime;
	int i = 0;
	for (auto iplate = plates.cbegin(); iplate != plates.cend(); ++iplate,++i)//������ʾ����ѯ��������
	{
		ptime.Format(_T("%ld"), (*iplate)->get_time());
		serveList.InsertItem(i,(CString)(*iplate)->get_number().c_str());
		serveList.SetItemText(i,1,ptime);
		serveList.SetItemText(i,2, (CString)(*iplate)->get_path().c_str());
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTrafficMonitorDlg::OnBnClickedShowAll()
{
	CString ptime;
	plates.swap(plateDao.findAll());
	for (int i = 0; i < plates.size(); ++i)
	{
		ptime.Format(_T("%ld"), plates[i]->get_time());
		serveList.InsertItem(i,(CString)plates[i]->get_number().c_str());
		serveList.SetItemText(i, 1,ptime);
		serveList.SetItemText(i, 2, (CString)plates[i]->get_path().c_str());
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


