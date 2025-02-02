// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "Splash.h"
#include "afxdialogex.h"
#include <string>
#include <gdiplusheaders.h>
#include "Settings.h"
// CSplashWnd dialog
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CSplashWnd, CDialog)

/*CSplashWnd::CSplashWnd(CWnd* pParent)
	: CDialog(CSplashWnd::IDD, pParent)
{

}*/


BOOL CSplashWnd::Create(CWnd* pParent)
{
	//{{AFX_DATA_INIT(CSplashWnd)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	if (!CDialog::Create(CSplashWnd::IDD, pParent))
	{
		TRACE0("Warning: creation of CSplashWnd dialog failed\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CSplashWnd::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	//SetBackgroundColor(RGB(240,240,200));

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CSplashWnd, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSplashWnd message handlers


void CSplashWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//dc.SetBkMode(TRANSPARENT);
	//dc.TextOutW(5,5,L"به نام خدا", 10);
	//SetBackgroundColor(RGB(00,240,200));

	Gdiplus::Graphics graphics(m_hWnd, 0);
	Gdiplus::Font fnt(_T("B Roya"), 12, 1);
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	std::wstring s = L"اللهمّ صَلِّ علی مُحمَّـدٍ وَ آلِ محّمدٍ وَ عجّـِل فَرَجهم";
	RECT rc1;
	GetClientRect(&rc1);
	RectF rc;
	rc.X = (float)rc1.left;
	rc.Y = (float)rc1.top;
	rc.Width = (float)(rc1.right - rc1.left);
	rc.Height = (float)(rc1.bottom - rc1.top);

	LinearGradientBrush br(rc, Color(255, 163, 196, 255), Color(255, 229, 238, 255), Gdiplus::LinearGradientModeVertical);
	//LinearGradientBrush br(rc, Color(255, 200, 200, 170), Color(255, 240, 240, 220), Gdiplus::LinearGradientModeVertical);
	graphics.FillRectangle(&br, rc);

	Gdiplus::StringFormat string_format;
	string_format.SetAlignment(StringAlignmentCenter);
	if(config.active_lang == langFA || config.active_lang == langAR)
		string_format.SetFormatFlags(StringFormatFlagsDirectionRightToLeft);

	//LinearGradientBrush br2(rc, Color(255, 0, 32, 96), Color(255, 255, 255, 255), Gdiplus::LinearGradientModeForwardDiagonal);
	SolidBrush br2(Color(255, 0, 32, 96));
	rc.Y += 10;
	graphics.DrawString(s.c_str(), s.length(), &fnt, rc, &string_format, &br2);

	rc.Y += 40;
	CString waitStr;
	waitStr.LoadString(IDS_PLEASE_WAIT);
	s = waitStr;//L"در حال بارگذاری منابع، لطفا منتظر بمانید...";
	Gdiplus::Font fnt2(_T("B Roya"), 17, 1);
	graphics.DrawString(s.c_str(), s.length(), &fnt2, rc, &string_format, &br2);

	//rc.Width *= 0.3;
	rc.Y += 50;
	CString str;
	str.LoadString(IDS_VERSION);
	//Gdiplus::Font fnt3(_T("B Roya"), 12, 1);
	graphics.DrawString(str.GetBuffer(), str.GetLength(), &fnt, rc, &string_format, &br2);

	//Pen p(Color(100, 200, 0, 0));
	//graphics.DrawLine(&p, 5, 5, 25, 25);

}
