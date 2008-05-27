//////////////////////////////////////////////
// MDIChildView.cpp
//  Definitions for the CMDIChildView class

#include "MDIChildView.h"
#include "resource.h"


CMDIChildView::CMDIChildView() : m_Color(RGB(0,0,255))
{
	SetChildMenu(_T("MdiMenuView"));
}

CMDIChildView::~CMDIChildView()
{
	TRACE(_T("MDI Child destroyed\n"));
}

void CMDIChildView::OnInitialUpdate()
{
	::SetWindowText(m_hWnd, _T("View Window"));
	SetIconLarge(IDI_VIEW);
	SetIconSmall(IDI_VIEW);

	TRACE(_T("MDI Child created\n"));
}

void CMDIChildView::OnPaint(HDC hDC)
{
	//Centre some text in our view window
	CRect rc = GetClientRect();
	::SetTextColor(hDC, m_Color);
	::DrawText(hDC, _T("View Window"), -1, &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

BOOL CMDIChildView::OnCommand(WPARAM wParam, LPARAM /*lParam*/)
{
	switch (LOWORD(wParam))
	{
	case IDM_COLOR_BLACK:
		m_Color = RGB(0,0,0);
		::InvalidateRect(m_hWnd, NULL, TRUE);
		return TRUE;
	case IDM_COLOR_RED:
		m_Color = RGB(255, 0, 0);
		::InvalidateRect(m_hWnd, NULL, TRUE);
		return TRUE;
	case IDM_COLOR_GREEN:
		m_Color = RGB(0, 255, 0);
		::InvalidateRect(m_hWnd, NULL, TRUE);
		return TRUE;
	case IDM_COLOR_BLUE:
		m_Color = RGB(0, 0, 255);
		::InvalidateRect(m_hWnd, NULL, TRUE);
		return TRUE;
	case IDM_COLOR_WHITE:
		m_Color = RGB(255, 255, 255);
		::InvalidateRect(m_hWnd, NULL, TRUE);
		return TRUE;
	}
	
	return FALSE;
}

LRESULT CMDIChildView::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
		::InvalidateRect(m_hWnd, NULL, TRUE);
		break;  // and also do default processing for this message
	}

	// pass unhandled messages on for default processing
	return WndProcDefault(hWnd, uMsg, wParam, lParam);	
}
