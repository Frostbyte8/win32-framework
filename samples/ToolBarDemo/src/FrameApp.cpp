/////////////////////////////
//FrameApp.cpp
//

#include "stdafx.h"
#include "FrameApp.h"

////////////////////////////////////////
// CToolBarDemoApp function definitions.
//
CToolBarDemoApp::CToolBarDemoApp()
{
}

CToolBarDemoApp::~CToolBarDemoApp()
{
}

BOOL CToolBarDemoApp::InitInstance()
{
    // Create the frame window.
    m_frame.Create();   // throws a CWinException on failure

    return TRUE;
}


