﻿
#include "common.h"
#include "configxml.h"

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "xmllite.lib")

//tag

LPCWSTR TagRoot = L"skk";
LPCWSTR TagSection = L"section";
LPCWSTR TagEntry = L"entry";
LPCWSTR TagKey = L"key";
LPCWSTR TagList = L"list";
LPCWSTR TagRow = L"row";

//attribute

LPCWSTR AttributeName = L"name";
LPCWSTR AttributeValue = L"value";
LPCWSTR AttributeCandidate = L"c";
LPCWSTR AttributeAnnotation = L"a";
LPCWSTR AttributeKey = L"key";
LPCWSTR AttributePath = L"path";
LPCWSTR AttributeEnabled = L"enabled";
LPCWSTR AttributeVKey = L"vkey";
LPCWSTR AttributeMKey = L"mkey";
LPCWSTR AttributeCPStart = L"st";
LPCWSTR AttributeCPAlter = L"al";
LPCWSTR AttributeCPOkuri = L"ok";
LPCWSTR AttributeRoman = L"ro";
LPCWSTR AttributeHiragana = L"hi";
LPCWSTR AttributeSpOp = L"so";
LPCWSTR AttributeLatin = L"la";
LPCWSTR AttributeJLatin = L"jl";

//dictionary section

LPCWSTR SectionDictionary = L"dictionary";

//behavior section

LPCWSTR SectionBehavior = L"behavior";

//behavior keys

LPCWSTR ValueDefaultMode = L"defaultmode";
LPCWSTR ValueDefModeAscii = L"defmodeascii";
LPCWSTR ValueBeginCvOkuri = L"begincvokuri";
LPCWSTR ValuePrecedeOkuri = L"precedeokuri";
LPCWSTR ValueShiftNNOkuri = L"shiftnnokuri";
LPCWSTR ValueSrchAllOkuri = L"srchallokuri";
LPCWSTR ValueDelCvPosCncl = L"delcvposcncl";
LPCWSTR ValueDelOkuriCncl = L"delokuricncl";
LPCWSTR ValueBackIncEnter = L"backincenter";

LPCWSTR ValueCompMultiNum = L"compmultinum";
LPCWSTR ValueStaCompMulti = L"stacompmulti";
LPCWSTR ValueDynamicComp = L"dynamiccomp";
LPCWSTR ValueDynCompMulti = L"dyncompmulti";
LPCWSTR ValueCompUserDic = L"compuserdic";

//font section

LPCWSTR SectionFont = L"font";

//font keys

LPCWSTR ValueFontName = L"name";
LPCWSTR ValueFontSize = L"size";
LPCWSTR ValueFontWeight = L"weight";
LPCWSTR ValueFontItalic = L"italic";

//display section

LPCWSTR SectionDisplay = L"display";

//display keys

LPCWSTR ValueMaxWidth = L"maxwidth";
LPCWSTR ValueColorBG = L"colorbg";
LPCWSTR ValueColorFR = L"colorfr";
LPCWSTR ValueColorSE = L"colorse";
LPCWSTR ValueColorCO = L"colorco";
LPCWSTR ValueColorCA = L"colorca";
LPCWSTR ValueColorSC = L"colorsc";
LPCWSTR ValueColorAN = L"coloran";
LPCWSTR ValueColorNO = L"colorno";
LPCWSTR ValueDrawAPI = L"drawapi";
LPCWSTR ValueColorFont = L"colorfont";
LPCWSTR ValueUntilCandList = L"untilcandlist";
LPCWSTR ValueDispCandNo = L"dispcandno";
LPCWSTR ValueVerticalCand = L"verticalcand";
LPCWSTR ValueAnnotation = L"annotation";
LPCWSTR ValueAnnotatLst = L"annotatlst";
LPCWSTR ValueShowModeInl = L"showmodeinl";
LPCWSTR ValueShowModeImm = L"showmodeimm";
LPCWSTR ValueShowModeMark = L"showmodemark";
LPCWSTR ValueShowRoman = L"showroman";

//displayattr section

LPCWSTR SectionDisplayAttr = L"displayattr";

//displayattr keys

LPCWSTR ValueDisplayAttrInputMark = L"inputmark";
LPCWSTR ValueDisplayAttrInputText = L"inputtext";
LPCWSTR ValueDisplayAttrInputOkuri = L"inputokuri";
LPCWSTR ValueDisplayAttrConvMark = L"convmark";
LPCWSTR ValueDisplayAttrConvText = L"convtext";
LPCWSTR ValueDisplayAttrConvOkuri = L"convokuri";
LPCWSTR ValueDisplayAttrConvAnnot = L"convannot";

//selkey section

LPCWSTR SectionSelKey = L"selkey";

//preservedkey section

LPCWSTR SectionPreservedKey = L"preservedkey";	//for compatibility
LPCWSTR SectionPreservedKeyON = L"preservedkeyon";
LPCWSTR SectionPreservedKeyOFF = L"preservedkeyoff";

//keymap section

LPCWSTR SectionKeyMap = L"keymap";

//vkeymap section

LPCWSTR SectionVKeyMap = L"vkeymap";

//keymap and vkeymap keys

LPCWSTR ValueKeyMapAffix = L"affix";
LPCWSTR ValueKeyMapNextCand = L"nextcand";
LPCWSTR ValueKeyMapPrevCand = L"prevcand";
LPCWSTR ValueKeyMapPurgeDic = L"purgedic";
LPCWSTR ValueKeyMapNextComp = L"nextcomp";
LPCWSTR ValueKeyMapPrevComp = L"prevcomp";
LPCWSTR ValueKeyMapHint = L"hint";
LPCWSTR ValueKeyMapConvPoint = L"convpoint";
LPCWSTR ValueKeyMapDirect = L"direct";
LPCWSTR ValueKeyMapEnter = L"enter";
LPCWSTR ValueKeyMapCancel = L"cancel";
LPCWSTR ValueKeyMapBack = L"back";
LPCWSTR ValueKeyMapDelete = L"delete";
LPCWSTR ValueKeyMapVoid = L"void";
LPCWSTR ValueKeyMapLeft = L"left";
LPCWSTR ValueKeyMapUp = L"up";
LPCWSTR ValueKeyMapRight = L"right";
LPCWSTR ValueKeyMapDown = L"down";
LPCWSTR ValueKeyMapPaste = L"paste";

//convpoint section

LPCWSTR SectionConvPoint = L"convpoint";

//kana section

LPCWSTR SectionKana = L"kana";

HRESULT CreateStreamReader(LPCWSTR path, IXmlReader **ppReader, IStream **ppFileStream)
{
	HRESULT hr = S_FALSE;

	if(ppReader != nullptr && ppFileStream != nullptr)
	{
		hr = CreateXmlReader(IID_PPV_ARGS(ppReader), nullptr);
		EXIT_NOT_S_OK(hr);

		hr = SHCreateStreamOnFileW(path, STGM_READ, ppFileStream);
		EXIT_NOT_S_OK(hr);

		hr = (*ppReader)->SetInput(*ppFileStream);
		EXIT_NOT_S_OK(hr);
	}

NOT_S_OK:
	return hr;
}

void CloseStreamReader(IXmlReader *pReader, IStream *pFileStream)
{
	SafeRelease(&pReader);
	SafeRelease(&pFileStream);
}

HRESULT ReadList(LPCWSTR path, LPCWSTR section, APPDATAXMLLIST &list)
{
	HRESULT hr;
	IXmlReader *pReader = nullptr;
	IStream *pFileStream = nullptr;
	XmlNodeType nodeType;
	LPCWSTR pwszLocalName;
	LPCWSTR pwszAttributeName;
	LPCWSTR pwszAttributeValue;
	int sequence = 0;

	APPDATAXMLATTR attr;
	APPDATAXMLROW row;

	hr = CreateStreamReader(path, &pReader, &pFileStream);
	EXIT_NOT_S_OK(hr);

	while(pReader->Read(&nodeType) == S_OK)
	{
		switch(nodeType)
		{
		case XmlNodeType_Element:
			hr = pReader->GetLocalName(&pwszLocalName, nullptr);
			EXIT_NOT_S_OK(hr);

			switch(sequence)
			{
			case 0:
				if(wcscmp(TagRoot, pwszLocalName) == 0)
				{
					sequence = 1;
				}
				break;
			case 1:
				if(wcscmp(TagSection, pwszLocalName) == 0)
				{
					sequence = 2;
				}
				break;
			case 3:
				if(wcscmp(TagList, pwszLocalName) == 0)
				{
					sequence = 4;
				}
				break;
			case 4:
				if(wcscmp(TagRow, pwszLocalName) == 0)
				{
					sequence = 5;
					row.clear();
				}
				break;
			default:
				break;
			}

			for(hr = pReader->MoveToFirstAttribute(); hr == S_OK; hr = pReader->MoveToNextAttribute())
			{
				hr = pReader->GetLocalName(&pwszAttributeName, nullptr);
				EXIT_NOT_S_OK(hr);
				hr = pReader->GetValue(&pwszAttributeValue, nullptr);
				EXIT_NOT_S_OK(hr);

				switch(sequence)
				{
				case 2:
					if(wcscmp(TagSection, pwszLocalName) == 0 &&
						wcscmp(AttributeName, pwszAttributeName) == 0 && wcscmp(section, pwszAttributeValue) == 0)
					{
						sequence = 3;
					}
					break;
				case 5:
					if(wcscmp(TagRow, pwszLocalName) == 0)
					{
						attr.first = pwszAttributeName;
						attr.second = pwszAttributeValue;
						row.push_back(attr);
					}
					break;
				default:
					break;
				}
			}

			switch(sequence)
			{
			case 2:
				sequence = 1;
				break;
			case 5:
				list.push_back(row);
				row.clear();
				break;
			default:
				break;
			}
			break;

		case XmlNodeType_EndElement:
			hr = pReader->GetLocalName(&pwszLocalName, nullptr);
			EXIT_NOT_S_OK(hr);

			switch(sequence)
			{
			case 1:
				if(wcscmp(TagRoot, pwszLocalName) == 0)
				{
					goto exit;
				}
				break;
			case 2:
				if(wcscmp(TagSection, pwszLocalName) == 0)
				{
					sequence = 1;
				}
				break;
			case 3:
				if(wcscmp(TagSection, pwszLocalName) == 0)
				{
					goto exit;
				}
				break;
			case 4:
				if(wcscmp(TagSection, pwszLocalName) == 0 || wcscmp(TagList, pwszLocalName) == 0)
				{
					goto exit;
				}
				break;
			case 5:
				if(wcscmp(TagList, pwszLocalName) == 0)
				{
					goto exit;
				}
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

NOT_S_OK:
exit:
	CloseStreamReader(pReader, pFileStream);
	return hr;
}

HRESULT ReadValue(LPCWSTR path, LPCWSTR section, LPCWSTR key, std::wstring &strxmlval, LPCWSTR defval)
{
	IXmlReader *pReader = nullptr;
	IStream *pFileStream = nullptr;
	HRESULT hr;
	XmlNodeType nodeType;
	LPCWSTR pwszLocalName;
	LPCWSTR pwszAttributeName;
	LPCWSTR pwszAttributeValue;
	int sequence = 0;

	strxmlval = defval;

	hr = CreateStreamReader(path, &pReader, &pFileStream);
	EXIT_NOT_S_OK(hr);

	while(pReader->Read(&nodeType) == S_OK)
	{
		switch(nodeType)
		{
		case XmlNodeType_Element:
			hr = pReader->GetLocalName(&pwszLocalName, nullptr);
			EXIT_NOT_S_OK(hr);

			switch(sequence)
			{
			case 0:
				if(wcscmp(TagRoot, pwszLocalName) == 0)
				{
					sequence = 1;
				}
				break;
			case 1:
				if(wcscmp(TagSection, pwszLocalName) == 0)
				{
					sequence = 2;
				}
				break;
			case 3:
				if(wcscmp(TagKey, pwszLocalName) == 0)
				{
					sequence = 4;
				}
				break;
			default:
				break;
			}

			for(hr = pReader->MoveToFirstAttribute(); hr == S_OK; hr = pReader->MoveToNextAttribute())
			{
				hr = pReader->GetLocalName(&pwszAttributeName, nullptr);
				EXIT_NOT_S_OK(hr);
				hr = pReader->GetValue(&pwszAttributeValue, nullptr);
				EXIT_NOT_S_OK(hr);

				switch(sequence)
				{
				case 2:
					if(wcscmp(AttributeName, pwszAttributeName) == 0 && wcscmp(section, pwszAttributeValue) == 0)
					{
						sequence = 3;
					}
					break;
				case 4:
					if(wcscmp(AttributeName, pwszAttributeName) == 0 && wcscmp(key, pwszAttributeValue) == 0)
					{
						sequence = 5;
					}
					break;
				case 5:
					if(wcscmp(AttributeValue, pwszAttributeName) == 0)
					{
						strxmlval.assign(pwszAttributeValue);
						goto exit;
					}
					break;
				default:
					break;
				}
			}
			break;

		case XmlNodeType_EndElement:
			hr = pReader->GetLocalName(&pwszLocalName, nullptr);
			EXIT_NOT_S_OK(hr);

			switch(sequence)
			{
			case 1:
				if(wcscmp(TagRoot, pwszLocalName) == 0)
				{
					goto exit;
				}
				break;
			case 2:
				if(wcscmp(TagSection, pwszLocalName) == 0)
				{
					sequence = 1;
				}
				break;
			case 3:
			case 4:
			case 5:
				if(wcscmp(TagSection, pwszLocalName) == 0)
				{
					goto exit;
				}
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

NOT_S_OK:
exit:
	CloseStreamReader(pReader, pFileStream);
	return hr;
}

HRESULT CreateStreamWriter(LPCWSTR path, IXmlWriter **ppWriter, IStream **ppFileStream)
{
	HRESULT hr = S_FALSE;

	if(ppWriter != nullptr && ppFileStream != nullptr)
	{
		hr = CreateXmlWriter(IID_PPV_ARGS(ppWriter), nullptr);
		EXIT_NOT_S_OK(hr);

		hr = SHCreateStreamOnFileW(path, STGM_WRITE | STGM_CREATE, ppFileStream);
		EXIT_NOT_S_OK(hr);

		hr = (*ppWriter)->SetOutput(*ppFileStream);
	}

NOT_S_OK:
	return hr;
}

void CloseStreamWriter(IXmlWriter *pWriter, IStream *pFileStream)
{
	SafeRelease(&pWriter);
	SafeRelease(&pFileStream);
}

HRESULT WriterInit(LPCWSTR path, IXmlWriter **ppWriter, IStream **pFileStream, BOOL indent)
{
	HRESULT hr = S_FALSE;

	if(ppWriter != nullptr && pFileStream != nullptr)
	{
		hr = CreateStreamWriter(path, ppWriter, pFileStream);
		EXIT_NOT_S_OK(hr);

		hr = (*ppWriter)->SetProperty(XmlWriterProperty_Indent, indent);
		EXIT_NOT_S_OK(hr);

		hr = (*ppWriter)->WriteStartDocument(XmlStandalone_Omit);
		EXIT_NOT_S_OK(hr);
	}

NOT_S_OK:
	return hr;
}

HRESULT WriterFinal(IXmlWriter **ppWriter, IStream **ppFileStream)
{
	HRESULT hr = S_FALSE;

	if(ppWriter != nullptr && *ppWriter != nullptr)
	{
		hr = (*ppWriter)->WriteEndDocument();
		EXIT_NOT_S_OK(hr);

		hr = (*ppWriter)->Flush();
	}

NOT_S_OK:
	if(ppWriter != nullptr && ppFileStream != nullptr)
	{
		CloseStreamWriter(*ppWriter, *ppFileStream);
	}
	return hr;
}

HRESULT WriterNewLine(IXmlWriter *pWriter)
{
	HRESULT hr = S_FALSE;

	if(pWriter != nullptr)
	{
		hr = pWriter->WriteRaw(L"\r\n");
	}

	return hr;
}

HRESULT WriterStartElement(IXmlWriter *pWriter, LPCWSTR element)
{
	HRESULT hr = S_FALSE;

	if(pWriter != nullptr)
	{
		hr = pWriter->WriteStartElement(nullptr, element, nullptr);
	}

	return hr;
}

HRESULT WriterEndElement(IXmlWriter *pWriter)
{
	HRESULT hr = S_FALSE;

	if(pWriter != nullptr)
	{
		hr = pWriter->WriteEndElement();
	}

	return hr;
}

HRESULT WriterAttribute(IXmlWriter *pWriter, LPCWSTR name, LPCWSTR value)
{
	HRESULT hr = S_FALSE;

	if(pWriter != nullptr)
	{
		hr = pWriter->WriteAttributeString(nullptr, name, nullptr, value);
	}

	return hr;
}

HRESULT WriterStartSection(IXmlWriter *pWriter, LPCWSTR name)
{
	HRESULT hr;

	hr = WriterStartElement(pWriter, TagSection);
	EXIT_NOT_S_OK(hr);

	hr = WriterAttribute(pWriter, AttributeName, name);

NOT_S_OK:
	return hr;
}

HRESULT WriterEndSection(IXmlWriter *pWriter)
{
	return WriterEndElement(pWriter);
}

HRESULT WriterKey(IXmlWriter *pWriter, LPCWSTR key, LPCWSTR value)
{
	HRESULT hr = S_FALSE;

	if(pWriter != nullptr)
	{
		hr = WriterStartElement(pWriter, TagKey);
		EXIT_NOT_S_OK(hr);

		hr = WriterAttribute(pWriter, AttributeName, key);
		EXIT_NOT_S_OK(hr);

		hr = WriterAttribute(pWriter, AttributeValue, value);
		EXIT_NOT_S_OK(hr);

		hr = WriterEndElement(pWriter);	//key
	}

NOT_S_OK:
	return hr;
}

HRESULT WriterRow(IXmlWriter *pWriter, const APPDATAXMLROW &row)
{
	HRESULT hr = S_FALSE;

	FORWARD_ITERATION_I(r_itr, row)
	{
		hr = WriterAttribute(pWriter, r_itr->first.c_str(), r_itr->second.c_str());
		EXIT_NOT_S_OK(hr);
	}

NOT_S_OK:
	return hr;
}

HRESULT WriterList(IXmlWriter *pWriter, const APPDATAXMLLIST &list, BOOL newline)
{
	HRESULT hr;

	hr = WriterStartElement(pWriter, TagList);
	EXIT_NOT_S_OK(hr);

	if(newline)
	{
		hr = WriterNewLine(pWriter);
		EXIT_NOT_S_OK(hr);
	}

	FORWARD_ITERATION_I(l_itr, list)
	{
		hr = WriterStartElement(pWriter, TagRow);
		EXIT_NOT_S_OK(hr);

		hr = WriterRow(pWriter, *l_itr);
		EXIT_NOT_S_OK(hr);

		hr = WriterEndElement(pWriter);	//row
		EXIT_NOT_S_OK(hr);

		if(newline)
		{
			hr = WriterNewLine(pWriter);
			EXIT_NOT_S_OK(hr);
		}
	}

	hr = WriterEndElement(pWriter);	//list
	EXIT_NOT_S_OK(hr);

NOT_S_OK:
	return hr;
}
