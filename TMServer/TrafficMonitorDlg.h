
// TrafficMonitorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Plate.h"
#include "PlateDao.h"
#include "afxwin.h"


// CTrafficMonitorDlg �Ի���
class CTrafficMonitorDlg : public CDialogEx
{
// ����
public:
	CTrafficMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAFFICMONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Plate plate;//�������ƺ���Ϣ
	PlateDao plateDao;
	CListCtrl serveList;
	int NowID=-1;//ѡ���еı�ʶ��
	std::vector<Plate *> plates;//�����ʾ���������г��ƺ���Ϣ
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedFind();
	afx_msg void OnBnClickedShowAll();
	CEdit Edit_carNum;//���ƺ�
	CEdit Edit_time;//�ϴ�ʱ��
	CEdit Edit_path;//�ϴ�·��
	CEdit edit_find;
};
