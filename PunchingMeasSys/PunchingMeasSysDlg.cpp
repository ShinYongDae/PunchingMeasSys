
// PunchingMeasSysDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PunchingMeasSys.h"
#include "PunchingMeasSysDlg.h"
#include "afxdialogex.h"

#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CPunchingMeasSysDlg 대화 상자



CPunchingMeasSysDlg::CPunchingMeasSysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PUNCHINGMEASSYS_DIALOG, pParent)
	, m_dPixelRes(0.008)
	, m_dSetJudgeScore(70)
	, m_dSetPmAngle(0)
	, m_dSetPmScore(0)
	, m_nSetPmPosX(0)
	, m_nSetPmPosY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pVision = NULL;

	m_bUseCamMstModel = TRUE;
	m_pCamMstModelImg = NULL;
}

void CPunchingMeasSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RES, m_dPixelRes);
	DDV_MinMaxDouble(pDX, m_dPixelRes, 0.0, 1);
	DDX_Text(pDX, IDC_EDIT_SET_JUDGE_SCORE, m_dSetJudgeScore);
	DDV_MinMaxDouble(pDX, m_dSetJudgeScore, 0.0, 100.0);
	DDX_Text(pDX, IDC_STC_SET_PM_ANGL, m_dSetPmAngle);
	DDV_MinMaxDouble(pDX, m_dSetPmAngle, -360.0, 360.0);
	DDX_Text(pDX, IDC_STC_SET_PM_SCORE, m_dSetPmScore);
	DDV_MinMaxDouble(pDX, m_dSetPmScore, 0.0, 100.0);
	DDX_Text(pDX, IDC_STC_SET_PM_X, m_nSetPmPosX);
	DDV_MinMaxInt(pDX, m_nSetPmPosX, 0, 100);
	DDX_Text(pDX, IDC_STC_SET_PM_Y, m_nSetPmPosY);
	DDV_MinMaxInt(pDX, m_nSetPmPosY, 0, 100);
}

BEGIN_MESSAGE_MAP(CPunchingMeasSysDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MODEL, &CPunchingMeasSysDlg::OnBnClickedBtnModel)
	ON_BN_CLICKED(IDC_BTN_TARGET, &CPunchingMeasSysDlg::OnBnClickedBtnTarget)
	ON_BN_CLICKED(IDC_BTN_JUDGE, &CPunchingMeasSysDlg::OnBnClickedBtnJudge)
	ON_EN_CHANGE(IDC_EDIT_SET_JUDGE_SCORE, &CPunchingMeasSysDlg::OnChangeEditSetJudgeScore)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_BLOB, &CPunchingMeasSysDlg::OnBnClickedBtnBlob)
	ON_BN_CLICKED(IDC_BTN_MODEL2, &CPunchingMeasSysDlg::OnBnClickedBtnModel2)
	ON_BN_CLICKED(IDC_BTN_THINNING, &CPunchingMeasSysDlg::OnBnClickedBtnThinning)
	ON_BN_CLICKED(IDC_BTN_TOP_HAT, &CPunchingMeasSysDlg::OnBnClickedBtnTopHat)
	ON_BN_CLICKED(IDC_BTN_SEGMENTATION, &CPunchingMeasSysDlg::OnBnClickedBtnSegmentation)
	ON_BN_CLICKED(IDC_BTN_RECONSTRUCTION, &CPunchingMeasSysDlg::OnBnClickedBtnReconstruction)
	ON_BN_CLICKED(IDC_BTN_THEAD, &CPunchingMeasSysDlg::OnBnClickedBtnThead)
	ON_BN_CLICKED(IDC_BTN_MEASURE, &CPunchingMeasSysDlg::OnBnClickedBtnMeasure)
END_MESSAGE_MAP()


// CPunchingMeasSysDlg 메시지 처리기

BOOL CPunchingMeasSysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitVision();

	GetDlgItem(IDC_STC_VISION)->ShowWindow(SW_HIDE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPunchingMeasSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPunchingMeasSysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPunchingMeasSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPunchingMeasSysDlg::InitVision()
{
	// Select Live Camera Viewer
	HWND hCtrlV0[4] = { 0 };
	hCtrlV0[0] = GetDlgItem(IDC_STC_VISION)->GetSafeHwnd();
	MIL_ID MilSys = M_NULL;
	m_pVision = new CVision(0, MilSys, hCtrlV0, this);
	MilSys = m_pVision->GetSystemID();


	// Select Model Viewer
	HWND hW;
	CRect rt;

	if (m_bUseCamMstModel)
	{
		hW = GetDlgItem(IDC_PIC_CAM_MODEL)->GetSafeHwnd();
		GetDlgItem(IDC_PIC_CAM_MODEL)->GetWindowRect(&rt);
		m_pVision->SelDispCamMstModelCrop(hW, rt);
	}

	hW = GetDlgItem(IDC_PIC_MODEL)->GetSafeHwnd();
	GetDlgItem(IDC_PIC_MODEL)->GetWindowRect(&rt);
	m_pVision->SelDispModel(hW, rt);

	//m_pVision->SetOvrCadFontSz(nIdxMkInfo);

	hW = GetDlgItem(IDC_PIC_TARGET)->GetSafeHwnd();
	GetDlgItem(IDC_PIC_TARGET)->GetWindowRect(&rt);
	m_pVision->SelDispTarget(hW, rt);

	hW = GetDlgItem(IDC_STC_VISION2)->GetSafeHwnd();
	GetDlgItem(IDC_STC_VISION2)->GetWindowRect(&rt);
	m_pVision->SelDispModel2(hW, rt);
}


BOOL CPunchingMeasSysDlg::FileBrowse(CString& sPath)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	static TCHAR BASED_CODE szFilter[] = _T("Mst Files (*.tif)|*.tif|All Files (*.*)|*.*||");

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12를 Win2k Style로 다이얼로그 박스가 Open됨.

	// Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}


void CPunchingMeasSysDlg::OnBnClickedBtnModel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STC_PATH_MODEL)->SetWindowText(sPath);
	ShowModel(sPath);
}

void CPunchingMeasSysDlg::OnBnClickedBtnTarget()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STC_PATH_TARGET)->SetWindowText(sPath);
	ShowTarget(sPath);
}

void CPunchingMeasSysDlg::ShowModel(CString sPath)
{
	CFileFind findfile;
	if (findfile.FindFile(sPath))
	{
		if (m_bUseCamMstModel)
		{
			if (LoadCamMstModelImgFile(sPath)) // TRUE : m_pCamMstModelImg 에 이미지 로딩 완료.
			{
				m_pVision->Crop();
				//m_pVision->Blob();
				m_pVision->ShowBlobModel(); // Show 100 x 100 Image
			}
			else
			{
				AfxMessageBox(_T("m_pCamMstModelImg 에 이미지 로딩 실패"));
				return;
			}
		}
		else
		{
			if (m_pVision)
				m_pVision->ShowModel(sPath, m_bUseCamMstModel);
		}
	}
}

void CPunchingMeasSysDlg::ShowTarget(CString sPath)
{
	CFileFind findfile;
	if (findfile.FindFile(sPath))
	{
		if (m_pVision)
			m_pVision->ShowTarget(sPath);
	}
}



void CPunchingMeasSysDlg::OnBnClickedBtnJudge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Judge();
}

BOOL CPunchingMeasSysDlg::Judge()
{
	BOOL bSameImg;
	stPtMtRst stRst;
	if (!m_pVision->Judge(stRst))
	{
		GetDlgItem(IDC_STC_JUDGE)->SetWindowText(_T("실패"));
		return FALSE;
	}

	CString sVal;
	sVal.Format(_T("%.3f"), stRst.dX);
	GetDlgItem(IDC_STC_SET_PM_X)->SetWindowText(sVal);
	sVal.Format(_T("%.3f"), stRst.dY);
	GetDlgItem(IDC_STC_SET_PM_Y)->SetWindowText(sVal);
	sVal.Format(_T("%.3f"), stRst.dAngle);
	GetDlgItem(IDC_STC_SET_PM_ANGL)->SetWindowText(sVal);
	sVal.Format(_T("%.3f"), stRst.dScore);
	GetDlgItem(IDC_STC_SET_PM_SCORE)->SetWindowText(sVal);

	if (stRst.dScore >= m_dSetJudgeScore)
		bSameImg = TRUE;
	else
		bSameImg = FALSE;

	if (bSameImg)
	{
		GetDlgItem(IDC_STC_JUDGE)->SetWindowText(_T("마킹 않됨"));
	}
	else
	{
		GetDlgItem(IDC_STC_JUDGE)->SetWindowText(_T("마킹 됨"));
	}

	return TRUE;
}


void CPunchingMeasSysDlg::OnChangeEditSetJudgeScore()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CPunchingMeasSysDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pCamMstModelImg)
	{
		GlobalFreePtr(m_pCamMstModelImg);
		m_pCamMstModelImg = NULL;
	}

	if (m_pVision)
	{
		delete m_pVision;
		m_pVision = NULL;
	}
}


void CPunchingMeasSysDlg::OnBnClickedBtnBlob()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pVision->Blob();
	//m_pVision->ShowBlobModel();
	DispResultBlob();
}

void CPunchingMeasSysDlg::DispResultBlob()
{
	CString sVal;

	sVal.Format(_T("%d"), m_pVision->BlobRst.nBoxRight -  m_pVision->BlobRst.nBoxLeft);
	GetDlgItem(IDC_STC_BLOB_SIZE_X)->SetWindowText(sVal);
	sVal.Format(_T("%d"), m_pVision->BlobRst.nBoxBottom - m_pVision->BlobRst.nBoxTop);
	GetDlgItem(IDC_STC_BLOB_SIZE_Y)->SetWindowText(sVal);
}

BOOL CPunchingMeasSysDlg::LoadCamMstModelImgFile(CString sPath)
{
	// CAM-Master File Copy and Local File Load

	TCHAR szCamMstModel[MAX_PATH];
	CFile file;
	int nFileSize, RSize;

	_stprintf(szCamMstModel, _T("%s"), sPath);

	if (!file.Open(szCamMstModel, CFile::modeRead | CFile::typeBinary))
	{
		if (!file.Open(szCamMstModel, CFile::modeRead | CFile::typeBinary))
		{
			return(FALSE);
		}
	}

	nFileSize = file.GetLength();
	if (nFileSize != 0)
	{
		if (m_pCamMstModelImg)
		{
			GlobalFreePtr(m_pCamMstModelImg);
			m_pCamMstModelImg = NULL;
		}

		m_pCamMstModelImg = (UCHAR *)GlobalAllocPtr(GMEM_MOVEABLE, nFileSize);
	}

	RSize = file.Read((void *)m_pCamMstModelImg, nFileSize);
	if (RSize != nFileSize)
	{
		file.Close();
		return(FALSE);
	}

	file.Close();
	return TRUE;
}

void CPunchingMeasSysDlg::OnBnClickedBtnModel2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STC_PATH_MODEL2)->SetWindowText(sPath);
	ShowModel2(sPath);
}

void CPunchingMeasSysDlg::ShowModel2(CString sPath)
{
	CFileFind findfile;
	if (findfile.FindFile(sPath))
	{
		if (m_pVision)
			m_pVision->ShowModel2(sPath);
	}
}


void CPunchingMeasSysDlg::OnBnClickedBtnThinning()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ObjectSkeleton();
}

void CPunchingMeasSysDlg::ObjectSkeleton()
{
	if (m_pVision)
		m_pVision->ObjectSkeleton();
}

void CPunchingMeasSysDlg::OnBnClickedBtnTopHat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pVision)
		m_pVision->TopHatFiltering();
}


void CPunchingMeasSysDlg::OnBnClickedBtnSegmentation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pVision)
		m_pVision->ObjectSegmentation();
}


void CPunchingMeasSysDlg::OnBnClickedBtnReconstruction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pVision)
		m_pVision->MorphologicalReconstruction();
}


void CPunchingMeasSysDlg::OnBnClickedBtnThead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pVision)
		m_pVision->MThread();
}


void CPunchingMeasSysDlg::OnBnClickedBtnMeasure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pVision)
		m_pVision->SingleMeasurement();
}
