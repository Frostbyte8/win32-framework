////////////////////////////////////////////////////
// Mainfrm.cpp


#include "resource.h"
#include "TabbedMDIApp.h"
#include "mainfrm.h"


// Definitions for the CMainFrame class
CMainFrame::CMainFrame()
{
	// Constructor for CMainFrame. Its called after CFrame's constructor

	//Set m_DockTabbedMDI as the view window of the frame
	SetView(m_DockTabbedMDI);

	// Set the registry key name, and load the initial window position
	// Use a registry key name like "CompanyName\\Application"
	LoadRegistrySettings(_T("Win32++\\TabbedMDI Docking"));
}

CMainFrame::~CMainFrame()
{
	// Destructor for CMainFrame.
}

void CMainFrame::AddDocked(DockInfo di, CDockable* pDock)
{
	switch(di.DockID)
	{
	case ID_CONTAINCLASSES1:
		pDock->AddDockedChild(new CDockClasses, di.DockStyle, di.DockWidth, ID_CONTAINCLASSES1);
		break;
	case ID_CONTAINCLASSES2:
		pDock->AddDockedChild(new CDockClasses, di.DockStyle, di.DockWidth, ID_CONTAINCLASSES2);					
		break;
	case ID_CONTAINFILES1:
		pDock->AddDockedChild(new CDockFiles, di.DockStyle, di.DockWidth, ID_CONTAINFILES1);
		break;
	case ID_CONTAINFILES2:
		pDock->AddDockedChild(new CDockFiles, di.DockStyle, di.DockWidth, ID_CONTAINFILES2);
		break;
	case ID_OUTPUT1:
		pDock->AddDockedChild(new CDockOutput, di.DockStyle, di.DockWidth, ID_OUTPUT1);
		break;
	case ID_OUTPUT2:
		pDock->AddDockedChild(new CDockOutput, di.DockStyle, di.DockWidth, ID_OUTPUT2);
		break;
	case ID_TEXT1:
		pDock->AddDockedChild(new CDockText, di.DockStyle, di.DockWidth, ID_TEXT1);
		break;
	case ID_TEXT2:
		pDock->AddDockedChild(new CDockText, di.DockStyle, di.DockWidth, ID_TEXT2);
		break;
	default:
		TRACE(_T("Unknown Dock ID\n"));
		break;
	}
}

void CMainFrame::AddUndocked(DockInfo di)
{
	switch(di.DockID)
	{
	case ID_CONTAINCLASSES1:
		m_DockTabbedMDI.AddUndockedChild(new CDockClasses, di.DockStyle, di.DockWidth, di.Rect, ID_CONTAINCLASSES1);
		break;
	case ID_CONTAINCLASSES2:
		m_DockTabbedMDI.AddUndockedChild(new CDockClasses, di.DockStyle, di.DockWidth, di.Rect, ID_CONTAINCLASSES2);					
		break;
	case ID_CONTAINFILES1:
		m_DockTabbedMDI.AddUndockedChild(new CDockFiles, di.DockStyle, di.DockWidth, di.Rect, ID_CONTAINFILES1);
		break;
	case ID_CONTAINFILES2:
		m_DockTabbedMDI.AddUndockedChild(new CDockFiles, di.DockStyle, di.DockWidth, di.Rect, ID_CONTAINFILES2);
		break;
	case ID_OUTPUT1:
		m_DockTabbedMDI.AddUndockedChild(new CDockOutput, di.DockStyle, di.DockWidth, di.Rect, ID_OUTPUT1);
		break;
	case ID_OUTPUT2:
		m_DockTabbedMDI.AddUndockedChild(new CDockOutput, di.DockStyle, di.DockWidth, di.Rect, ID_OUTPUT2);
		break;
	case ID_TEXT1:
		m_DockTabbedMDI.AddUndockedChild(new CDockText, di.DockStyle, di.DockWidth, di.Rect, ID_TEXT1);
		break;
	case ID_TEXT2:
		m_DockTabbedMDI.AddUndockedChild(new CDockText, di.DockStyle, di.DockWidth, di.Rect, ID_TEXT2);
		break;
	default:
		TRACE(_T("Unknown Dock ID\n"));
		break; 
	}
}

void CMainFrame::OnFileNew()
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

void CMainFrame::OnContainerTabsAtTop()
// Reposition the tabs in the containers
{
	BOOL bTop = FALSE;
	std::vector<CDockable*>::iterator iter;
	
	// Set the Tab position for each container
	for (iter = m_DockTabbedMDI.GetAllDockables().begin(); iter < m_DockTabbedMDI.GetAllDockables().end(); ++iter)
	{
		CContainer* pContainer = (*iter)->GetContainer();
		if (pContainer)
		{
			bTop = pContainer->GetTabsAtTop();
			pContainer->SetTabsAtTop(!bTop);
		}
	}
		
	// Set the menu checkmark
	UINT uCheck = (bTop)? MF_UNCHECKED : MF_CHECKED;
	::CheckMenuItem(GetFrameMenu(), IDM_CONTAINER_TOP, uCheck);
}

void CMainFrame::OnMDITabsAtTop()
// Reposition TabbedMDI's tabs
{
	CTabbedMDI* pTabbedMDI = m_DockTabbedMDI.GetTabbedMDI();

	BOOL bTop = pTabbedMDI->GetTab().GetTabsAtTop();
	pTabbedMDI->GetTab().SetTabsAtTop(!bTop);
	
	// Set the menu checkmark
	UINT uCheck = (bTop)? MF_UNCHECKED : MF_CHECKED;
	::CheckMenuItem(GetFrameMenu(), IDM_TABBEDMDI_TOP, uCheck);
}

void CMainFrame::LoadDefaultDockables()
{
	// Note: The  DockIDs are used for saving/restoring the dockables state in the registry

	DWORD dwStyle = DS_CLIENTEDGE; // The style added to each dockable
	
	// Add the parent dockables
	CDockable* pDockRight  = m_DockTabbedMDI.AddDockedChild(new CDockClasses, DS_DOCKED_RIGHT | dwStyle, 200, ID_CONTAINCLASSES1);	
	CDockable* pDockBottom = m_DockTabbedMDI.AddDockedChild(new CDockText, DS_DOCKED_BOTTOM | dwStyle, 100, ID_TEXT1);

	// Add the remaining dockables
	pDockRight->AddDockedChild(new CDockFiles, DS_DOCKED_CONTAINER | dwStyle, 200, ID_CONTAINFILES1);
	pDockRight->AddDockedChild(new CDockClasses, DS_DOCKED_CONTAINER | dwStyle, 200, ID_CONTAINCLASSES2);
	pDockRight->AddDockedChild(new CDockFiles, DS_DOCKED_CONTAINER | dwStyle, 200, ID_CONTAINFILES2);

	pDockBottom->AddDockedChild(new CDockOutput, DS_DOCKED_CONTAINER | dwStyle, 100, ID_OUTPUT1);
	pDockBottom->AddDockedChild(new CDockText, DS_DOCKED_CONTAINER | dwStyle, 100, ID_TEXT2);
	pDockBottom->AddDockedChild(new CDockOutput, DS_DOCKED_CONTAINER | dwStyle, 100, ID_OUTPUT2);
}

void CMainFrame::LoadDefaultMDITabs()
{
	// Add some MDI tabs
	CTabbedMDI* pTabbedMDI = (CTabbedMDI*)m_DockTabbedMDI.GetView();
	pTabbedMDI->AddMDIChild(new CViewSimple, _T("Simple View"));
	pTabbedMDI->AddMDIChild(new CViewRect, _T("Rectangles"));
	pTabbedMDI->AddMDIChild(new CViewText, _T("TextView"));
	pTabbedMDI->AddMDIChild(new CViewClasses, _T("Classes"));
	pTabbedMDI->AddMDIChild(new CViewFiles, _T("Files"));
	pTabbedMDI->SetActiveTab(0);
}

void CMainFrame::LoadRegistryDockables()
{
	if (0 != GetRegistryKeyName().size())
	{
		std::vector<DockInfo> vDockList;
		tString tsKey = _T("Software\\") + GetRegistryKeyName() + _T("\\Dock Windows");
		HKEY hKey = 0;
		RegOpenKeyEx(HKEY_CURRENT_USER, tsKey.c_str(), 0, KEY_READ, &hKey);
		if (hKey)
		{
			DWORD dwType = REG_BINARY;
			DWORD BufferSize = sizeof(DockInfo);
			DockInfo di;
			int i = 0;
			TCHAR szNumber[16];
			tString tsSubKey = _T("DockChild");
			tsSubKey += _itot(i, szNumber, 10);
			
			// Fill the DockList vector from the registry
			while (0 == RegQueryValueEx(hKey, tsSubKey.c_str(), NULL, &dwType, (LPBYTE)&di, &BufferSize))
			{
				vDockList.push_back(di);
				i++;
				tsSubKey = _T("DockChild");
				tsSubKey += _itot(i, szNumber, 10);
			}
			
			RegCloseKey(hKey);
		}

		// Add dockables without parents first
		for (int i = vDockList.size() -1; i >= 0; --i)
		{
			DockInfo di = vDockList[i];
			if (di.DockParentID == 0)
			{
				if (di.DockStyle & 0xF)
					AddDocked(di, &m_DockTabbedMDI);
				else
					AddUndocked(di);

				vDockList.erase(vDockList.begin() + i);
			}
		}

		// Add remaining dockables
		while (vDockList.size() > 0)
		{
			bool bFound = false;
			std::vector<DockInfo>::iterator iter;
			for (iter = vDockList.begin(); iter < vDockList.end(); ++iter)
			{
				CDockable* pDock = m_DockTabbedMDI.GetDockFromID((*iter).DockParentID);
				if (pDock != 0)
				{
					AddDocked(*iter, pDock);
					bFound = true;
					vDockList.erase(iter);
					break;
				}
			}

			if (!bFound)
			{
				TRACE(_T("Orphaned dockables !!! \n"));
				break;
			}
		}	
	}	
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM /*lParam*/)
{
	CTabbedMDI* pTabbedMDI = (CTabbedMDI*)m_DockTabbedMDI.GetView();

	// OnCommand responds to menu and and toolbar input
	switch(LOWORD(wParam))
	{
	case IDM_FILE_NEW:
		OnFileNew();
		return TRUE;
	case IDM_FILE_NEWSIMPLE:
		pTabbedMDI->AddMDIChild(new CViewSimple, _T("Simple View"));	
		return TRUE;
	case IDM_FILE_NEWRECT:
		pTabbedMDI->AddMDIChild(new CViewRect, _T("Rectangles"));	
		return TRUE;
	case IDM_FILE_NEWTEXT:
		pTabbedMDI->AddMDIChild(new CViewText, _T("TextView"));	
		return TRUE;
	case IDM_FILE_NEWTREE:
		pTabbedMDI->AddMDIChild(new CViewClasses, _T("TreeView"));	
		return TRUE;
	case IDM_FILE_NEWLIST:
		pTabbedMDI->AddMDIChild(new CViewFiles, _T("ListView"));
		return TRUE;
	case IDM_FILE_EXIT:
		// End the application
		::PostMessage(m_hWnd, WM_CLOSE, 0L, 0L);
		return TRUE;
	case IDM_CONTAINER_TOP:
		OnContainerTabsAtTop();
		return TRUE;
	case IDM_TABBEDMDI_TOP:
		OnMDITabsAtTop();
		return TRUE;
	case IDM_DOCK_DEFAULT:
		m_DockTabbedMDI.CloseAllDockables();
		LoadDefaultDockables();
		return TRUE;
	case IDM_DOCK_CLOSEALL:
		m_DockTabbedMDI.CloseAllDockables();
		return TRUE;
	case IDW_VIEW_STATUSBAR:
		OnViewStatusbar();
		return TRUE;
	case IDW_VIEW_TOOLBAR:
		OnViewToolbar();
		return TRUE;
	case IDM_HELP_ABOUT:
		// Display the help dialog
		OnHelp();
		return TRUE;
	}

	return FALSE;
}

void CMainFrame::OnCreate()
{
	// OnCreate controls the way the frame is created.
	// Overriding CFrame::Oncreate is optional.
	// The default for the following variables is TRUE

	// m_bShowIndicatorStatus = FALSE;	// Don't show statusbar indicators
	// m_bShowMenuStatus = FALSE;		// Don't show toolbar or menu status
	// m_bUseRebar = FALSE;				// Don't use rebars
	// m_bUseThemes = FALSE;            // Don't use themes
	// m_bUseToolbar = FALSE;			// Don't use a toolbar

	// call the base class function
	CFrame::OnCreate();
}

void CMainFrame::OnInitialUpdate()
{
	m_DockTabbedMDI.SetDockStyle(DS_CLIENTEDGE);

	if (0 == GetRegistryKeyName().size())
		LoadDefaultDockables();
	else
		LoadRegistryDockables();

	// Ensure we have some docked/undocked windows
	if (0 == m_DockTabbedMDI.GetAllDockables().size())
		LoadDefaultDockables();

	LoadDefaultMDITabs();

	// PreCreate initially set the window as invisible, so show it now.
	ShowWindow();
}

void CMainFrame::PreCreate(CREATESTRUCT &cs)
{
	// Call the base class function first
	CFrame::PreCreate(cs);
	
	// Hide the window initially by removing the WS_VISIBLE style
	cs.style &= ~WS_VISIBLE;
}

void CMainFrame::SaveDockables()
{
	m_DockTabbedMDI.VerifyDockables();
	// NOTE: This function assumes that each dockable has a unique DockID

	std::vector<CDockable*>::iterator iter;
	std::vector<DockInfo> vDockList;

	if (0 != GetRegistryKeyName().size())
	{
		// Fill the DockList vector with the docking information
		for (iter = m_DockTabbedMDI.GetAllDockables().begin(); iter <  m_DockTabbedMDI.GetAllDockables().end(); ++iter)
		{
			DockInfo di	 = {0};
			di.DockID	 = (*iter)->GetDockID();
			di.DockStyle = (*iter)->GetDockStyle();
			di.DockWidth = (*iter)->GetDockWidth();
			di.Rect		 = (*iter)->GetWindowRect();
			if ((*iter)->GetDockParent())
				di.DockParentID = (*iter)->GetDockParent()->GetDockID();
			
			vDockList.push_back(di);
		}

		tString tsKeyName = _T("Software\\") + GetRegistryKeyName();
		HKEY hKey = NULL;
		HKEY hKeyDock = NULL;
		if (RegCreateKeyEx(HKEY_CURRENT_USER, tsKeyName.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL))
			throw (CWinException(_T("RegCreateKeyEx Failed")));

		RegDeleteKey(hKey, _T("Dock Windows"));
		if (RegCreateKeyEx(hKey, _T("Dock Windows"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyDock, NULL))
			throw (CWinException(_T("RegCreateKeyEx Failed")));

		// Add the Dock windows information to the registry
		for (size_t u = 0; u < vDockList.size(); ++u)
		{
			DockInfo di = vDockList[u];
			TCHAR szNumber[16];
			tString tsSubKey = _T("DockChild");
			tsSubKey += _itot(u, szNumber, 10);
			RegSetValueEx(hKeyDock, tsSubKey.c_str(), 0, REG_BINARY, (LPBYTE)&di, sizeof(DockInfo));
		}

		RegCloseKey(hKeyDock);
		RegCloseKey(hKey);
	}
}

void CMainFrame::SaveRegistrySettings()
{
	CFrame::SaveRegistrySettings();
	SaveDockables();
}

void CMainFrame::SetupToolbar()
{
	// Set the Resource IDs for the toolbar buttons
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

	// Remove the checkmark for container tabs at top
	::CheckMenuItem(GetFrameMenu(), IDM_CONTAINER_TOP, MF_UNCHECKED);
}

