////////////////////////////////////////////////////
// MainMDIfrm.cpp  - definitions for the CMainMDIFrame class


#include "resource.h"
#include "mainMDIfrm.h"
#include "MDIChildSimple.h"
#include "MDIChildRect.h"
#include "MDIChildMax.h"
#include "MDIChildText.h"
#include "MDIChildTreeView.h"
#include "MDIChildListView.h"


CMainMDIFrame::CMainMDIFrame()
{
	// Set the registry key name, and load the initial window position
	// Use a registry key name like "CompanyName\\Application"
	LoadRegistrySettings(_T("Win32++\\MDI Frame Sample"));
}

CMainMDIFrame::~CMainMDIFrame()
{
}

void CMainMDIFrame::OnInitialUpdate()
{
	//The frame is now created.
	//Place any additional startup code here.
}

void CMainMDIFrame::OnFileNew()
{
	// Creates the popup menu when the "New" toolbar button is pressed

	// Position the popup menu
	CToolbar& TB = GetToolbar();
	RECT rc = TB.GetItemRect(TB.CommandToIndex(IDM_FILE_NEW));
	::MapWindowPoints(GetToolbar(), NULL, (LPPOINT)&rc, 2);

	TPMPARAMS tpm;
	tpm.cbSize = sizeof(TPMPARAMS);
	tpm.rcExclude = rc;

	// Load the popup menu
	HMENU hTopMenu = ::LoadMenu(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDM_NEWMENU));
	HMENU hPopupMenu = ::GetSubMenu(hTopMenu, 0);

	// Start the popup menu
	::TrackPopupMenuEx(hPopupMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, rc.left, rc.bottom, m_hWnd, &tpm);

	// Release the menu resource
	::DestroyMenu(hTopMenu);
}

BOOL CMainMDIFrame::OnCommand(WPARAM wParam, LPARAM /*lParam*/)
{
	switch (LOWORD(wParam))
	{
	case IDM_FILE_NEW:
		// For ComCtl versions 4.71 and older
		OnFileNew();
		return TRUE;
	case IDM_FILE_NEWVIEW:
		AddMDIChild(new CMDIChildSimple);	// CMDIFrame::RemoveMDIChild deletes this pointer
		return TRUE;
	case IDM_FILE_NEWRECT:
		AddMDIChild(new CMDIChildRect);	// CMDIFrame::RemoveMDIChild deletes this pointer
		return TRUE;
	case IDM_FILE_NEWTEXT:
		AddMDIChild(new CMDIChildText);	// CMDIFrame::RemoveMDIChild deletes this pointer
		return TRUE;
	case IDM_FILE_NEWMAX:
		AddMDIChild(new CMDIChildMax);	// CMDIFrame::RemoveMDIChild deletes this pointer
		return TRUE;
	case IDM_FILE_NEWTREE:
		AddMDIChild(new CMDIChildTreeView);	// CMDIFrame::RemoveMDIChild deletes this pointer
		return TRUE;
	case IDM_FILE_NEWLIST:
		AddMDIChild(new CMDIChildListView);	// CMDIFrame::RemoveMDIChild deletes this pointer
		return TRUE;
	case IDM_FILE_CLOSE:	// Close the active MDI window
		GetActiveMDIChild()->SendMessage(WM_CLOSE, 0L, 0L);
		return TRUE;
	case IDM_FILE_EXIT:
		::PostMessage(m_hWnd, WM_CLOSE, 0L, 0L);
		return TRUE;
	case IDM_HELP_ABOUT:
		OnHelp();
		return TRUE;
	}

	return FALSE;
}

void CMainMDIFrame::OnCreate()
{
	// OnCreate controls the way the frame is created.
	// Overriding CFrame::Oncreate is optional.
	// The default for the following variables is TRUE

	// m_bShowIndicatorStatus = FALSE;	// Don't show statusbar indicators
	// m_bShowMenuStatus = FALSE;		// Don't show toolbar or menu status
	// m_bUseRebar = FALSE;				// Don't use rebars
	// m_bUseThemes = FALSE;			// Don't use themes
	// m_bUseToolbar = FALSE;			// Don't use a toolbar

	// call the base class function
	CMDIFrame::OnCreate();

	SetButtons(GetToolbar().GetToolbarData());


}

LRESULT CMainMDIFrame::OnNotify(WPARAM /*wParam*/, LPARAM lParam)
{
	// Notification from our dropdown button is recieved if Comctl32.dll version
	// is 4.70 or later (IE v3 required).
    switch(((LPNMHDR)lParam)->code)
	{
 		//Menu for dropdown toolbar button
		case TBN_DROPDOWN:
		{
			if (((LPNMHDR)lParam)->hwndFrom == GetToolbar())
				OnFileNew();
		}
		break;

	} //switch LPNMHDR

	return 0L;
}

void CMainMDIFrame::SetButtons(const std::vector<UINT> ToolbarData)
{

}

void CMainMDIFrame::SetupToolbar()
{
	// Define the resource IDs for the toolbar
	AddToolbarButton( IDM_FILE_NEW   );
	AddToolbarButton( IDM_FILE_OPEN,  FALSE );
	AddToolbarButton( IDM_FILE_SAVE,  FALSE );
	
	AddToolbarButton( 0 );	// Separator
	AddToolbarButton( IDM_EDIT_CUT,   FALSE );
	AddToolbarButton( IDM_EDIT_COPY,  FALSE );
	AddToolbarButton( IDM_EDIT_PASTE, FALSE );
	
	AddToolbarButton( 0 );	// Separator
	AddToolbarButton( IDM_FILE_PRINT, FALSE );
	
	AddToolbarButton( 0 );	// Separator
	AddToolbarButton( IDM_HELP_ABOUT );

	// Use larger buttons with seperate imagelists for normal, hot and disabled buttons.
	CToolbar& TB = GetToolbar();
	SetToolbarImages(TB, RGB(192,192,192), IDB_TOOLBAR_NORM, IDB_TOOLBAR_HOT, IDB_TOOLBAR_DIS);

	// Add some extra icons for menu items
	AddMenuIcon(IDM_FILE_NEWVIEW, ::LoadIcon(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDI_VIEW)));
	AddMenuIcon(IDM_FILE_NEWRECT, ::LoadIcon(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDI_RECT)));
	AddMenuIcon(IDM_FILE_NEWMAX,  ::LoadIcon(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDI_MAX)));
	AddMenuIcon(IDM_FILE_NEWTEXT, ::LoadIcon(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDI_TEXT)));
	AddMenuIcon(IDM_FILE_NEWLIST, ::LoadIcon(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDI_FILES)));
	AddMenuIcon(IDM_FILE_NEWTREE, ::LoadIcon(GetApp()->GetInstanceHandle(), MAKEINTRESOURCE(IDI_CLASSES)));

	// Configure the "New" toolbar button to bring up a menu
	// Setting this style requires comctl32.dll version 4.72 or later
	if (GetComCtlVersion() >= 472)
	{
		GetToolbar().SetButtonStyle(IDM_FILE_NEW, BTNS_WHOLEDROPDOWN);
	}
}

LRESULT CMainMDIFrame::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WndProcDefault(hWnd, uMsg, wParam, lParam);
}

