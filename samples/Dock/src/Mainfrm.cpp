/////////////////////////////
// Mainfrm.cpp
//

#include "stdafx.h"
#include "Mainfrm.h"
#include "resource.h"


//////////////////////////////////
// CMainFrame function definitions
//

// Constructor.
CMainFrame::CMainFrame()
{
    m_useProportionalResize = false;
    m_use3DBorder = true;
    m_disableUndocking = false;
    m_disableResize = false;
    m_disableDockLR = false;
    m_disableDockClose = false;
    m_disableDockCaption = false;
}

// Destructor.
CMainFrame::~CMainFrame()
{
}

// Create the frame window.
HWND CMainFrame::Create(HWND parent)
{
    //Set m_view as the view window of the frame
    SetView(m_view);

    // Set the registry key name, and load the initial window position
    // Use a registry key name like "CompanyName\\Application"
    LoadRegistrySettings(_T("Win32++\\Dock"));

    return CDockFrame::Create(parent);
}

// Adjusts the dockers in response to window DPI changes.
// Required for per-monitor DPI-aware.
void CMainFrame::DPIScaleDockers()
{
    std::vector<CDocker*> v = GetAllDockers();
    std::vector<CDocker*>::iterator it;
    for (it = v.begin(); it != v.end(); ++it)
    {
        if ((*it)->IsWindow())
        {
            // Reset the docker size.
            int size = (*it)->GetDockSize();
            (*it)->SetDockSize(size);

            // Notify the docker that the DPI has changed.
            (*it)->SendMessage(UWM_DPICHANGED, 0, 0);
        }
    }

    RecalcDockLayout();
}

// Assigns the appropriately sized menu icons.
// Required for per-monitor DPI-aware.
void CMainFrame::DPIScaleMenuIcons()
{
    // Load the toolbar bitmap.
    CBitmap toolbarImage(IDW_MAIN);

    // Scale the bitmap to the menu item height.
    int menuHeight = GetMenuIconHeight();
    int scale = menuHeight / toolbarImage.GetSize().cy;
    CBitmap scaledImage;
    if (scale > 0)
        scaledImage = ScaleUpBitmap(toolbarImage, scale);
    else
        scaledImage.LoadBitmap(IDB_TOOLBAR16);

    // Create the image-list from the scaled image
    CSize sz = scaledImage.GetSize();
    m_menuImages.Create(sz.cy, sz.cy, ILC_COLOR32 | ILC_MASK, 0, 0);
    COLORREF mask = RGB(192, 192, 192);
    m_menuImages.Add(scaledImage, mask);

    // Assign the image-list to the menu items.
    SetMenuImages(m_menuImages);
}

// Assigns the appropriately sized toolbar icons.
// Required for per-monitor DPI-aware.
void CMainFrame::DPIScaleToolBar()
{
    if (GetToolBar().IsWindow())
    {
        // Reset the toolbar images.
        SetToolBarImages(RGB(192, 192, 192), IDW_MAIN, 0, 0);
    }
}

// Loads a default configuration of dockers.
void CMainFrame::LoadDefaultDockers()
{
    // Note: The  DockIDs are used for saving/restoring the dockers state in the registry

    CDocker* pDockLeft = AddDockedChild(new CDockClasses, DS_DOCKED_LEFT, DPIScaleInt(200), ID_DOCK_CLASSES1);
    CDocker* pDockRight = AddDockedChild(new CDockClasses, DS_DOCKED_RIGHT, DPIScaleInt(200), ID_DOCK_CLASSES2);
    CDocker* pDockTop = AddDockedChild(new CDockText, DS_DOCKED_TOP, DPIScaleInt(100), ID_DOCK_TEXT1);
    CDocker* pDockBottom = AddDockedChild(new CDockText, DS_DOCKED_BOTTOM, DPIScaleInt(100), ID_DOCK_TEXT2);

    pDockLeft->AddDockedChild(new CDockFiles, DS_DOCKED_BOTTOM, DPIScaleInt(150), ID_DOCK_FILES1);
    pDockRight->AddDockedChild(new CDockFiles, DS_DOCKED_BOTTOM, DPIScaleInt(150), ID_DOCK_FILES2);
    pDockTop->AddDockedChild(new CDockSimple, DS_DOCKED_RIGHT, DPIScaleInt(100), ID_DOCK_SIMPLE1);
    pDockBottom->AddDockedChild(new CDockSimple, DS_DOCKED_RIGHT, DPIScaleInt(100), ID_DOCK_SIMPLE2);

    // Adjust dockstyles as per menu selections
    SetDockStyles();
    DPIScaleDockers();
}

// Adds a new docker. The id specifies the dock type.
CDocker* CMainFrame::NewDockerFromID(int id)
{
    CDocker* pDock = NULL;
    switch (id)
    {
    case ID_DOCK_CLASSES1:
        pDock = new CDockClasses;
        break;
    case ID_DOCK_CLASSES2:
        pDock = new CDockClasses;
        break;
    case ID_DOCK_FILES1:
        pDock = new CDockFiles;
        break;
    case ID_DOCK_FILES2:
        pDock = new CDockFiles;
        break;
    case ID_DOCK_SIMPLE1:
        pDock = new CDockSimple;
        break;
    case ID_DOCK_SIMPLE2:
        pDock = new CDockSimple;
        break;
    case ID_DOCK_TEXT1:
        pDock = new CDockText;
        break;
    case ID_DOCK_TEXT2:
        pDock = new CDockText;
        break;
    default:
        TRACE("Unknown Dock ID\n");
        break;
    }

    return pDock;
}

// Toggle the display of a 3D border.
BOOL CMainFrame::On3DBorder()
{
    m_use3DBorder = !m_use3DBorder;
    SetDockStyles();
    return TRUE;
}

// OnCommand responds to menu and and toolbar input.
BOOL CMainFrame::OnCommand(WPARAM wparam, LPARAM)
{
    UINT id = LOWORD(wparam);
    switch(id)
    {
    case IDM_FILE_EXIT:         return OnFileExit();
    case IDM_DOCK_DEFAULT:      return OnDockDefault();
    case IDM_DOCK_CLOSEALL:     return OnDockCloseAll();
    case IDM_PROP_RESIZE:       return OnPropResize();
    case IDM_3DBORDER:          return On3DBorder();
    case IDM_NO_UNDOCK:         return OnNoUndocking();
    case IDM_NO_RESIZE:         return OnNoResize();
    case IDM_NO_DOCK_LR:        return OnNoDockLR();
    case IDM_NO_DOCK_CAPTION:   return OnNoDockCaption();
    case IDM_NO_DOCK_CLOSE:     return OnNoDockClose();
    case IDW_VIEW_STATUSBAR:    return OnViewStatusBar();
    case IDW_VIEW_TOOLBAR:      return OnViewToolBar();
    case IDM_HELP_ABOUT:        return OnHelp();
    }

    return FALSE;
}

// OnCreate controls the way the frame is created.
// Overriding CFrame::OnCreate is optional.
int CMainFrame::OnCreate(CREATESTRUCT& cs)
{
    // A menu is added if the IDW_MAIN menu resource is defined.
    // Frames have all options enabled by default.
    // Use the following functions to disable options.

    // UseIndicatorStatus(FALSE);    // Don't show keyboard indicators in the StatusBar.
    // UseMenuStatus(FALSE);         // Don't show menu descriptions in the StatusBar.
    // UseOwnerDrawnMenu(FALSE);     // Don't use owner draw for popup menu items.
    // UseReBar(FALSE);              // Don't use a ReBar.
    // UseStatusBar(FALSE);          // Don't use a StatusBar.
    // UseThemes(FALSE);             // Don't use themes.
    // UseToolBar(FALSE);            // Don't use a ToolBar.

    // call the base class function
    return CDockFrame::OnCreate(cs);
}

// Closes all of the dockers.
BOOL CMainFrame::OnDockCloseAll()
{
    CloseAllDockers();
    return TRUE;
}

// Loads a default arrangement of dockers.
BOOL CMainFrame::OnDockDefault()
{
    // Suppress redraw to render the docking changes smoothly.
    SetRedraw(FALSE);

    CloseAllDockers();
    LoadDefaultDockers();

    // Enable redraw and redraw the frame.
    SetRedraw(TRUE);
    RedrawWindow();
    return TRUE;
}

// Called when the effective dots per inch (dpi) for a window has changed.
// This occurs when:
//  - The window is moved to a new monitor that has a different DPI.
//  - The DPI of the monitor hosting the window changes.
LRESULT CMainFrame::OnDPIChanged(UINT msg, WPARAM wparam, LPARAM lparam)
{
    // Supress redraw to render the DPI changes smoothly.
    SetRedraw(FALSE);

    CDockFrame::OnDPIChanged(msg, wparam, lparam);
    DPIScaleDockers();
    DPIScaleMenuIcons();
    DPIScaleToolBar();
    RecalcDockLayout();
    RecalcLayout();

    // Enable redraw and redraw the frame.
    SetRedraw(TRUE);
    RedrawWindow();
    return 0;
}

// Issues a close request to the frame to end the program.
BOOL CMainFrame::OnFileExit()
{
    Close();
    return TRUE;
}

// Called after the window is created.
void CMainFrame::OnInitialUpdate()
{
    // Load dock settings.
    if (!LoadDockRegistrySettings(GetRegistryKeyName()))
        LoadDefaultDockers();

    // Adjust dockstyles as per menu selections.
    SetDockStyles();

    // Rescale the dockers for the current DPI.
    DPIScaleDockers();

    // PreCreate initially set the window as invisible, so show it now.
    ShowWindow(GetInitValues().showCmd);
}

// Updates the menu items before they are displayed.
void CMainFrame::OnMenuUpdate(UINT id)
{
    switch(id)
    {
    case IDM_PROP_RESIZE:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_useProportionalResize ? MF_CHECKED : MF_UNCHECKED));
        break;
    case IDM_3DBORDER:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_use3DBorder ? MF_CHECKED : MF_UNCHECKED));
        break;
    case IDM_NO_UNDOCK:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_disableUndocking ? MF_CHECKED : MF_UNCHECKED));
        break;
    case IDM_NO_RESIZE:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_disableResize ? MF_CHECKED : MF_UNCHECKED));
        break;
    case IDM_NO_DOCK_LR:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_disableDockLR ? MF_CHECKED : MF_UNCHECKED));
        break;
    case IDM_NO_DOCK_CLOSE:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_disableDockClose ? MF_CHECKED : MF_UNCHECKED));
        break;
    case IDM_NO_DOCK_CAPTION:
        GetFrameMenu().CheckMenuItem(id, MF_BYCOMMAND | (m_disableDockCaption ? MF_CHECKED : MF_UNCHECKED));
        break;
    }

    CDockFrame::OnMenuUpdate(id);
}

// Toggle the docking caption.
BOOL CMainFrame::OnNoDockCaption()
{
    m_disableDockCaption = !m_disableDockCaption;
    SetDockStyles();
    RedrawWindow();
    return TRUE;
}

// Toggle the ability to close of dockers.
BOOL CMainFrame::OnNoDockClose()
{
    m_disableDockClose = !m_disableDockClose;
    SetDockStyles();
    RedrawWindow();
    return TRUE;
}

// Toggle the ability to dock left or right.
BOOL CMainFrame::OnNoDockLR()
{
    m_disableDockLR = !m_disableDockLR;
    SetDockStyles();
    return TRUE;
}

// Toggle the ability to resize dockers using the splitter bar.
BOOL CMainFrame::OnNoResize()
{
    m_disableResize = !m_disableResize;
    SetDockStyles();
    return TRUE;
}

// Toggle the ability to undock a docker.
BOOL CMainFrame::OnNoUndocking()
{
    m_disableUndocking = !m_disableUndocking;
    SetDockStyles();
    return TRUE;
}

// Toggle proportional resizing.
BOOL CMainFrame::OnPropResize()
{
    m_useProportionalResize = !m_useProportionalResize;
    SetDockStyles();
    return TRUE;
}

// Specify the CREATESTRUCT parameters before the window is created.
void CMainFrame::PreCreate(CREATESTRUCT& cs)
{
    // Call base class to set defaults
    CDockFrame::PreCreate(cs);

    // Hide the window initially by removing the WS_VISIBLE style
    cs.style &= ~WS_VISIBLE;
}

// Save the docking configuration in the registry.
BOOL CMainFrame::SaveRegistrySettings()
{
    if (CDockFrame::SaveRegistrySettings())
        return SaveDockRegistrySettings(GetRegistryKeyName());
    else
        return FALSE;
}

// Sets the style for all the dockers.
void CMainFrame::SetDockStyles()
{
    std::vector<CDocker*>::const_iterator iter;

    for (iter = GetAllDockers().begin(); iter != GetAllDockers().end(); ++iter)
    {
        DWORD style = (*iter)->GetDockStyle();

        // Filter unwanted styles
        style &= 0xF000F;

        // Add styles selected from the menu
        if (m_useProportionalResize)    style |= DS_NO_FIXED_RESIZE;
        if (m_use3DBorder)              style |= DS_CLIENTEDGE;
        if (m_disableUndocking)         style |= DS_NO_UNDOCK;
        if (m_disableResize)            style |= DS_NO_RESIZE;
        if (m_disableDockLR)            style |= DS_NO_DOCKCHILD_LEFT | DS_NO_DOCKCHILD_RIGHT;
        if (m_disableDockClose)         style |= DS_NO_CLOSE;
        if (m_disableDockCaption)       style |= DS_NO_CAPTION;

        (*iter)->SetDockStyle(style);
    }
}

// Specify the icons used in popup menus.
void CMainFrame::SetupMenuIcons()
{
    std::vector<UINT> data = GetToolBarData();
    if (GetMenuIconHeight() >= 24)
        SetMenuIcons(data, RGB(192, 192, 192), IDW_MAIN);
    else
        SetMenuIcons(data, RGB(192, 192, 192), IDB_TOOLBAR16);

    // Update the menu icons
    DPIScaleMenuIcons();
}

// Sets the Resource IDs for the toolbar buttons
void CMainFrame::SetupToolBar()
{
    AddToolBarButton( IDM_FILE_NEW,   FALSE );
    AddToolBarButton( IDM_FILE_OPEN,  FALSE );
    AddToolBarButton( IDM_FILE_SAVE,  FALSE );

    AddToolBarButton( 0 );  // Separator
    AddToolBarButton( IDM_EDIT_CUT,   FALSE );
    AddToolBarButton( IDM_EDIT_COPY,  FALSE );
    AddToolBarButton( IDM_EDIT_PASTE, FALSE );

    AddToolBarButton( 0 );  // Separator
    AddToolBarButton( IDM_FILE_PRINT, FALSE );

    AddToolBarButton( 0 );  // Separator
    AddToolBarButton( IDM_HELP_ABOUT );
}

// Process the frame's window messages.
LRESULT CMainFrame::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    try
    {
        return WndProcDefault(msg, wparam, lparam);
    }

    catch (const CException& e)
    {
        // Display the exception.
        ::MessageBox(0, e.GetText(), AtoT(e.what()), MB_ICONERROR);
        return 0;
    }
}
