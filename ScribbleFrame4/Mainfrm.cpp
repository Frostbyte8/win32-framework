////////////////////////////////////////////////////
// Mainfrm.cpp  - definitions for the CMainFrame class


#include "resource.h"
#include "mainfrm.h"


CMainFrame::CMainFrame()
{
	// Set m_View as the view window of the frame
	SetView(m_View);

	// Define our toolbar
	m_ToolbarData.clear();
	m_ToolbarData.push_back ( IDM_FILE_NEW   );
	m_ToolbarData.push_back ( IDM_FILE_OPEN  );
	m_ToolbarData.push_back ( IDM_FILE_SAVE  );
	m_ToolbarData.push_back ( 0 );				// Separator
	m_ToolbarData.push_back ( IDM_EDIT_CUT   );
	m_ToolbarData.push_back ( IDM_EDIT_COPY  );
	m_ToolbarData.push_back ( IDM_EDIT_PASTE );
	m_ToolbarData.push_back ( IDM_FILE_PRINT );
	m_ToolbarData.push_back ( 0 );				// Separator
	m_ToolbarData.push_back ( IDM_PEN_RED    );
	m_ToolbarData.push_back ( IDM_PEN_BLUE   );
	m_ToolbarData.push_back ( IDM_PEN_GREEN  );
	m_ToolbarData.push_back ( IDM_PEN_BLACK  );
	m_ToolbarData.push_back ( 0 );				// Separator
	m_ToolbarData.push_back ( IDM_HELP_ABOUT );
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// Process the messages from the Menu and Tool Bar
	switch (LOWORD(wParam))
	{
	case IDM_FILE_NEW:
		::MessageBox(NULL, TEXT("File New"), TEXT("Menu"), MB_OK);
		break;
	case IDM_FILE_OPEN:
		::MessageBox(NULL, TEXT("File Open"), TEXT("Menu"), MB_OK);
		break;
	case IDM_FILE_SAVE:
		::MessageBox(NULL, TEXT("File Save"), TEXT("Menu"), MB_OK);
		break;
	case IDM_FILE_SAVEAS:
		::MessageBox(NULL, TEXT("File SaveAs"), TEXT("Menu"), MB_OK);
		break;
	case IDM_FILE_PRINT:
		::MessageBox(NULL, TEXT("File Print"), TEXT("Menu"), MB_OK);
		break;
	case IDM_EDIT_COPY:
		::MessageBox(NULL, TEXT("Edit Copy"), TEXT("Menu"), MB_OK);
		break;
	case IDM_EDIT_PASTE:
		::MessageBox(NULL, TEXT("Edit Paste"), TEXT("Menu"), MB_OK);
		break;
	case IDM_EDIT_CUT:
		::MessageBox(NULL, TEXT("Edit Cut"), TEXT("Menu"), MB_OK);
		break;
	case IDM_EDIT_DELETE:
		::MessageBox(NULL, TEXT("Edit Delete"), TEXT("Menu"), MB_OK);
		break;
	case IDM_EDIT_REDO:
		::MessageBox(NULL, TEXT("Edit Redo"), TEXT("Menu"), MB_OK);
		break;
	case IDM_EDIT_UNDO:
		::MessageBox(NULL, TEXT("Edit Undo"), TEXT("Menu"), MB_OK);
		break;
	case IDM_PEN_RED:
		TRACE("Red pen selected");
		m_View.SetPen(RGB(255,0,0));
		break;
	case IDM_PEN_BLUE:
		TRACE("Blue pen selected");
		m_View.SetPen(RGB(0,0,255));
		break;
	case IDM_PEN_GREEN:
		TRACE("Green pen selected");
		m_View.SetPen(RGB(0,196,0));
		break;
	case IDM_PEN_BLACK:
		TRACE("Black pen selected");
		m_View.SetPen(RGB(0,0,0));
		break;
	case IDM_HELP_ABOUT:
		OnHelp();
		break;
	case IDM_FILE_EXIT:
		::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;
	}

	return CFrame::OnCommand(wParam, lParam);
}

LRESULT CMainFrame::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	switch (uMsg)
//	{

//	} // switch (uMsg)

	//Use the frame default message handling for remaining messages
	return CFrame::WndProc(hWnd, uMsg, wParam, lParam);
} // LRESULT CMainFrame::WndProc(...)

