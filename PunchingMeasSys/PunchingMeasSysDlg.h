
// PunchingMeasSysDlg.h : ��� ����
//

#pragma once


#include "Vision.h"

// CPunchingMeasSysDlg ��ȭ ����
class CPunchingMeasSysDlg : public CDialog
{

	BOOL FileBrowse(CString& sPath);

// �����Դϴ�.
public:
	CPunchingMeasSysDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CVision *m_pVision;
	UCHAR *m_pCamMstModelImg;

	void InitVision();
	void ShowModel(CString sPath);
	void ShowTarget(CString sPath);
	BOOL Judge();
	BOOL LoadCamMstModelImgFile(CString sPath);
	void DispResultBlob();

	void ShowModel2(CString sPath);
	void ObjectSkeleton();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUNCHINGMEASSYS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModel();
	afx_msg void OnBnClickedBtnTarget();
	// �̹����� ���ȼ��� ũ��[������ mm]
	double m_dPixelRes; // Camera Pixel Resolution
	double m_dSetJudgeScore;
	double m_dSetPmAngle;
	double m_dSetPmScore;
	int m_nSetPmPosX;
	int m_nSetPmPosY;

	// CamMaster Info
	BOOL m_bUseCamMstModel;

	afx_msg void OnBnClickedBtnJudge();
	afx_msg void OnChangeEditSetJudgeScore();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnBlob();
	afx_msg void OnBnClickedBtnModel2();
	afx_msg void OnBnClickedBtnThinning();
	afx_msg void OnBnClickedBtnTopHat();
	afx_msg void OnBnClickedBtnSegmentation();
	afx_msg void OnBnClickedBtnReconstruction();
	afx_msg void OnBnClickedBtnThead();
	afx_msg void OnBnClickedBtnMeasure();
};
