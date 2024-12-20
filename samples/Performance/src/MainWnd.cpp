/////////////////////////////
// MainWnd.cpp
//

#include "stdafx.h"
#include "MainWnd.h"
#include "MyDialog.h"
#include "PerfApp.h"
#include "resource.h"

///////////////////////////////////
// CMainWindow function definitions
//

// Constructor.
CMainWindow::CMainWindow() : m_testMessages(0), m_testWindows(0), m_windowsCreated(0)
{
    LARGE_INTEGER li;
    VERIFY(QueryPerformanceFrequency(&li));
    m_frequency = li.QuadPart;
}

// Destructor.
CMainWindow::~CMainWindow()
{
}

// Creates the main window.
HWND CMainWindow::Create(HWND hParent /*= NULL*/)
{
    CString str = _T("Main Window");

    // Create the main window
    CRect rc(20, 50, 400, 300);
    CRect rcDPI = DpiScaleRect(rc);

    return CreateEx(WS_EX_TOPMOST, NULL, str, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        rcDPI, hParent, 0);
}

// Creates several test windows.
void CMainWindow::CreateTestWindows(int windows)
{
    m_testWindows = windows;

    for (int i = 0 ; i < windows; i++)
    {
        // Create the test windows
        TestWindowPtr pTestWindow(new CTestWindow());
        m_pTestWindows.push_back(pTestWindow);
        m_pTestWindows[i]->CreateWin(i);
    }
}

// Retrieves the current performance counter.
LONGLONG CMainWindow::GetCounter() const
{
    LARGE_INTEGER current;
    QueryPerformanceCounter(&current);
    return current.QuadPart;
}

// Called when the main window is created.
int CMainWindow::OnCreate(CREATESTRUCT&)
{
    SetIconSmall(IDW_MAIN);
    SetIconLarge(IDW_MAIN);

    m_edit.Create(*this);

    return 0;
}

// Called when the main window is destroyed.
void CMainWindow::OnDestroy()
{
    // End the application
    ::PostQuitMessage(0);
}

LRESULT CMainWindow::OnDpiChanged(UINT, WPARAM, LPARAM lparam)
{
    LPRECT prc = reinterpret_cast<LPRECT>(lparam);
    SetWindowPos(HWND_TOP, *prc, SWP_SHOWWINDOW);
    m_edit.DPISetFont();

    return 0;
}

// Called after the main window is created.
// Called after OnCreate.
void CMainWindow::OnInitialUpdate()
{
    CMyDialog myDialog(IDD_DIALOG1);
    myDialog.DoModal(*this);
}

// Called when the main window is resized.
LRESULT CMainWindow::OnSize()
{
    CRect r = GetClientRect();

    // Resize the edit window when the main window is resized
    m_edit.MoveWindow(0, 0, r.right - r.left, r.bottom - r.top, TRUE);

    return 0;
}

// Respond to the message received when a test window is created.
LRESULT CMainWindow::OnWindowCreated()
{
    if (++m_windowsCreated == m_testWindows)
        OnAllWindowsCreated();

    return 0;
}

// Called when all the test windows have been created.
void CMainWindow::OnAllWindowsCreated()
{
    CString str;
    str.Format(_T("%d  Windows Created"), m_testWindows);
    SendText(str);
    SendText(_T("Ready to run performance test"));

    int result = MessageBox(_T("Start the Performance Test?"), _T("Ready"), MB_OKCANCEL | MB_ICONEXCLAMATION);
    if (result != IDOK) return;

    PerformanceTest();

    // Loop the performance test
    result = IDYES;
    while(result == IDYES)
    {
        result = MessageBox(_T("Run Test Again?"), _T("Ready"), MB_YESNO | MB_ICONEXCLAMATION);
        if (result != IDYES) break;

        PerformanceTest();
    }
    SendText(_T("Testing complete"));
}

// Do the performance test.
void CMainWindow::PerformanceTest() const
{
    LRESULT result = 0;
    int messages = 0;

    CString str;
    str.Format(str, _T("Sending %d  Messages\n"), m_testMessages);
    SendText(str);

    // Choose a Window handle(HWND) to send the messages to
    HWND wnd = m_pTestWindows[(m_testWindows-1)/2]->GetHwnd();

    // Store the starting counter
    LONGLONG start = GetCounter();

    // Send the messages
    while(messages++ < m_testMessages)
        result = ::SendMessage(wnd, WM_TESTMESSAGE, 0, 0);

    // Calculate the time the messages took to send
    LONGLONG end = GetCounter();
    double mSeconds = 1000.0 * (end - start) / m_frequency;

    // Display the results
    str.Format(_T("%.2f milliseconds to process %d messages"), mSeconds, m_testMessages);
    SendText(str);

    str.Format(_T("%d total messages sent\n"), result);
    TRACE(str);

    MessageBox(str, _T("Info"), MB_OK);
}

// Send text to the edit window.
void CMainWindow::SendText(LPCTSTR str) const
{
    m_edit.AppendText(str);
    m_edit.AppendText(_T("\r\n"));

    TRACE(str);
    TRACE("\n");
}

// Process the main window's messages.
LRESULT CMainWindow::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    try
    {
        switch (msg)
        {
        case WM_DPICHANGED:     return OnDpiChanged(msg, wparam, lparam);
        case WM_SIZE:           return OnSize();
        case WM_WINDOWCREATED:  return OnWindowCreated();
        }

        return WndProcDefault(msg, wparam, lparam);
    }

    // Catch all unhandled CException types.
    catch (const CException& e)
    {
        // Display the exception and continue.
        CString str1;
        str1 << e.GetText() << _T("\n") << e.GetErrorString();
        CString str2;
        str2 << "Error: " << e.what();
        ::MessageBox(NULL, str1, str2, MB_ICONERROR);
    }

    // Catch all unhandled std::exception types.
    catch (const std::exception& e)
    {
        // Display the exception and continue.
        CString str1 = e.what();
        ::MessageBox(NULL, str1, _T("Error: std::exception"), MB_ICONERROR);
    }

    return 0;
}

