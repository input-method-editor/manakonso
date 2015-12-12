﻿
#include "imcrvtip.h"
#include "TextService.h"
#include "CandidateList.h"

WCHAR CTextService::_GetCh(BYTE vk, BYTE vkoff)
{
	BYTE keystate[256];
	WCHAR ubuff;
	WCHAR u = L'\0';

	GetKeyboardState(keystate);

	switch(inputmode)
	{
	case im_hiragana:
	case im_katakana:
	case im_katakana_ank:
		keystate[VK_CAPITAL] = 0;
		if(abbrevmode || purgedicmode)
		{
			keystate[VK_KANA] = 0;
		}
		if(vkoff != 0)
		{
			keystate[vkoff] = 0;
		}
		break;
	case im_jlatin:
	case im_ascii:
		keystate[VK_KANA] = 0;
		break;
	default:
		break;
	}

	int retu = ToUnicode(vk, 0, keystate, &ubuff, 1, 0);
	if(retu == 1)
	{
		u = ubuff;
	}

	return u;
}

BYTE CTextService::_GetSf(BYTE vk, WCHAR ch)
{
	BYTE k = SKK_NULL;
	SHORT vk_shift = GetKeyState(VK_SHIFT) & 0x8000;
	SHORT vk_ctrl = GetKeyState(VK_CONTROL) & 0x8000;

	if(vk < VKEYMAPNUM)
	{
		switch(inputmode)
		{
		case im_ascii:
		case im_jlatin:
			if(vk_shift)
			{
				k = vkeymap_shift.keylatin[vk];
			}
			else if(vk_ctrl)
			{
				k = vkeymap_ctrl.keylatin[vk];
			}
			else
			{
				k = vkeymap.keylatin[vk];
			}
			break;
		case im_hiragana:
		case im_katakana:
		case im_katakana_ank:
			if(vk_shift)
			{
				k = vkeymap_shift.keyjmode[vk];
			}
			else if(vk_ctrl)
			{
				k = vkeymap_ctrl.keyjmode[vk];
			}
			else
			{
				k = vkeymap.keyjmode[vk];
			}
			break;
		default:
			break;
		}
	}

	if(k == SKK_NULL && ch < CKEYMAPNUM)
	{
		switch(inputmode)
		{
		case im_ascii:
		case im_jlatin:
			k = ckeymap.keylatin[ch];
			break;
		case im_hiragana:
		case im_katakana:
		case im_katakana_ank:
			k = ckeymap.keyjmode[ch];
			break;
		default:
			break;
		}
	}

	//カタカナ/ｶﾀｶﾅモードかつ確定入力モードのとき「ひらがな」を有効にする
	switch(inputmode)
	{
	case im_katakana:
	case im_katakana_ank:
		if(!inputkey)
		{
			if(vk < VKEYMAPNUM)
			{
				if((vkeymap.keylatin[vk] == SKK_JMODE) ||
					(vk_shift && (vkeymap_shift.keylatin[vk] == SKK_JMODE)) ||
					(vk_ctrl && (vkeymap_ctrl.keylatin[vk] == SKK_JMODE)))
				{
					k = SKK_KANA;
				}
			}
			if(k != SKK_KANA && ch < CKEYMAPNUM)
			{
				if(ckeymap.keylatin[ch] == SKK_JMODE)
				{
					k = SKK_KANA;
				}
			}
		}
		break;
	}

	switch(ch)
	{
	case TKB_NEXT_PAGE:
		k = SKK_NEXT_CAND;
		break;
	case TKB_PREV_PAGE:
		k = SKK_PREV_CAND;
		break;
	default:
		break;
	}

	return k;
}

HRESULT CTextService::_ConvRomanKana(ROMAN_KANA_CONV *pconv)
{
	HRESULT ret = _SearchRomanKanaNode(roman_kana_tree, pconv, 0);

	return ret;
}

HRESULT CTextService::_SearchRomanKanaNode(const ROMAN_KANA_NODE &tree, ROMAN_KANA_CONV *pconv, int depth)
{
	HRESULT ret = E_ABORT;	//一致なし

	if((pconv == NULL) ||
		(_countof(pconv->hacm) <= (depth + 1)) || (pconv->hacm[depth] == L'\0'))
	{
		return ret;
	}

	auto v_itr = std::lower_bound(tree.nodes.begin(), tree.nodes.end(),
		pconv->hacm[depth], [] (ROMAN_KANA_NODE m, WCHAR v) { return (m.ch < v); });

	if(v_itr != tree.nodes.end() && v_itr->ch == pconv->hacm[depth])
	{
		if(pconv->hacm[depth + 1] == L'\0')
		{
			*pconv = v_itr->conv;
			if(v_itr->nodes.empty())
			{
				ret = S_OK;	//一致 葉ノード
			}
			else
			{
				ret = E_PENDING;	//途中まで一致 内部ノード
			}
		}
		else
		{
			//子ノードを探索
			ret = _SearchRomanKanaNode(*v_itr, pconv, depth + 1);
		}
	}

	if(ret == E_ABORT)
	{
		ZeroMemory(pconv, sizeof(*pconv));
	}

	return ret;
}

HRESULT CTextService::_ConvAsciiJLatin(ASCII_JLATIN_CONV *pconv)
{
	HRESULT ret = E_ABORT;	//一致なし

	if(pconv == NULL)
	{
		return ret;
	}

	auto v_itr = std::lower_bound(ascii_jlatin_conv.begin(), ascii_jlatin_conv.end(),
		pconv->ascii[0], [] (ASCII_JLATIN_CONV m, WCHAR v) { return (m.ascii[0] < v); });

	if(v_itr != ascii_jlatin_conv.end() && v_itr->ascii[0] == pconv->ascii[0])
	{
		*pconv = *v_itr;
		ret = S_OK;	//一致
	}

	if(ret == E_ABORT)
	{
		ZeroMemory(pconv, sizeof(*pconv));
	}

	return ret;
}

void CTextService::_StartConv(TfEditCookie ec, ITfContext *pContext)
{
	CANDIDATES candidates_sel;
	CANDIDATES candidates_hint;
	std::wstring keyhint, key, hint;
	std::wstring candidate, str;
	size_t okuriidx_bak;

	_EndCompletionList(ec, pContext);

	size_t hintchidx = kana.find_first_of(CHAR_SKK_HINT);

	if(!hintmode || hintchidx == std::wstring::npos)
	{
		_StartSubConv(REQ_SEARCH);
	}
	else
	{
		keyhint = kana;

		key = keyhint.substr(0, hintchidx);
		if(okuriidx > key.size())
		{
			keyhint = keyhint.substr(0, okuriidx + 1);
			okuriidx = 0;
		}
		okuriidx_bak = okuriidx;
		okuriidx = 0;
		hint = keyhint.substr(hintchidx + 1);

		//ヒント検索
		kana = hint;
		_StartSubConv(REQ_SEARCH);
		candidates_hint = candidates;

		//通常検索
		okuriidx = okuriidx_bak;
		kana = key;
		cursoridx = kana.size();
		_StartSubConv(REQ_SEARCH);

		//ヒント候補の文字を含む通常候補をヒント候補順で抽出
		FORWARD_ITERATION_I(candidates_hint_itr, candidates_hint)
		{
			candidate = candidates_hint_itr->first.first;
			for(size_t i = 0; i < candidate.size(); i++)
			{
				str.clear();
				if((i + 1) != candidate.size() && IS_SURROGATE_PAIR(candidate[i], candidate[i + 1]))
				{
					str.push_back(candidate[i]);
					str.push_back(candidate[i + 1]);
					i++;
				}
				else
				{
					str.push_back(candidate[i]);
				}

				FORWARD_ITERATION(candidates_itr, candidates)
				{
					if(candidates_itr->first.first.find(str) != std::wstring::npos)
					{
						candidates_sel.push_back(*candidates_itr);
						candidates_itr = candidates.erase(candidates_itr);
					}
					else
					{
						++candidates_itr;
					}
				}
			}
		}
		candidates = candidates_sel;
	}

	hintmode = FALSE;
}

void CTextService::_StartSubConv(WCHAR command)
{
	CANDIDATES candidates_bak;
	CANDIDATES candidates_num;
	std::wstring kanaconv, okurikey;

	searchkey.clear();
	searchkeyorg.clear();

	//仮名を平仮名にして検索
	if(okuriidx != 0)
	{
		_ConvKanaToKana(kana.substr(0, okuriidx), inputmode, searchkey, im_hiragana);
		searchkey += kana.substr(okuriidx, 1);
	}
	else
	{
		_ConvKanaToKana(kana, inputmode, searchkey, im_hiragana);
	}

	candidates.clear();
	candidates.shrink_to_fit();
	candorgcnt = 0;

	searchkeyorg = searchkey;

	//通常検索
	_SearchDic(command);

	if(cx_srchallokuri && okuriidx != 0)
	{
		candidates_bak = candidates;
		candidates.clear();
		candidates.shrink_to_fit();

		searchkey.pop_back();

		//送りなしエントリ検索
		_SearchDic(command);

		searchkey = searchkeyorg;

		//重複候補を削除
		FORWARD_ITERATION_I(candidates_bak_itr, candidates_bak)
		{
			FORWARD_ITERATION(candidates_itr, candidates)
			{
				if(candidates_itr->first.first == candidates_bak_itr->first.first)
				{
					candidates_itr = candidates.erase(candidates_itr);
				}
				else
				{
					++candidates_itr;
				}
			}
		}

		if(!candidates_bak.empty())
		{
			candidates.insert(candidates.begin(), candidates_bak.begin(), candidates_bak.end());
		}
	}

	//片仮名変換
	if(cx_addcandktkn && !abbrevmode)
	{
		switch(inputmode)
		{
		case im_hiragana:
		case im_katakana:
			if(okuriidx != 0)
			{
				_ConvKanaToKana(kana.substr(0, okuriidx), inputmode, kanaconv, im_katakana);
			}
			else
			{
				_ConvKanaToKana(kana, inputmode, kanaconv, im_katakana);
			}

			if(!kanaconv.empty())
			{
				FORWARD_ITERATION_I(candidates_itr, candidates)
				{
					if(candidates_itr->first.first == kanaconv)
					{
						kanaconv.clear();
						break;
					}
				}

				if(!kanaconv.empty())
				{
					candidates.push_back(CANDIDATE(CANDIDATEBASE(kanaconv, L""), CANDIDATEBASE(kanaconv, L"")));
				}
			}
			break;
		default:
			break;
		}
	}

	candorgcnt = candidates.size();

	candidates_bak = candidates;
	candidates.clear();
	candidates.shrink_to_fit();

	searchkeyorg = searchkey;	//オリジナルバックアップ

	if(okuriidx != 0)
	{
		okurikey = kana.substr(okuriidx + 1);
		if(okurikey.size() >= 2 &&
			IS_SURROGATE_PAIR(okurikey.c_str()[0], okurikey.c_str()[1]))
		{
			okurikey = okurikey.substr(0, 2);
		}
		else
		{
			okurikey = okurikey.substr(0, 1);
		}
	}

	//見出し語変換
	_ConvertWord(REQ_CONVERTKEY, searchkeyorg, std::wstring(L""), okurikey, searchkey);

	if(!searchkey.empty() && searchkey != searchkeyorg)
	{
		//変換済み見出し語検索
		_SearchDic(command);
	}

	candidates_num = candidates;
	candidates.clear();
	candidates.shrink_to_fit();

	if(!candidates_bak.empty())
	{
		candidates.insert(candidates.end(), candidates_bak.begin(), candidates_bak.end());
	}
	if(!candidates_num.empty())
	{
		candidates.insert(candidates.end(), candidates_num.begin(), candidates_num.end());
	}

	candidx = 0;
}

void CTextService::_NextConv()
{
	if(!candidates.empty() && candidx < candidates.size())
	{
		//candidx == candidates.size() となる場合があるが、
		//_Update() で candidx = 0 される
		++candidx;
	}
	else
	{
		showentry = FALSE;
		candidx = 0;
	}
}

void CTextService::_PrevConv()
{
	if(candidx > 0)
	{
		--candidx;
	}
	else
	{
		showentry = FALSE;
		if(cx_delokuricncl && okuriidx != 0)
		{
			kana = kana.substr(0, okuriidx);
			okuriidx = 0;
			cursoridx = kana.size();
		}
		if(cx_delcvposcncl && okuriidx != 0)
		{
			kana.erase(okuriidx, 1);
			okuriidx = 0;
			cursoridx--;
		}
	}
}

void CTextService::_NextComp()
{
	if(!complement)
	{
		if(okuriidx != 0)
		{
			return;
		}

		cursoridx = kana.size();
		searchkey.clear();
		searchkeyorg.clear();

		if(abbrevmode)
		{
			searchkey = kana;
		}
		else
		{
			_ConvKanaToKana(kana, inputmode, searchkey, im_hiragana);
		}

		candidates.clear();
		candidates.shrink_to_fit();

		//補完
		_SearchDic(REQ_COMPLEMENT);

		if(!candidates.empty())
		{
			complement = TRUE;
			candidx = 0;
			_SetComp(candidates[candidx].first.first);
		}
	}
	else
	{
		if(candidx < candidates.size() - 1)
		{
			++candidx;
			_SetComp(candidates[candidx].first.first);
		}
	}
}

void CTextService::_PrevComp()
{
	if(complement)
	{
		if(candidx == 0)
		{
			complement = FALSE;
			_SetComp(searchkey);
		}
		else
		{
			--candidx;
			if(candidx < candidates.size())
			{
				_SetComp(candidates[candidx].first.first);
			}
		}
	}
}

void CTextService::_SetComp(const std::wstring &candidate)
{
	kana.clear();

	if(abbrevmode)
	{
		kana = candidate;
	}
	else
	{
		_ConvKanaToKana(candidate, im_hiragana, kana, inputmode);
	}

	if(cursoridx > kana.size())
	{
		cursoridx = kana.size();
	}
}

void CTextService::_DynamicComp(TfEditCookie ec, ITfContext *pContext, BOOL sel)
{
	if(kana.empty() || !roman.empty())
	{
		_EndCompletionList(ec, pContext);
		_Update(ec, pContext);
		return;
	}

	std::wstring kana_bak = kana;
	size_t cursoridx_bak = cursoridx;

#ifdef _DEBUG
	_CommandDic(REQ_DEBUGOUT_OFF);
#endif

	//補完
	complement = FALSE;
	_NextComp();

#ifdef _DEBUG
	_CommandDic(REQ_DEBUGOUT_ON);
#endif

	cursoridx = cursoridx_bak;

	if(complement)
	{
		if(cx_compuserdic)
		{
			//ユーザー辞書検索
			_UserDicComp(MAX_SELKEY_C);
			if(!candidates.empty())
			{
				kana += markSP + candidates[0].first.second;
			}
		}

		okuriidx = kana_bak.size();

		BOOL vertical = _GetVertical(ec, pContext);

		if(cx_dynamiccomp && (!cx_dyncompmulti || !vertical || pContext == NULL))
		{
			kana.insert(okuriidx, 1, CHAR_SKK_OKURI);

			_Update(ec, pContext);

			kana.erase(okuriidx);
			okuriidx = 0;
		}
		else
		{
			kana.erase(okuriidx);
			okuriidx = 0;

			_Update(ec, pContext);
		}

		if(pContext != NULL)
		{
			if(cx_dyncompmulti)
			{
				if(!sel)
				{
					candidx = (size_t)-1;
				}

				if(_pCandidateList != NULL && _pCandidateList->_IsShowCandidateWindow())
				{
					_pCandidateList->_UpdateComp();
				}
				else
				{
					showcandlist = FALSE;
					_ShowCandidateList(ec, pContext, FALSE, TRUE);
				}
			}
			else
			{
				_EndCompletionList(ec, pContext);
			}
		}

		complement = FALSE;
	}
	else
	{
		_EndCompletionList(ec, pContext);
		_Update(ec, pContext);
	}
}

void CTextService::_UserDicComp(size_t max)
{
	std::wstring kana_bak = kana;
	std::wstring searchkey_bak = searchkey;
	CANDIDATES candidates_bak = candidates;
	size_t candidx_bak = candidx;
	size_t count = 0;

#ifdef _DEBUG
	_CommandDic(REQ_DEBUGOUT_OFF);
#endif

	FORWARD_ITERATION_I(candidates_bak_itr, candidates_bak)
	{
		if(max < ++count)
		{
			break;
		}

		//ユーザー辞書検索
		kana = candidates_bak_itr->first.first;
		_StartSubConv(REQ_SEARCHUSER);

		if(!candidates.empty() && cx_untilcandlist > 1)
		{
			candidates_bak_itr->first.second = L"/";
			size_t i = 1;
			FORWARD_ITERATION_I(candidates_itr, candidates)
			{
				//「候補一覧表示に要する変換回数」-1 個まで
				if(cx_untilcandlist < ++i)
				{
					break;
				}
				candidates_bak_itr->first.second += candidates_itr->first.first + L"/";
			}

			if(cx_untilcandlist - 1 < candidates.size())
			{
				candidates_bak_itr->first.second += L"…";
			}
		}
	}

#ifdef _DEBUG
	_CommandDic(REQ_DEBUGOUT_ON);
#endif

	kana = kana_bak;
	searchkey = searchkey_bak;
	candidates = candidates_bak;
	candidx = candidx_bak;
}

void CTextService::_ConvRoman()
{
	if(!_ConvShift(WCHAR_MAX))
	{
		roman.clear();
	}

	if(okuriidx != 0 && okuriidx + 1 == cursoridx)
	{
		kana.erase(cursoridx - 1, 1);
		cursoridx--;
		okuriidx = 0;
	}
}

BOOL CTextService::_ConvShift(WCHAR ch)
{
	ROMAN_KANA_CONV rkc;
	HRESULT ret;

	if(roman.empty())
	{
		return TRUE;
	}

	wcsncpy_s(rkc.hacm, roman.c_str(), _TRUNCATE);
	ret = _ConvRomanKana(&rkc);
	switch(ret)
	{
	case S_OK:	//一致
	case E_PENDING:	//途中まで一致
		if(rkc.hacm[0] != L'\0' && rkc.wait)	//待機
		{
			if(okuriidx != 0 && okuriidx + 1 == cursoridx)
			{
				WCHAR chN = L'\0';
				switch(inputmode)
				{
				case im_hiragana:
					chN = rkc.yula[0];
					break;
				case im_katakana:
					chN = rkc.yula[0];
					break;
				case im_katakana_ank:
					chN = rkc.yula[0];
					break;
				default:
					break;
				}

				WCHAR chO = L'\0';

				auto va_itr = std::lower_bound(conv_point_a.begin(), conv_point_a.end(),
					chN, [] (CONV_POINT m, WCHAR v) { return (m.ch[1] < v); });

				if(va_itr != conv_point_a.end() && chN == va_itr->ch[1])
				{
					chO = va_itr->ch[2];
				}

				if(chO == L'\0')
				{
					okuriidx = 0;
				}
				else
				{
					kana.replace(okuriidx, 1, 1, chO);	//送りローマ字
				}
			}

			std::wstring kana_ins;
			switch(inputmode)
			{
			case im_hiragana:
				kana_ins = rkc.yula;
				break;
			case im_katakana:
				kana_ins = rkc.yula;
				break;
			case im_katakana_ank:
				kana_ins = rkc.yula;
				break;
			default:
				break;
			}

			if(!kana_ins.empty())
			{
				kana.insert(cursoridx, kana_ins);
				if(okuriidx != 0 && cursoridx <= okuriidx)
				{
					okuriidx += kana_ins.size();
				}
				cursoridx += kana_ins.size();
			}

			roman.clear();
			return TRUE;
		}
		break;
	default:
		break;
	}

	// SKK_CONV_POINTのみ
	if(ch != L'\0' && ch != WCHAR_MAX)
	{
		std::wstring roman_conv = roman;
		roman_conv.push_back(ch);
		wcsncpy_s(rkc.hacm, roman_conv.c_str(), _TRUNCATE);
		ret = _ConvRomanKana(&rkc);
		switch(ret)
		{
		case S_OK:		//一致
		case E_PENDING:	//途中まで一致
			if(rkc.hacm[0] != L'\0' && rkc.soku)
			{
				std::wstring kana_ins;
				switch(inputmode)
				{
				case im_hiragana:
					kana_ins = rkc.yula;
					break;
				case im_katakana:
					kana_ins = rkc.yula;
					break;
				case im_katakana_ank:
					kana_ins = rkc.yula;
					break;
				default:
					break;
				}

				if(!kana_ins.empty())
				{
					kana.insert(cursoridx, kana_ins);
					if(okuriidx != 0 && cursoridx <= okuriidx)
					{
						okuriidx += kana_ins.size();
					}
					cursoridx += kana_ins.size();
				}

				roman.clear();
				return TRUE;	//「nk, ss」etc.
			}
			else
			{
				if(cx_shiftnnokuri || (!cx_shiftnnokuri && (!inputkey || (inputkey && okuriidx == 0))))
				{
					_ConvN();
				}
				return TRUE;	//「ka, na, nn」etc.「ky, ny」etc.
			}
			break;
		default:
			break;
		}
	}

	if(_ConvN())
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CTextService::_ConvN()
{
	ROMAN_KANA_CONV rkc;
	HRESULT ret;

	wcsncpy_s(rkc.hacm, roman.c_str(), _TRUNCATE);
	ret = _ConvRomanKana(&rkc);
	switch(ret)
	{
	case S_OK:	//一致
	case E_PENDING:	//途中まで一致
		if(rkc.hacm[0] != L'\0')
		{
			std::wstring kana_ins;
			switch(inputmode)
			{
			case im_hiragana:
				kana_ins = rkc.yula;
				break;
			case im_katakana:
				kana_ins = rkc.yula;
				break;
			case im_katakana_ank:
				kana_ins = rkc.yula;
				break;
			default:
				break;
			}

			if(!kana_ins.empty())
			{
				kana.insert(cursoridx, kana_ins);
				if(okuriidx != 0 && cursoridx <= okuriidx)
				{
					okuriidx += kana_ins.size();
				}
				cursoridx += kana_ins.size();
			}

			if(rkc.soku)
			{
				roman = roman.back();
			}
			else
			{
				roman.clear();
			}

			return TRUE;
		}
		break;
	}

	return FALSE;
}

void CTextService::_ConvKanaToKana(const std::wstring &src, int srcmode, std::wstring &dst, int dstmode)
{
	dst.assign(src);
}
