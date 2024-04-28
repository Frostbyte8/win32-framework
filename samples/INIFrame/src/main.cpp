/////////////////////////////
// main.cpp
//

#include "stdafx.h"
#include "FrameApp.h"


#if defined (_MSC_VER) && (_MSC_VER >= 1920) // >= VS2019
  int WINAPI WinMain (__in HINSTANCE, __in_opt HINSTANCE, __in LPSTR, __in int)
#else
  int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    try
    {
        // Start Win32++.
        CFrameApp theApp;

        // Run the application and the message loop.
        return theApp.Run();
    }

    // Catch all unhandled CException types.
    catch (const CException &e)
    {
        // Display the exception and quit.
        ::MessageBox(NULL, e.GetText(), AtoT(e.what()), MB_ICONERROR);

        return -1;
    }
}

