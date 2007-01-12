//////////////////////////////////////////////
// MDIChildView.cpp
//  Definitions for the CMDIChildView class

#include "MDIChildView.h"
#include "resource.h"


CMDIChildView::CMDIChildView() : m_Color(RGB(0,0,255))
{
	SetChildMenu(TEXT ("MdiMenuView"));
}

CMDIChildView::~CMDIChildView()
{
}

void CMDIChildView::OnInitialUpdate()
{
	::SetWindowText(m_hWnd, TEXT("View Window"));
	SetIconLarge(IDI_VIEW);
	SetIconSmall(IDI_VIEW);
}

void CMDIChildView::OnPaint(HDC hDC)
{
	//Centre some text in our view window
	RECT r;
	::GetClientRect(m_hWnd, &r);
	::SetTextColor(hDC, m_Color);
	::DrawText(hDC, TEXT("View Window"), -1, &r, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

BOOL CMDIChildView::OnCommand(UINT nID)
{
	switch (nID)
	{
	case IDM_COLOR_BLACK:
		m_Color = RGB(0,0,0);
		break;
	case IDM_COLOR_RED:
		m_Color = RGB(255, 0, 0);
		break;
	case IDM_COLOR_GREEN:
		m_Color = RGB(0, 255, 0);
		break;
	case IDM_COLOR_BLUE:
		m_Color = RGB(0, 0, 255);
		break;
	case IDM_COLOR_WHITE:
		m_Color = RGB(255, 255, 255);
		break;
	}

	::InvalidateRect(m_hWnd, NULL, TRUE);
	return 0;
}

LRESULT CMDIChildView::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
		::InvalidateRect(m_hWnd, NULL, TRUE);
		break;  // Continue with default processing
	}

	return CMDIChild::WndProc(hwnd, uMsg, wParam, lParam);
}
