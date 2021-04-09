/////////////////////////////
// MyStatusBar.h
//

#ifndef MYSTATUSBAR_H
#define MYSTATUSBAR_H

#include "Hyperlink.h"


/////////////////////////////////////////
// Declaration of the CMyStatusBar class.
//
class CMyStatusBar : public CStatusBar
{
public:
    CMyStatusBar() {}
    virtual ~CMyStatusBar() {}

    void OnSize();
    void OnTimer();

protected:
    virtual void OnAttach();
    virtual BOOL OnEraseBkgnd(CDC& dc);
    virtual void PreCreate(CREATESTRUCT& cs);
    virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

    void SetStatusParts();

private:
    CHyperlink m_hyperlink;
    CProgressBar m_progressBar;
};


#endif      // MYSTATUSBAR_H
