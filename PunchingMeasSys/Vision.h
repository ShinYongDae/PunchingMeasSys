#if !defined(AFX_VISION_H__422BC495_1B91_4BA6_87F5_CBA4276E4598__INCLUDED_)
#define AFX_VISION_H__422BC495_1B91_4BA6_87F5_CBA4276E4598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Vision.h : header file
//

#define USE_VISION


// #define DEF_VIEW_IMG_NUMBER			6
#define DEF_VIEW_IMG_NUMBER			12

#define DEF_IMG_DISP_SIZEX			100
#define DEF_IMG_DISP_SIZEY			100

#define PIN_IMG_DISP_SIZEX			200		// 1pixel is 33um , 6.6mm / 0.033mm = 200 pixel
#define PIN_IMG_DISP_SIZEY			200		// 1pixel is 33um , 6.6mm / 0.033mm = 200 pixel

#define ALIGN_IMG_DISP_SIZEX		200		// 1pixel is 33um , 6.6mm / 0.033mm = 200 pixel
#define ALIGN_IMG_DISP_SIZEY		200		// 1pixel is 33um , 6.6mm / 0.033mm = 200 pixel

#define PCS_IMG_DISP_SIZEX			520		// 1pixel is 33um
#define PCS_IMG_DISP_SIZEY			440		// 1pixel is 33um

#define TIM_CLR_OVERLAY				500


//#include "../Global/MyData.h"
//#include "../Global/GlobalDefine.h"


#ifdef USE_VISION

//#include "Vicdefs.h"
#include "Vic7defs.h"
//#include "FreeImage.h"

#ifdef USE_IDS
#include "CamIds.h"
#endif

#ifdef USE_CREVIS
#include "CamCrevis.h"
#endif

#ifdef USE_IRAYPLE
#include "CamIRayple.h"
#endif


#include "LibMil.h"

//#pragma comment (lib, "vic32ms.lib")
#pragma comment (lib, "lib/vic64.lib")
//#pragma comment(lib, "lib/FreeImage_x64")

#define USE_MIL		1

#define MAX_TRIG	1
#define CAMERA_WIDTH	640
#define CAMERA_HEIGHT	480

/* Minimum and maximum area of blobs. */
// Grab Image Size 100 x 100
#define BLOB_AREA_MIN			100L			// 10 x 10
#define BLOB_AREA_MAX			8100L			// 90 x 90
#define BLOB_CENTER_OFFSET		20L			

#define MIN_BLOB_SIZE_X       2L			
#define MIN_BLOB_SIZE_Y       2L			

// for MThread()
//#define IMAGE_WIDTH        1024
//#define IMAGE_HEIGHT       1024
#define IMAGE_WIDTH        256L
#define IMAGE_HEIGHT       240L
#define STRING_LENGHT_MAX  40
#define STRING_POS_X       10
#define STRING_POS_Y       220
#define DRAW_RADIUS_NUMBER 5
#define DRAW_RADIUS_STEP   10
#define DRAW_CENTER_POSX   196
#define DRAW_CENTER_POSY   180

typedef struct stPtMtRst
{
	double dX, dY, dAngle, dScore;
} PT_MT_RST;

typedef struct stBlobRst
{
	int nBlobTotal;
	int nBoxArea;
	double dCenterX, dCenterY;
	int nBoxLeft, nBoxRight, nBoxTop, nBoxBottom;
} BLOB_RST;

/* Thread parameters structure. */
typedef struct ThreadParam
{
	MIL_ID Id;
	MIL_ID System;
	MIL_ID OrgImage;
	MIL_ID SrcImage;
	MIL_ID DstImage;
	MIL_ID ReadyEvent;
	MIL_ID DoneEvent;
	MIL_INT NumberOfIteration;
	MIL_INT Radius;
	MIL_INT Exit;
	MIL_INT LicenseModules;
	struct ThreadParam *SlaveThreadParam;
} THREAD_PARAM;

/////////////////////////////////////////////////////////////////////////////
// CVision window

class CVision : public CWnd
{
	int m_nIdx;
	HWND m_hCtrl[4];
	CWnd *m_pParent;
	MIL_ID m_MilSysId;

	int m_nTest;
	//double m_dEnc[MAX_AXIS], m_dBufEnc, m_dFdEnc;

	CLibMilBuf *m_pMilBufModel, *m_pMilBufTarget, *m_pMilBufModel2;
	CLibMilDisp *m_pMilDispModel, *m_pMilDispTarget, *m_pMilDispModel2;
	CLibMilDraw *m_pMilBufOverlayModel2, *m_pMilBufDelOverlayModel2;
	CLibMilDraw *m_pMilBufOverlayTarget, *m_pMilBufDelOverlayTarget;

	MIL_ID m_MilBufCamMstModel, m_MilBufCamMstModelCrop;
	CLibMilBuf *m_pMilBufCamMstModelCrop;
	CLibMilDisp *m_pMilDispCamMstModelCrop;

	CLibMilBuf *m_pMilBufBlobCamMstModelCropRzImg;

#ifdef USE_IRAYPLE
	CCamIRayple *m_pIRayple;
#endif

#ifdef USE_IDS
	CCamIds *m_pIds[2];
#endif

#ifdef USE_CREVIS
	CCamCrevis *m_pCrevis[2]; // Max(2)
#endif

	//CLibMil *m_pMil;
	int m_nTrig[2];

	/////////////////////////////////////////////////////////////////////////////////

	CLibMilBuf *m_pMilBufCad[DEF_VIEW_IMG_NUMBER], *m_pMilBufDef[DEF_VIEW_IMG_NUMBER];
	CLibMilDisp *m_pMilDispCad[DEF_VIEW_IMG_NUMBER], *m_pMilDispDef[DEF_VIEW_IMG_NUMBER];
	CLibMilDraw *m_pMilOvrCad[DEF_VIEW_IMG_NUMBER], *m_pMilOvrDef[DEF_VIEW_IMG_NUMBER];
	CLibMilDraw *m_pMilDelOvrCad[DEF_VIEW_IMG_NUMBER], *m_pMilDelOvrDef[DEF_VIEW_IMG_NUMBER];

	CLibMilDisp *m_pMilDispPin;// , *m_pMilDispAlign;//, *m_pMilDispPcs;
	CLibMilBuf *m_pMilBufPin, *m_pMilBufAlign;//, *m_pMilBufPcs;
	CLibMilDraw *m_pMilPinOverlay;
	CLibMilDraw *m_pMilPinOverlayDelete;

	MIL_ID MilCADImgBuf, MilBufCADTemp;
	MIL_ID MilBufPinTemp, MilPinImgBuf;
	//MIL_ID MilBufAlignTemp[2], MilAlignImgBuf[2];	// 2 points
	MIL_ID MilBufAlignTemp[4], MilAlignImgBuf[4];	// 4 points

	int m_nCenterMarkLineLength;
	int m_nDisplayCenterX;
	int m_nDisplayCenterY;
	int m_nCenterMarkSpaceLength;

	CPoint m_ptDisplayAxisPosOffset;
	int m_nDisplayAxisPosLineHeight;
	double m_dFontSizePixelX, m_dFontSizePixelY;

	int m_nPinCtrX, m_nPinCtrY, m_nPinCrsLen;


	void DrawCross(int nCenterX, int nCenterY, int nLineLength);
	void SetClrOverlay();

	BOOL GrabIRayple(int nPos, BOOL bDraw = TRUE);
	BOOL GrabCrevis(int nPos, BOOL bDraw = TRUE);
	BOOL GrabIds(int nPos, BOOL bDraw = TRUE);


// Construction
public:
	CVision(int nIdx, MIL_ID MilSysId, HWND *hCtrl, CWnd* pParent=NULL); // hCtrl : Max(4)
	CCriticalSection m_cs;

	void ShowModel(CString sPath, BOOL bUseCamMstModel = TRUE);
	void ShowTarget(CString sPath);
	void SelDispModel(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void SelDispTarget(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void SelDispCamMstModelCrop(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void FreeDispModel(HWND hDispCtrl, CRect rtDispCtrl,  int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void FreeDispTarget(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void FreeDispCamMstModelCrop(HWND hDispCtrl, CRect rtDispCtrl,  int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void ClrDispModel();
	void ClrDispTarget();

	void SelDispModel2(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void ShowModel2(CString sPath);
	void ObjectSkeleton();
	void AllocGenPseudoColorLUT(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_INT StartIndex, MIL_INT EndIndex, MIL_ID &MilPseudoColorLut, MIL_ID MilOverlay);
	void TopHatFiltering();
	void AllocDisplayImage(MIL_ID MilSystem, MIL_ID MilSrcImage, MIL_ID MilDisplay, MIL_ID &MilDispProcImage, MIL_ID &MilOverlayImage);
	void ObjectSegmentation();
	void MorphologicalReconstruction();
	void MorphologicalReconstruction(const MIL_TEXT_CHAR *SrcFilename, MIL_ID MilSystem, MIL_ID MilDisplay);
	void MorphoReconstruction(MIL_ID MilSystem, MIL_ID MilSrcImage, MIL_ID MilSeedImage, MIL_ID MilDstImage, MIL_INT MaxIter);

	void MThread();
	///* Function prototypes. */
	//MIL_UINT32 MFTYPE TopThread(void *TPar);
	//MIL_UINT32 MFTYPE BotLeftThread(void *TPar);
	//MIL_UINT32 MFTYPE BotRightThread(void *TPar);
	//void BalanceThreadScheduling();

// Attributes
public:
	CLibMil *m_pMil;
	stPtMtRst PtMtRst;
	stBlobRst BlobRst;

// Operations
public:
	CWnd* GetParent();

	BOOL StartLive(int nIdx=0);
	BOOL StopLive(int nIdx=0);

	// from IDS
	LRESULT OnUEyeMessage0(WPARAM wParam, LPARAM lParam);
	LRESULT OnUEyeMessage1(WPARAM wParam, LPARAM lParam);

	// from Crevis


	void DisplaySelect(int nKind, HWND hDispCtrl, CRect rtDispCtrl, int nIdx); // nKind : CAD_image[0], Defect_image[1]

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MIL_ID GetSystemID();

	void SelDispCad(HWND hDispCtrl, CRect rtDispCtrl, int nIdx, int nDisplayFitMode=DISPLAY_FIT_MODE_CENTERVIEW);
	void FreeDispCad(HWND hDispCtrl, CRect rtDispCtrl, int nIdx, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void SelDispDef(HWND hDispCtrl, CRect rtDispCtrl, int nIdx, int nDisplayFitMode=DISPLAY_FIT_MODE_CENTERVIEW);
	void FreeDispDef(HWND hDispCtrl, CRect rtDispCtrl, int nIdx, int nDisplayFitMode = DISPLAY_FIT_MODE_CENTERVIEW);
	void SelDispPin(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode);
	void SelDispAlign(HWND hDispCtrl, CRect rtDispCtrl, int nDisplayFitMode);

	void SetOvrCadFontSz(int nIdxMkInfo);
	void InitCADBuf(int nLayer);
	void InitDispDef();
	void ClrDispCad();
	void ClrDispDef();

	void ShiftDisp();
	void ShowDispCad(int nIdxMkInfo, int nSerial, int nLayer, int nIdxDef);
	void ShowDispDef(int nIdxMkInfo, int nSerial, int nLayer, int nDefPcs);
	void ShowOvrCad(int nIdxMkInfo, int nSerial);
	void ShowDispPin(int nLayer);
	void ShowDispAlign();

	void CropCadImg(int nIdxMkInfo, int nSerial, int nLayer, int nIdxDef);
	void CropCadImg(short cell, short cx, short cy, int BufID, int nLayer);
	BOOL SetCADCoord(int CellNum, int StX, int StY, int Coord, int nLayer);
	void LoadCADBuf(int CurrCell, long OrgStX, long OrgStY, long DesStX, long DesStY, long SizeX, long SizeY, int nLayer);
	BOOL VicFileLoadFromMem(MIL_ID MilImage, UCHAR *pCADImg, TiffData &tdat);
	BOOL VicGetImgInfo(UCHAR *pCADImg, TiffData &tdat);
	void ClrOvrCad(int nIdx);

	void InitPinBuf();
	void LoadPinBuf(int nLayer);
	void DrawCrossOnPin(int nCenterX, int nCenterY, int nLineLength);
	BOOL ClearPinCenterMarkArea(int nCenterX, int nCenterY, int nLineLength);

	void InitAlignBuf();
	void LoadAlignBuf();

	void ClearOverlay();
	void DrawCenterMark(int nMode=0); // 0: Cross, 1: Rect, 2: None
	void DrawCross();
	BOOL ClearCenterMarkArea();
	void DrawText(CString str, long lX, long lY, long lColor);
	void SetDispAxisPos();
	void DispAxisPos(BOOL bForceWrite=FALSE);

	double CalcCameraPixelSize();
	BOOL Grab(int nPos, BOOL bDraw=TRUE);
	void GetCameraSize(int &nX, int &nY);
	void GetIdsSize(int &nX, int &nY);
	void GetCrevisSize(int &nX, int &nY);
	void GetIRaypleSize(int &nX, int &nY);

	BOOL SaveMkImg(CString sPath);
	void SaveCadImg(int nIdxMkInfo, CString sPath); // (ȭ���� IDC �ε���, ������ ���� Path)

	// ITS
	//CLibMilBuf *m_pMilBufCad[DEF_VIEW_IMG_NUMBER], *m_pMilBufDef[DEF_VIEW_IMG_NUMBER];
	//CLibMilDisp *m_pMilDispCad[DEF_VIEW_IMG_NUMBER], *m_pMilDispDef[DEF_VIEW_IMG_NUMBER];
	//CLibMilDraw *m_pMilOvrCad[DEF_VIEW_IMG_NUMBER], *m_pMilOvrDef[DEF_VIEW_IMG_NUMBER];
	//CLibMilDraw *m_pMilDelOvrCad[DEF_VIEW_IMG_NUMBER], *m_pMilDelOvrDef[DEF_VIEW_IMG_NUMBER];

	double m_dCamMstPixelRes; // CamMasterPixel Resolution
	int m_nCamMstCropSize;

	BOOL Judge(stPtMtRst &stRst);
	void LoadCamMstModelBuf();
	void InitCamMstModelBuf();
	BOOL Crop();
	BOOL Blob();
	BOOL ShowBlobModel();

	void ClrDispModel2();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVision)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVision();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVision)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);// (UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#else

#include "../Process/FreeImage.h"
#pragma comment(lib, "lib/FreeImage_x64")

#endif // #ifdef USE_VISION

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISION_H__422BC495_1B91_4BA6_87F5_CBA4276E4598__INCLUDED_)
