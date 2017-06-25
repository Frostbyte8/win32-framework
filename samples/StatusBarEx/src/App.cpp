/* [Tab/Indent: 8/8][Line/Box: 80/74]	                             (App.cpp) *
********************************************************************************

	Contents Description: Implementation of the Windows interface andCApp 
	class for a sample program demonstrating the expanded use of the status 
	bar using the Win32++  Windows framework, Copyright (c) 2005-2017 
	David Nash.

	This particular program was adapted from the StatusBar sample progam
	in the Win32++ distribution by Robert C. Tausworthe to illustrate the 
	definition of the status bar makeup by way of a data structure, in a
	similar fashion as that appearing in the Microsoft Foundation Classes 
	(MFC), and to override the Win32++ normal statusbar definition of four 
	parts to any number suitable for an application.

	The code changes to the StatusBar sample program only occur in the 
	CMainFrame and MyStatusBar classes. However, the entire program has
	been reformatted for better readability, per the Programming Notes,
	below.

	These materials are provided "as is", without warranty of any kind,
	express or implied, including but not limited to: warranties of
	merchantability, fitness for a particular purpose, and non-infringement.

	Programming Notes:
                The programming conventions used here roughly follow those 
		established by the 1997-1999 Jet Propulsion Laboratory Deep 
		Space Network Planning and Preparation Subsystem project for 
		C++ programming.

*******************************************************************************/

#include "stdafx.h"
#include "App.h"

/*******************************************************************************

	Implementation of the Windows execution interface

*=============================================================================*/
	int APIENTRY 
WinMain(HINSTANCE, HINSTANCE, LPSTR, int)				/*

*-----------------------------------------------------------------------------*/
{
	try
	{
		  // Start Win32++
		CApp theApp;

		  // Run the application and the message loop
		return theApp.Run();
	}

	  // catch all unhandled CException types
	catch (const CException &e)
	{
		  // Display the exception and quit
		MessageBox(NULL, e.GetText(), AtoT(e.what()), MB_ICONERROR);

		return -1;
	}
}

/*******************************************************************************

	Implementation of the CApp class

*=============================================================================*/
	CApp::
CApp()									/*

*-----------------------------------------------------------------------------*/
{
}

/*============================================================================*/
	CApp::
~CApp()									/*

*-----------------------------------------------------------------------------*/
{
}

/*============================================================================*/
	BOOL CApp::
InitInstance()								/*

	Create the Frame Window.
*-----------------------------------------------------------------------------*/
{
	try
	{
		m_Frame.Create(); // throws a CWinException on failue
		return TRUE;
	}
	catch (...)
	{	  // We get here if the Frame creation fails
		::MessageBox(NULL, _T("Failed to create Frame window"), 
		    _T("ERROR"), MB_ICONERROR);
	}
	return FALSE; // returning FALSE ends the application
}
