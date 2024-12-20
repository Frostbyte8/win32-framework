//////////////////////////////////////////////////////////
// MDIChildListView.h
//  Declaration of the CViewList and CMDIChildListView classes

#ifndef MDICHILDLISTVIEW_H
#define MDICHILDLISTVIEW_H


///////////////////////////////////////////
// CViewList manages a list view control.
// It is the view window for CMDIChildList.
class CViewList : public CListView
{
public:
    CViewList();
    virtual ~CViewList();

protected:
    // Virtual functions that override base class functions
    virtual void OnAttach();
    virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

private:
    CViewList(const CViewList&);               // Disable copy construction
    CViewList& operator=(const CViewList&);    // Disable assignment operator

    void InsertItems();
    void SetColumns();
};


////////////////////////////////////////////
// CMDIChildList manages a MDI child window.
// It use CViewList as its view window.
class CMDIChildList : public CMDIChild
{
public:
    CMDIChildList();
    virtual ~CMDIChildList();

protected:
    // Virtual functions that override base class functions
    virtual int  OnCreate(CREATESTRUCT& cs);
    virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

private:
    CMDIChildList(const CMDIChildList&);                // Disable copy construction
    CMDIChildList& operator=(const CMDIChildList&);   // Disable assignment operator

    CViewList m_listView;
    CMenu m_menu;
};

#endif  //MDICHILDLISTVIEW_H

