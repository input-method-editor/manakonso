﻿
#ifndef CANDIDATEWINDOW_H
#define CANDIDATEWINDOW_H

#include "TextService.h"
#include "CandidateList.h"
#include "InputModeWindow.h"

class CCandidateWindow : public ITfCandidateListUIElementBehavior
{
public:
	CCandidateWindow(CTextService *pTextService, CCandidateList *pCandidateList);
	~CCandidateWindow();

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	// ITfUIElement
	STDMETHODIMP GetDescription(BSTR *bstr);
	STDMETHODIMP GetGUID(GUID *pguid);
	STDMETHODIMP Show(BOOL bShow);
	STDMETHODIMP IsShown(BOOL *pbShow);

	// ITfCandidateListUIElement
	STDMETHODIMP GetUpdatedFlags(DWORD *pdwFlags);
	STDMETHODIMP GetDocumentMgr(ITfDocumentMgr **ppdim);
	STDMETHODIMP GetCount(UINT *puCount);
	STDMETHODIMP GetSelection(UINT *puIndex);
	STDMETHODIMP GetString(UINT uIndex, BSTR *pstr);
	STDMETHODIMP GetPageIndex(UINT *pIndex, UINT uSize, UINT *puPageCnt);
	STDMETHODIMP SetPageIndex(UINT *pIndex, UINT uPageCnt);
	STDMETHODIMP GetCurrentPage(UINT *puPage);

	// ITfCandidateListUIElementBehavior
	STDMETHODIMP SetSelection(UINT nIndex);
	STDMETHODIMP Finalize();
	STDMETHODIMP Abort();

	BOOL _Create(HWND hwndParent, CCandidateWindow *pCandidateWindowParent, DWORD dwUIElementId, UINT depth, BOOL reg, BOOL comp);
	static BOOL _InitClass();
	static void _UninitClass();
	static LRESULT CALLBACK _WindowPreProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void _Destroy();
	void _Move(LPCRECT lpr);
	void _BeginUIElement();
	void _EndUIElement();
	BOOL _CanShowUIElement();
	void _Redraw();
	HRESULT _OnKeyDown(UINT uVKey);
	void _SetText(const std::wstring &text, BOOL fixed, BOOL showcandlist, BOOL showreg);
	void _PreEnd();
	void _End();
	void _UpdateComp();

private:
	LONG _cRef;

	void _InitList();
	void _UpdateUIElement();
	void _NextPage();
	void _PrevPage();
	void _NextComp();
	void _PrevComp();
	void _OnKeyDownRegword(UINT uVKey);
	void _Update();
	void _InvokeSfHandler(BYTE sf);
	void _InvokeKeyHandler(UINT uVKey);
	void _HandleKey(WPARAM wParam, BYTE bSf);
	void _GetChSf(UINT uVKey, WCHAR &ch, BYTE &sf, BYTE vkoff = 0);
	void _BackUpStatus();
	void _ClearStatus();
	void _RestoreStatusReg();
	void _ClearStatusReg();
	void _PreEndReq();
	void _EndReq();
	void _CreateNext(BOOL reg);

	//Paint
	void _WindowProcPaint(HWND hWnd);
	std::wstring _MakeRegWordString();
	void _PaintRegWord(HDC hdc, LPRECT lpr);
	std::wstring _MakeCandidateString(UINT page, UINT count, UINT idx, int cycle);
	void _PaintCandidate(HDC hdc, LPRECT lpr, UINT page, UINT count, UINT idx);
	void _CalcWindowRect();
	HRESULT _GetTextMetrics(LPCWSTR text, DWRITE_TEXT_METRICS *metrics);

	DWORD _dwUIElementId;
	BOOL _bShow;
	DWORD _dwFlags;
	UINT _uShowedCount;
	UINT _uCount;
	UINT _uIndex;
	UINT _uPageCnt;
	std::vector< UINT > _CandCount;
	std::vector< UINT > _PageIndex;
	std::vector< std::wstring > _CandStr;

	CTextService *_pTextService;
	CCandidateList *_pCandidateList;
	CCandidateWindow *_pCandidateWindow;		//子
	CCandidateWindow *_pCandidateWindowParent;	//親
	CInputModeWindow *_pInputModeWindow;
	HWND _hwnd;			//自分
	HWND _hwndParent;	//親
	BOOL _preEnd;		//親に対する終了要求
	RECT _rect;			//親の位置
	UINT _depth;		//深さ

	//候補一覧、辞書登録のウィンドウ
	std::wstring disptext;		//表示文字列
	HFONT hFont;				//フォント

	//Direct2D/DirectWrite
	ID2D1Factory *_pD2DFactory;
	ID2D1DCRenderTarget *_pD2DDCRT;
	ID2D1SolidColorBrush *_pD2DBrush[DISPLAY_COLOR_NUM];
	D2D1_DRAW_TEXT_OPTIONS _drawtext_option;
	IDWriteFactory *_pDWFactory;
	IDWriteTextFormat *_pDWTF;

	BOOL _reg;		//初期表示から辞書登録
	BOOL _comp;		//複数補完/複数動的補完

	CANDIDATES candidates;		//描画用候補
	size_t candidx;				//描画用候補インデックス
	std::wstring searchkey;		//描画用見出し語

	//辞書登録
	BOOL regword;				//モード
	BOOL regwordul;				//UILess
	BOOL regwordfixed;			//未確定文字列を確定
	std::wstring regwordtext;	//確定文字列
	size_t regwordtextpos;		//カーソルインデックス
	std::wstring comptext;		//未確定文字列

	//辞書登録前の状態バックアップ
	int inputmode_bak;
	std::wstring kana_bak;
	size_t okuriidx_bak;
	size_t cursoridx_bak;
	std::wstring searchkey_bak;
	std::wstring searchkeyorg_bak;
	CANDIDATES candidates_bak;
	size_t candidx_bak;
	size_t candorgcnt_bak;
};

#endif //CANDIDATEWINDOW_H
