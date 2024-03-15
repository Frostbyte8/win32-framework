/////////////////////////////
// Mainfrm.h
//

#ifndef MAINFRM_H
#define MAINFRM_H

#include "RichView.h"
#include "resource.h"


// Encoding IDs

const int ANSI = 0;            // Default for plain text
const int UTF8 = 1;            // Default for rich text
const int UTF16LE = 2;


///////////////////////////////////////////////////////////
// CMainFrame manages the application's main window.
// The main window is a frame that has a menubar, toolbar,
// statusbar and view window.
class CMainFrame : public CFrame
{
public:
    CMainFrame();
    virtual ~CMainFrame();
    virtual HWND Create(HWND parent = 0);
    void UpdateToolbar();

protected:
    // Virtual functions that override base class functions
    virtual void OnClose();
    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam);
    virtual int  OnCreate(CREATESTRUCT& cs);
    virtual LRESULT OnDpiChanged(UINT msg, WPARAM wparam, LPARAM lparam);
    virtual void OnInitialUpdate();
    virtual void OnMenuUpdate(UINT id);
    virtual LRESULT OnNotify(WPARAM wparam, LPARAM lparam);
    virtual void SetStatusIndicators();
    virtual void SetStatusParts();
    virtual void SetupMenuIcons();
    virtual void SetupToolBar();
    virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

private:
    CMainFrame(const CMainFrame&);               // Disable copy construction
    CMainFrame& operator=(const CMainFrame&);    // Disable assignment operator

    // Static callback functions
    static  DWORD CALLBACK MyStreamInCallback(DWORD cookie, LPBYTE pBuffer, LONG cb, LONG* pcb);
    static  DWORD CALLBACK MyStreamOutCallback(DWORD cookie, LPBYTE pBuffer, LONG cb, LONG* pcb);

    // Command handlers
    void OnDropFiles(HDROP dropInfo);
    BOOL OnEditCut();
    BOOL OnEditCopy();
    BOOL OnEditPaste();
    BOOL OnEditDelete();
    BOOL OnEditRedo();
    BOOL OnEditUndo();
    BOOL OnEncodeANSI();
    BOOL OnEncodeUTF8();
    BOOL OnEncodeUTF16();
    BOOL OnFileMRU(WPARAM wparam);
    BOOL OnFileExit();
    BOOL OnFileNewPlain();
    BOOL OnFileNewRich();
    BOOL OnFileOpen();
    BOOL OnFilePreview();
    BOOL OnFilePrint();
    BOOL OnFilePrintSetup();
    BOOL OnFilePrintNow();
    BOOL OnFileSaveAs();
    BOOL OnFileSave();
    BOOL OnOptionsFont();
    BOOL OnOptionsWrap();
    BOOL OnUpdateRangeOfIDs(UINT idFirst, UINT idLast, UINT id);

    // Message handlers
    LRESULT OnPreviewClose();
    LRESULT OnPreviewPrint();
    LRESULT OnPreviewSetup();

    int  AdjustForDPI(int value) const;
    void ClearContents();
    void DetermineEncoding(CFile& file);
    int  GetTextPartWidth(LPCTSTR text) const;
    BOOL ReadFile(LPCTSTR fileName);
    void RestoreFocus() { ::SetFocus(m_oldFocus); }
    void SaveFocus() { m_oldFocus = ::GetFocus(); }
    void SaveModifiedText();
    void SetEncoding(UINT encoding);
    void SetPathName(LPCTSTR fullFileName);

    void SetWindowTitle();
    BOOL WriteFile(LPCTSTR fileName);

    // Member variables
    CPrintPreview<CRichView>  m_preview;   // CRichView is the source of for CPrintPreview
    CRichView m_richView;
    CString m_pathName;
    CString m_mode;
    CString m_cap;
    CString m_num;
    CString m_ovr;
    CString m_encoding;
    UINT m_encodeMode;
    bool m_isToolbarShown;
    bool m_isWrapped;
    bool m_isRTF;
    HWND m_oldFocus;
};

#endif //MAINFRM_H

