
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// PunchingMeasSys.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


/*
CfPoint::CfPoint()
{
}

CfPoint::CfPoint(double initfX, double initfY)
{
	x = initfX;
	y = initfY;
}
CfPoint::CfPoint(FPOINT initfPt)
{
	*(FPOINT*)this = initfPt;
}
CfPoint::CfPoint(FSIZE initfSize)
{
	//	*(FSIZE*)this = initfSize;
	x = initfSize.cx;
	y = initfSize.cy;
}
CfPoint::CfPoint(DWORD dwPoint)
{
	x = (short)LOWORD(dwPoint);
	y = (short)HIWORD(dwPoint);
}
CfPoint::~CfPoint()
{

}
void CfPoint::Offset(double fXOffset, double fYOffset)
{
	x += fXOffset;
	y += fYOffset;
}

void CfPoint::Offset(FPOINT fPoint)
{
	x += fPoint.x;
	y += fPoint.y;
}
void CfPoint::Offset(FSIZE fSize)
{
	x += fSize.cx;
	y += fSize.cy;
}

CfPoint CfPoint::Round(CfPoint fPoint, int nPos)
{
	CfPoint fTemp;
	fTemp.x = fPoint.x * pow(10.0, nPos);
	fTemp.x = floor(fTemp.x + 0.5);
	fTemp.x *= pow(10.0, -nPos);

	fTemp.y = fPoint.y * pow(10.0, nPos);
	fTemp.y = floor(fTemp.y + 0.5);
	fTemp.y *= pow(10.0, -nPos);

	return fTemp;
}

BOOL CfPoint::operator ==(FPOINT fPoint)
{
	return (x == fPoint.x && y == fPoint.y);
}

BOOL CfPoint::operator !=(FPOINT fPoint)
{
	return (x != fPoint.x || y != fPoint.y);
}

void CfPoint::operator +=(FSIZE  fSize)
{
	x += fSize.cx; y += fSize.cy;
}
void CfPoint::operator +=(FPOINT fPoint)
{
	x += fPoint.x; y += fPoint.y;
}
void CfPoint::operator -=(FSIZE  fSize)
{
	x += fSize.cx; y += fSize.cy;
}
void CfPoint::operator -=(FPOINT fPoint)
{
	x -= fPoint.x; y -= fPoint.y;
}
CfPoint CfPoint::operator +(FSIZE fSize) const
{
	return CfPoint(x + fSize.cx, y + fSize.cy);
}
CfPoint CfPoint::operator +(FPOINT fPoint) const
{
	return CfPoint(x + fPoint.x, y + fPoint.y);
}
CfRect CfPoint::operator +(const FRECT* lpfRect) const
{
	return CfRect(lpfRect->left + x, lpfRect->top + y, lpfRect->right + x, lpfRect->bottom + y);
}
CfSize CfPoint::operator -(FPOINT fPoint) const
{
	return CfSize(x - fPoint.x, y - fPoint.y);
}
CfPoint CfPoint::operator -(FSIZE fSize) const
{
	return CfPoint(x - fSize.cx, y - fSize.cy);
}
CfRect CfPoint::operator -(const FRECT* lpfRect) const
{
	return CfRect(lpfRect->left - x, lpfRect->top - y, lpfRect->right - x, lpfRect->bottom - y);
}
//	CfRect CfPoint::operator -(const RECT* lpRect ) const
CfPoint CfPoint::operator -() const
{
	return CfPoint(-x, -y);
}



//////////////////////////////////////////////////////////////////////
// CfRect Class
//////////////////////////////////////////////////////////////////////
CfRect::CfRect() {}
CfRect::CfRect(double l, double t, double r, double b)
{
	left = l;	top = t;	right = r;	bottom = b;
	m_fWidth = r - l;
	m_fHeight = t - b;
}
CfRect::~CfRect() {}

double CfRect::Width() {
	return m_fWidth = right - left;
}
double CfRect::Height() {
	return m_fHeight = top - bottom;
}
CfSize CfRect::Size() {
	CfSize fSize;
	fSize.cx = m_fWidth;
	fSize.cy = m_fHeight;
	return fSize;
}
CfPoint CfRect::TopLeft() {
	CfPoint fPt(left, top);
	return fPt;
}
CfPoint CfRect::BottomRight() {
	CfPoint fPt(right, bottom);
	return fPt;
}
CfPoint CfRect::CenterPoint() {
	CfPoint fPt;
	fPt.x = (right - left) / 2.;
	fPt.y = (bottom - top) / 2.;
	return fPt;
}
BOOL CfRect::IsRectEmpty() {
	if (m_fHeight <= 0. || m_fWidth <= 0.)
		return TRUE;
	return FALSE;
}
BOOL CfRect::IsRectNull() {
	if (left == 0. && top == 0. && right == 0. && bottom == 0.)
		return TRUE;
	return FALSE;
}
BOOL CfRect::PtInRect(CfPoint fPt) {
	if (fPt.x >= left && fPt.x < right && fPt.y < top && fPt.y >= bottom)
		return TRUE;
	return FALSE;
}
void CfRect::SetRect(double x1, double y1, double x2, double y2)
{
	left = x1;
	top = y1;
	right = x2;
	bottom = y2;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::SetRectEmpty() {
	left = right = top = bottom = 0.;
	m_fWidth = 0.;
	m_fHeight = 0.;
}
void CfRect::CopyRect(LPCFRECT lpSrcfRect) {
	left = lpSrcfRect->left;
	right = lpSrcfRect->right;
	top = lpSrcfRect->top;
	bottom = lpSrcfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
BOOL CfRect::EqualRect(LPCFRECT lpfRect) {
	if (lpfRect->left == left && lpfRect->top == top &&
		lpfRect->right == right && lpfRect->bottom == bottom)
		return TRUE;
	return FALSE;
}
void CfRect::InflateRect(double x, double y) {
	left = left - x;
	right = right + x;
	top = top - y;
	bottom = bottom + y;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::InflateRect(FSIZE fSize) {
	left = left - fSize.cx;
	right = right + fSize.cx;
	top = top - fSize.cy;
	bottom = bottom + fSize.cy;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::InflateRect(LPCFRECT lpfRect) {
	left = left - lpfRect->left;
	right = right + lpfRect->right;
	top = top - lpfRect->top;
	bottom = bottom + lpfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::InflateRect(double l, double t, double r, double b) {
	left = left - l;
	right = right + t;
	top = top - r;
	bottom = bottom + b;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(double x, double y) {
	left = left + x;
	right = right - x;
	top = top + y;
	bottom = bottom - y;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(FSIZE fSize) {
	left = left + fSize.cx;
	right = right - fSize.cx;
	top = top + fSize.cy;
	bottom = bottom - fSize.cy;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(LPCFRECT lpfRect) {
	left = left + lpfRect->left;
	right = right - lpfRect->right;
	top = top + lpfRect->top;
	bottom = bottom - lpfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(double l, double t, double r, double b) {
	left = left + l;
	right = right - t;
	top = top + r;
	bottom = bottom - b;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::NormalizeRect() {
	if (left > right)
		swap(left, right);
	if (top > bottom)
		swap(top, bottom);
}
void CfRect::OffsetRect(double x, double y) {
	left += x;
	right += x;
	top += y;
	bottom += y;
}
void CfRect::OffsetRect(FPOINT fPoint) {
	left += fPoint.x;
	right += fPoint.x;
	top += fPoint.y;
	bottom += fPoint.y;
}
void CfRect::OffsetRect(FSIZE fSize) {
	left += fSize.cx;
	right += fSize.cx;
	top += fSize.cy;
	bottom += fSize.cy;
}
BOOL CfRect::SubtractRect(LPCFRECT lpfRectSrc1, LPCFRECT lpfRectSrc2)
{
	BOOL bChanged = FALSE;
	int nOverlap = 0;
	left = lpfRectSrc1->left;
	top = lpfRectSrc1->top;
	right = lpfRectSrc1->right;
	bottom = lpfRectSrc1->bottom;
	if ((lpfRectSrc2->left <= lpfRectSrc1->left) && (lpfRectSrc2->right >= lpfRectSrc1->right))
	{
		if ((lpfRectSrc2->top > lpfRectSrc1->top) && (lpfRectSrc2->top < lpfRectSrc1->bottom))
		{
			bottom = lpfRectSrc2->top;
			bChanged = TRUE;
		}
		if ((lpfRectSrc2->bottom < lpfRectSrc1->bottom) && (lpfRectSrc2->bottom > lpfRectSrc1->top))
		{
			top = lpfRectSrc2->bottom;
			bChanged = TRUE;
		}
		nOverlap++;
	}
	if ((lpfRectSrc2->top <= lpfRectSrc1->top) && (lpfRectSrc2->bottom >= lpfRectSrc1->bottom))
	{
		if ((lpfRectSrc2->left > lpfRectSrc1->left) && (lpfRectSrc2->left < lpfRectSrc1->right))
		{
			right = lpfRectSrc2->left;
			bChanged = TRUE;
		}
		if ((lpfRectSrc2->right < lpfRectSrc1->right) && (lpfRectSrc2->right > lpfRectSrc1->left))
		{
			left = lpfRectSrc2->right;
			bChanged = TRUE;
		}
		nOverlap++;
	}
	if (nOverlap == 2)
		left = right = top = bottom = 0.;
	return bChanged;
}

BOOL CfRect::IntersectRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2) {
	BOOL bChanged = FALSE;
	left = 0.;
	top = 0.;
	right = 0.;
	bottom = 0.;

	if ((lpfRect2->left > lpfRect1->left) && (lpfRect2->left < lpfRect1->right))
	{
		left = lpfRect2->left;
		bChanged = TRUE;
	}

	if ((lpfRect2->right > lpfRect1->left) && (lpfRect2->right < lpfRect1->right))
	{
		right = lpfRect2->right;
		bChanged = TRUE;
	}

	if ((lpfRect2->top > lpfRect1->top) && (lpfRect2->top < lpfRect1->bottom))
	{
		top = lpfRect2->top;
		bChanged = TRUE;
	}

	if ((lpfRect2->bottom > lpfRect1->top) && (lpfRect2->bottom < lpfRect1->bottom))
	{
		bottom = lpfRect2->bottom;
		bChanged = TRUE;
	}
	return bChanged;
}

BOOL CfRect::UnionRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2) {

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////
CfSize::CfSize()
{
}
CfSize::CfSize(double initfCX, double initfCY)
{
	cx = initfCX;
	cy = initfCY;
}
CfSize::CfSize(FSIZE initfSize)
{
	*(FSIZE*)this = initfSize;
}
CfSize::CfSize(FPOINT initfPt)
{
	//	*(FPOINT*)this = initfPt; 
	cx = initfPt.x;
	cy = initfPt.y;
}
CfSize::CfSize(DWORD dwSize)
{
	cx = (short)LOWORD(dwSize);
	cy = (short)HIWORD(dwSize);
}
CfSize::~CfSize()
{

}

// Checks for equality between two sizes.
// Returns nonzero if the sizes are equal, otherwize 0.
BOOL CfSize::operator ==(FSIZE fSize) const
{
	return (cx == fSize.cx && cy == fSize.cy);
}

// Checks for inequality between two sizes.
// Returns nonzero if the sizes are not equal, otherwise 0.
BOOL CfSize::operator !=(FSIZE fSize) const
{
	return (cx != fSize.cx || cy != fSize.cy);
}

// Adds a fSize to this CfSize.
void CfSize::operator += (FSIZE fSize)
{
	cx += fSize.cx; cy += fSize.cy;
}

// Subtracts a size from this CfSize.
void CfSize::operator -=(FSIZE fSize)
{
	cx -= fSize.cx; cy -= fSize.cy;
}

// This operation adds two CSize values.
CfSize CfSize::operator +(FSIZE fSize) const
{
	return CfSize(cx + fSize.cx, cy + fSize.cy);
}

// The cx and cy members of this CSize value are added
// to the x and y data members of the POINT value
CfPoint CfSize::operator +(FPOINT fPoint) const
{
	return CfPoint(cx + fPoint.x, cy + fPoint.y);
}

// This operation subtracts two CSize values.
CfSize CfSize::operator -(FSIZE fSize) const
{
	return CfSize(cx - fSize.cx, cy - fSize.cy);
}

// This operation offsets (moves) aFPOINT or CfPoint value by the additive inverse 
// of this CfSize value. The cx and cy of this CfSize value are subtracted from 
// the x and y data members of the FPOINT value. 
// It is analogous to the version of CfPoint::operator - that takes aFSIZE parameter.
CfPoint CfSize::operator -(FPOINT fPoint) const
{
	return CfPoint(cx - fPoint.x, cy - fPoint.y);
}

// This operation offsets (moves) aRECT or CRect value by the additive inverse of this CSize value.
// The cx and cy members of this CSize value are subtracted from the left, top, right, and bottom data members of the RECT value. 
// It is analogous to the version of CRect::operator - that takes aSIZE parameter.
//CfRect operator -(const FRECT* lpfRect ) const;
//{
//}

// This operation returns the additive inverse of this CSize value.
CfSize CfSize::operator -() const
{
	return CfSize(-cx, -cy);
}
*/
