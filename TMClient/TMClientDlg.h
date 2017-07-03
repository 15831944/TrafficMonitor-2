
// TMClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Uploader.h"


// CTMClientDlg �Ի���
class CTMClientDlg : public CDialogEx
{
// ����
public:
	CTMClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TMCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int fileNum = 0;
	int upNum;//��¼���ϴ��ļ���
	std::string  filepath;
	std::vector<std::string> filename;
	CListCtrl clientList;
	Uploader uploadFile;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OpenFile();
	afx_msg void HelpInformation();
	afx_msg void OnBnClickedUpload();
};
