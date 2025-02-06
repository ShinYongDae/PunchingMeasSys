
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


/*
// The FSIZE structure specifies the width and height of a rectangle. 
typedef struct tagfSIZE {
	double cx; // Specifies the x-extent when a function returns. 
	double cy; // Specifies the y-extent when a function returns. 
}FSIZE;

// The FRECT structure defines the coordinates of the upper-left and 
// lower-right corners of a rectangle.
typedef struct tagfRECT {
	double left; // Specifies the x-coordinate of the upper-left corner of a rectangle.
	double top; // Specifies the y-coordinate of the upper-left corner of a rectangle.
	double right; // Specifies the x-coordinate of the lower-right corner of a rectangle.
	double bottom; // Specifies the y-coordinate of the lower-right corner of a rectangle.
}FRECT, *LPCFRECT;

// The FPOINT structure defines the x- and y-coordinates of a point.
typedef struct tagfPOINT {
	double x; // Specifies the x-coordinate of a point.
	double y; // Specifies the y-coordinate of a point.
} FPOINT;


class CfSize : public tagfSIZE
{
public:
	CfSize();
	CfSize(double initfCX, double initfCY);
	CfSize(FSIZE initfSize);
	CfSize(FPOINT initfPt);
	CfSize(DWORD dwfSize);
	virtual ~CfSize();

	BOOL operator ==(FSIZE fSize) const; // Checks for equality between two sizes. Returns nonzero if the sizes are equal, otherwize 0.
	BOOL operator !=(FSIZE fSize) const; // Checks for inequality between two sizes. Returns nonzero if the sizes are not equal, otherwise 0.
	void operator +=(FSIZE fSize); // Adds a size to this CfSize.
	void operator -=(FSIZE fSize); // Subtracts a size from this CfSize.
	CfSize operator +(FSIZE fSize) const; // This operation adds two CSize values.
	CfPoint operator +(FPOINT fPoint) const; // The cx and cy members of this CSize value are added to the x and y data members of the POINT value
											 //	CfRect operator +(const FRECT* lpfRect ) const;

	CfSize operator -(FSIZE fSize) const;
	CfPoint operator -(FPOINT fPoint) const;
	//	CfRect operator -(const FRECT* lpfRect ) const;
	CfSize operator -()const;
};


class CfPoint;
class CfSize;
//class CfLine;
class CfRect;
//class CfQuad;



class CfRect : public tagfRECT
{
public:
	CfRect();
	CfRect(double left, double top, double right, double bottom);
	virtual ~CfRect();
	double Width();
	double Height();
	CfSize Size();
	CfPoint TopLeft();
	CfPoint BottomRight();
	CfPoint CenterPoint();
	BOOL IsRectEmpty(); // Determines whether CRect is empty. A rectangle is empty if the width and/or height are 0 or negative. Differs from IsRectNull, which determines whether all coordinates of the rectangle are zero.
	BOOL IsRectNull(); // Determines whether the top, left, bottom, and right values of CRect are all equal to 0.
	BOOL PtInRect(CfPoint fPt); // A point is within CRect if it lies on or within all four sides.
	void SetRect(double x1, double y1, double x2, double y2);
	void SetRectEmpty(); // Makes CfRect a null rectangle by setting all coordinates to zero
	void CopyRect(LPCFRECT lpSrcfRect); // Copies the lpSrcfRect rectangle into CfRect
	BOOL EqualRect(LPCFRECT lpfRect); // Nonzero if the two rectangles have the same top, left, bottom, and right values; otherwise 0.
	void InflateRect(double x, double y);
	void InflateRect(FSIZE fSize);
	void InflateRect(LPCFRECT lpfRect);
	void InflateRect(double l, double t, double r, double b);
	void DeflateRect(double x, double y);
	void DeflateRect(FSIZE fSize);
	void DeflateRect(LPCFRECT lpfRect);
	void DeflateRect(double l, double t, double r, double b);
	void NormalizeRect(); // Normalizes CfRect so that both the height and width are positive
	void OffsetRect(double x, double y);
	void OffsetRect(FPOINT fPoint);
	void OffsetRect(FSIZE fSize);
	BOOL SubtractRect(LPCFRECT lpfRectSrc1, LPCFRECT lpfRectSrc2);
	BOOL IntersectRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2);
	BOOL UnionRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2);

public:
	double m_fWidth, m_fHeight;
};

class CfPoint : public tagfPOINT
{
public:
	CfPoint();
	CfPoint(double initfX, double initfY);
	CfPoint(FPOINT initfPt);
	CfPoint(FSIZE initfSize);
	CfPoint(DWORD dwPoint);
	virtual ~CfPoint();

	void	Offset(double fXOffset, double fYOffset);
	void	Offset(FPOINT fPoint);
	void	Offset(FSIZE fSize);
	CfPoint Round(CfPoint fPoint, int nPos = 3);

	BOOL    operator ==(FPOINT fPoint); // Nonzero if the points are equal; otherwise 0.
	BOOL    operator !=(FPOINT fPoint); // Nonzero if the points are not equal; otherwise 0.

	void	operator +=(FSIZE  fSize);
	void	operator +=(FPOINT fPoint);
	void	operator -=(FSIZE  fSize);
	void	operator -=(FPOINT fPoint);

	CfPoint operator +(FSIZE fSize) const;
	CfPoint operator +(FPOINT fPoint) const;
	CfRect operator +(const FRECT* lpfRect) const;

	CfSize operator -(FPOINT fPoint) const;
	CfPoint operator -(FSIZE fSize) const;
	//	CfPoint operator -(FPOINT fPoint ) const; �� �Լ��� CfSize�� �����.
	CfRect operator -(const FRECT* lpfRect) const;
	CfPoint operator -() const;
};

*/





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


