
// PunchingMeasSysDlg.h : 헤더 파일
//

#pragma once


#include "Vision.h"

// CPunchingMeasSysDlg 대화 상자
class CPunchingMeasSysDlg : public CDialog
{

	BOOL FileBrowse(CString& sPath);

// 생성입니다.
public:
	CPunchingMeasSysDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

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

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUNCHINGMEASSYS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModel();
	afx_msg void OnBnClickedBtnTarget();
	// 이미지의 한픽셀의 크기[단위는 mm]
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
