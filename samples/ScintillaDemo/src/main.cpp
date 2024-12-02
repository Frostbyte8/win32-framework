/////////////////////////////
// main.cpp
//

#include "stdafx.h"
#include "ScintillaApp.h"


#if defined (_MSC_VER) && (_MSC_VER >= 1920) // >= VS2019
int WINAPI wWinMain (__in HINSTANCE, __in_opt HINSTANCE, __in LPWSTR, __in int)
#else
int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#endif
{
    try
    {
        // Start Win32++.
        ScintillaApp theApp;

        // Run the application and the message loop.
        return theApp.Run();
    }

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

    return -1;
}