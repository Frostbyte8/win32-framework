/* (08-Feb-2016)                                                 (MyFileDlg.h) *
********************************************************************************
|                                                                              |
|                   Copyright (c) 2016, David Nash                             |
|                          All Rights Reserved.                                |
|                       email: dnash@bigpond.net.au                            |
|            url: https://sourceforge.net/projects/win32-framework             |
|                                                                              |
===============================================================================*

    Contents Description: This file contains the declaration and
    implementation of the MyFileDlg class, which is derived from the
    CFileDalog class found in the Win32++ Windows interface framework. 

        Caveats: The copyright displayed above extends only to the author's
    original contributions to the subject class, and to the alterations,
    additions, deletions, and other treatments of materials that may have
    been extracted from the cited sources.  Unaltered portions of those
    materials retain their original copyright status. The author hereby
    grants permission to any person obtaining a copy of this treatment
    of the subject class and any associated documentation composed by
    the author, to utilize this material, free of charge and without
    restriction or limitation, subject to the following conditions:

    These materials are provided "as is", without warranty of any kind,
    express or implied, including but not limited to: warranties of
    merchantability, fitness for a particular purpose, and non-infringement.
    In no event shall the author or copyright holders be liable for any
    claim, damages, or other liability, whether in an action of contract,
    tort or otherwise, arising from, out of, or in connection with, these
    materials, the use thereof, or any other other dealings therewith.

    Acknowledgement:
        The author would like to thank and acknowledge the advice,
        critical review, insight, and assistance provided by David Nash
        in the development of this work.

    Programming Notes:
                The programming standards roughly follow those established
                by the 1997-1999 Jet Propulsion Laboratory Deep Space Network
        Planning and Preparation Subsystem project for C++ programming.

********************************************************************************

    Declaration and implementation of the MyFileDialog class

*******************************************************************************/

#ifndef MY_FILE_DLG_H
#define MY_FILE_DLG_H

#include "ListBoxDlgRC.h"

/*============================================================================*/
    class
MyFileDialog : public CFileDialog

/*----------------------------------------------------------------------------*/
{
    public:
        MyFileDialog
        (
            BOOL bOpenFileDialog = TRUE,
            LPCTSTR sDefExt      = NULL,   
            LPCTSTR sFileName    = NULL,                                   
            DWORD dwFlags        = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
            LPCTSTR  sFilter     = NULL
        )   : CFileDialog(bOpenFileDialog, sDefExt, sFileName,
                dwFlags, sFilter)
        {
        }

    void SetBoxTitle(const CString& title)  
          // Set the title of the read/saveas dialog box to the title
          // string. This must be used after an object of this class is
          // constructed, but before DoModal() is invoked. It also must
          // deposit a pointer to an object persistent over the span
          // of the object.
        {
            m_sTitle = title;
            SetTitle(m_sTitle.c_str());
        }
              
    protected:
        virtual BOOL OnInitDialog()
        // This method is activated within  immediately before
        // the dialog box is displayed, and too late for any changes to
        // m_OFN fields to take effect.  However, if there are other
        // actions required for initialization of this object before the
        // open/save-as choice box appears, do them here or override
        // this method to add any initialization actions required.
        {
              // do the base class initialization first
              // (it currently does nothing)
            CDialog::OnInitDialog();
            return TRUE;
        }

    private:
        CString m_sTitle;       // persistent over object span
};
/*----------------------------------------------------------------------------*/
#endif // MY_FILE_DLG_H
