
// PunchingMeasSys.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

// CPunchingMeasSysApp:
// �� Ŭ������ ������ ���ؼ��� PunchingMeasSys.cpp�� �����Ͻʽÿ�.
//

class CPunchingMeasSysApp : public CWinApp
{
public:
	CPunchingMeasSysApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPunchingMeasSysApp theApp;