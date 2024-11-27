
// SelectionSortView.h : interface of the CSelectionSortView class
//

#pragma once


class CSelectionSortView : public CScrollView
{
protected: // create from serialization only
	CSelectionSortView() noexcept;
	DECLARE_DYNCREATE(CSelectionSortView)

// Attributes
public:
	CSelectionSortDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSelectionSortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDemo();
	CString viewStr;
	void SelectSort(CString& str);
	void turnCString(vector<long long> data);
};

#ifndef _DEBUG  // debug version in SelectionSortView.cpp
inline CSelectionSortDoc* CSelectionSortView::GetDocument() const
   { return reinterpret_cast<CSelectionSortDoc*>(m_pDocument); }
#endif

