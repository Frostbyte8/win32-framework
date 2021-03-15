/////////////////////////////
// Mainfrm.h
//

#ifndef MAINFRM_H
#define MAINFRM_H

#include "View.h"


///////////////////////////////////////////////////////////
// CMainFrame manages the application's main window.
// The main window is a frame which has a menubar, toolbar,
// statusbar and view window.
class CMainFrame : public CFrame
{
public:
    CMainFrame();
    virtual ~CMainFrame();
    virtual HWND Create(HWND parent = 0);
    BOOL OnFileExit();
    void OnBottom();
    void OnLeft();
    void OnRight();
    void OnTop();
    void SetReBarPos();
    void SetWrapState(CToolBar* pToolBar, BOOL isWrapped);

protected:
    virtual CRect   GetViewRect() const;
    virtual BOOL    OnCommand(WPARAM wparam, LPARAM lparam);
    virtual int     OnCreate(CREATESTRUCT& cs);
    virtual void    OnInitialUpdate();
    virtual void    SetupToolBar();
    virtual void    RecalcLayout();
    virtual LRESULT WndProc(UINT msg, WPARAM wmaram, LPARAM lmaram);

private:
    CReBar m_reBar;
    CToolBar m_toolBar;
    CImageList m_toolBarImages;
    CView m_view;
};

#endif //MAINFRM_H

