
// SelectionSortView.cpp : implementation of the CSelectionSortView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SelectionSort.h"
#endif

#include "SelectionSortDoc.h"
#include "SelectionSortView.h"
#include "CTest.h"
#include "sstream"
#include "vector"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSelectionSortView

IMPLEMENT_DYNCREATE(CSelectionSortView, CScrollView)

BEGIN_MESSAGE_MAP(CSelectionSortView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSelectionSortView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DEMO, &CSelectionSortView::OnDemo)
END_MESSAGE_MAP()

// CSelectionSortView construction/destruction

CSelectionSortView::CSelectionSortView() noexcept
{
	// TODO: add construction code here

}

CSelectionSortView::~CSelectionSortView()
{
}

BOOL CSelectionSortView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CSelectionSortView drawing

void CSelectionSortView::OnDraw(CDC* pDC)
{
	CSelectionSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CFont aFont;
	aFont.CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");
	pDC->SelectObject(&aFont);

	if (pDoc->m_output.size() > 0)
		for (int i = 0; i < (pDoc->m_output.size()); i++)
			pDC->TextOut(0, i * 50, pDoc->m_output[i]);
}

void CSelectionSortView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 50000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CSelectionSortView printing


void CSelectionSortView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSelectionSortView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSelectionSortView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSelectionSortView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSelectionSortView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSelectionSortView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSelectionSortView diagnostics

#ifdef _DEBUG
void CSelectionSortView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSelectionSortView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSelectionSortDoc* CSelectionSortView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSelectionSortDoc)));
	return (CSelectionSortDoc*)m_pDocument;
}
#endif //_DEBUG


// CSelectionSortView message handlers


void CSelectionSortView::OnDemo()
{
	// TODO: Add your command handler code here
	CSelectionSortDoc* pDoc = GetDocument();
	CTest aDiag;
	CClientDC aDC(this);
	if (aDiag.DoModal() == IDOK) {
		pDoc->m_output.clear();
		viewStr = aDiag.diagStr;
		//pDoc->m_output.push_back(viewStr);
		SelectSort(viewStr);
		pDoc->UpdateAllViews(NULL);

	}
}


void CSelectionSortView::SelectSort(CString& str)
{
	// TODO: Add your implementation code here.
	string str2 = CT2A(str.GetBuffer());
	string s1;
	CSelectionSortDoc* pDoc = GetDocument();
	long long n;
	stringstream s, s2;
	s << str2;
	vector<long long> data;
	while (getline(s, s1, ',')) {
		s2 << s1;
		s2 >> n;
		data.push_back(n);
		s2.clear();
	}

		turnCString(data);

		for (int i = 0; i <(data.size()); i++)
		{
			short min = i;

			for (int j = i+1; j < (data.size()); j++)
				if (data[min] > data[j])
					min = j;
			long long tmp = data[min];
			data[min] = data[i];
			data[i] = tmp;
			turnCString(data);
		}
}


void CSelectionSortView::turnCString(vector<long long> data)
{
	// TODO: Add your implementation code here.
	CSelectionSortDoc* pDoc = GetDocument();
	CString str,tmp;
	str.Format(L"%lli", data[0]);
	for (int i = 1; i < data.size(); i++)
	{
		str += L",";
		tmp.Format(L"%lli", data[i]);
		str += tmp;
	}
	pDoc->m_output.push_back(str);
}
