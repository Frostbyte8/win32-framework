/////////////////////////////
// Files.cpp
//

#include "stdafx.h"
#include "Files.h"
#include "Resource.h"

//////////////////////////////////
// CViewFiles function definitions
//
CViewFiles::CViewFiles()
{
}

CViewFiles::~CViewFiles()
{
    if (IsWindow()) DeleteAllItems();
}

// Insert 4 list view items.
void CViewFiles::InsertItems()
{
    // Add 4th item
    int item = InsertItem(0, L"ListViewApp.h", 2);
    SetItemText(item, 1, L"1 KB");
    SetItemText(item, 2, L"C Header file");

    // add 3rd item
    item = InsertItem(item, L"ListViewApp.cpp", 1);
    SetItemText(item, 1, L"3 KB");
    SetItemText(item, 2, L"C++ Source file");

    // add 2nd item
    item = InsertItem(item, L"main.cpp", 1);
    SetItemText(item, 1, L"1 KB");
    SetItemText(item, 2, L"C++ Source file");

    // add 1st item
    item = InsertItem(item, L"ListView", 0);
    SetItemText(item, 2, L"Folder");
}

void CViewFiles::OnAttach()
{
    // Set the image lists
    SetDPIImages();

    // Set the report style
    DWORD dwStyle = GetStyle();
    SetStyle((dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);

    SetColumns();
    InsertItems();
}

void CViewFiles::OnDestroy()
{
    SetImageList(0, LVSIL_SMALL);
}

LRESULT CViewFiles::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
    // Set window focus. The docker will now report this as active.
    SetFocus();
    return FinalWindowProc(msg, wparam, lparam);
}

// Called in response to a UWM_DPICHANGED message which is sent to child windows
// when the top-level window receives a WM_DPICHANGED message. WM_DPICHANGED is
// received when the DPI changes and the application is DPI_AWARENESS_PER_MONITOR_AWARE.
LRESULT CViewFiles::OnUserDPIChanged(UINT, WPARAM, LPARAM)
{
    SetDPIImages();
    SetDPIColumnWidths();
    return 0;
}

void CViewFiles::SetColumns()
{
    // empty the list
    DeleteAllItems();

    // initialize the columns
    LV_COLUMN column;
    ZeroMemory(&column, sizeof(column));
    column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    column.fmt = LVCFMT_LEFT;
    column.cx = 120;
    WCHAR string[3][20] = {L"Name", L"Size", L"Type"};
    for(int i = 0; i < 3; ++i)
    {
        column.pszText = string[i];
        InsertColumn(i, column);
    }

    SetDPIColumnWidths();
}

// Adjusts the listview column widths in response to window DPI changes.
void CViewFiles::SetDPIColumnWidths()
{
    SetColumnWidth(0, DPIScaleInt(120));
    SetColumnWidth(1, DPIScaleInt(50));
    SetColumnWidth(2, DPIScaleInt(100));
}

// Adjusts the listview image sizes widths in response to window DPI changes.
void CViewFiles::SetDPIImages()
{
    // Set the image lists
    CBitmap bmImage(IDB_FILEVIEW);
    bmImage = DPIScaleUpBitmap(bmImage);
    int scale = bmImage.GetSize().cy / 15;
    m_smallImages.Create(scale * 16, scale * 15, ILC_COLOR32 | ILC_MASK, 1, 0);
    m_smallImages.Add(bmImage, RGB(255, 0, 255));
    SetImageList(m_smallImages, LVSIL_SMALL);
}

LRESULT CViewFiles::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    try
    {
        switch (msg)
        {
        case WM_MOUSEACTIVATE:      return OnMouseActivate(msg, wparam, lparam);
        case UWM_DPICHANGED:        return OnUserDPIChanged(msg, wparam, lparam);
        }

        return WndProcDefault(msg, wparam, lparam);
    }

    // Catch all CException types.
    catch (const CException& e)
    {
        // Display the exception and continue.
        ::MessageBox(0, e.GetText(), AtoT(e.what()), MB_ICONERROR);

        return 0;
    }
}

/////////////////////////////////////
// CContainFiles function definitions
//
CContainFiles::CContainFiles()
{
    SetTabText(L"FileView");
    SetTabIcon(IDI_FILEVIEW);
    SetDockCaption (L"File View - Docking container");
    SetView(m_viewFiles);
}

///////////////////////////////////
//  CDockFiles function definitions
//
CDockFiles::CDockFiles()
{
    SetView(m_files);
    SetBarWidth(DPIScaleInt(8));
}

// Called in response to a UWM_DPICHANGED message which is sent to child windows
// when the top-level window receives a WM_DPICHANGED message. WM_DPICHANGED is
// received when the DPI changes and the application is DPI_AWARENESS_PER_MONITOR_AWARE.
LRESULT CDockFiles::OnUserDPIChanged(UINT msg, WPARAM wparam, LPARAM lparam)
{
    // Set the width of the splitter bar.
    SetBarWidth(DPIScaleInt(8));
    return CDocker::OnUserDPIChanged(msg, wparam, lparam);
}

