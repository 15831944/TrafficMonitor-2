
// TMClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TMClient.h"
#include "TMClientDlg.h"
#include "afxdialogex.h"
#include "Uploader.h"

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


// CTMClientDlg �Ի���



CTMClientDlg::CTMClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TMCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTMClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clientList);
}

BEGIN_MESSAGE_MAP(CTMClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTMClientDlg::OnLvnItemchangedList1)
	ON_COMMAND(ID_32772, &CTMClientDlg::OpenFile)
	ON_COMMAND(ID_32771, &CTMClientDlg::HelpInformation)
	ON_BN_CLICKED(IDC_BUTTON1, &CTMClientDlg::OnBnClickedUpload)
END_MESSAGE_MAP()


// CTMClientDlg ��Ϣ�������

BOOL CTMClientDlg::OnInitDialog()
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
	CRect rect;
	clientList.GetClientRect(&rect);
	clientList.SetExtendedStyle(clientList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	clientList.InsertColumn(0, _T("�ļ���"), LVCFMT_CENTER, rect.Width() / 2, 0);
	clientList.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, rect.Width() / 2, 1);

	//CRgn rgntmp;
	//RECT rc;
	//GetClientRect(&rc);
	//rgntmp.CreateRoundRectRgn(rc.left + 3, rc.top + 3, rc.right - rc.left, rc.bottom - rc.top - 3, 6, 6);
	//SetWindowRgn(rgntmp, TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTMClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTMClientDlg::OnPaint()
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
HCURSOR CTMClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTMClientDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NMLISTVIEW *pnml = (NMLISTVIEW*)pNMHDR;
	CString str;
	if (-1 != pnml->iItem)
		str = clientList.GetItemText(pnml->iItem, 0);//��ȡ��ַ
	CImage image;
	image.Load(str);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����
	CRect rectControl;                        //�ؼ����ζ���
	CRect rectPicture;                        //ͼƬ���ζ���

	int x = image.GetWidth();
	int y = image.GetHeight();
	//Picture Control��IDΪIDC_IMAGE
	CWnd  *pWnd = GetDlgItem(IDC_STATIC);
	pWnd->GetClientRect(rectControl);


	CDC *pDc = GetDlgItem(IDC_STATIC)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_STATIC))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);                //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������

	image.Destroy();
	pWnd->ReleaseDC(pDc);

	*pResult = 0;
}


void CTMClientDlg::OpenFile()  // �˵���  ���ļ�  Ԥ�� ѡ��
{
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, _T("Picture files(*.bmp;*.jpg;*.jpeg;*.png;*.gif)|*.bmp;*.jpg;*.jpeg;*.png;*.gif|"), NULL);
	//�ļ�������
	USES_CONVERSION;//unicode  ������CString ת��Ϊstd����string
	if (filedlg.DoModal() == IDOK)//����ѡ��
	{
		POSITION pos;
		CString path;
		pos = filedlg.GetStartPosition();
		while (pos != NULL)
		{
			
		     path =filedlg.GetNextPathName(pos);//��ȡ����ļ�·��	
			clientList.InsertItem(fileNum, path);   //�����ļ�·����list control
			clientList.SetItemText(fileNum, 1, _T("0"));
			filename.push_back(W2A(path.Mid(path.ReverseFind('\\') + 1)));
			++fileNum;
		}
		filepath =W2A(path.Mid(0,path.ReverseFind('\\')));	
	}

}


void CTMClientDlg::HelpInformation()//������� --�汾��Ϣ   ��ʾ�汾��Ϣ
{
	CDialog *dlg = new CDialog;
	dlg->Create(IDD_ABOUTBOX, this);//�汾��Ϣ
	dlg->ShowWindow(SW_SHOW);
	// TODO: �ڴ���������������
}


void CTMClientDlg::OnBnClickedUpload()
{
	Uploader uploadFile;
	uploadFile.batch_upload(filepath, filename);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
