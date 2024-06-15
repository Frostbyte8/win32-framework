/////////////////////////////
// scintillaview.h
//

#ifndef SCINTILLAVIEW_H
#define SCINTILLAVIEW_H

#include "targetver.h"
#include "Scintilla.h"


///////////////////////////////////////////////
// ScintillaView manages the application's main window.
class ScintillaView : public CWnd
{
public:
    ScintillaView();
    virtual ~ScintillaView();

    Sci_Position CollatePages(Sci_Position startChar = 0, Sci_Position endChar = -1);
    Sci_Rectangle GetPageRect(CDC& dc) const;
    Sci_Rectangle GetPrintMargins(CDC& dc) const;
    Sci_Rectangle GetPrintRect(CDC& dc) const;

    void InitialiseEditor();
    void OpenFile(LPCWSTR fileName);
    void PrintFooter(CDC& dc, const CString& footerText) const;
    void PrintHeader(CDC& dc, const CString& headerText) const;
    void PrintPage(CDC& dc, size_t page);
    void QuickPrint(LPCTSTR docName);
    void SaveFile(LPCWSTR fullPath);
    void SetHeaderText(const CString& headerText) { m_header = headerText; }

    // Scintalla control functions.
    void AddText(Sci_Position length, const char* text);
    void Cancel();
    bool CanPaste();
    bool CanRedo();
    bool CanUndo();
    void Clear();
    void ClearAll();
    void Copy();
    void Cut();
    void EmptyUndoBuffer();
    Sci_Position FormatRangeFull(bool draw, Sci_RangeToFormatFull* fr);
    bool GetModify();
    void GetRangeFull(Sci_Position start, Sci_Position end, char* text);
    Sci_Position GetTextLength();
    Sci_Position GetSelectionEnd();
    Sci_Position GetSelectionStart();
    void GotoPos(Sci_Position position);
    void Paste();
    void Redo();
    void SelectAll();
    void SetSavePoint();
    void SetScrollWidth(int pixelWidth);
    void SetScrollWidthTracking(bool tracking);
    void SetUndoCollection(bool collectUndo);
    void StyleClearAll();
    COLORREF StyleGetBack(int style);
    bool StyleGetBold(int style);
    int  StyleGetFont(int style, char* fontName);
    COLORREF StyleGetFore(int style);
    bool StyleGetItalic(int style);
    int  StyleGetSize(int style);
    bool StyleGetUnderLine(int style);
    bool StyleGetWeight(int style);
    void StyleSetBack(int style, COLORREF back);
    void StyleSetBold(int style, bool bold);
    void StyleSetFont(int style, const char* fontName);
    void StyleSetFore(int style, COLORREF fore);
    void StyleSetItalic(int style, bool italic);
    void StyleSetSize(int style, int size);
    void StyleSetUnderLine(int style, bool underLine);
    void StyleSetWeight(int style, int weight);
    void Undo();

protected:
    virtual void OnInitialUpdate();
    virtual void PreCreate(CREATESTRUCT& cs);
    virtual void PreRegisterClass(WNDCLASS& wc);

private:
    inline LRESULT Call(UINT message, WPARAM wParam, LPARAM lParam);
    std::vector<Sci_Position> m_pageBreaks;
    CString m_header;
    Sci_RangeToFormatFull m_fr;
    SciFnDirect m_directFunction;
    LRESULT m_directPointer;
    HMODULE m_module;
};

#endif // SCINTILLAVIEW_H