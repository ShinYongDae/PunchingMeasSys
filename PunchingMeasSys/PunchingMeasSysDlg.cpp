
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



///*******************************************************************************/
///*
//* File name: MBlob.cpp
//* Location: ...\Matrox Imaging\MILxxx\Examples\General\Mblob\C++
//*
//* Synopsis:  This program loads an image of some nuts, bolts and washers,
//*            determines the number of each of these, finds and marks
//*            their center of gravity using the Blob analysis module.
//*/
//#include <mil.h>  
//#include <malloc.h>
//
///* Target MIL image file specifications. */
//#define IMAGE_FILE            M_IMAGE_PATH MIL_TEXT("BoltsNutsWashers.mim")
//#define IMAGE_THRESHOLD_VALUE 26L 
//
///* Minimum and maximum area of blobs. */
//#define MIN_BLOB_AREA         50L 
//#define MAX_BLOB_AREA         50000L
//
///* Radius of the smallest particles to keep. */
//#define MIN_BLOB_RADIUS       3L
//
///* Minimum hole compactness corresponding to a washer. */
//#define MIN_COMPACTNESS       1.5
//
//
//int MosMain(void)
//{
//	MIL_ID     MilApplication,                 /* Application identifier.            */
//		MilSystem,                      /* System identifier.                 */
//		MilDisplay,                     /* Display identifier.                */
//		MilImage,                       /* Image buffer identifier.           */
//		MilGraphicList,                 /* Graphic list identifier.           */
//		MilBinImage,                    /* Binary image buffer identifier.    */
//		MilBlobResult,                  /* Blob result buffer identifier.     */
//		MilBlobFeatureList;             /* Feature list identifier.           */
//	MIL_INT    TotalBlobs,                     /* Total number of blobs.             */
//		BlobsWithHoles,                 /* Number of blobs with holes.        */
//		BlobsWithRoughHoles,            /* Number of blobs with rough holes.  */
//		n,                              /* Counter.                           */
//		SizeX,                          /* Size X of the source buffer.       */
//		SizeY;                          /* Size Y of the source buffer.       */
//
//	MIL_DOUBLE *CogX,                          /* X coordinate of center of gravity. */
//		*CogY;                          /* Y coordinate of center of gravity. */
//
//										/* Allocate defaults. */
//	MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);
//
//	/* Restore source image into image buffer. */
//	MbufRestore(IMAGE_FILE, MilSystem, &MilImage);
//
//	/* Allocate a graphic list to hold the subpixel annotations to draw. */
//	MgraAllocList(MilSystem, M_DEFAULT, &MilGraphicList);
//
//	/* Associate the graphic list to the display. */
//	MdispControl(MilDisplay, M_ASSOCIATED_GRAPHIC_LIST_ID, MilGraphicList);
//
//	/* Display the buffer. */
//	MdispSelect(MilDisplay, MilImage);
//
//	/* Allocate a binary image buffer for fast processing. */
//	MbufInquire(MilImage, M_SIZE_X, &SizeX);
//	MbufInquire(MilImage, M_SIZE_Y, &SizeY);
//	MbufAlloc2d(MilSystem, SizeX, SizeY, 1 + M_UNSIGNED, M_IMAGE + M_PROC, &MilBinImage);
//
//	/* Pause to show the original image. */
//	MosPrintf(MIL_TEXT("\nBLOB ANALYSIS:\n"));
//	MosPrintf(MIL_TEXT("--------------\n\n"));
//	MosPrintf(MIL_TEXT("This program determines the number of bolts, nuts and washers\n"));
//	MosPrintf(MIL_TEXT("in the image and finds their center of gravity.\n"));
//	MosPrintf(MIL_TEXT("Press <Enter> to continue.\n\n"));
//	MosGetch();
//
//	/* Binarize image. */
//	MimBinarize(MilImage, MilBinImage, M_FIXED + M_GREATER_OR_EQUAL,
//		IMAGE_THRESHOLD_VALUE, M_NULL);
//
//	/* Remove small particles and then remove small holes. */
//	MimOpen(MilBinImage, MilBinImage, MIN_BLOB_RADIUS, M_BINARY);
//	MimClose(MilBinImage, MilBinImage, MIN_BLOB_RADIUS, M_BINARY);
//
//	/* Allocate a feature list. */
//	MblobAllocFeatureList(MilSystem, &MilBlobFeatureList);
//
//	/* Enable the Area and Center Of Gravity feature calculation. */
//	MblobSelectFeature(MilBlobFeatureList, M_AREA);
//	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY);
//
//	/* Allocate a blob result buffer. */
//	MblobAllocResult(MilSystem, &MilBlobResult);
//
//	/* Calculate selected features for each blob. */
//	MblobCalculate(MilBinImage, M_NULL, MilBlobFeatureList, MilBlobResult);
//
//	/* Exclude blobs whose area is too small. */
//	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL,
//		MIN_BLOB_AREA, M_NULL);
//
//	/* Get the total number of selected blobs. */
//	MblobGetNumber(MilBlobResult, &TotalBlobs);
//	MosPrintf(MIL_TEXT("There are %ld objects "), TotalBlobs);
//
//	/* Read and print the blob's center of gravity. */
//	if ((CogX = (MIL_DOUBLE *)malloc(TotalBlobs * sizeof(MIL_DOUBLE))) &&
//		(CogY = (MIL_DOUBLE *)malloc(TotalBlobs * sizeof(MIL_DOUBLE)))
//		)
//	{
//		/* Get the results. */
//		MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_X, CogX);
//		MblobGetResult(MilBlobResult, M_CENTER_OF_GRAVITY_Y, CogY);
//
//		/* Print the center of gravity of each blob. */
//		MosPrintf(MIL_TEXT("and their centers of gravity are:\n"));
//		for (n = 0; n < TotalBlobs; n++)
//			MosPrintf(MIL_TEXT("Blob #%ld: X=%5.1f, Y=%5.1f\n"), n, CogX[n], CogY[n]);
//		free(CogX);
//		free(CogY);
//	}
//	else
//		MosPrintf(MIL_TEXT("\nError: Not enough memory.\n"));
//
//	/* Draw a cross at the center of gravity of each blob. */
//	MgraColor(M_DEFAULT, M_COLOR_RED);
//	MblobDraw(M_DEFAULT, MilBlobResult, MilGraphicList, M_DRAW_CENTER_OF_GRAVITY,
//		M_INCLUDED_BLOBS, M_DEFAULT);
//
//	/* Reverse what is considered to be the background so that
//	* holes are seen as being blobs.
//	*/
//	MblobControl(MilBlobResult, M_FOREGROUND_VALUE, M_ZERO);
//
//	/* Add a feature to distinguish between types of holes. Since area
//	* has already been added to the feature list, and the processing
//	* mode has been changed, all blobs will be re-included and the area
//	* of holes will be calculated automatically.
//	*/
//	MblobSelectFeature(MilBlobFeatureList, M_COMPACTNESS);
//
//	/* Calculate selected features for each blob. */
//	MblobCalculate(MilBinImage, M_NULL, MilBlobFeatureList, MilBlobResult);
//
//	/* Exclude small holes and large (the area around objects) holes. */
//	MblobSelect(MilBlobResult, M_EXCLUDE, M_AREA, M_OUT_RANGE,
//		MIN_BLOB_AREA, MAX_BLOB_AREA);
//
//	/* Get the number of blobs with holes. */
//	MblobGetNumber(MilBlobResult, &BlobsWithHoles);
//
//	/* Exclude blobs whose holes are compact (i.e. nuts). */
//	MblobSelect(MilBlobResult, M_EXCLUDE, M_COMPACTNESS, M_LESS_OR_EQUAL,
//		MIN_COMPACTNESS, M_NULL);
//
//	/* Get the number of blobs with holes that are NOT compact. */
//	MblobGetNumber(MilBlobResult, &BlobsWithRoughHoles);
//
//	/* Print results. */
//	MosPrintf(MIL_TEXT("\nIdentified objects:\n"));
//	MosPrintf(MIL_TEXT("%ld bolts\n"), TotalBlobs - BlobsWithHoles);
//	MosPrintf(MIL_TEXT("%ld nuts\n"), BlobsWithHoles - BlobsWithRoughHoles);
//	MosPrintf(MIL_TEXT("%ld washers\n\n"), BlobsWithRoughHoles);
//	MosPrintf(MIL_TEXT("Press <Enter> to end.\n\n"));
//	MosGetch();
//
//	/* Free all allocations. */
//	MgraFree(MilGraphicList);
//	MblobFree(MilBlobResult);
//	MblobFree(MilBlobFeatureList);
//	MbufFree(MilBinImage);
//	MbufFree(MilImage);
//	MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);
//
//	return 0;
//}
//

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
/*	
	_stprintf(FileNLoc, _T("%s"), PATH_ALIGN0_IMG);
	if (m_sLayerUp.IsEmpty())
	{
		if (m_sPathCamSpecDir.Right(1) != "\\")
			strFileNAlign.Format(_T("%s\\%s\\%s-md0.tif"), m_sPathCamSpecDir, m_sModel, m_sLayer);
		else
			strFileNAlign.Format(_T("%s%s\\%s-md0.tif"), m_sPathCamSpecDir, m_sModel, m_sLayer);
	}
	else
	{
		if (m_sPathCamSpecDir.Right(1) != "\\")
			strFileNAlign.Format(_T("%s\\%s\\%s-md0.tif"), m_sPathCamSpecDir, m_sModel, m_sLayerUp);
		else
			strFileNAlign.Format(_T("%s%s\\%s-md0.tif"), m_sPathCamSpecDir, m_sModel, m_sLayerUp);
	}
	_stprintf(FileNAlign, _T("%s"), strFileNAlign);

	if(!CopyFile((LPCTSTR)FileNAlign, (LPCTSTR)FileNLoc, FALSE))
	{
		if (!CopyFile((LPCTSTR)FileNAlign, (LPCTSTR)FileNLoc, FALSE))
		{
			if (!CopyFile((LPCTSTR)FileNAlign, (LPCTSTR)FileNLoc, FALSE))
			{
				prcStopF = TRUE;
			}
		}
	}
*/	


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
