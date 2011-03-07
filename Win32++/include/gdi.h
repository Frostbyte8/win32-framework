// Win32++  PreRelease Version 7.1
// Released: N/A
//
//      David Nash
//      email: dnash@bigpond.net.au
//      url: https://sourceforge.net/projects/win32-framework
//
//
// Copyright (c) 2005-2011  David Nash
//
// Permission is hereby granted, free of charge, to
// any person obtaining a copy of this software and
// associated documentation files (the "Software"),
// to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice
// shall be included in all copies or substantial portions
// of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// gdi.h
//  Declaration of the CDC class, and CBitmapInfoPtr class

// The CDC class provides a device context, along with the various associated
//  objects such as Bitmaps, Brushes, Bitmaps, Fonts and Pens. This class
//  handles the creation, selection, de-selection and deletion of these objects
//  automatically. It also automatically deletes or releases the device context
//  itself as appropriate. Any failure to create the new GDI object throws an
//  exception.
//
// Coding Exampe without CDC ...
//  HDC hDC = ::CreateCompatibleDC(SomeHDC);
//  HPEN hPen = :: CreatePen(PS_SOLID, 1, RGB(255,0,0);
//  HPEN hPenOld = (HPEN)::SelectObject(hDC, hPen);
//	::MoveToEx(hDC, 0, 0, NULL);
//  ::LineTo(hDC, 50, 50);
//  ::SelectObject(hDC, hPenOld);
//  ::DeleteObject(hPen);
//  ::DeleteDC(hDC);
//
// Coding Example with CDC ...
//  CDC DrawDC = ::CreateCompatibleDC(SomeHDC);
//  DrawDC.CreatePen(PS_SOLID, 1, RGB(255,0,0);
//	DrawDC.MoveTo(0, 0);
//  DrawDC.LineTo(50, 50);
//
// When the CDC object drops out of scope, it's destructor is called, cleaning up
//  the GDI objects and device context.
//
// Notes:
//  * A device context assigned to a CDC object will be released or deleted, unless
//     it is detached.
//  * A GDI object created by one of the CDC member functions will be deleted when
//     the CDC object is destroyed, unless it is detached.
//  * The GDI objects attached to the CDC (by using AttachPen for example) are not
//     deleted when the CDC goes out of scope. Only GDI objects created by the CDC
//     are automatically deleted.
//  * GDI objects belonging to the GDI classes (eg. CPen) are automatically deleted
//     when the class object goes out of scope.
//  * The various AttachXXX functions can attach either a gdi handle (eg HPEN) or
//     a gdi class object (eg CPen).
//  * A GDI object (with the exception of regions) can only be selected into one
//     device context at a time.
//  * Set the region's shape before selecting it into a DC.

// The CBitmapInfoPtr class is a convienient wrapper for the BITMAPINFO structure.
// The size of the BITMAPINFO structure is dependant on the type of HBITMAP, and its
// space needs to be allocated dynamically. CBitmapInfoPtr automatically allocates
// and deallocates the memory for the structure. A CBitmapInfoPtr object can be
// used anywhere in place of a LPBITMAPINFO. LPBITMAPINFO is used in functions like
// GetDIBits and SetDIBits.
//
// Coding example ...
//  CDC MemDC = CreateCompatibleDC(NULL);
//  CBitmapInfoPtr pbmi(hBitmap);
//  MemDC.GetDIBits(hBitmap, 0, pbmi->bmiHeader.biHeight, NULL, pbmi, DIB_RGB_COLORS);

#ifndef _GDI_H_
#define _GDI_H_

#include "wincore.h"

namespace Win32xx
{

	/////////////////////////////////////////////////////////////////
	// Declarations for some global functions in the Win32xx namespace
	//
#ifndef _WIN32_WCE
	void GrayScaleBitmap( HBITMAP hbmSource );
	void TintBitmap( HBITMAP hbmSource, int cRed, int cGreen, int cBlue );
	HIMAGELIST CreateDisabledImageList( HIMAGELIST himlNormal );
#endif


	///////////////////////////////////////////////
	// Declarations for the CBitmap class
	//
	class CBitmap
	{
	  public:
		struct DataMembers	// A structure that contains the data members for CBitmap
		{
			HBITMAP hBitmap;
			long	Count;
		};

		CBitmap ();
		CBitmap (HBITMAP hBitmap);
		CBitmap (LPCTSTR lpstr);
		CBitmap (int nID);
		CBitmap (const CBitmap& rhs);
		operator HBITMAP () const;
		void operator = (HBITMAP hBitmap);
		CBitmap& operator = (const CBitmap& rhs);
		~CBitmap ();

		void Attach( HBITMAP hBitmap );
		HBITMAP Detach ();

		// Create and load methods
		HBITMAP LoadBitmap (LPCTSTR lpstr);
		HBITMAP LoadBitmap (int nID);
		HBITMAP LoadImage(LPCTSTR lpszName, int cxDesired, int cyDesired, UINT fuLoad);
		HBITMAP LoadImage(UINT nID, int cxDesired, int cyDesired, UINT fuLoad);
		void LoadOEMBitmap (UINT nIDBitmap);
		void CreateBitmap (int nWidth, int nHeight, UINT nPlanes, UINT nBitsPerPixel, const void* lpBits);
		void CreateCompatibleBitmap (HDC hDC, int nWidth, int nHeight);

		// Attributes
		BITMAP GetBitmap () const;
		void CreateDIBSection (HDC hDC, CONST BITMAPINFO* lpbmi, UINT uColorUse, VOID** ppvBits, HANDLE hSection, DWORD dwOffset);

#ifndef _WIN32_WCE
		int GetDIBits (HDC hDC, UINT uStartScan, UINT cScanLines,  LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT uColorUse) const;
		int SetDIBits (HDC hDC, UINT uStartScan, UINT cScanLines, CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT uColorUse);
		HBITMAP LoadMappedBitmap (UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = NULL, int nMapSize = 0);
		void CreateBitmapIndirect (LPBITMAP lpBitmap);
		void CreateDiscardableBitmap (HDC hDC, int nWidth, int nHeight);
		CSize GetBitmapDimensionEx () const;
		CSize SetBitmapDimensionEx (int nWidth, int nHeight);

		// DIB support
		HBITMAP CreateDIBitmap (HDC hDC, CONST BITMAPINFOHEADER* lpbmih, DWORD dwInit, CONST VOID* lpbInit, CONST BITMAPINFO* lpbmi, UINT uColorUse);
#endif // !_WIN32_WCE

	private:
		void Release();
		DataMembers* m_pData;					// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CBrush class
	//
	class CBrush
	{
	  public:
		struct DataMembers	// A structure that contains the data members for CBrush
		{
			HBRUSH hBrush;
			long	Count;
		};

		CBrush ();
		CBrush (HBRUSH hBrush);
		CBrush (COLORREF crColor);
		CBrush (const CBrush& rhs);
		operator HBRUSH () const;
		void operator = (HBRUSH hBrush);
		CBrush& operator = (const CBrush& rhs);
		~CBrush ();

		void Attach (HBRUSH hBrush);
		HBRUSH Detach ();
		void CreateSolidBrush (COLORREF crColor);
		void CreatePatternBrush (HBITMAP hBitmap);
		void CreateDIBPatternBrushPt (LPCVOID lpPackedDIB, UINT nUsage);
		void CreateSysColorBrush (int nIndex);
		LOGBRUSH GetLogBrush () const;

#ifndef _WIN32_WCE
		void CreateHatchBrush (int nIndex, COLORREF crColor);
		void CreateBrushIndirect (LPLOGBRUSH lpLogBrush);
#endif // !defined(_WIN32_WCE)

	  private:
		void Release();
		DataMembers* m_pData;						// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CFont class
	//
	class CFont
	{
	public:
		struct DataMembers	// A structure that contains the data members for CFont
		{
			HFONT hFont;
			long	Count;
		};

		CFont ();
		CFont (HFONT hFont);
		CFont (const CFont& rhs);
		operator HFONT () const;
		void operator = (HFONT hFont);
		CFont& operator = (const CFont& rhs);
		~CFont ();

		void Attach (HFONT hFont);
		HFONT Detach ();

		// Create methods
		void CreateFontIndirect (const LOGFONT* lpLogFont);
		LOGFONT GetLogFont () const;
		void CreatePointFont (int nPointSize, LPCTSTR lpszFaceName, HDC hDC = NULL, BOOL bBold = FALSE, BOOL bItalic = FALSE);
		void CreatePointFontIndirect (const LOGFONT* lpLogFont, HDC hDC = NULL);

#ifndef _WIN32_WCE
//		void CreateFontIndirectEx (const ENUMLOGFONTEXDV* penumlfex);
		void CreateFont (int nHeight, int nWidth, int nEscapement,
				int nOrientation, int nWeight, DWORD dwItalic, DWORD dwUnderline,
				DWORD dwStrikeOut, DWORD dwCharSet, DWORD dwOutPrecision,
				DWORD dwClipPrecision, DWORD dwQuality, DWORD dwPitchAndFamily,
				LPCTSTR lpszFacename);
#endif // #ifndef _WIN32_WCE

	  private:
		void Release();
		DataMembers* m_pData;				// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CPalette class
	//
	class CPalette
	{
	  public:
		struct DataMembers	// A structure that contains the data members for CPalette
		{
			HPALETTE hPalette;
			long	Count;
		};

		CPalette ();
		CPalette (HPALETTE hPalette);
		CPalette (const CPalette& rhs);
		operator HPALETTE () const;
		void operator = (HPALETTE hPalette);
		CPalette& operator = (const CPalette& rhs);
		~CPalette ();

		void Attach (HPALETTE hPalette);
		HPALETTE Detach ();

		// Create methods
		void CreatePalette (LPLOGPALETTE lpLogPalette);

#ifndef _WIN32_WCE
		void CreateHalftonePalette (HDC hDC);
#endif // !_WIN32_WCE

		// Attributes
		int GetEntryCount () const;
		UINT GetPaletteEntries (UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
		UINT SetPaletteEntries (UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);

		// Operations
#ifndef _WIN32_WCE
		BOOL ResizePalette (UINT nNumEntries);
		void AnimatePalette (UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
#endif // !_WIN32_WCE

		UINT GetNearestPaletteIndex (COLORREF crColor) const;

	  private:
		void Release();
		DataMembers* m_pData;					// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CPen class
	//
	class CPen
	{
	public:
		struct DataMembers	// A structure that contains the data members for CPen
		{
			HPEN hPen;
			long Count;
		};

		CPen ();
		CPen (HPEN hPen);
		CPen (int nPenStyle, int nWidth, COLORREF crColor);
#ifndef _WIN32_WCE
		CPen (int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL);
#endif // !_WIN32_WCE
		CPen (const CPen& rhs);
		operator HPEN () const;
		void operator= (HPEN hPen);
		CPen& operator = (const CPen& rhs);
		~CPen ();

		void Attach (HPEN hPen);
		HPEN Detach ();

		void CreatePen (int nPenStyle, int nWidth, COLORREF crColor);
		void CreatePenIndirect (LPLOGPEN lpLogPen);
		LOGPEN GetLogPen () const;

#ifndef _WIN32_WCE
		void ExtCreatePen (int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL);
		EXTLOGPEN GetExtLogPen () const;
#endif // !_WIN32_WCE

	  private:
		void Release();
		DataMembers* m_pData;				// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CRgn class
	//
	class CRgn
	{
	  public:
		struct DataMembers	// A structure that contains the data members for CRgn
		{
			HRGN hRgn;
			long Count;
		};

		CRgn ();
		CRgn (HRGN hRgn);
		CRgn (const CRgn& rhs);
		operator HRGN () const;
		void operator = (HRGN hRgn);
		CRgn& operator = (const CRgn& rhs);
		~CRgn ();

		void Attach (HRGN hRgn);
		HRGN Detach ();

		// Create methods
		void CreateRectRgn (int x1, int y1, int x2, int y2);
		void CreateRectRgnIndirect (LPCRECT lpRect);

#ifndef _WIN32_WCE
		void CreateEllipticRgn (int x1, int y1, int x2, int y2);
		void CreateEllipticRgnIndirect (LPCRECT lpRect);
		void CreatePolygonRgn (LPPOINT lpPoints, int nCount, int nMode);
		void CreatePolyPolygonRgn (LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode);
		void CreateRoundRectRgn (int x1, int y1, int x2, int y2, int x3, int y3);
		void CreateFromPath (HDC hDC);
#endif // !_WIN32_WCE

		void CreateFromData (const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData);

		// Operations
		void SetRectRgn (int x1, int y1, int x2, int y2);
		void SetRectRgn (LPCRECT lpRect);
		int CombineRgn (HRGN hRgnSrc1, HRGN hRgnSrc2, int nCombineMode);
		int CombineRgn (HRGN hRgnSrc, int nCombineMode);
		int CopyRgn (HRGN hRgnSrc);
		BOOL EqualRgn (HRGN hRgn) const;
		int OffsetRgn (int x, int y);
		int OffsetRgn (POINT point);
		int GetRgnBox (LPRECT lpRect) const;
		BOOL PtInRegion (int x, int y) const;
		BOOL PtInRegion (POINT point) const;
		BOOL RectInRegion (LPCRECT lpRect) const;
		int GetRegionData (LPRGNDATA lpRgnData, int nDataSize) const;

	  private:
		void Release();
		DataMembers* m_pData;				// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CDC class
	//
	class CDC
	{
	public:
		struct DataMembers	// A structure that contains the data members for CDC
		{
			CBitmap Bitmap;
			CBrush	Brush;
			CFont	Font;
			CPen	Pen;
			CRgn	Rgn;
			HDC		hDC;
			HBITMAP hBitmapOld;
			HBRUSH	hBrushOld;
			HFONT	hFontOld;
			HPEN	hPenOld;
			long	Count;
		};

		CDC ();									// Constructs a new CDC without assigning a HDC
		CDC (HDC hDC);							// Assigns a HDC to a new CDC
		CDC (const CDC& rhs);					// Constructs a new copy of the CDC
		void operator = (const HDC hDC);		// Assigns a HDC to an existing CDC
		CDC& operator = (const CDC& rhs);		// Assigns a CDC to an existing CDC
		operator HDC () const { return m_pData->hDC; }	// Converts a CDC to a HDC
		virtual ~CDC ();

		void AttachDC (HDC hDC);
		HDC  DetachDC ();
		HDC GetHDC () const { return m_pData->hDC; }
		static CDC* FromHandle(HDC hDC);

		// Create and Select Bitmaps
		void AttachBitmap (HBITMAP hBitmap);
		void CreateBitmap (int cx, int cy, UINT Planes, UINT BitsPerPixel, CONST VOID *pvColors);
		void CreateCompatibleBitmap (HDC hDC, int cx, int cy);
		void CreateDIBSection (HDC hdc, const BITMAPINFO& bmi, UINT iUsage, VOID **ppvBits,
										HANDLE hSection, DWORD dwOffset);
		HBITMAP DetachBitmap ();
		BITMAP GetBitmapInfo ();
		void LoadBitmap (UINT nID);
		void LoadBitmap (LPCTSTR lpstr);
		void LoadImage(UINT nID, int cxDesired, int cyDesired, UINT fuLoad);
		void LoadImage(LPCTSTR lpszName, int cxDesired, int cyDesired, UINT fuLoad);
		void LoadOEMBitmap (UINT nIDBitmap); // for OBM_/OCR_/OIC

#ifndef _WIN32_WCE
		void CreateBitmapIndirect (LPBITMAP pBitmap);
		void CreateDIBitmap(HDC hdc, const BITMAPINFOHEADER& bmih, DWORD fdwInit, CONST VOID *lpbInit,
										BITMAPINFO& bmi, UINT fuUsage);
		void LoadMappedBitmap (UINT nIDBitmap, UINT nFlags /*= 0*/, LPCOLORMAP lpColorMap /*= NULL*/, int nMapSize /*= 0*/);
#endif

		// Create and Select Brushes
		void AttachBrush (HBRUSH hBrush);
		void CreateDIBPatternBrushPt (LPCVOID lpPackedDIB, UINT iUsage);
		void CreatePatternBrush (HBITMAP hbmp);
		void CreateSolidBrush (COLORREF rbg);
		HBRUSH DetachBrush ();
		LOGBRUSH GetBrushInfo ();

#ifndef _WIN32_WCE
		void CreateBrushIndirect (LPLOGBRUSH& pLogBrush);
		void CreateHatchBrush (int fnStyle, COLORREF rgb);
#endif

		// Create and Select Fonts
		void AttachFont (HFONT hFont);
		void CreateFontIndirect (const LOGFONT& lf);
		HFONT DetachFont ();
		LOGFONT GetFontInfo ();

#ifndef _WIN32_WCE
		void CreateFont (int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight,
  							DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet,
  							DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality,
  							DWORD fdwPitchAndFamily, LPCTSTR lpszFace);
#endif

		// Create and Select Pens
		void AttachPen (HPEN hPen);
		void CreatePen (int nStyle, int nWidth, COLORREF rgb);
		void CreatePenIndirect (LPLOGPEN pLogPen);
		HPEN DetachPen ();
		LOGPEN GetPenInfo ();

		// Create Select Regions
		void CreateRectRgn (int left, int top, int right, int bottom);
		void CreateRectRgnIndirect (const RECT& rc);
		void CreateFromData (const XFORM* Xform, DWORD nCount, const RGNDATA *pRgnData);
#ifndef _WIN32_WCE
		void CreateEllipticRgn (int left, int top, int right, int bottom);
		void CreateEllipticRgnIndirect (const RECT& rc);
		void CreatePolygonRgn (LPPOINT ppt, int cPoints, int fnPolyFillMode);
		void CreatePolyPolygonRgn (LPPOINT ppt, LPINT pPolyCounts, int nCount, int fnPolyFillMode);
#endif

		// Wrappers for WinAPI functions

		// Initialization
		HDC CreateCompatibleDC () const;
		HDC CreateDC (LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, const DEVMODE& dvmInit) const;
		int GetDeviceCaps (int nIndex) const;
#ifndef _WIN32_WCE
		HDC CreateIC (LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, const DEVMODE& dvmInit) const;
#endif

		// Point and Line Drawing Functions
		CPoint GetCurrentPosition () const;
		CPoint MoveTo (int x, int y) const;
		CPoint MoveTo (POINT pt) const;
		BOOL LineTo (int x, int y) const;
		BOOL LineTo (POINT pt) const;
		COLORREF GetPixel (int x, int y) const;
		COLORREF GetPixel (POINT pt) const;
		COLORREF SetPixel (int x, int y, COLORREF crColor) const;
		COLORREF SetPixel (POINT pt, COLORREF crColor) const;
#ifndef _WIN32_WCE
		BOOL Arc (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const;
		BOOL Arc (RECT& rc, POINT ptStart, POINT ptEnd) const;
		BOOL ArcTo (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const;
		BOOL ArcTo (RECT& rc, POINT ptStart, POINT ptEnd) const;
		BOOL AngleArc (int x, int y, int nRadius, float fStartAngle, float fSweepAngle) const;
		int GetArcDirection () const;
		int SetArcDirection (int nArcDirection) const;
		BOOL PolyDraw (const POINT* lpPoints, const BYTE* lpTypes, int nCount) const;
		BOOL Polyline (LPPOINT lpPoints, int nCount) const;
		BOOL PolyPolyline (const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount) const;
		BOOL PolylineTo (const POINT* lpPoints, int nCount) const;
		BOOL PolyBezier (const POINT* lpPoints, int nCount) const;
		BOOL PolyBezierTo (const POINT* lpPoints, int nCount) const;
		BOOL SetPixelV (int x, int y, COLORREF crColor) const;
		BOOL SetPixelV (POINT pt, COLORREF crColor) const;
#endif

		// Shape Drawing Functions
		void DrawFocusRect (const RECT& rc) const;
		BOOL Ellipse (int x1, int y1, int x2, int y2) const;
		BOOL Ellipse (const RECT& rc) const;
		BOOL Polygon (LPPOINT lpPoints, int nCount) const;
		BOOL Rectangle (int x1, int y1, int x2, int y2) const;
		BOOL Rectangle (const RECT& rc) const;
		BOOL RoundRect (int x1, int y1, int x2, int y2, int nWidth, int nHeight) const;
		BOOL RoundRect (const RECT& rc, int nWidth, int nHeight) const;
		
#ifndef _WIN32_WCE
		BOOL Chord (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const;
		BOOL Chord (const RECT& rc, POINT ptStart, POINT ptEnd) const;
		BOOL Pie (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const;
		BOOL Pie (const RECT& rc, POINT ptStart, POINT ptEnd) const;
		BOOL PolyPolygon (LPPOINT lpPoints, LPINT lpPolyCounts, int nCount) const;
#endif

		// Fill and Image Drawing functions
		BOOL FillRect (const RECT& rc, HBRUSH hbr) const;
		BOOL InvertRect (const RECT& rc) const;
		BOOL DrawIconEx (int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) const;
		BOOL DrawEdge (const RECT& rc, UINT nEdge, UINT nFlags) const;
		BOOL DrawFrameControl (const RECT& rc, UINT nType, UINT nState) const;
		BOOL FillRgn (HRGN hrgn, HBRUSH hbr) const;
		virtual void GradientFill (COLORREF Color1, COLORREF Color2, const RECT& rc, BOOL bVertical);
		virtual void SolidFill (COLORREF Color, const RECT& rc);
		
#ifndef _WIN32_WCE
		BOOL DrawIcon (int x, int y, HICON hIcon) const;
		BOOL DrawIcon (POINT point, HICON hIcon) const;
		BOOL FrameRect (const RECT& rc, HBRUSH hbr) const;
		BOOL PaintRgn (HRGN hrgn) const;
#endif

		// Bitmap Functions
		virtual void DrawBitmap (int x, int y, int cx, int cy, HBITMAP hbmImage, COLORREF clrMask);
		int StretchDIBits (int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth,
			           int nSrcHeight, CONST VOID *lpBits, BITMAPINFO& bi, UINT iUsage, DWORD dwRop) const;
		BOOL PatBlt (int x, int y, int nWidth, int nHeight, DWORD dwRop) const;
		BOOL BitBlt (int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, DWORD dwRop) const;
		BOOL StretchBlt (int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop) const;
		
#ifndef _WIN32_WCE
		int GetDIBits (HBITMAP hbmp, UINT uStartScan, UINT cScanLines, LPVOID lpvBits, LPBITMAPINFO lpbi, UINT uUsage) const;
		int SetDIBits (HBITMAP hbmp, UINT uStartScan, UINT cScanLines, CONST VOID *lpvBits, LPBITMAPINFO lpbi, UINT fuColorUse) const;
		int GetStretchBltMode () const;
		int SetStretchBltMode (int iStretchMode) const;
		BOOL FloodFill (int x, int y, COLORREF crColor) const;
		BOOL ExtFloodFill (int x, int y, COLORREF crColor, UINT nFillType) const;
#endif

		// Clipping Functions
		int ExcludeClipRect (int Left, int Top, int Right, int BottomRect );
		int ExcludeClipRect (const RECT& rc);
		int GetClipBox (RECT& rc);			
		int GetClipRgn (HRGN hrgn);				
		int IntersectClipRect (int Left, int Top, int Right, int Bottom);
		int IntersectClipRect (const RECT& rc);
		BOOL RectVisible (const RECT& rc);
		int SelectClipRgn (HRGN hrgn);

#ifndef _WIN32_WCE
		int OffsetClipRgn (int nXOffset, int nYOffset);
		BOOL PtVisible (int X, int Y);
#endif

        // Co-ordinate Functions
#ifndef _WIN32_WCE
		BOOL DPtoLP (LPPOINT lpPoints, int nCount )  const;
		BOOL DPtoLP (LPRECT lpRect)  const;
		BOOL LPtoDP (LPPOINT lpPoints, int nCount )  const;
		BOOL LPtoDP (LPRECT lpRect)  const;
#endif

		// Layout Functions
		DWORD GetLayout () const;
		DWORD SetLayout (DWORD dwLayout) const;

		// Mapping functions
#ifndef _WIN32_WCE
		int GetMapMode ()  const;
		int SetMapMode (int nMapMode) const;
		BOOL GetViewportOrgEx (LPPOINT lpPoint)  const;
		BOOL SetViewportOrgEx (int x, int y, LPPOINT lpPoint = NULL) const;
		BOOL SetViewportOrgEx (POINT point, LPPOINT lpPointRet = NULL) const;
		BOOL OffsetViewportOrgEx (int nWidth, int nHeight, LPPOINT lpPoint = NULL ) const;
		BOOL GetViewportExtEx (LPSIZE lpSize)  const;
		BOOL SetViewportExtEx (int x, int y, LPSIZE lpSize ) const;
		BOOL SetViewportExtEx (SIZE size, LPSIZE lpSizeRet ) const;
		BOOL ScaleViewportExtEx (int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize ) const;
		BOOL OffsetWindowOrg (int nWidth, int nHeight, LPPOINT lpPoint ) const;
		BOOL GetWindowExtEx (LPSIZE lpSize)  const;
		BOOL SetWindowExtEx (int x, int y, LPSIZE lpSize ) const;
		BOOL SetWindowExtEx (SIZE size, LPSIZE lpSizeRet) const;
		BOOL ScaleWindowExtEx (int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize) const;
		BOOL GetWindowOrgEx (LPPOINT lpPoint)  const;
		BOOL SetWindowOrgEx (int x, int y, LPPOINT lpPoint ) const;
		BOOL SetWindowOrgEx (POINT point, LPPOINT lpPointRet ) const;
		BOOL OffsetWindowOrgEx (int nWidth, int nHeight, LPPOINT lpPoint ) const;
#endif

		// Printer Functions
		int StartDoc (LPDOCINFO lpDocInfo) const;
		int EndDoc () const;
		int StartPage () const;
		int EndPage () const;
		int AbortDoc () const;
		int SetAbortProc (BOOL (CALLBACK* lpfn)(HDC, int)) const;

		// Text Functions
		BOOL ExtTextOut (int x, int y, UINT nOptions, LPCRECT lprc, LPCTSTR lpszString, int nCount = -1, LPINT lpDxWidths = NULL) const;
		int DrawText (LPCTSTR lpszString, int nCount, LPRECT lprc, UINT nFormat) const;
		UINT GetTextAlign () const;
		UINT SetTextAlign (UINT nFlags) const;
		int GetTextFace (int nCount, LPTSTR lpszFacename) const;
		BOOL GetTextMetrics (TEXTMETRIC& Metrics) const;
		COLORREF GetBkColor () const;
		COLORREF SetBkColor (COLORREF crColor) const;
		COLORREF GetTextColor () const;
		COLORREF SetTextColor (COLORREF crColor) const;
		int GetBkMode () const;
		int SetBkMode (int iBkMode) const;
		
#ifndef _WIN32_WCE
		CSize GetTextExtentPoint (LPCTSTR lpszString, int nCount) const;
		BOOL TextOut (int x, int y, LPCTSTR lpszString, int nCount = -1) const;
		CSize TabbedTextOut (int x, int y, LPCTSTR lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin) const;
		int DrawTextEx (LPTSTR lpszString, int nCount, LPRECT lprc, UINT nFormat, const DRAWTEXTPARAMS& DTParams) const;
		CSize GetTabbedTextExtent (LPCTSTR lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions) const;
		BOOL GrayString (HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight) const;
		int SetTextJustification (int nBreakExtra, int nBreakCount) const;
		int GetTextCharacterExtra () const;
		int SetTextCharacterExtra (int nCharExtra) const;
		CSize GetTextExtentPoint32 (LPCTSTR lpszString, int nCount) const;
#endif

	private:
		void AddToMap();
		void Release ();
		void RemoveCurrentBitmap ();
		void RemoveCurrentBrush ();
		void RemoveCurrentFont ();
		void RemoveCurrentPen ();
		void RemoveCurrentRgn ();
		BOOL RemoveFromMap();

		DataMembers* m_pData;		// pointer to the class's data members
	};


	///////////////////////////////////////////////
	// Declarations for the CBitmapInfoPtr class
	// The CBitmapInfoPtr class is a convienient wrapper for the BITMAPINFO structure.
	class CBitmapInfoPtr
	{
	public:
		CBitmapInfoPtr(HBITMAP hbm)
		{
			BITMAP bmSource;
			::GetObject(hbm, sizeof(BITMAP), &bmSource);

			// Convert the color format to a count of bits.
			WORD cClrBits = (WORD)(bmSource.bmPlanes * bmSource.bmBitsPixel);
			if (cClrBits == 1) 	     cClrBits = 1;
			else if (cClrBits <= 4)  cClrBits = 4;
			else if (cClrBits <= 8)  cClrBits = 8;
			else if (cClrBits <= 16) cClrBits = 16;
			else if (cClrBits <= 24) cClrBits = 24;
			else                     cClrBits = 32;

			// Allocate memory for the BITMAPINFO structure.
			UINT uQuadSize = (cClrBits == 24)? 0 : sizeof(RGBQUAD) * (int)(1 << cClrBits);
			m_bmi.assign(sizeof(BITMAPINFOHEADER) + uQuadSize, 0);
			m_pbmiArray = (LPBITMAPINFO) &m_bmi.front();

			m_pbmiArray->bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
			m_pbmiArray->bmiHeader.biHeight		= bmSource.bmHeight;
			m_pbmiArray->bmiHeader.biWidth		= bmSource.bmWidth;
			m_pbmiArray->bmiHeader.biPlanes		= bmSource.bmPlanes;
			m_pbmiArray->bmiHeader.biBitCount	= bmSource.bmBitsPixel;
			m_pbmiArray->bmiHeader.biCompression = BI_RGB;
			if (cClrBits < 24)
				m_pbmiArray->bmiHeader.biClrUsed = (1<<cClrBits);
		}
		LPBITMAPINFO get() const { return m_pbmiArray; }
		operator LPBITMAPINFO() const { return m_pbmiArray; }
		LPBITMAPINFO operator->() const { return m_pbmiArray; }

	private:
		CBitmapInfoPtr(const CBitmapInfoPtr&);				// Disable copy construction
		CBitmapInfoPtr& operator = (const CBitmapInfoPtr&);	// Disable assignment operator
		LPBITMAPINFO m_pbmiArray;
		std::vector<byte> m_bmi;
	};

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


namespace Win32xx
{
	///////////////////////////////////////////////
	// Declarations for the CBitmap class
	//
	inline CBitmap::CBitmap ()
	{
		m_pData = new DataMembers;
		m_pData->hBitmap = 0;
		m_pData->Count = 1L;
	}

	inline CBitmap::CBitmap (HBITMAP hBitmap)
	{
		m_pData = new DataMembers;
		m_pData->hBitmap = hBitmap;
		m_pData->Count = 1L;
	}

	inline CBitmap::CBitmap (LPCTSTR lpstr)
	{
		m_pData = new DataMembers;
		m_pData->hBitmap = 0;
		LoadBitmap(lpstr);
		m_pData->Count = 1L;
	}

	inline CBitmap::CBitmap (int nID)
	{
		m_pData = new DataMembers;
		m_pData->hBitmap = 0;
		LoadBitmap(nID);
		m_pData->Count = 1L;
	}

	inline CBitmap::CBitmap (const CBitmap& rhs)
	{
		m_pData->hBitmap = rhs.m_pData->hBitmap;
		m_pData->Count = rhs.m_pData->Count;

		InterlockedIncrement(&m_pData->Count);
	}

	inline CBitmap::operator HBITMAP () const
	{
		return m_pData->hBitmap;
	}

	inline void CBitmap::operator = (HBITMAP hBitmap)
	{
		assert (m_pData->hBitmap == NULL);
		m_pData->hBitmap = hBitmap;
	}

	inline CBitmap& CBitmap::operator = ( const CBitmap& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}


	inline CBitmap::~CBitmap ()
	{
		Release();
	}

	inline void CBitmap::Attach (HBITMAP hBitmap)
	{
		if (m_pData->hBitmap != NULL && m_pData->hBitmap != hBitmap)
			::DeleteObject(m_pData->hBitmap);
		m_pData->hBitmap = hBitmap;
	}

	inline HBITMAP CBitmap::Detach ()
	{
		assert(m_pData->hBitmap);
		HBITMAP hBitmap = m_pData->hBitmap;
		m_pData->hBitmap = NULL;
		return hBitmap;
	}

	inline HBITMAP CBitmap::LoadBitmap (int nID)
	{
		return LoadBitmap(MAKEINTRESOURCE(nID));
	}

	inline HBITMAP CBitmap::LoadBitmap (LPCTSTR lpstr)
	{
		assert(m_pData->hBitmap == NULL);
		assert(GetApp());
		m_pData->hBitmap = ::LoadBitmap (GetApp()->GetResourceHandle(), lpstr);
		if (m_pData->hBitmap == NULL)
			m_pData->hBitmap = ::LoadBitmap (GetApp()->GetInstanceHandle(), lpstr);

		return m_pData->hBitmap;
	}

	inline HBITMAP CBitmap::LoadImage(UINT nID, int cxDesired, int cyDesired, UINT fuLoad)
	{
		return LoadImage(MAKEINTRESOURCE(nID), cxDesired, cyDesired, fuLoad);
	}

	inline HBITMAP CBitmap::LoadImage(LPCTSTR lpszName, int cxDesired, int cyDesired, UINT fuLoad)
	{
		assert(m_pData->hBitmap == NULL);
		assert(GetApp());
		m_pData->hBitmap = (HBITMAP)::LoadImage(GetApp()->GetResourceHandle(), lpszName, IMAGE_BITMAP, cxDesired, cyDesired, fuLoad);
		if (m_pData->hBitmap == NULL)
			m_pData->hBitmap = (HBITMAP)::LoadImage(GetApp()->GetInstanceHandle(), lpszName, IMAGE_BITMAP, cxDesired, cyDesired, fuLoad);

		return m_pData->hBitmap;
	}

	inline void CBitmap::LoadOEMBitmap (UINT nIDBitmap) // for OBM_/OCR_/OIC_
	{
		assert(m_pData->hBitmap == NULL);
		m_pData->hBitmap = ::LoadBitmap (NULL, MAKEINTRESOURCE(nIDBitmap));
		assert(m_pData->hBitmap);
	}

#ifndef _WIN32_WCE
		inline HBITMAP CBitmap::LoadMappedBitmap (UINT nIDBitmap, UINT nFlags /*= 0*/, LPCOLORMAP lpColorMap /*= NULL*/, int nMapSize /*= 0*/)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateMappedBitmap (GetApp()->GetResourceHandle(), nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize);
			if (m_pData->hBitmap == NULL)
				m_pData->hBitmap = ::CreateMappedBitmap (GetApp()->GetInstanceHandle(), nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize);

			return m_pData->hBitmap;
		}
#endif // !_WIN32_WCE

		inline void CBitmap::CreateBitmap (int nWidth, int nHeight, UINT nPlanes, UINT nBitsPerPixel, const void* lpBits)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateBitmap (nWidth, nHeight, nPlanes, nBitsPerPixel, lpBits);
			assert(m_pData->hBitmap);
		}

#ifndef _WIN32_WCE
		inline void CBitmap::CreateBitmapIndirect (LPBITMAP lpBitmap)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateBitmapIndirect(lpBitmap);
			assert(m_pData->hBitmap);
		}
#endif // !_WIN32_WCE

		inline void CBitmap::CreateCompatibleBitmap (HDC hDC, int nWidth, int nHeight)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
			assert(m_pData->hBitmap);
		}

#ifndef _WIN32_WCE
		inline void CBitmap::CreateDiscardableBitmap (HDC hDC, int nWidth, int nHeight)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateDiscardableBitmap(hDC, nWidth, nHeight);
			assert(m_pData->hBitmap);
		}
#endif // !_WIN32_WCE

		// Attributes
		inline BITMAP CBitmap::GetBitmap () const
		{
			assert(m_pData->hBitmap != NULL);
			BITMAP bmp = {0};
			::GetObject(m_pData->hBitmap, sizeof(BITMAP), &bmp);
			return bmp;
		}

#ifndef _WIN32_WCE
		inline CSize CBitmap::GetBitmapDimensionEx () const
		{
			assert(m_pData->hBitmap != NULL);
			CSize Size;
			::GetBitmapDimensionEx(m_pData->hBitmap, &Size);
			return Size;
		}

		inline CSize CBitmap::SetBitmapDimensionEx (int nWidth, int nHeight)
		{
			assert(m_pData->hBitmap != NULL);
			CSize Size;
			::SetBitmapDimensionEx(m_pData->hBitmap, nWidth, nHeight, Size);
			return Size;
		}

		// DIB support
		inline HBITMAP CBitmap::CreateDIBitmap (HDC hDC, CONST BITMAPINFOHEADER* lpbmih, DWORD dwInit, CONST VOID* lpbInit, CONST BITMAPINFO* lpbmi, UINT uColorUse)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateDIBitmap(hDC, lpbmih, dwInit, lpbInit, lpbmi, uColorUse);
			assert(m_pData->hBitmap);
			return m_pData->hBitmap;
		}
#endif // !_WIN32_WCE

		inline void CBitmap::CreateDIBSection (HDC hDC, CONST BITMAPINFO* lpbmi, UINT uColorUse, VOID** ppvBits, HANDLE hSection, DWORD dwOffset)
		{
			assert(m_pData->hBitmap == NULL);
			m_pData->hBitmap = ::CreateDIBSection(hDC, lpbmi, uColorUse, ppvBits, hSection, dwOffset);
			assert(m_pData->hBitmap);
		}

#ifndef _WIN32_WCE
		inline int CBitmap::GetDIBits (HDC hDC, UINT uStartScan, UINT cScanLines,  LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT uColorUse) const
		{
			assert(m_pData->hBitmap != NULL);
			return ::GetDIBits(hDC, m_pData->hBitmap, uStartScan, cScanLines,  lpvBits, lpbmi, uColorUse);
		}

		inline int CBitmap::SetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines, CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT uColorUse)
		{
			assert(m_pData->hBitmap != NULL);
			return ::SetDIBits(hDC, m_pData->hBitmap, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
		}
#endif // !_WIN32_WCE

		inline void CBitmap::Release()
		{
			BOOL bSucceeded = TRUE;

			if (InterlockedDecrement(&m_pData->Count) == 0)
			{
				if (m_pData->hBitmap != NULL)
					bSucceeded = ::DeleteObject(m_pData->hBitmap);

				delete m_pData;
			}

			assert(bSucceeded);
		}


	///////////////////////////////////////////////
	// Definitions of the CBrush class
	//
	inline CBrush::CBrush ()
	{
		m_pData = new DataMembers;
		m_pData->hBrush = 0;
		m_pData->Count = 1L;
	}

	inline CBrush::CBrush (HBRUSH hBrush)
	{
		m_pData = new DataMembers;
		m_pData->hBrush = hBrush;
		m_pData->Count = 1L;
	}

	inline CBrush::CBrush (COLORREF crColor)
	{
		m_pData->hBrush = ::CreateSolidBrush (crColor);
		assert (m_pData->hBrush);
	}

	inline CBrush::CBrush (const CBrush& rhs)
	{
		m_pData->hBrush = rhs.m_pData->hBrush;
		m_pData->Count = rhs.m_pData->Count;

		InterlockedIncrement(&m_pData->Count);
	}

	inline CBrush::operator HBRUSH () const
	{
		return m_pData->hBrush;
	}

	inline CBrush& CBrush::operator = ( const CBrush& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}


	inline CBrush::~CBrush ()
	{
		Release();
	}

	inline void CBrush::Attach (HBRUSH hBrush)
	{
		if (m_pData->hBrush != NULL && m_pData->hBrush != hBrush)
			::DeleteObject(m_pData->hBrush);
		m_pData->hBrush = hBrush;
	}

	inline HBRUSH CBrush::Detach ()
	{
		HBRUSH hBrush = m_pData->hBrush;
		m_pData->hBrush = NULL;
		return hBrush;
	}

	inline void CBrush::CreateSolidBrush (COLORREF crColor)
	{
		assert(m_pData->hBrush == NULL);
		m_pData->hBrush = ::CreateSolidBrush (crColor);
		assert (m_pData->hBrush);
	}

#ifndef _WIN32_WCE
	inline void CBrush::CreateHatchBrush (int nIndex, COLORREF crColor)
	{
		assert(m_pData->hBrush == NULL);
		m_pData->hBrush = ::CreateHatchBrush (nIndex, crColor);
		assert (m_pData->hBrush);
	}

	inline void CBrush::CreateBrushIndirect (LPLOGBRUSH lpLogBrush)
	{
		assert(m_pData->hBrush == NULL);
		m_pData->hBrush = ::CreateBrushIndirect (lpLogBrush);
		assert (m_pData->hBrush);
	}
#endif // !defined(_WIN32_WCE)

	inline void CBrush::CreatePatternBrush (HBITMAP hBitmap)
	{
		assert(m_pData->hBrush == NULL);
		m_pData->hBrush = ::CreatePatternBrush (hBitmap);
		assert (m_pData->hBrush);
	}

	inline void CBrush::CreateDIBPatternBrushPt (LPCVOID lpPackedDIB, UINT nUsage)
	{
		assert(m_pData->hBrush == NULL);
		m_pData->hBrush = ::CreateDIBPatternBrushPt (lpPackedDIB, nUsage);
		assert (m_pData->hBrush);
	}

	inline void CBrush::CreateSysColorBrush (int nIndex)
	{
		assert(m_pData->hBrush == NULL);
		m_pData->hBrush = ::GetSysColorBrush (nIndex);
		assert (m_pData->hBrush);
	}

	inline LOGBRUSH CBrush::GetLogBrush () const
	{
		assert(m_pData->hBrush != NULL);
		LOGBRUSH LogBrush = {0};
		::GetObject (m_pData->hBrush, sizeof(LOGBRUSH), &LogBrush);
		return LogBrush;
	}

	inline void CBrush::Release()
	{
		BOOL bSucceeded = TRUE;

		if (InterlockedDecrement(&m_pData->Count) == 0)
		{
			if (m_pData->hBrush != NULL)
				bSucceeded = ::DeleteObject(m_pData->hBrush);

			delete m_pData;
		}

		assert(bSucceeded);
	}


	///////////////////////////////////////////////
	// Definitions of the CFont class
	//
	inline CFont::CFont ()
	{
		m_pData = new DataMembers;
		m_pData->hFont = 0;
		m_pData->Count = 1L;
	}

	inline CFont::CFont (HFONT hFont)
	{
		m_pData = new DataMembers;
		m_pData->hFont = hFont;
		m_pData->Count = 1L;
	}

	inline CFont::CFont (const CFont& rhs)
	{
		m_pData->hFont = rhs.m_pData->hFont;
		m_pData->Count = rhs.m_pData->Count;

		InterlockedIncrement(&m_pData->Count);
	}

	inline void CFont::operator = (HFONT hFont)
	{
		assert (m_pData->hFont == NULL);
		m_pData->hFont = hFont;
	}

	inline CFont::operator HFONT () const
	{
		return m_pData->hFont;
	}

	inline CFont& CFont::operator = ( const CFont& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}

	inline CFont::~CFont ()
	{
		Release();
	}

	inline void CFont::Attach (HFONT hFont)
	{
		if (m_pData->hFont != NULL && m_pData->hFont != hFont)
			::DeleteObject(m_pData->hFont);
		m_pData->hFont = hFont;
	}

	inline HFONT CFont::Detach ()
	{
		HFONT hFont = m_pData->hFont;
		m_pData->hFont = NULL;
		return hFont;
	}

	inline void CFont::CreateFontIndirect (const LOGFONT* lpLogFont)
	{
		assert(m_pData->hFont == NULL);
		m_pData->hFont = ::CreateFontIndirect(lpLogFont);
		assert(m_pData->hFont);
	}

	inline void CFont::CreatePointFont (int nPointSize, LPCTSTR lpszFaceName, HDC hDC /*= NULL*/, BOOL bBold /*= FALSE*/, BOOL bItalic /*= FALSE*/)
	{
		LOGFONT logFont = { 0 };
		logFont.lfCharSet = DEFAULT_CHARSET;
		logFont.lfHeight = nPointSize;

		lstrcpy (logFont.lfFaceName, lpszFaceName);

		if (bBold)
			logFont.lfWeight = FW_BOLD;
		if (bItalic)
			logFont.lfItalic = (BYTE)TRUE;

		CreatePointFontIndirect (&logFont, hDC);
	}

	inline void CFont::CreatePointFontIndirect (const LOGFONT* lpLogFont, HDC hDC /* = NULL*/)
	{
		HDC hDC1 = (hDC != NULL) ? hDC : ::GetDC(NULL);

		// convert nPointSize to logical units based on hDC
		LOGFONT logFont = *lpLogFont;

#ifndef _WIN32_WCE
		POINT pt = { 0, 0 };
		pt.y = ::MulDiv(::GetDeviceCaps(hDC1, LOGPIXELSY), logFont.lfHeight, 720);   // 72 points/inch, 10 decipoints/point
		::DPtoLP(hDC1, &pt, 1);

		POINT ptOrg = { 0, 0 };
		::DPtoLP(hDC1, &ptOrg, 1);

		logFont.lfHeight = -abs(pt.y - ptOrg.y);
#else // CE specific
		// DP and LP are always the same on CE
	//	logFont.lfHeight = -abs(::MulDiv(::GetDeviceCaps(hDC1, LOGPIXELSY), logFont.lfHeight, 720));
		logFont.lfHeight = -abs(((::GetDeviceCaps(hDC1, LOGPIXELSY)* logFont.lfHeight)/ 720));
#endif // _WIN32_WCE

		if (hDC == NULL)
			::ReleaseDC (NULL, hDC1);

		CreateFontIndirect (&logFont);
	}

#ifndef _WIN32_WCE
//	inline void CFont::CreateFontIndirectEx (const ENUMLOGFONTEXDV* penumlfex)
//	{
//		assert(m_hFont == NULL);
//		m_hFont = ::CreateFontIndirectEx (penumlfex);
//	}

	inline void CFont::CreateFont (int nHeight, int nWidth, int nEscapement,
			int nOrientation, int nWeight, DWORD dwItalic, DWORD dwUnderline,
			DWORD dwStrikeOut, DWORD dwCharSet, DWORD dwOutPrecision,
			DWORD dwClipPrecision, DWORD dwQuality, DWORD dwPitchAndFamily,
			LPCTSTR lpszFacename)
	{
		assert(m_pData->hFont == NULL);
		m_pData->hFont = ::CreateFont (nHeight, nWidth, nEscapement,
			nOrientation, nWeight, dwItalic, dwUnderline, dwStrikeOut,
			dwCharSet, dwOutPrecision, dwClipPrecision, dwQuality,
			dwPitchAndFamily, lpszFacename);
		assert(m_pData->hFont);
	}
#endif // #ifndef _WIN32_WCE

	inline LOGFONT CFont::GetLogFont () const
	{
		assert(m_pData->hFont != NULL);
		LOGFONT LogFont = {0};
		::GetObject (m_pData->hFont, sizeof(LOGFONT), &LogFont);
		return LogFont;
	}

	inline void CFont::Release()
	{
		BOOL bSucceeded = TRUE;

		if (InterlockedDecrement(&m_pData->Count) == 0)
		{
			if (m_pData->hFont != NULL)
				bSucceeded = ::DeleteObject(m_pData->hFont);

			delete m_pData;
		}

		assert(bSucceeded);
	}


	///////////////////////////////////////////////
	// Definitions of the CPalette class
	//
	inline CPalette::CPalette ()
	{
		m_pData = new DataMembers;
		m_pData->hPalette = 0;
		m_pData->Count = 1L;
	}

	inline CPalette::CPalette (HPALETTE hPalette)
	{
		m_pData = new DataMembers;
		m_pData->hPalette = hPalette;
		m_pData->Count = 1L;
	}

	inline CPalette::CPalette (const CPalette& rhs)
	{
		m_pData->hPalette = rhs.m_pData->hPalette;
		m_pData->Count = rhs.m_pData->Count;

		InterlockedIncrement(&m_pData->Count);
	}

	inline CPalette::operator HPALETTE () const
	{
		return m_pData->hPalette;
	}

	inline void CPalette::operator = (HPALETTE hPalette)
	{
		assert (m_pData->hPalette == NULL);
		m_pData->hPalette = hPalette;
	}

	inline CPalette& CPalette::operator = ( const CPalette& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}


	inline CPalette::~CPalette ()
	{
		Release();
	}

	inline void CPalette::Attach (HPALETTE hPalette)
	{
		if (m_pData->hPalette != NULL && m_pData->hPalette != hPalette)
			::DeleteObject(m_pData->hPalette);
		m_pData->hPalette = hPalette;
	}

	inline HPALETTE CPalette::Detach ()
	{
		HPALETTE hPalette = m_pData->hPalette;
		m_pData->hPalette = NULL;
		return hPalette;
	}

	inline void CPalette::CreatePalette (LPLOGPALETTE lpLogPalette)
	{
		assert(m_pData->hPalette == NULL);
		m_pData->hPalette = ::CreatePalette (lpLogPalette);
		assert(m_pData->hPalette);
	}

#ifndef _WIN32_WCE
	inline void CPalette::CreateHalftonePalette (HDC hDC)
	{
		assert(m_pData->hPalette == NULL);
		assert(hDC != NULL);
		m_pData->hPalette = ::CreateHalftonePalette(hDC);
		assert(m_pData->hPalette);
	}
#endif // !_WIN32_WCE

	inline int CPalette::GetEntryCount () const
	{
		assert(m_pData->hPalette != NULL);
		WORD nEntries = 0;
		::GetObject (m_pData->hPalette, sizeof(WORD), &nEntries);
		return (int)nEntries;
	}

	inline UINT CPalette::GetPaletteEntries (UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
	{
		assert(m_pData->hPalette != NULL);
		return ::GetPaletteEntries (m_pData->hPalette, nStartIndex, nNumEntries, lpPaletteColors);
	}

	inline UINT CPalette::SetPaletteEntries (UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
	{
		assert(m_pData->hPalette != NULL);
		return ::SetPaletteEntries (m_pData->hPalette, nStartIndex, nNumEntries, lpPaletteColors);
	}

#ifndef _WIN32_WCE
	inline void CPalette::AnimatePalette (UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
	{
		assert(m_pData->hPalette != NULL);
		::AnimatePalette (m_pData->hPalette, nStartIndex, nNumEntries, lpPaletteColors);
	}

	inline BOOL CPalette::ResizePalette (UINT nNumEntries)
	{
		assert(m_pData->hPalette != NULL);
		return ::ResizePalette (m_pData->hPalette, nNumEntries);
	}
#endif // !_WIN32_WCE

	inline UINT CPalette::GetNearestPaletteIndex (COLORREF crColor) const
	{
		assert(m_pData->hPalette != NULL);
		return ::GetNearestPaletteIndex (m_pData->hPalette, crColor);
	}

	inline void CPalette::Release()
	{
		BOOL bSucceeded = TRUE;

		if (InterlockedDecrement(&m_pData->Count) == 0)
		{
			if (m_pData->hPalette != NULL)
				bSucceeded = ::DeleteObject(m_pData->hPalette);

			delete m_pData;
		}

		assert(bSucceeded);
	}

	///////////////////////////////////////////////
	// Declarations for the CPen class
	//
	inline CPen::CPen ()
	{
		m_pData = new DataMembers;
		m_pData->hPen = 0;
		m_pData->Count = 1L;
	}
	inline CPen::CPen (int nPenStyle, int nWidth, COLORREF crColor)
	{
		m_pData = new DataMembers;
		m_pData->hPen = ::CreatePen (nPenStyle, nWidth, crColor);
		m_pData->Count = 1L;

		assert (m_pData->hPen);
	}

#ifndef _WIN32_WCE
	inline CPen::CPen (int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount /*= 0*/, const DWORD* lpStyle /*= NULL*/)
	{
		m_pData = new DataMembers;
		m_pData->hPen = ::ExtCreatePen (nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle);
		m_pData->Count = 1L;

		assert (m_pData->hPen);
	}
#endif // !_WIN32_WCE

	inline CPen::CPen (const CPen& rhs)
	{
		m_pData->hPen = rhs.m_pData->hPen;
		m_pData->Count = rhs.m_pData->Count;

		InterlockedIncrement(&m_pData->Count);
	}

	inline void CPen::operator = (HPEN hPen)
	{
		assert (m_pData->hPen == NULL);
		m_pData->hPen = hPen;
	}

	inline CPen::operator HPEN () const
	{
		return m_pData->hPen;
	}

	inline CPen& CPen::operator = ( const CPen& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}


	inline CPen::~CPen ()
	{
		Release();
	}

	inline void CPen::Attach (HPEN hPen)
	{
		if (m_pData->hPen != NULL && m_pData->hPen != hPen)
			::DeleteObject(m_pData->hPen);
		m_pData->hPen = hPen;
	}

	inline HPEN CPen::Detach ()
	{
		HPEN hPen = m_pData->hPen;
		m_pData->hPen = NULL;
		return hPen;
	}

	inline void CPen::CreatePen (int nPenStyle, int nWidth, COLORREF crColor)
	{
		assert(m_pData->hPen == NULL);
		m_pData->hPen = ::CreatePen(nPenStyle, nWidth, crColor);
		assert(m_pData->hPen);
	}

	inline void CPen::CreatePenIndirect (LPLOGPEN lpLogPen)
	{
		assert(m_pData->hPen == NULL);
		m_pData->hPen = ::CreatePenIndirect(lpLogPen);
		assert(m_pData->hPen);
	}

	inline LOGPEN CPen::GetLogPen () const
	{
		assert(m_pData->hPen != NULL);

		LOGPEN LogPen = {0};
		::GetObject(m_pData->hPen, sizeof(LOGPEN), &LogPen);
		return LogPen;
	}

#ifndef _WIN32_WCE
	inline void CPen::ExtCreatePen (int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount /* = 0*/, const DWORD* lpStyle /*= NULL*/)
	{
		assert(m_pData->hPen == NULL);
		m_pData->hPen = ::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle);
		assert(m_pData->hPen);
	}

	inline EXTLOGPEN CPen::GetExtLogPen () const
	{
		assert(m_pData->hPen != NULL);

		EXTLOGPEN ExLogPen = {0};
		::GetObject(m_pData->hPen, sizeof(EXTLOGPEN), &ExLogPen);
		return ExLogPen;
	}
#endif // !_WIN32_WCE

	inline void CPen::Release()
	{
		BOOL bSucceeded = TRUE;

		if (InterlockedDecrement(&m_pData->Count) == 0)
		{
			if (m_pData->hPen != NULL)
				bSucceeded = ::DeleteObject(m_pData->hPen);

			delete m_pData;
		}

		assert(bSucceeded);
	}


	///////////////////////////////////////////////
	// Definitions of the CRgn class
	//
	inline CRgn::CRgn ()
	{
		m_pData = new DataMembers;
		m_pData->hRgn = 0;
		m_pData->Count = 1L;
	}

	inline CRgn::CRgn (HRGN hRgn)
	{
		m_pData = new DataMembers;
		m_pData->hRgn = hRgn;
		m_pData->Count = 1L;
	}

	inline CRgn::CRgn (const CRgn& rhs)
	{
		m_pData->hRgn = rhs.m_pData->hRgn;
		m_pData->Count = rhs.m_pData->Count;

		InterlockedIncrement(&m_pData->Count);
	}

	inline CRgn::operator HRGN() const
	{
		return m_pData->hRgn;
	}

	inline void CRgn::operator = (HRGN hRgn)
	{
		assert (m_pData->hRgn == NULL);
		m_pData->hRgn = hRgn;
	}

	inline CRgn& CRgn::operator = ( const CRgn& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}


	inline CRgn::~CRgn ()
	{
		Release();
	}

	inline void CRgn::Attach (HRGN hRgn)
	{
		if (m_pData->hRgn != NULL && m_pData->hRgn != hRgn)
			::DeleteObject(m_pData->hRgn);
		m_pData->hRgn = hRgn;
	}

	inline HRGN CRgn::Detach ()
	{
		HRGN hRgn = m_pData->hRgn;
		m_pData->hRgn = NULL;
		return hRgn;
	}

	inline void CRgn::CreateRectRgn (int x1, int y1, int x2, int y2)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreateRectRgn(x1, y1, x2, y2);
		assert (m_pData->hRgn);
	}

	inline void CRgn::CreateRectRgnIndirect (LPCRECT lpRect)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreateRectRgnIndirect(lpRect);
		assert (m_pData->hRgn);
	}

#ifndef _WIN32_WCE
	inline void CRgn::CreateEllipticRgn (int x1, int y1, int x2, int y2)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreateEllipticRgn (x1, y1, x2, y2);
		assert (m_pData->hRgn);
	}

	inline void CRgn::CreateEllipticRgnIndirect (LPCRECT lpRect)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreateEllipticRgnIndirect (lpRect);
		assert (m_pData->hRgn);
	}

	inline void CRgn::CreatePolygonRgn (LPPOINT lpPoints, int nCount, int nMode)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreatePolygonRgn (lpPoints, nCount, nMode);
		assert (m_pData->hRgn);
	}

	inline void CRgn::CreatePolyPolygonRgn (LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreatePolyPolygonRgn (lpPoints, lpPolyCounts, nCount, nPolyFillMode);
		assert (m_pData->hRgn);
	}

	inline void CRgn::CreateRoundRectRgn (int x1, int y1, int x2, int y2, int x3, int y3)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::CreateRoundRectRgn (x1, y1, x2, y2, x3, y3);
		assert (m_pData->hRgn);
	}

	inline void CRgn::CreateFromPath (HDC hDC)
	{
		assert(m_pData->hRgn == NULL);
		assert(hDC != NULL);
		m_pData->hRgn = ::PathToRegion(hDC);
		assert(m_pData->hRgn);
	}

#endif // !_WIN32_WCE

	inline void CRgn::CreateFromData (const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
	{
		assert(m_pData->hRgn == NULL);
		m_pData->hRgn = ::ExtCreateRegion (lpXForm, nCount, pRgnData);
		assert(m_pData->hRgn);
	}

	inline void CRgn::SetRectRgn (int x1, int y1, int x2, int y2)
	{
		assert(m_pData->hRgn != NULL);
		::SetRectRgn (m_pData->hRgn, x1, y1, x2, y2);
	}

	inline void CRgn::SetRectRgn (LPCRECT lpRect)
	{
		assert(m_pData->hRgn != NULL);
		::SetRectRgn (m_pData->hRgn, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	inline int CRgn::CombineRgn (HRGN hRgnSrc1, HRGN hRgnSrc2, int nCombineMode)
	{
		assert(m_pData->hRgn != NULL);
		return ::CombineRgn (m_pData->hRgn, hRgnSrc1, hRgnSrc2, nCombineMode);
	}

	inline int CRgn::CombineRgn (HRGN hRgnSrc, int nCombineMode)
	{
		assert(m_pData->hRgn != NULL);
		return ::CombineRgn (m_pData->hRgn, m_pData->hRgn, hRgnSrc, nCombineMode);
	}

	inline int CRgn::CopyRgn (HRGN hRgnSrc)
	{
		assert(m_pData->hRgn != NULL);
		return ::CombineRgn (m_pData->hRgn, hRgnSrc, NULL, RGN_COPY);
	}

	inline BOOL CRgn::EqualRgn (HRGN hRgn) const
	{
		assert(m_pData->hRgn != NULL);
		return ::EqualRgn (m_pData->hRgn, hRgn);
	}

	inline int CRgn::OffsetRgn (int x, int y)
	{
		assert(m_pData->hRgn != NULL);
		return ::OffsetRgn (m_pData->hRgn, x, y);
	}

	inline int CRgn::OffsetRgn (POINT point)
	{
		assert(m_pData->hRgn != NULL);
		return ::OffsetRgn (m_pData->hRgn, point.x, point.y);
	}

	inline int CRgn::GetRgnBox (LPRECT lpRect) const
	{
		assert(m_pData->hRgn != NULL);
		return ::GetRgnBox (m_pData->hRgn, lpRect);
	}

	inline BOOL CRgn::PtInRegion (int x, int y) const
	{
		assert(m_pData->hRgn != NULL);
		return ::PtInRegion (m_pData->hRgn, x, y);
	}

	inline BOOL CRgn::PtInRegion (POINT point) const
	{
		assert(m_pData->hRgn != NULL);
		return ::PtInRegion (m_pData->hRgn, point.x, point.y);
	}

	inline BOOL CRgn::RectInRegion (LPCRECT lpRect) const
	{
		assert(m_pData->hRgn != NULL);
		return ::RectInRegion (m_pData->hRgn, lpRect);
	}

	inline int CRgn::GetRegionData (LPRGNDATA lpRgnData, int nDataSize) const
	{
		assert(m_pData->hRgn != NULL);
		return (int)::GetRegionData (m_pData->hRgn, nDataSize, lpRgnData);
	}

	inline void CRgn::Release()
	{
		BOOL bSucceeded = TRUE;

		if (InterlockedDecrement(&m_pData->Count) == 0)
		{
			if (m_pData->hRgn != NULL)
				bSucceeded = ::DeleteObject(m_pData->hRgn);

			delete m_pData;
		}

		assert(bSucceeded);
	}


	///////////////////////////////////////////////
	// Definitions of the CDC class
	//
	inline CDC::CDC ()
	{
		// Allocate memory for our data members
		m_pData = new DataMembers;

		// Assign values to our data members
		m_pData->hDC = 0;
		m_pData->hBitmapOld = 0;
		m_pData->hBrushOld = 0;
		m_pData->hFontOld = 0;
		m_pData->hPenOld = 0;
		m_pData->Count = 1L;
	}

	inline CDC::CDC (HDC hDC)
	{
		// This constructor assigns an existing HDC to the CDC
		// The HDC WILL be released or deleted when the CDC object is destroyed

		// Note: this constructor permits a call like this:
		// CDC MyCDC = SomeHDC;
		//  or
		// CDC MyCDC = ::CreateCompatibleDC(SomeHDC);
		//  or
		// CDC MyCDC = ::GetDC(SomeHWND);

		assert(hDC);

		// Allocate memory for our data members
		m_pData = new DataMembers;

		// Assign values to our data members
		m_pData->hDC = hDC;
		m_pData->hBitmapOld = 0;
		m_pData->hBrushOld = 0;
		m_pData->hFontOld = 0;
		m_pData->hPenOld = 0;
		m_pData->Count = 1L;

		AddToMap();
	}

	inline CDC::CDC (const CDC& rhs)	// Copy constructor
	{
		// The copy constructor is called when a temporary copy of the CDC needs to be created.
		// This can happen when a CDC is passed by value in a function call. Each CDC copy manages
		// the same Device Context and GDI objects.

		m_pData = rhs.m_pData;
		InterlockedIncrement(&m_pData->Count);
	}

	inline void CDC::operator = (const HDC hDC)
	{
		// Note: this assignment operater permits a call like this:
		// CDC MyCDC;
		// MyCDC = SomeHDC;

		AttachDC(hDC);
	}

	inline CDC& CDC::operator = ( const CDC& rhs )
	{
		// Note: A copy of a CDC is a clone of the original.
		//       Both objects manipulate the one HDC
		if (this != &rhs)
		{
			InterlockedIncrement(&rhs.m_pData->Count);
			Release();
			m_pData = rhs.m_pData;
		}

		return *this;
	}

	inline CDC::~CDC ()
	{
		Release();
	}

	inline void CDC::AddToMap()
	// Store the HDC and CDC pointer in the HDC map
	{
		assert( GetApp() );
		assert(m_pData->hDC);
		GetApp()->m_csMapLock.Lock();

		assert(m_pData->hDC);
		assert(!GetApp()->GetCDCFromMap(m_pData->hDC));

		GetApp()->m_mapHDC.insert(std::make_pair(m_pData->hDC, this));
		GetApp()->m_csMapLock.Release();
	}

	inline void CDC::AttachDC (HDC hDC)
	{
		assert(m_pData);
		assert(0 == m_pData->hDC);
		assert(hDC);

		m_pData->hDC = hDC;
		AddToMap();
	}

	inline HDC CDC::DetachDC ()
	{
		assert(m_pData);
		assert(m_pData->hDC);

		if (m_pData->hPenOld)	::SelectObject(m_pData->hDC, m_pData->hPenOld);
		if (m_pData->hBrushOld)	::SelectObject(m_pData->hDC, m_pData->hBrushOld);
		if (m_pData->hBitmapOld)::SelectObject(m_pData->hDC, m_pData->hBitmapOld);
		if (m_pData->hFontOld)	::SelectObject(m_pData->hDC, m_pData->hFontOld);

		m_pData->hPenOld = 0;
		m_pData->hBrushOld = 0;
		m_pData->hBitmapOld = 0;
		m_pData->hFontOld = 0;

		HDC hDC = m_pData->hDC;

		m_pData->hDC = 0;
		RemoveFromMap();
		return hDC;
	}

	inline void CDC::DrawBitmap (int x, int y, int cx, int cy, HBITMAP hbmImage, COLORREF clrMask)
	// Draws the specified bitmap to the specified DC using the mask colour provided as the transparent colour
	// Suitable for use with a Window DC or a memory DC
	{
		// Create the Image memory DC
		CDC dcImage = CreateCompatibleDC();
		dcImage.SetBkColor(clrMask);
		dcImage.AttachBitmap(hbmImage);

		// Create the Mask memory DC
		CDC dcMask = CreateCompatibleDC();
        dcMask.CreateBitmap(cx, cy, 1, 1, NULL);
		dcMask.BitBlt(0, 0, cx, cy, dcImage, 0, 0, SRCCOPY);

		// Mask the image to 'this' DC
		BitBlt(x, y, cx, cy, dcImage, 0, 0, SRCINVERT);
		BitBlt(x, y, cx, cy, dcMask, 0, 0, SRCAND);
		BitBlt(x, y, cx, cy, dcImage, 0, 0, SRCINVERT);
	}

	inline CDC* CDC::FromHandle(HDC hDC)
	// Returns the CDC object associated with the device context handle
	{
		assert( GetApp() );
		CDC* pDC = GetApp()->GetCDCFromMap(hDC);
		return pDC;
	}

	inline void CDC::GradientFill (COLORREF Color1, COLORREF Color2, const RECT& rc, BOOL bVertical)
	// An efficient color gradient filler compatible with all Windows operating systems
	{
		int Width = rc.right - rc.left;
		int Height = rc.bottom - rc.top;

		int r1 = GetRValue(Color1);
		int g1 = GetGValue(Color1);
		int b1 = GetBValue(Color1);

		int r2 = GetRValue(Color2);
		int g2 = GetGValue(Color2);
		int b2 = GetBValue(Color2);

		COLORREF OldBkColor = GetBkColor();

		if (bVertical)
		{
			for(int i=0; i < Width; ++i)
			{
				int r = r1 + (i * (r2-r1) / Width);
				int g = g1 + (i * (g2-g1) / Width);
				int b = b1 + (i * (b2-b1) / Width);
				SetBkColor(RGB(r, g, b));
				CRect line( i + rc.left, rc.top, i + 1 + rc.left, rc.top+Height);
				ExtTextOut(0, 0, ETO_OPAQUE, line, NULL, 0, 0);
			}
		}
		else
		{
			for(int i=0; i < Height; ++i)
			{
				int r = r1 + (i * (r2-r1) / Height);
				int g = g1 + (i * (g2-g1) / Height);
				int b = b1 + (i * (b2-b1) / Height);
				SetBkColor(RGB(r, g, b));
				CRect line( rc.left, i + rc.top, rc.left+Width, i + 1 + rc.top);
				ExtTextOut(0, 0, ETO_OPAQUE, line, NULL, 0, 0);
			}
		}

		SetBkColor(OldBkColor);
	}

	inline void CDC::Release ()
	{
		if (m_pData->Count)
		{
			if (InterlockedDecrement(&m_pData->Count) == 0)
			{
				if (m_pData->hDC)
				{
					// Delete any GDI objects belonging to this CDC
					if (m_pData->hPenOld)	::SelectObject(m_pData->hDC, m_pData->hPenOld);
					if (m_pData->hBrushOld)	::SelectObject(m_pData->hDC, m_pData->hBrushOld);
					if (m_pData->hBitmapOld)::SelectObject(m_pData->hDC, m_pData->hBitmapOld);
					if (m_pData->hFontOld)	::SelectObject(m_pData->hDC, m_pData->hFontOld);

					// We need to release a Window DC, and delete a memory DC
		#ifndef _WIN32_WCE
					HWND hwnd = ::WindowFromDC(m_pData->hDC);
					if (hwnd) ::ReleaseDC(hwnd, m_pData->hDC);
					else      ::DeleteDC(m_pData->hDC);
		#else
					::DeleteDC(m_pData->hDC);
		#endif
				}

				delete m_pData;
				m_pData = 0;
				RemoveFromMap();
			}
		}
	}

	inline BOOL CDC::RemoveFromMap()
	{
		assert( GetApp() );
		BOOL Success = FALSE;

		// Allocate an iterator for our HDC map
		std::map<HDC, CDC*, CompareHDC>::iterator m;

		CWinApp* pApp = GetApp();
		if (pApp)
		{
			// Erase the CDC pointer entry from the map
			pApp->m_csMapLock.Lock();
			for (m = pApp->m_mapHDC.begin(); m != pApp->m_mapHDC.end(); ++m)
			{
				if (this == m->second)
				{
					pApp->m_mapHDC.erase(m);
					Success = TRUE;
					break;
				}
			}

			pApp->m_csMapLock.Release();
		}

		return Success;
	}

	inline void CDC::RemoveCurrentBitmap ()
	{
		if (m_pData->hBitmapOld)
		{
			HBITMAP hBitmap = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->hBitmapOld);
			if (hBitmap == m_pData->Bitmap)
			{
				// Only delete the bitmap objects we create
				m_pData->Bitmap.Detach();
				DeleteObject(hBitmap);
			}
		}
	}

	inline void CDC::RemoveCurrentBrush ()
	{
		if (m_pData->hBrushOld)
		{
			HBRUSH hBrush = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->hBrushOld);
			if (hBrush == m_pData->Brush)
			{
				// Only delete the brush objects we create
				m_pData->Brush.Detach();
				DeleteObject(hBrush);
			}
		}
	}

	inline void CDC::RemoveCurrentFont ()
	{
		if (m_pData->hFontOld)
		{
			HFONT hFont = (HFONT)::SelectObject(m_pData->hDC, m_pData->hFontOld);
			if (hFont == m_pData->Font)
			{
				// Only delete the font objects we create
				m_pData->Font.Detach();
				DeleteObject(hFont);
			}
		}
	}

	inline void CDC::RemoveCurrentPen ()
	{
		if (m_pData->hPenOld)
		{
			HPEN hPen = (HPEN)::SelectObject(m_pData->hDC, m_pData->hPenOld);
			if (hPen == m_pData->Pen)
			{
				// Only delete the pen objects we create
				m_pData->Pen.Detach();
				DeleteObject(hPen);
			}
		}
	}

	inline void CDC::RemoveCurrentRgn ()
	{
		if (m_pData->Rgn)
		{
			// Only delete the region objects we create
			HRGN hRgn = m_pData->Rgn.Detach();
			DeleteObject(hRgn);
		}
	}

	inline void CDC::SolidFill (COLORREF Color, const RECT& rc)
	// Fills a rectangle with a solid color
	{
		COLORREF OldColor = SetBkColor(Color);
		ExtTextOut(0, 0, ETO_OPAQUE, &rc, NULL, 0, 0);
		SetBkColor(OldColor);
	}

	// Bitmap functions
	inline void CDC::AttachBitmap (HBITMAP hBitmap)
	{
		// Use this to attach an existing bitmap.
		// The bitmap will be deleted for you, unless its detached

		assert(m_pData->hDC);
		assert(hBitmap);

		RemoveCurrentBitmap();
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, hBitmap);
	}

	inline void CDC::CreateCompatibleBitmap (HDC hDC, int cx, int cy)
	{
		// Creates a compatible bitmap and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBitmap();

		m_pData->Bitmap.CreateCompatibleBitmap(hDC, cx, cy);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

	inline void CDC::CreateBitmap (int cx, int cy, UINT Planes, UINT BitsPerPixel, CONST VOID *pvColors)
	{
		// Creates a bitmap and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBitmap();

		m_pData->Bitmap.CreateBitmap(cx, cy, Planes, BitsPerPixel, pvColors);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

#ifndef _WIN32_WCE
	inline void CDC::CreateBitmapIndirect (LPBITMAP pBitmap)
	{
		// Creates a bitmap and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBitmap();

		m_pData->Bitmap.CreateBitmapIndirect(pBitmap);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

	inline void CDC::CreateDIBitmap (HDC hdc, const BITMAPINFOHEADER& bmih, DWORD fdwInit, CONST VOID *lpbInit,
										BITMAPINFO& bmi,  UINT fuUsage)
	{
		// Creates a bitmap and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBitmap();

		m_pData->Bitmap.CreateDIBitmap(hdc, &bmih, fdwInit, lpbInit, &bmi, fuUsage);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}
#endif

	inline void CDC::CreateDIBSection (HDC hdc, const BITMAPINFO& bmi, UINT iUsage, VOID **ppvBits,
										HANDLE hSection, DWORD dwOffset)
	{
		// Creates a bitmap and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBitmap();

		m_pData->Bitmap.CreateDIBSection(hdc, &bmi, iUsage, ppvBits, hSection, dwOffset);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

	inline HBITMAP CDC::DetachBitmap ()
	{
		// Use this to detach the bitmap from the HDC.

		assert(m_pData->hDC);

		HBITMAP hBitmap = 0;	
		if(m_pData->hBitmapOld)
		{
			hBitmap = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->hBitmapOld);
			if (hBitmap == m_pData->Bitmap)
				m_pData->Bitmap.Detach();
		}

		m_pData->hBitmapOld = NULL;
		return hBitmap;
	}

	inline BITMAP CDC::GetBitmapInfo ()
	{
		// Retrieves the BITMAP for the current HBITMAP

		assert(m_pData->hDC);

		HBITMAP hbm = (HBITMAP)::GetCurrentObject(m_pData->hDC, OBJ_BITMAP);
		BITMAP bm = {0};
		::GetObject(hbm, sizeof(bm), &bm);
		return bm;
	}

	inline void CDC::LoadBitmap (UINT nID)
	{
		LoadBitmap(MAKEINTRESOURCE(nID));
	}

	inline void CDC::LoadBitmap (LPCTSTR lpstr)
	{
		assert(m_pData->hDC);
		assert(GetApp());
		m_pData->Bitmap.LoadBitmap (lpstr);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

	inline void CDC::LoadImage(UINT nID, int cxDesired, int cyDesired, UINT fuLoad)
	{
		LoadImage(nID, cxDesired, cyDesired, fuLoad);
	}

	inline void CDC::LoadImage(LPCTSTR lpszName, int cxDesired, int cyDesired, UINT fuLoad)
	{
		assert(m_pData->hDC);
		assert(GetApp());
		m_pData->Bitmap.LoadImage(lpszName, cxDesired, cyDesired, fuLoad);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

	inline void CDC::LoadOEMBitmap (UINT nIDBitmap) // for OBM_/OCR_/OIC_
	{
		assert(m_pData->hDC);
		m_pData->Bitmap.LoadOEMBitmap (nIDBitmap);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}

#ifndef _WIN32_WCE
	inline void CDC::LoadMappedBitmap (UINT nIDBitmap, UINT nFlags /*= 0*/, LPCOLORMAP lpColorMap /*= NULL*/, int nMapSize /*= 0*/)
	{
		assert(m_pData->hDC);
		m_pData->Bitmap.LoadMappedBitmap (nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize);
		m_pData->hBitmapOld = (HBITMAP)::SelectObject(m_pData->hDC, m_pData->Bitmap);
	}
#endif // !_WIN32_WCE


	// Brush functions
	inline void CDC::AttachBrush (HBRUSH hBrush)
	{
		// Use this to attach an existing brush.
		// The brush will be deleted for you, unless its detached

		assert(m_pData->hDC);
		assert(hBrush);
		RemoveCurrentBrush();
		m_pData->hBrushOld = (HBRUSH)::SelectObject(m_pData->hDC, hBrush);
	}

#ifndef _WIN32_WCE
	inline void CDC::CreateBrushIndirect (LPLOGBRUSH& pLogBrush)
	{
		// Creates the brush and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBrush();

		m_pData->Brush.CreateBrushIndirect(pLogBrush);
		m_pData->hBrushOld = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->Brush);
	}

	inline void CDC::CreateHatchBrush (int fnStyle, COLORREF rgb)
	{
		// Creates the brush and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBrush();

		m_pData->Brush.CreateHatchBrush(fnStyle, rgb);
		m_pData->hBrushOld = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->Brush);
	}
#endif

	inline void CDC::CreateDIBPatternBrushPt (LPCVOID lpPackedDIB, UINT iUsage)
	{
		// Creates the brush and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBrush();

		m_pData->Brush.CreateDIBPatternBrushPt(lpPackedDIB, iUsage);
		m_pData->hBrushOld = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->Brush);
	}

	inline void CDC::CreatePatternBrush (HBITMAP hbmp)
	{
		// Creates the brush and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBrush();

		m_pData->Brush.CreatePatternBrush(hbmp);
		m_pData->hBrushOld = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->Brush);
	}

	inline void CDC::CreateSolidBrush (COLORREF rgb)
	{
		// Creates the brush and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentBrush();

		m_pData->Brush.CreateSolidBrush(rgb);
		m_pData->hBrushOld = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->Brush);
	}

	inline HBRUSH CDC::DetachBrush ()
	{
		// Use this to detach the brush from the HDC.

		assert(m_pData->hDC);

		HBRUSH hBrush = 0;
		if (m_pData->hBrushOld)
		{
			hBrush = (HBRUSH)::SelectObject(m_pData->hDC, m_pData->hBrushOld);
			if (hBrush == m_pData->Brush)
				m_pData->Brush.Detach();
		}
		
		m_pData->hBrushOld = NULL;
		return hBrush;
	}

	inline LOGBRUSH CDC::GetBrushInfo ()
	{
		// Retrieves the current brush information

		assert(m_pData->hDC);

		HBRUSH hBrush = (HBRUSH)::GetCurrentObject(m_pData->hDC, OBJ_BRUSH);
		LOGBRUSH lBrush = {0};
		::GetObject(hBrush, sizeof(lBrush), &lBrush);
		return lBrush;
	}


	// Font functions
	inline void CDC::AttachFont (HFONT hFont)
	{
		// Use this to attach an existing font.
		// The font will be deleted for you, unless its detached

		assert(m_pData->hDC);
		assert(hFont);

		RemoveCurrentFont();
		m_pData->hFontOld = (HFONT)::SelectObject(m_pData->hDC, hFont);
	}

#ifndef _WIN32_WCE
	inline void CDC::CreateFont (
					int nHeight,               // height of font
  					int nWidth,                // average character width
  					int nEscapement,           // angle of escapement
  					int nOrientation,          // base-line orientation angle
  					int fnWeight,              // font weight
  					DWORD fdwItalic,           // italic attribute option
  					DWORD fdwUnderline,        // underline attribute option
  					DWORD fdwStrikeOut,        // strikeout attribute option
  					DWORD fdwCharSet,          // character set identifier
  					DWORD fdwOutputPrecision,  // output precision
  					DWORD fdwClipPrecision,    // clipping precision
  					DWORD fdwQuality,          // output quality
  					DWORD fdwPitchAndFamily,   // pitch and family
  					LPCTSTR lpszFace           // typeface name
 					)

	{
		// Creates a logical font with the specified characteristics.

		assert(m_pData->hDC);
		RemoveCurrentFont();

		m_pData->Font.CreateFont (nHeight, nWidth, nEscapement, nOrientation, fnWeight,
								fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet,
								fdwOutputPrecision, fdwClipPrecision, fdwQuality,
								fdwPitchAndFamily, lpszFace);

		m_pData->hFontOld = (HFONT)::SelectObject(m_pData->hDC, m_pData->Font);
	}
#endif

	inline void CDC::CreateFontIndirect (const LOGFONT& lf)
	{
		// Creates a logical font that has the specified characteristics

		assert(m_pData->hDC);
		RemoveCurrentFont();

		m_pData->Font.CreateFontIndirect(&lf);
		m_pData->hFontOld = (HFONT)::SelectObject(m_pData->hDC, m_pData->Font);
	}

	inline HFONT CDC::DetachFont ()
	{
		// Use this to detach the font from the HDC.

		assert(m_pData->hDC);

		HFONT hFont = 0;
		if (m_pData->hFontOld)
		{
			hFont = (HFONT)::SelectObject(m_pData->hDC, m_pData->hFontOld);
			if (m_pData->Font == hFont)
				m_pData->Font.Detach();
		}

		m_pData->hFontOld = NULL;
		return hFont;
	}

	inline LOGFONT CDC::GetFontInfo ()
	{
		// Retrieves the current font information

		assert(m_pData->hDC);

		HFONT hFont = (HFONT)::GetCurrentObject(m_pData->hDC, OBJ_FONT);
		LOGFONT lFont = {0};
		::GetObject(hFont, sizeof(lFont), &lFont);
		return lFont;
	}

	// Pen functions
	inline void CDC::AttachPen (HPEN hPen)
	{
		// Use this to attach an existing pen.
		// The pen will be deleted for you, unless its detached

		assert(m_pData->hDC);
		assert(hPen);
		RemoveCurrentPen();

		m_pData->hPenOld = (HPEN)::SelectObject(m_pData->hDC, hPen);
	}

	inline void CDC::CreatePen (int nStyle, int nWidth, COLORREF rgb)
	{
		// Creates the pen and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentPen();

		m_pData->Pen.CreatePen(nStyle, nWidth, rgb);
		m_pData->hPenOld = (HPEN)::SelectObject(m_pData->hDC, m_pData->Pen);
	}

	inline void CDC::CreatePenIndirect (LPLOGPEN pLogPen)
	{
		// Creates the pen and selects it into the device context

		assert(m_pData->hDC);
		RemoveCurrentPen();

		m_pData->Pen.CreatePenIndirect(pLogPen);
		m_pData->hPenOld = (HPEN)::SelectObject(m_pData->hDC, m_pData->Pen);
	}

	inline HPEN CDC::DetachPen ()
	{
		// Use this to detach the pen from the HDC.

		assert(m_pData->hDC);
		HPEN hPen = 0;

		if (m_pData->hPenOld)
		{
			hPen = (HPEN)::SelectObject(m_pData->hDC, m_pData->hPenOld);
			if (hPen == m_pData->Pen)
				m_pData->Pen.Detach();
		}

		m_pData->hPenOld = NULL;
		return hPen;
	}

	inline LOGPEN CDC::GetPenInfo ()
	{
		// Retrieves the current pen information as a LOGPEN

		assert(m_pData->hDC);

		HPEN hPen = (HPEN)::GetCurrentObject(m_pData->hDC, OBJ_PEN);
		LOGPEN lPen = {0};
		::GetObject(hPen, sizeof(lPen), &lPen);
		return lPen;
	}

	// Region functions
	inline void CDC::CreateRectRgn (int left, int top, int right, int bottom)
	{
		// Creates a rectangular region from the rectangle co-ordinates.
		// Note: The shape of a region cannot be changed while it is attached to a DC

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreateRectRgn(left, top, right, bottom);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}

	inline void CDC::CreateRectRgnIndirect (const RECT& rc)
	{
		// Creates a rectangular region from the rectangle co-ordinates.
		// Note: The shape of a region cannot be changed while it is attached to a DC

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreateRectRgnIndirect(&rc);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}

	inline void CDC::CreateFromData (const XFORM* Xform, DWORD nCount, const RGNDATA *pRgnData)
	{
		// Creates a region from the specified region data and tranformation data.
		// Notes: The shape of a region cannot be changed while it is attached to a DC
		//        GetRegionData can be used to get a region's data
		//        If the XFROM pointer is NULL, the identity transformation is used.

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreateFromData(Xform, nCount, pRgnData);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}

#ifndef _WIN32_WCE
		inline void CDC::CreateEllipticRgn (int left, int top, int right, int bottom)
	{
		// Creates the ellyiptical region from the bounding rectangle co-ordinates
		// and selects it into the device context
		// Note: The shape of a region cannot be changed while it is attached to a DC

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreateEllipticRgn(left, top, right, bottom);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}

	inline void CDC::CreateEllipticRgnIndirect (const RECT& rc)
	{
		// Creates the ellyiptical region from the bounding rectangle co-ordinates
		// and selects it into the device context
		// Note: The shape of a region cannot be changed while it is attached to a DC

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreateEllipticRgnIndirect(&rc);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}

	inline void CDC::CreatePolygonRgn (LPPOINT ppt, int cPoints, int fnPolyFillMode)
	{
		// Creates the polygon region from the array of points and selects it into
		// the device context. The polygon is presumed closed
		// Note: The shape of a region cannot be changed while it is attached to a DC

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreatePolygonRgn(ppt, cPoints, fnPolyFillMode);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}

	inline void CDC::CreatePolyPolygonRgn (LPPOINT ppt, LPINT pPolyCounts, int nCount, int fnPolyFillMode)
	{
		// Creates the polygon region from a series of polygons.The polygons can overlap.
		// Note: The shape of a region cannot be changed while it is attached to a DC

		assert(m_pData->hDC);
		RemoveCurrentRgn();

		m_pData->Rgn.CreatePolyPolygonRgn(ppt, pPolyCounts, nCount, fnPolyFillMode);
		::SelectClipRgn(m_pData->hDC, m_pData->Rgn);
	}
#endif


	// Wrappers for WinAPI functions

	// Initialization
	inline HDC CDC::CreateCompatibleDC () const
	{
		return ::CreateCompatibleDC( m_pData->hDC );
	}

	inline HDC CDC::CreateDC(LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, const DEVMODE& dvmInit) const
	{
		return ::CreateDC( lpszDriver, lpszDevice, lpszOutput, &dvmInit );
	}
	
	inline int CDC::GetDeviceCaps (int nIndex) const
	{
		return ::GetDeviceCaps(m_pData->hDC, nIndex);
	}

	// Clipping functions
	inline int CDC::ExcludeClipRect (int Left, int Top, int Right, int BottomRect )
	{
		assert(m_pData->hDC);
		return ::ExcludeClipRect (m_pData->hDC, Left, Top, Right, BottomRect );
	}

	inline int CDC::ExcludeClipRect (const RECT& rc)
	{
		assert(m_pData->hDC);
		return ::ExcludeClipRect(m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom);
	}

	inline int CDC::GetClipBox (RECT& rc)
	{
		assert(m_pData->hDC);
		return ::GetClipBox(m_pData->hDC, &rc);
	}

	inline int CDC::GetClipRgn (HRGN hrgn)
	{
		assert(m_pData->hDC);
		return ::GetClipRgn(m_pData->hDC, hrgn);
	}

	inline int CDC::IntersectClipRect (int Left, int Top, int Right, int Bottom)
	{
		assert(m_pData->hDC);
		return ::IntersectClipRect(m_pData->hDC, Left, Top, Right, Bottom);
	}
	
	inline int CDC::IntersectClipRect (const RECT& rc)
	{
		assert(m_pData->hDC);
		return ::IntersectClipRect(m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom);
	}

	inline BOOL CDC::RectVisible (const RECT& rc)
	{
		assert(m_pData->hDC);
		return ::RectVisible (m_pData->hDC, &rc);
	}

	inline int CDC::SelectClipRgn(HRGN hRegion)
	{
		assert(m_pData->hDC);
		return ::SelectClipRgn(m_pData->hDC, hRegion);
	}

#ifndef _WIN32_WCE
	inline BOOL CDC::PtVisible (int X, int Y)
	{
		assert(m_pData->hDC);
		return ::PtVisible (m_pData->hDC, X, Y);
	}

	inline int CDC::OffsetClipRgn (int nXOffset, int nYOffset)
	{
		assert(m_pData->hDC);
		return ::OffsetClipRgn (m_pData->hDC, nXOffset, nYOffset);
	}
#endif

	// Point and Line Drawing Functions
	inline CPoint CDC::GetCurrentPosition () const
	{
		//  returns the current "MoveToEx" position
		CPoint pt;
		::MoveToEx( m_pData->hDC, 0, 0, &pt );
		::MoveToEx( m_pData->hDC, pt.x, pt.y, NULL);
		return pt;
	}
	inline CPoint CDC::MoveTo (int x, int y) const
	{
		// Updates the current position to the specified point
		return ::MoveToEx( m_pData->hDC, x, y, NULL );
	}
	inline CPoint CDC::MoveTo (POINT pt) const
	{
		// Updates the current position to the specified point
		return ::MoveToEx( m_pData->hDC, pt.x, pt.y, NULL );
	}
	inline BOOL CDC::LineTo (int x, int y) const
	{
		// Draws a line from the current position up to, but not including, the specified point
		return ::LineTo( m_pData->hDC, x, y );
	}
	inline BOOL CDC::LineTo (POINT pt) const
	{
		// Draws a line from the current position up to, but not including, the specified point
		return ::LineTo( m_pData->hDC, pt.x, pt.y );
	}

#ifndef _WIN32_WCE
	inline BOOL CDC::Arc (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const
	{
		return ::Arc (m_pData->hDC, x1, y1, x2, y2, x3, y3, x4, y4);
	}
	inline BOOL CDC::Arc (RECT& rc, POINT ptStart, POINT ptEnd) const
	{
		// Draws an elliptical arc
		return ::Arc( m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom,
			ptStart.x, ptStart.y, ptEnd.x, ptEnd.y );
	}
	inline BOOL CDC::ArcTo (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const
	{
		// Draws an elliptical arc
		return ::ArcTo( m_pData->hDC, x1, y1, x2, y2, x3, y3, x4, y4) ;
	}
	inline BOOL CDC::ArcTo (RECT& rc, POINT ptStart, POINT ptEnd) const
	{
		// Draws an elliptical arc
		return ::ArcTo (m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom,
			ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
	}
	inline BOOL CDC::AngleArc (int x, int y, int nRadius, float fStartAngle, float fSweepAngle) const
	{
		// Draws a line segment and an arc
		return ::AngleArc (m_pData->hDC, x, y, nRadius, fStartAngle, fSweepAngle);
	}
	inline int CDC::GetArcDirection () const
	{
		// Retrieves the current arc direction ( AD_COUNTERCLOCKWISE or AD_CLOCKWISE )
		return ::GetArcDirection (m_pData->hDC);
	}
	inline int CDC::SetArcDirection (int nArcDirection) const
	{
		// Sets the current arc direction ( AD_COUNTERCLOCKWISE or AD_CLOCKWISE )
		return ::SetArcDirection( m_pData->hDC, nArcDirection );
	}
	inline BOOL CDC::PolyDraw (const POINT* lpPoints, const BYTE* lpTypes, int nCount) const
	{
		// Draws a set of line segments and Bzier curves
		return ::PolyDraw( m_pData->hDC, lpPoints, lpTypes, nCount );
	}
	inline BOOL CDC::Polyline (LPPOINT lpPoints, int nCount) const
	{
		// Draws a series of line segments by connecting the points in the specified array
		return ::Polyline( m_pData->hDC, lpPoints, nCount );
	}
	inline BOOL CDC::PolyPolyline (const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount) const
	{
		// Draws multiple series of connected line segments
		return ::PolyPolyline( m_pData->hDC, lpPoints, lpPolyPoints, nCount );
	}
	inline BOOL CDC::PolylineTo (const POINT* lpPoints, int nCount) const
	{
		// Draws one or more straight lines
		return ::PolylineTo( m_pData->hDC, lpPoints, nCount );
	}
	inline BOOL CDC::PolyBezier (const POINT* lpPoints, int nCount) const
	{
		// Draws one or more Bzier curves
		return ::PolyBezier( m_pData->hDC, lpPoints, nCount );
	}
	inline BOOL CDC::PolyBezierTo (const POINT* lpPoints, int nCount) const
	{
		// Draws one or more Bzier curves
		return ::PolyBezierTo(m_pData->hDC, lpPoints, nCount );
	}
	inline COLORREF CDC::GetPixel (int x, int y) const
	{
		// Retrieves the red, green, blue (RGB) color value of the pixel at the specified coordinates
		return ::GetPixel ( m_pData->hDC, x, y );
	}
	inline COLORREF CDC::GetPixel (POINT pt) const
	{
		// Retrieves the red, green, blue (RGB) color value of the pixel at the specified coordinates
		return ::GetPixel( m_pData->hDC, pt.x, pt.y );
	}
	inline COLORREF CDC::SetPixel (int x, int y, COLORREF crColor) const
	{
		// Sets the pixel at the specified coordinates to the specified color
		return ::SetPixel( m_pData->hDC, x, y, crColor );
	}
	inline COLORREF CDC::SetPixel (POINT pt, COLORREF crColor) const
	{
		// Sets the pixel at the specified coordinates to the specified color
		return ::SetPixel( m_pData->hDC, pt.x, pt.y, crColor );
	}
	inline BOOL CDC::SetPixelV (int x, int y, COLORREF crColor) const
	{
		// Sets the pixel at the specified coordinates to the closest approximation of the specified color
		return ::SetPixelV( m_pData->hDC, x, y, crColor );
	}
	inline BOOL CDC::SetPixelV (POINT pt, COLORREF crColor) const
	{
		// Sets the pixel at the specified coordinates to the closest approximation of the specified color
		return ::SetPixelV( m_pData->hDC, pt.x, pt.y, crColor );
	}
#endif

	// Shape Drawing Functions
	inline void CDC::DrawFocusRect (const RECT& rc) const
	{
		// draws a rectangle in the style used to indicate that the rectangle has the focus
		::DrawFocusRect( m_pData->hDC, &rc );
	}
	inline BOOL CDC::Ellipse (int x1, int y1, int x2, int y2) const
	{
		// Draws an ellipse. The center of the ellipse is the center of the specified bounding rectangle.
		return ::Ellipse( m_pData->hDC, x1, y1, x2, y2 );
	}
	inline BOOL CDC::Ellipse (const RECT& rc) const
	{
		// Draws an ellipse. The center of the ellipse is the center of the specified bounding rectangle.
		return ::Ellipse( m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom );
	}
	inline BOOL CDC::Polygon (LPPOINT lpPoints, int nCount) const
	{
		// Draws a polygon consisting of two or more vertices connected by straight lines
		return ::Polygon( m_pData->hDC, lpPoints, nCount);
	}
	inline BOOL CDC::Rectangle (int x1, int y1, int x2, int y2) const
	{
		// Draws a rectangle. The rectangle is outlined by using the current pen and filled by using the current brush.
		return ::Rectangle( m_pData->hDC, x1, y1, x2, y2 );
	}
	inline BOOL CDC::Rectangle (const RECT& rc) const
	{
		// Draws a rectangle. The rectangle is outlined by using the current pen and filled by using the current brush.
		return ::Rectangle( m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom );
	}
	inline BOOL CDC::RoundRect( int x1, int y1, int x2, int y2, int nWidth, int nHeight ) const
	{
		// Draws a rectangle with rounded corners
		return ::RoundRect (m_pData->hDC, x1, y1, x2, y2, nWidth, nHeight);
	}
	inline BOOL CDC::RoundRect (const RECT& rc, int nWidth, int nHeight) const
	{
		// Draws a rectangle with rounded corners
		return ::RoundRect(m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom, nWidth, nHeight );
	}

#ifndef _WIN32_WCE
	inline BOOL CDC::Chord (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const
	{
		// Draws a chord (a region bounded by the intersection of an ellipse and a line segment, called a secant)
		return ::Chord( m_pData->hDC, x1, y1, x2, y2, x3, y3, x4, y4 );
	}
	inline BOOL CDC::Chord (const RECT& rc, POINT ptStart, POINT ptEnd) const
	{
		// Draws a chord (a region bounded by the intersection of an ellipse and a line segment, called a secant)
		return ::Chord( m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom,
			ptStart.x, ptStart.y, ptEnd.x, ptEnd.y );
	}
	inline BOOL CDC::Pie (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const
	{
		// Draws a pie-shaped wedge bounded by the intersection of an ellipse and two radials.
		return ::Pie( m_pData->hDC, x1, y1, x2, y2, x3, y3, x4, y4 );
	}
	inline BOOL CDC::Pie (const RECT& rc, POINT ptStart, POINT ptEnd) const
	{
		// Draws a pie-shaped wedge bounded by the intersection of an ellipse and two radials.
		return ::Pie( m_pData->hDC, rc.left, rc.top, rc.right, rc.bottom,
			ptStart.x, ptStart.y, ptEnd.x, ptEnd.y );
	}
	inline BOOL CDC::PolyPolygon (LPPOINT lpPoints, LPINT lpPolyCounts, int nCount) const
	{
		// Draws a series of closed polygons
		return ::PolyPolygon( m_pData->hDC, lpPoints, lpPolyCounts, nCount );
	}
#endif

	// Fill and 3D Drawing functions
	inline BOOL CDC::FillRect (const RECT& rc, HBRUSH hbr) const
	{
		// Fills a rectangle by using the specified brush
		return (BOOL)::FillRect(m_pData->hDC, &rc, hbr);
	}
	inline BOOL CDC::InvertRect (const RECT& rc) const
	{
		// Inverts a rectangle in a window by performing a logical NOT operation on the color values for each pixel in the rectangle's interior
		return ::InvertRect( m_pData->hDC, &rc );
	}
	inline BOOL CDC::DrawIconEx (int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) const
	{
		// draws an icon or cursor, performing the specified raster operations, and stretching or compressing the icon or cursor as specified.
		return ::DrawIconEx( m_pData->hDC, xLeft, yTop, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags );
	}
	inline BOOL CDC::DrawEdge (const RECT& rc, UINT nEdge, UINT nFlags) const
	{
		// Draws one or more edges of rectangle
		return ::DrawEdge( m_pData->hDC, (LPRECT)&rc, nEdge, nFlags );
	}
	inline BOOL CDC::DrawFrameControl (const RECT& rc, UINT nType, UINT nState) const
	{
		// Draws a frame control of the specified type and style
		return ::DrawFrameControl( m_pData->hDC, (LPRECT)&rc, nType, nState );
	}
	inline BOOL CDC::FillRgn (HRGN hrgn, HBRUSH hbr) const
	{
		// Fills a region by using the specified brush
		return ::FillRgn( m_pData->hDC, hrgn, hbr );
	}

#ifndef _WIN32_WCE
	inline BOOL CDC::DrawIcon (int x, int y, HICON hIcon) const
	{
		// Draws an icon or cursor
		return ::DrawIcon( m_pData->hDC, x, y, hIcon );
	}
	inline BOOL CDC::DrawIcon (POINT pt, HICON hIcon) const
	{
		// Draws an icon or cursor
		return ::DrawIcon( m_pData->hDC, pt.x, pt.y, hIcon );
	}
	inline BOOL CDC::FrameRect (const RECT& rc, HBRUSH hbr) const
	{
		// Draws a border around the specified rectangle by using the specified brush
		return (BOOL)::FrameRect( m_pData->hDC, &rc, hbr );
	}
	inline BOOL CDC::PaintRgn (HRGN hrgn) const
	{
		// Paints the specified region by using the brush currently selected into the device context
		return ::PaintRgn( m_pData->hDC, hrgn);
	}
#endif

	// Bitmap Functions
	inline int CDC::StretchDIBits (int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth,
		           int nSrcHeight, CONST VOID *lpBits, BITMAPINFO& bi, UINT iUsage, DWORD dwRop) const
	{
		// Copies the color data for a rectangle of pixels in a DIB to the specified destination rectangle
		return ::StretchDIBits( m_pData->hDC, XDest, YDest, nDestWidth, nDestHeight, XSrc, YSrc, nSrcWidth, nSrcHeight, lpBits, &bi, iUsage, dwRop );
	}

	inline BOOL CDC::PatBlt (int x, int y, int nWidth, int nHeight, DWORD dwRop) const
	{
		// Paints the specified rectangle using the brush that is currently selected into the device context
		return ::PatBlt( m_pData->hDC, x, y, nWidth, nHeight, dwRop );
	}
	inline BOOL CDC::BitBlt (int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, DWORD dwRop) const
	{
		// Performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context
		return ::BitBlt( m_pData->hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, dwRop );
	}
	inline BOOL CDC::StretchBlt (int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop) const
	{
		// Copies a bitmap from a source rectangle into a destination rectangle, stretching or compressing the bitmap to fit the dimensions of the destination rectangle, if necessary
		return ::StretchBlt( m_pData->hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop );
	}

#ifndef _WIN32_WCE
	inline int CDC::GetDIBits (HBITMAP hbmp, UINT uStartScan, UINT cScanLines, LPVOID lpvBits, LPBITMAPINFO lpbi, UINT uUsage) const
	{
		// Retrieves the bits of the specified compatible bitmap and copies them into a buffer as a DIB using the specified format
		return ::GetDIBits( m_pData->hDC, hbmp, uStartScan, cScanLines, lpvBits, lpbi, uUsage );
	}
	inline int CDC::SetDIBits (HBITMAP hbmp, UINT uStartScan, UINT cScanLines, CONST VOID *lpvBits, LPBITMAPINFO lpbi, UINT fuColorUse) const
	{
		// Sets the pixels in a compatible bitmap (DDB) using the color data found in the specified DIB
		return ::SetDIBits( m_pData->hDC, hbmp, uStartScan, cScanLines, lpvBits, lpbi, fuColorUse );
	}
	inline int CDC::GetStretchBltMode () const
	{
		// Retrieves the current stretching mode
		// Possible modes: BLACKONWHITE, COLORONCOLOR, HALFTONE, STRETCH_ANDSCANS, STRETCH_DELETESCANS, STRETCH_HALFTONE, STRETCH_ORSCANS, WHITEONBLACK
		return ::GetStretchBltMode( m_pData->hDC );
	}
	inline int CDC::SetStretchBltMode (int iStretchMode) const
	{
		// Sets the stretching mode
		// Possible modes: BLACKONWHITE, COLORONCOLOR, HALFTONE, STRETCH_ANDSCANS, STRETCH_DELETESCANS, STRETCH_HALFTONE, STRETCH_ORSCANS, WHITEONBLACK
		return ::SetStretchBltMode( m_pData->hDC, iStretchMode );
	}
	inline BOOL CDC::FloodFill (int x, int y, COLORREF crColor) const
	{
		// Fills an area of the display surface with the current brush
		return ::FloodFill (m_pData->hDC, x, y, crColor);
	}
	inline BOOL CDC::ExtFloodFill (int x, int y, COLORREF crColor, UINT nFillType) const
	{
		// Fills an area of the display surface with the current brush
		// Fill type: FLOODFILLBORDER or FLOODFILLSURFACE
		return ::ExtFloodFill(m_pData->hDC, x, y, crColor, nFillType );
	}

	// co-ordinate functions
	inline BOOL CDC::DPtoLP (LPPOINT lpPoints, int nCount) const
	{
		if (m_pData->hDC != NULL)
			return ::DPtoLP(m_pData->hDC, lpPoints, nCount);
		return FALSE;
	}
	inline BOOL CDC::DPtoLP (LPRECT lpRect) const
	{
		if (m_pData->hDC != NULL)
			return ::DPtoLP(m_pData->hDC, (LPPOINT)lpRect, 2);
		return FALSE;
	}

	inline BOOL CDC::LPtoDP (LPPOINT lpPoints, int nCount) const
	{
		if (m_pData->hDC != NULL)
			return ::LPtoDP(m_pData->hDC, lpPoints, nCount);
		return FALSE;
	}
	inline BOOL CDC::LPtoDP (LPRECT lpRect) const
	{
		if (m_pData->hDC != NULL)
			return ::LPtoDP(m_pData->hDC, (LPPOINT)lpRect, 2);
		return FALSE;
	}

#endif

	// Layout Functions
	inline DWORD CDC::GetLayout () const
	{
		// Returns the layout of a device context (LAYOUT_RTL and LAYOUT_BITMAPORIENTATIONPRESERVED)
#if defined(WINVER) && defined (GetLayout) && (WINVER >= 0x0500)
		return ::GetLayout(m_pData->hDC);
#else
		return 0;
#endif
	}
	inline DWORD CDC::SetLayout (DWORD dwLayout) const
	{
#if defined(WINVER) && defined (SetLayout) && (WINVER >= 0x0500)
		// Sets the layout of a device context
		return ::SetLayout(m_pData->hDC, dwLayout);
#else
		UNREFERENCED_PARAMETER(dwLayout); // no-op
		return 0;
#endif
	}

	// Mapping Functions
#ifndef _WIN32_WCE
	inline int CDC::GetMapMode ()  const
	{
		if (m_pData->hDC != NULL)
			return ::GetMapMode(m_pData->hDC);
		return 0;
	}
	inline BOOL CDC::GetViewportOrgEx (LPPOINT lpPoint)  const
	{
		if (m_pData->hDC != NULL)
			return ::GetViewportOrgEx(m_pData->hDC, lpPoint);
		return 0;
	}
	inline int CDC::SetMapMode (int nMapMode) const
	{
		if (m_pData->hDC != NULL)
			return ::SetMapMode(m_pData->hDC, nMapMode);
		return 0;
	}
	inline BOOL CDC::SetViewportOrgEx (int x, int y, LPPOINT lpPoint /* = NULL */) const
	{
		if (m_pData->hDC != NULL)
			return ::SetViewportOrgEx(m_pData->hDC, x, y, lpPoint);
		return FALSE;
	}
	inline BOOL CDC::SetViewportOrgEx (POINT point, LPPOINT lpPointRet /* = NULL */) const
	{
		if (m_pData->hDC != NULL)
			return SetViewportOrgEx (point.x, point.y, lpPointRet);
		return FALSE;
	}
	inline BOOL CDC::OffsetViewportOrgEx (int nWidth, int nHeight, LPPOINT lpPoint /* = NULL */) const
	{
		if (m_pData->hDC != NULL)
			return ::OffsetViewportOrgEx(m_pData->hDC, nWidth, nHeight, lpPoint);
		return FALSE;
	}
	inline BOOL CDC::GetViewportExtEx (LPSIZE lpSize)  const
	{
		if (m_pData->hDC != NULL)
			return ::GetViewportExtEx(m_pData->hDC, lpSize);
		return FALSE;
	}
	inline BOOL CDC::SetViewportExtEx (int x, int y, LPSIZE lpSize ) const
	{
		if (m_pData->hDC != NULL)
			return ::SetViewportExtEx(m_pData->hDC, x, y, lpSize);
		return FALSE;
	}
	inline BOOL CDC::SetViewportExtEx (SIZE size, LPSIZE lpSizeRet ) const
	{
		if (m_pData->hDC != NULL)
			return SetViewportExtEx(size.cx, size.cy, lpSizeRet);
		return FALSE;
	}
	inline BOOL CDC::ScaleViewportExtEx (int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize ) const
	{
		if (m_pData->hDC != NULL)
			return ::ScaleViewportExtEx(m_pData->hDC, xNum, xDenom, yNum, yDenom, lpSize);
		return FALSE;
	}
	inline BOOL CDC::GetWindowOrgEx (LPPOINT lpPoint) const
	{
		if (m_pData->hDC != NULL)
			return ::GetWindowOrgEx(m_pData->hDC, lpPoint);
		return FALSE;
	}
	inline BOOL CDC::SetWindowOrgEx (int x, int y, LPPOINT lpPoint ) const
	{
		if (m_pData->hDC != NULL)
			return ::SetWindowOrgEx(m_pData->hDC, x, y, lpPoint);
		return FALSE;
	}
	inline BOOL CDC::SetWindowOrgEx (POINT point, LPPOINT lpPointRet ) const
	{
		if (m_pData->hDC != NULL)
			return SetWindowOrgEx(point.x, point.y, lpPointRet);
		return FALSE;
	}
	inline BOOL CDC::OffsetWindowOrgEx (int nWidth, int nHeight, LPPOINT lpPoint ) const
	{
		if (m_pData->hDC != NULL)
			return ::OffsetWindowOrgEx(m_pData->hDC, nWidth, nHeight, lpPoint);
		return FALSE;
	}
	inline BOOL CDC::GetWindowExtEx (LPSIZE lpSize)  const
	{
		if (m_pData->hDC != NULL)
			return ::GetWindowExtEx(m_pData->hDC, lpSize);
		return FALSE;
	}
	inline BOOL CDC::SetWindowExtEx (int x, int y, LPSIZE lpSize ) const
	{
		if (m_pData->hDC != NULL)
			return ::SetWindowExtEx(m_pData->hDC, x, y, lpSize);
		return FALSE;
	}
	inline BOOL CDC::SetWindowExtEx (SIZE size, LPSIZE lpSizeRet) const
	{
		if (m_pData->hDC != NULL)
			return SetWindowExtEx(size.cx, size.cy, lpSizeRet);
		return FALSE;
	}
	inline BOOL CDC::ScaleWindowExtEx (int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize) const
	{
		if (m_pData->hDC != NULL)
			return ::ScaleWindowExtEx(m_pData->hDC, xNum, xDenom, yNum, yDenom, lpSize);
		return FALSE;
	}
#endif

	// Printer Functions
	inline int CDC::StartDoc (LPDOCINFO lpDocInfo) const
	{
		return ::StartDoc(m_pData->hDC, lpDocInfo);
	}
	inline int CDC::EndDoc () const
	{
		return ::EndDoc(m_pData->hDC);
	}
	inline int CDC::StartPage () const
	{
		return ::StartPage(m_pData->hDC);
	}
	inline int CDC::EndPage () const
	{
		return ::EndPage(m_pData->hDC);
	}
	inline int CDC::AbortDoc () const
	{
		return ::AbortDoc(m_pData->hDC);
	}
	inline int CDC::SetAbortProc (BOOL (CALLBACK* lpfn)(HDC, int)) const
	{
		return ::SetAbortProc(m_pData->hDC, lpfn);
	}

	// Text Functions
	inline BOOL CDC::ExtTextOut (int x, int y, UINT nOptions, LPCRECT lprc, LPCTSTR lpszString, int nCount /*= -1*/, LPINT lpDxWidths /*=NULL*/) const
	{
		// Draws text using the currently selected font, background color, and text color
		if (nCount == -1)
			nCount = lstrlen (lpszString);

		return ::ExtTextOut(m_pData->hDC, x, y, nOptions, lprc, lpszString, nCount, lpDxWidths );
	}

	inline int CDC::DrawText (LPCTSTR lpszString, int nCount, LPRECT lprc, UINT nFormat) const
	{
		// Draws formatted text in the specified rectangle
		return ::DrawText(m_pData->hDC, lpszString, nCount, lprc, nFormat );
	}
	inline UINT CDC::GetTextAlign () const
	{
		// Retrieves the text-alignment setting
		// Values: TA_BASELINE, TA_BOTTOM, TA_TOP, TA_CENTER, TA_LEFT, TA_RIGHT, TA_RTLREADING, TA_NOUPDATECP, TA_UPDATECP
		return ::GetTextAlign( m_pData->hDC );
	}
	inline UINT CDC::SetTextAlign (UINT nFlags) const
	{
		// Sets the text-alignment setting
		// Values: TA_BASELINE, TA_BOTTOM, TA_TOP, TA_CENTER, TA_LEFT, TA_RIGHT, TA_RTLREADING, TA_NOUPDATECP, TA_UPDATECP
		return ::SetTextAlign( m_pData->hDC, nFlags );
	}
	inline int CDC::GetTextFace (int nCount, LPTSTR lpszFacename) const
	{
		// Retrieves the typeface name of the font that is selected into the device context
		return ::GetTextFace( m_pData->hDC, nCount, lpszFacename );
	}
	inline BOOL CDC::GetTextMetrics (TEXTMETRIC& Metrics) const
	{
		// Fills the specified buffer with the metrics for the currently selected font
		return ::GetTextMetrics( m_pData->hDC, &Metrics );
	}
	inline COLORREF CDC::GetBkColor () const
	{
		// Returns the current background color
		return ::GetBkColor( m_pData->hDC );
	}
	inline COLORREF CDC::SetBkColor (COLORREF crColor) const
	{
		// Sets the current background color to the specified color value
		return ::SetBkColor(m_pData->hDC, crColor );
	}
	inline COLORREF CDC::GetTextColor () const
	{
		// Retrieves the current text color
		return ::GetTextColor( m_pData->hDC);
	}
	inline COLORREF CDC::SetTextColor (COLORREF crColor) const
	{
		// Sets the current text color
		return ::SetTextColor( m_pData->hDC, crColor );
	}
	inline int CDC::GetBkMode () const
	{
		// returns the current background mix mode (OPAQUE or TRANSPARENT)
		return ::GetBkMode( m_pData->hDC );
	}
	inline int CDC::SetBkMode (int iBkMode) const
	{
		// Sets the current background mix mode (OPAQUE or TRANSPARENT)
		return ::SetBkMode( m_pData->hDC, iBkMode);
	}
#ifndef _WIN32_WCE
	inline CSize CDC::GetTextExtentPoint (LPCTSTR lpszString, int nCount) const
	{
		// Computes the width and height of the specified string of text
		CSize sz;
		::GetTextExtentPoint(m_pData->hDC, lpszString, nCount, &sz );
		return sz;
	}
	inline BOOL CDC::TextOut (int x, int y, LPCTSTR lpszString, int nCount/* = -1*/) const
	{
		// Writes a character string at the specified location
		if (nCount == -1)
			nCount = lstrlen (lpszString);

		return ::TextOut( m_pData->hDC, x, y, lpszString, nCount );
	}
	inline int CDC::DrawTextEx (LPTSTR lpszString, int nCount, LPRECT lprc, UINT nFormat, const DRAWTEXTPARAMS& DTParams) const
	{
		// Draws formatted text in the specified rectangle with more formatting options
		return ::DrawTextEx(m_pData->hDC, lpszString, nCount, lprc, nFormat, (LPDRAWTEXTPARAMS)&DTParams );
	}
	inline CSize CDC::TabbedTextOut (int x, int y, LPCTSTR lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin) const
	{
		// Writes a character string at a specified location, expanding tabs to the values specified in an array of tab-stop positions
		DWORD dwSize = ::TabbedTextOut(m_pData->hDC, x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin );
		CSize sz(dwSize);
		return sz;
	}
	inline CSize CDC::GetTabbedTextExtent (LPCTSTR lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions) const
	{
		// Computes the width and height of a character string
		DWORD dwSize = ::GetTabbedTextExtent(m_pData->hDC, lpszString, nCount, nTabPositions, lpnTabStopPositions );
		CSize sz(dwSize);
		return sz;
	}
	inline BOOL CDC::GrayString (HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight) const
	{
		// Draws gray text at the specified location
		return ::GrayString(m_pData->hDC, hBrush, lpOutputFunc, lpData, nCount, x, y, nWidth, nHeight );
	}
	inline int CDC::SetTextJustification (int nBreakExtra, int nBreakCount) const
	{
		// Specifies the amount of space the system should add to the break characters in a string of text
		return ::SetTextJustification( m_pData->hDC, nBreakExtra, nBreakCount  );
	}
	inline int CDC::GetTextCharacterExtra () const
	{
		// Retrieves the current intercharacter spacing for the device context
		return ::GetTextCharacterExtra( m_pData->hDC );
	}
	inline int CDC::SetTextCharacterExtra (int nCharExtra) const
	{
		// Sets the intercharacter spacing
		return ::SetTextCharacterExtra( m_pData->hDC, nCharExtra );
	}
	inline CSize CDC::GetTextExtentPoint32 (LPCTSTR lpszString, int nCount) const
	{
		// Computes the width and height of the specified string of text
		CSize sz;
		::GetTextExtentPoint32(m_pData->hDC, lpszString, nCount, &sz );
		return sz;
	}
#endif



	/////////////////////////////////////////////////////////////////
	// Definitions for some global functions in the Win32xx namespace
	//

#ifndef _WIN32_WCE
	inline void TintBitmap (HBITMAP hbmSource, int cRed, int cGreen, int cBlue)
	// Modifies the colour of the supplied Device Dependant Bitmap, by the colour
	// correction values specified. The correction values can range from -255 to +255.
	// This function gains its speed by accessing the bitmap colour information
	// directly, rather than using GetPixel/SetPixel.
	{
		// Create our LPBITMAPINFO object
		CBitmapInfoPtr pbmi(hbmSource);
		pbmi->bmiHeader.biBitCount = 24;

		// Create the reference DC for GetDIBits to use
		CDC MemDC = CreateCompatibleDC(NULL);

		// Use GetDIBits to create a DIB from our DDB, and extract the colour data
		MemDC.GetDIBits(hbmSource, 0, pbmi->bmiHeader.biHeight, NULL, pbmi, DIB_RGB_COLORS);
		std::vector<byte> vBits(pbmi->bmiHeader.biSizeImage, 0);
		byte* pByteArray = &vBits.front();

		MemDC.GetDIBits(hbmSource, 0, pbmi->bmiHeader.biHeight, pByteArray, pbmi, DIB_RGB_COLORS);
		UINT nWidthBytes = pbmi->bmiHeader.biSizeImage/pbmi->bmiHeader.biHeight;

		// Ensure sane colour correction values
		cBlue  = MIN(cBlue, 255);
		cBlue  = MAX(cBlue, -255);
		cRed   = MIN(cRed, 255);
		cRed   = MAX(cRed, -255);
		cGreen = MIN(cGreen, 255);
		cGreen = MAX(cGreen, -255);

		// Pre-calculate the RGB modification values
		int b1 = 256 - cBlue;
		int g1 = 256 - cGreen;
		int r1 = 256 - cRed;

		int b2 = 256 + cBlue;
		int g2 = 256 + cGreen;
		int r2 = 256 + cRed;

		// Modify the colour
		int yOffset = 0;
		int xOffset;
		int Index;
		for (int Row=0; Row < pbmi->bmiHeader.biHeight; Row++)
		{
			xOffset = 0;

			for (int Column=0; Column < pbmi->bmiHeader.biWidth; Column++)
			{
				// Calculate Index
				Index = yOffset + xOffset;

				// Adjust the colour values
				if (cBlue > 0)
					pByteArray[Index]   = (BYTE)(cBlue + (((pByteArray[Index] *b1)) >>8));
				else if (cBlue < 0)
					pByteArray[Index]   = (BYTE)((pByteArray[Index] *b2) >>8);

				if (cGreen > 0)
					pByteArray[Index+1] = (BYTE)(cGreen + (((pByteArray[Index+1] *g1)) >>8));
				else if (cGreen < 0)
					pByteArray[Index+1] = (BYTE)((pByteArray[Index+1] *g2) >>8);

				if (cRed > 0)
					pByteArray[Index+2] = (BYTE)(cRed + (((pByteArray[Index+2] *r1)) >>8));
				else if (cRed < 0)
					pByteArray[Index+2] = (BYTE)((pByteArray[Index+2] *r2) >>8);

				// Increment the horizontal offset
				xOffset += pbmi->bmiHeader.biBitCount >> 3;
			}

			// Increment vertical offset
			yOffset += nWidthBytes;
		}

		// Save the modified colour back into our source DDB
		MemDC.SetDIBits(hbmSource, 0, pbmi->bmiHeader.biHeight, pByteArray, pbmi, DIB_RGB_COLORS);
	}

	inline void GrayScaleBitmap (HBITMAP hbmSource)
	{
		// Create our LPBITMAPINFO object
		CBitmapInfoPtr pbmi(hbmSource);

		// Create the reference DC for GetDIBits to use
		CDC MemDC = CreateCompatibleDC(NULL);

		// Use GetDIBits to create a DIB from our DDB, and extract the colour data
		MemDC.GetDIBits(hbmSource, 0, pbmi->bmiHeader.biHeight, NULL, pbmi, DIB_RGB_COLORS);
		std::vector<byte> vBits(pbmi->bmiHeader.biSizeImage, 0);
		byte* pByteArray = &vBits.front();

		MemDC.GetDIBits(hbmSource, 0, pbmi->bmiHeader.biHeight, pByteArray, pbmi, DIB_RGB_COLORS);
		UINT nWidthBytes = pbmi->bmiHeader.biSizeImage/pbmi->bmiHeader.biHeight;

		int yOffset = 0;
		int xOffset;
		int Index;

		for (int Row=0; Row < pbmi->bmiHeader.biHeight; Row++)
		{
			xOffset = 0;

			for (int Column=0; Column < pbmi->bmiHeader.biWidth; Column++)
			{
				// Calculate Index
				Index = yOffset + xOffset;

				BYTE byGray = (BYTE) ((pByteArray[Index] + pByteArray[Index+1]*6 + pByteArray[Index+2] *3)/10);
				pByteArray[Index]   = byGray;
				pByteArray[Index+1] = byGray;
				pByteArray[Index+2] = byGray;

				// Increment the horizontal offset
				xOffset += pbmi->bmiHeader.biBitCount >> 3;
			}

			// Increment vertical offset
			yOffset += nWidthBytes;
		}

		// Save the modified colour back into our source DDB
		MemDC.SetDIBits(hbmSource, 0, pbmi->bmiHeader.biHeight, pByteArray, pbmi, DIB_RGB_COLORS);
	}

	inline HIMAGELIST CreateDisabledImageList (HIMAGELIST himlNormal)
	// Returns a greyed image list, created from hImageList
	{
		int cx, cy;
		int nCount = ImageList_GetImageCount(himlNormal);
		if (0 == nCount)
			return NULL;

		ImageList_GetIconSize(himlNormal, &cx, &cy);

		// Create the disabled ImageList
		HIMAGELIST himlDisabled = ImageList_Create(cx, cy, ILC_COLOR24 | ILC_MASK, nCount, 0);

		// Process each image in the ImageList
		for (int i = 0 ; i < nCount; ++i)
		{
			CDC DesktopDC = ::GetDC(NULL);
			CDC MemDC = ::CreateCompatibleDC(NULL);
			MemDC.CreateCompatibleBitmap(DesktopDC, cx, cx);
			CRect rc;
			rc.SetRect(0, 0, cx, cx);

			// Set the mask color to grey for the new ImageList
			COLORREF crMask = RGB(200, 199, 200);
			if ( GetDeviceCaps(DesktopDC, BITSPIXEL) < 24)
			{
				HPALETTE hPal = (HPALETTE)GetCurrentObject(DesktopDC, OBJ_PAL);
				UINT Index = GetNearestPaletteIndex(hPal, crMask);
				if (Index != CLR_INVALID) crMask = PALETTEINDEX(Index);
			}

			MemDC.SolidFill(crMask, rc);

			// Draw the image on the memory DC
			ImageList_SetBkColor(himlNormal, crMask);
			ImageList_Draw(himlNormal, i, MemDC, 0, 0, ILD_NORMAL);

			// Convert colored pixels to gray
			for (int x = 0 ; x < cx; ++x)
			{
				for (int y = 0; y < cy; ++y)
				{
					COLORREF clr = ::GetPixel(MemDC, x, y);

					if (clr != crMask)
					{
						BYTE byGray = (BYTE) (95 + (GetRValue(clr) *3 + GetGValue(clr)*6 + GetBValue(clr))/20);
						MemDC.SetPixel(x, y, RGB(byGray, byGray, byGray));
					}

				}
			}

			// Detach the bitmap so we can use it.
			HBITMAP hbm = MemDC.DetachBitmap();
			ImageList_AddMasked(himlDisabled, hbm, crMask);
			::DeleteObject(hbm);
		}

		return himlDisabled;
	}
#endif


} // namespace Win32xx

#endif // _GDI_H_

