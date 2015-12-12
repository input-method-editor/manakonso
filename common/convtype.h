﻿
#ifndef CONVTYPE_H
#define CONVTYPE_H

#define ROMAN_NUM	8
#define KANA_NUM	8
#define JLATIN_NUM	2

//ローマ字仮名変換
typedef struct {
	WCHAR hacm[ROMAN_NUM];
	WCHAR yula[KANA_NUM];
	BOOL  soku;
	BOOL  wait;
} ROMAN_KANA_CONV;

//ASCII全英変換
typedef struct {
	WCHAR ascii[JLATIN_NUM];
	WCHAR jlatin[JLATIN_NUM];
} ASCII_JLATIN_CONV;

#define ROMAN_KANA_TBL_MAX		32768
#define ASCII_JLATIN_TBL_NUM	128

#endif //CONVTYPE_H
