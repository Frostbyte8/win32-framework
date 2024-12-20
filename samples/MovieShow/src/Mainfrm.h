/////////////////////////////////////////////
// Mainfrm.h

#ifndef MAINFRM_H
#define MAINFRM_H

#include "Tree.h"
#include "List.h"
#include "MyDialog.h"
#include "CoverImage.h"
#include "SplashThread.h"
#include "MovieInfo.h"

// Support older compilers.
#ifndef WM_DPICHANGED
#define WM_DPICHANGED                   0x02E0
#endif

///////////////////////////////////////////////////////////
// CMainFrame manages the application's main window.
// The main window is a frame that has a menubar, toolbar,
// statusbar and view window.
class CMainFrame : public CDockFrame
{
public:
    struct FoundFileInfo
    {
        CString     fileName;
        FILETIME    lastModifiedTime;
    };

    CMainFrame();
    virtual ~CMainFrame() override;
    CMainFrame(const CMainFrame&) = delete;               // Disable copy construction
    CMainFrame& operator=(const CMainFrame&) = delete;    // Disable assignment operator

    virtual HWND Create(HWND parent = nullptr) override;
    void SetCaptionColor(COLORREF color);

protected:
    // Virtual functions that override base class functions
    virtual BOOL    LoadRegistrySettings(LPCTSTR szKeyName) override;
    virtual void    OnClose() override;
    virtual BOOL    OnCommand(WPARAM wparam, LPARAM lparam) override;
    virtual int     OnCreate(CREATESTRUCT& cs) override;
    virtual void    OnInitialUpdate() override;
    virtual void    OnMenuUpdate(UINT nID) override;
    virtual LRESULT OnNotify(WPARAM wparam, LPARAM lparam) override;
    virtual void    PreCreate(CREATESTRUCT& cs) override;
    virtual BOOL    SaveRegistrySettings() override;
    virtual void    SetupMenuIcons() override;
    virtual void    SetupToolBar() override;
    virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam) override;

private:
    static UINT WINAPI ThreadProc(void* pVoid);

    // Accessors
    std::vector<CString> GetBoxSets();
    CString GetDataPath() const;
    std::list<MovieInfo>* GetMoviesData() { return &m_moviesData; }
    CViewDialog& GetViewDialog()          { return m_pDockDialog->GetViewDialog(); }
    CViewList& GetViewList()              { return m_viewList; }
    CViewTree& GetViewTree()              { return m_pDockTree->GetViewTree(); }
    std::vector<CString> GetWords(const CString& str) const;

    // State functions
    bool IsWordInString(const CString& sentence, const CString& word) const;
    bool IsVideoFile(const CString& filename) const;

    void ClearDisplay();
    void ClearList();
    void FillImageData(const CString& source, std::vector<BYTE>& dest);
    void FillList();
    void FillListFromAllBoxSets();
    void FillListFromBoxSet(LPCTSTR boxset);
    void FillListFromDateRange(LPCTSTR dateRange);
    void FillListFromFlags(DWORD dwMask);
    void FillListFromGenre(LPCTSTR genre);
    void FillListFromGenres(LPCTSTR genreList);
    void FillListFromSearch();
    void FillListFromType(LPCTSTR videoType);
    void FillTreeItems();
    void ForceToForeground();
    void LoadMovieInfoFromFile(const FoundFileInfo& ffi, MovieInfo& movie);
    void LoadMovies();
    void OnFilesLoaded();

    // Message handlers
    LRESULT OnBoxSetChanged();
    LRESULT OnBarEnd(LPDRAGPOS pDragPos);
    LRESULT OnRClickListItem();
    LRESULT OnRClickTreeItem();
    LRESULT OnSelectListItem(const MovieInfo* pmi);
    LRESULT OnSelectTreeItem();
    LRESULT OnSysCommand(UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT OnWindowPosChanging(UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT PlayMovie(LPCTSTR path);

    // Command handlers
    BOOL    OnAddBoxSet();
    BOOL    OnAddFolder();
    BOOL    OnBoxSet(UINT nID);
    BOOL    OnFavourite();
    BOOL    OnPlay();
    BOOL    OnMoveDown();
    BOOL    OnMoveUp();
    BOOL    OnRenameBoxSet();
    BOOL    OnRemoveBoxSet();
    BOOL    OnRemoveFile();
    BOOL    OnSearch();
    BOOL    OnVideoType(LPCTSTR videoType);
    BOOL    OnWatchList();

    // Member variables
    CCriticalSection m_cs;
    CViewList        m_viewList;
    CWorkThread      m_thread;
    CSplashThread    m_splashThread;
    std::vector<FoundFileInfo> m_filesToAdd;
    std::vector<const MovieInfo*> m_foundMovies;
    HTREEITEM        m_searchItem;

    // Use lists because pointers to members of a list are always valid.
    std::list<CString> m_boxSets;
    std::list<CString> m_decades;
    std::list<CString> m_genres;

    MoviesData   m_moviesData;
    CImageList   m_toolbarImages;
    CMenu        m_boxSetMenu;
    CMenu        m_popupMenu;

    CDockTree*   m_pDockTree;
    CDockDialog* m_pDockDialog;
    CEvent       m_stopRequest;     // An event to signal the event thread should stop
    bool         m_isDirty;         // Has m_MoviesData has been modified?
    HTREEITEM    m_boxSetsItem;
    int          m_dialogHeight;
    int          m_treeWidth;
};

#endif //MAINFRM_H
