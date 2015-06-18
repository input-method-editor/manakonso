
# CorvusSKK ver. 1.8.9

Windowsで動作するSKK風のIMEです。


## ライセンス

Microsoft Public License (MS-PL)

詳細は LICENSE.TXT を見てください。


## インストール

### 対応OS

* Windows Vista (32-bit / 64-bit) SP2
* Windows 7     (32-bit / 64-bit)
* Windows 8     (32-bit / 64-bit)
* Windows 8.1   (32-bit / 64-bit)


### DirectX 9 以上をサポートしたGPU (推奨)

表示オプションでDirect2Dを使用するには、DirectX 9 以上をサポートしたGPUが必要です。

サポートしていない場合は自動的にGDIで描画されます。(多分)


### Vista 用更新プログラムのインストール

Windows Vista SP2 では、以下のプラットフォーム更新プログラムのいずれかを予めインストールして下さい。

Windows 7 以降ではインストールは不要です。

* KB971644 (Windows Update から)
* KB971512

    (x64) http://www.microsoft.com/ja-JP/download/details.aspx?id=4390

    (x86) http://www.microsoft.com/ja-JP/download/details.aspx?id=3274


### CorvusSKK のインストール

corvusskk-X.Y.Z.zip を展開し、32bit版 Windows では corvusskk-X.Y.Z-x86.msi、64bit版 Windows では corvusskk-X.Y.Z-x64.msi を実行して下さい。 (X, Y, Z はバージョン番号)

アップデートの後はOSを再起動しておくと安全です。


### 初期設定

任意のユーザーアカウントで初めて使用するときは、設定ダイアログでOKボタンを押して初期設定を保存して下さい。

設定ダイアログで保存した後は、IME OFF → ON で新しい設定が反映されます。

バージョンアップで設定項目が追加されているとき、機能の種類によっては設定ダイアログで一度は保存する必要があるので、バージョンアップしたら動かない機能がある！というときは設定ダイアログでOKボタンを押してみて下さい。


### Windows Store アプリ

Windows Store アプリで使用するには、設定ファイル (config.xml) に Windows Store アプリへのアクセス許可を付加させる必要があります。

Windows 8 以降で動作する設定ダイアログでOKボタンを押して保存を行うとアクセス許可の付加が自動的に行われます。


### Adobe Reader X, XI, Acrobat Reader DC

Adobe Reader X 以降で使用するには、設定ファイル (config.xml) に Adobe Reader へのアクセス許可を付加させる必要があります。

設定ダイアログでOKボタンを押して保存を行うとアクセス許可の付加が自動的に行われます。



## 設定

### 設定ダイアログ

設定ダイアログは、以下のいずれかの操作で開くことができます。

* 言語バーを右クリックし、メニューから「設定」を選択する。「テキストサービスと入力言語」ダイアログの「インストールされているサービス」からCorvusSKKを選択し、プロパティボタンを押す。
* 言語バーの入力モードアイコンを左クリックし、メニューから「設定」を選択する。
* 言語バーのヘルプボタンを左クリックし、メニューから「設定」を選択する。
* Windows 8 以降の通知領域の入力モードアイコンを右クリックし、メニューから「設定」を選択する。

設定ダイアログで保存した後は、IME OFF → ON で新しい設定が反映されます。

IME ON/OFF のキーのみ、IME ON → OFF のときにも反映されます。


### 設定ファイル、SKK辞書

各種設定及び取込済SKK辞書は、ディレクトリ %AppData%\CorvusSKK の各ファイルに保存されます。

| ファイル名 | 説明 |
|---|---|
| config.xml  | 各種設定 |
| skkdict.dic | 取込済SKK辞書 |
| skkdict.idx | 取込済SKK辞書インデックス |

各種設定の config.xml ファイルは、UTF-8 の XML フォーマットのテキストファイルとなっており、テキストエディタで編集可能です。変更した後は、IME OFF → ON で新しい設定が反映されます。


### ユーザー辞書

ユーザー辞書は、ディレクトリ %AppData%\CorvusSKK のファイルに保存されます。

| ファイル名 | 説明 |
|---|---|
| userdict.txt | ユーザー辞書 |

UTF-16 (LE, BOMあり) のSKK辞書フォーマットとなっています。

ユーザー辞書を編集する際は、ログオンユーザー権限で動作しているサーバープロセス (imcrvmgr.exe) をタスクマネージャなどで終了させた状態で行なって下さい。

編集後、以下のいずれかの操作を行うとサーバープロセスが自動的に起動します。

* IME OFF → ON
* 仮名漢字変換開始
* 補完開始

ユーザー辞書は、サーバープロセスの起動時にメモリ上に読み込まれ、追加、変更、削除があったとき、かつ、以下のいずれかのときに上書きされます。

* IME ON 状態から OFF 状態にするとき
* IME ON 状態のアプリケーションが終了するとき
* アプリケーションがフォーカスを失うとき
* サーバープロセス (imcrvmgr.exe) が終了するとき


### SKK辞書

SKK辞書の詳細はこちらを参照下さい。 http://openlab.jp/skk/wiki/wiki.cgi?page=FrontPage

こちらから辞書をダウンロード出来ます。 http://openlab.ring.gr.jp/skk/skk/dic/

SKK辞書ファイルの文字コードは、EUC-JIS-2004、UTF-8 (BOMなし/あり)、UTF-16 (LE, BOMあり) に対応しています。

設定ダイアログのリストにSKK辞書を追加し、取込ボタンを押して下さい。取込済SKK辞書に変換されて使用可能となります。

チェックボックスを外すと取込の対象外となります。

リストの選択されている行をクリックするとインライン編集することができます。

SKK辞書のURLを追加した場合は、取込処理のときにディレクトリ %TMP%\CorvusSKK または %TEMP%\CorvusSKK にダウンロードされてから取り込まれます。

SKK辞書のダウンロード機能では FTP, HTTP, HTTPS が使用可能です。プロキシはOSに設定されたものが使用されます。


### SKK辞書サーバー

別途用意されたSKK辞書サーバーと通信して、skkservプロトコルのクライアントとして辞書検索を行います。

同時に１つのみ使用可能です。IPv4、IPv6 に対応しています。

通信に使用する文字コードは、EUC-JIS-2004、UTF-8 に対応していますが、通常のSKK辞書サーバーではデフォルトの EUC-JIS-2004 を使用して下さい。

サーバーコンプリーション機能は未実装です。


### 動作

| 機能 | 備考 |
|---|---|
| 初期入力モード                       | プログラム起動時の入力モードを指定します。 |
| 送り仮名が決定したとき変換を開始する | 送り仮名を入力したとき自動的に変換を開始します。接頭辞も同様です。 |
| 送り仮名が一致した候補を優先する     | 送り仮名ブロックの送り仮名が一致する候補を優先して出力します。 |
| 送り仮名で撥音を送り出す             | 送り仮名入力開始後の変換位置指定を含む「な/にゃ」行の入力で「ん」を送り出します。<br>例) ON:「NoNO」→「▽の\*んお」/ OFF:「NoNO」→「▽の\*の」 |
| 取消のとき変換位置を削除する         | ▼モードから▽モードに遷移する際、送り仮名の位置情報を削除します。 |
| 取消のとき送り仮名を削除する         | ▼モードから▽モードに遷移する際、送り仮名の部分を削除します。 |
| 後退に確定を含める                   | ▼モードのとき後退すると一文字削除した上で確定します。<br>OFFでは▼モードのとき後退は前候補と同じ機能を有します。 |
| 候補に片仮名変換を追加する           | 見出し語を片仮名に変換した候補を追加します。 |
| 複数補完を使用する                   | 通常の補完のとき補完された見出し語を7個ずつ表示します。<br>補完対象は「候補一覧の色」の「選択」、補完部分は「候補」の色が使用されます。 |
| 動的補完を使用する                   | 見出し語が入力されたとき補完された見出し語を表示します。<br>「▽表示属性」の「\*送り」の色が使用されます。 |
| 複数動的補完を使用する               | 見出し語が入力されたとき補完された見出し語を7個ずつ表示します。<br>補完対象は「候補一覧の色」の「選択」、補完部分は「候補」の色が使用されます。 |
| 補完のときユーザー辞書を検索する     | 補完/複数補完/動的補完/複数動的補完のときユーザー辞書の検索結果を追加して表示します。<br>表示する候補の数は最大で「候補一覧表示に要する変換回数」-1 です。<br>補完/動的補完では「▽表示属性」の「\*送り」の色が使用されます。<br>複数補完/複数動的補完では「候補一覧の色」の「注釈」の色が使用されます。 |


###表示

| 機能 | 備考 |
|---|---|
| 候補一覧のフォント                        | 候補一覧に表示するフォントの種類、スタイル、サイズを指定します。 |
| 候補一覧の最大幅                          | 候補一覧の最大幅のサイズを指定します。 |
| 候補一覧の色                              | 候補一覧の色を指定します。 |
| 候補一覧の描画API                         | 候補一覧の描画を行うAPIを指定します。<br>Direct2Dと彩色の指定でカラーフォントをその色で表示します。(Windows8.1以降) |
| 候補一覧表示に要する変換回数(0は表示無し) | 指定した回数変換すると候補一覧が表示されます。 |
| 候補一覧が表示無しのとき候補数を表示する  | (<現在の候補の番号>/<候補数>) の形式を追加して表示します。 |
| 候補一覧を縦に表示する                    | 候補一覧で候補を縦に並べて表示します。 |
| 注釈を表示する                            | <候補><セミコロン><注釈> の形式で注釈を表示します。 |
| 入力モードを表示する                      | キャレットまたは辞書登録ウィンドウ付近に入力モードを表示します。<br>タイミングは、IME ON、入力モード変更、「\*無効\*」キー押下のときです。 |
| ▽▼\*マークを表示する                    | 大切なものは目に見えないようです。 |
| ローマ字を表示する                        | 仮名文字のローマ字プレフィックスを表示します。 |


### 表示属性

入力中文字列の表示属性を設定します。

「連続」のチェックボックスをチェックすると、表の左側の表示属性を継承し、下線は繋って表示されます。

確定入力モードでのローマ字は連続のチェックの有無に関わらず見出し語と同じ表示属性となります。

辞書削除の確認メッセージは注釈と同じ表示属性となります。


### 候補一覧選択キー

候補一覧での確定は、デフォルトで 1〜7 と ASDFJKL と asdfjkl を使用します。

コマンドプロンプト等では、デフォルトで 1〜9 と ASDFJKLGH と asdfjklgh を使用します。

候補一覧が表示されているとき、Kanaキーロックは無視されます。

| 機能 | 説明 |
|---|---|
| 数字 | 選択キー (1〜9で固定) |
| 表示 | 選択キー (必須、候補一覧の表示にも使用) |
| 予備 | 選択キー (空でもOK) |


### キー設定（ON/OFF）

IME ON/OFF のキーを指定します。

仮想キーコード、Alt、Control、Shift の組合せを設定して下さい。

仮想キーコードの詳細はこちらを参照下さい。 http://msdn.microsoft.com/en-us/library/dd375731(v=vs.85).aspx

最大で8行です。


### キー設定（文字）、キー設定（仮想キー）

各機能に対してキーを正規表現で設定して下さい。

Visual C++ 2013 の 正規表現で、文法は ECMAScript を使用しています。

正規表現の詳細はこちらを参照下さい。 http://msdn.microsoft.com/en-us/library/bb982727(v=vs.120).aspx

無効な正規表現で設定するとその機能は無効となります。警告等は表示されません。

キー設定（文字）とキー設定（仮想キー）とで重複する場合は、キー設定（仮想キー）のほうが優先されます。

キー設定（文字）には ASCII の範囲内の文字を設定出来ます。

キー設定（仮想キー）にはShiftキー(S)またはCtrlキー(C)をキーコードに前置することで、修飾キーを設定出来ます。

例えば、Shift+Tabであれば「S\x09」、Ctrl+Returnであれば「C\x0D」と記述します。


### キー設定デフォルト

キー設定 ON/OFF

| 機能 | キー | 備考 |
|---|---|---|
| ON / OFF  | Alt+`                  | 0xC0 + Alt |
| 〃        | 漢字                   | 0x19 |
| 〃        | (Alt+半角/全角  Alt+`) | 0x19 |
| 〃        | 半角/全角(Ctrl+`)      | 0xF3, 0xF4 |

キー設定（文字）

| 機能 | キー | 備考 |
|---|---|---|
| かな／カナ | q                      | ひらがな／カタカナモード、かなカナ変換 |
| ｶﾅ全英変換 | Ctrl+q                 | ひらがな／半角カタカナモード<br>ひらがなカタカナ→半角カタカナ変換<br>abbrev→全角英数字変換 |
| 全英       | L                      | 全英モード |
| ASCII      | l                      | アスキーモード |
| ひらがな   |                        | ひらがなモード |
| abbrev     | /                      | abbrevモード |
| 接辞       | <  >                   | 接頭辞・接尾辞 |
| 次候補     | Space  Ctrl+n          | 辞書検索開始、次候補 |
| 前候補     | x  Ctrl+p              | 「後退」のキーも使用可 |
| 辞書削除   | X  Ctrl+x              | ユーザー辞書から候補を削除 |
| 次補完     | Ctrl+i(Tab)            | 補完開始、次見出し語候補 |
| 前補完     | Ctrl+u                 | 前見出し語候補 |
| 絞り込み   |                        | 候補を絞り込む見出し語の入力開始<br>skk-hint-start-char |
| 変換位置   |                        | 変換位置指定<br>2回連続入力で文字自体が確定する<br>skk-sticky-key |
| 直接入力   | 0〜9                   | 見出し語入力でローマ字仮名変換しない |
| 確定       | Ctrl+m(Return)  Ctrl+j |  |
| 取消       | Ctrl+g  Ctrl+[(Escape) |  |
| 後退       | Ctrl+h(BS)             |  |
| 削除       | Ctrl+d  DEL(Ctrl+BS)   |  |
| \*無効\*   |                        | アプリケーション側に非通知<br>辞書登録の確定無効 |
| 左移動     | Ctrl+b                 |  |
| 先頭移動   | Ctrl+a                 |  |
| 右移動     | Ctrl+f                 |  |
| 末尾移動   | Ctrl+e                 |  |
| 貼付       | Ctrl+y  Ctrl+v         | クリップボードの文字列を貼り付け |

  キー設定（仮想キー）

| 機能 | キー | 備考 |
|---|---|---|
| かな／カナ |                        | ひらがな／カタカナモード、かなカナ変換 |
| ｶﾅ全英変換 |                        | ひらがな／半角カタカナモード<br>ひらがなカタカナ→半角カタカナ変換<br>abbrev→全角英数字変換 |
| 全英       |                        | 全英モード |
| ASCII      |                        | アスキーモード |
| ひらがな   | Ctrl+0x4A (Ctrl+j)     | ひらがなモード |
| abbrev     |                        | abbrevモード |
| 接辞       |                        | 接頭辞・接尾辞 |
| 次候補     |                        | 辞書検索開始、次候補 |
| 前候補     |                        | 「後退」のキーも使用可 |
| 辞書削除   |                        | ユーザー辞書から候補を削除 |
| 次補完     |                        | 補完開始、次見出し語候補 |
| 前補完     | Shift+0x09(Shift+Tab)  | 前見出し語候補 |
| 絞り込み   |                        | 候補を絞り込む見出し語の入力開始<br>skk-hint-start-char |
| 変換位置   |                        | 変換位置指定<br>skk-sticky-key |
| 直接入力   |                        | 見出し語入力でローマ字仮名変換しない（不使用） |
| 確定       |                        |  |
| 取消       |                        |  |
| 後退       |                        |  |
| 削除       | 0x2E (Delete)          |  |
| \*無効\*   | Ctrl+0x4A (Ctrl+j)     | アプリケーション側に非通知<br>辞書登録の確定無効 |
| 左移動     | 0x25 (カーソル左)      |  |
| 先頭移動   | 0x26 (カーソル上)      |  |
| 右移動     | 0x27 (カーソル右)      |  |
| 末尾移動   | 0x28 (カーソル下)      |  |
| 貼付       |                        | クリップボードの文字列を貼り付け |


### キー設定と入力モード遷移図

![](installer/README_mode.png)


### 半角カタカナモード

半角カタカナモードでは、ローマ字仮名変換のみ可能です。

ひらがな/カタカナへの変換、仮名漢字変換は出来ません。


### 変換位置指定

変換位置での挙動を指定します。最大で256行です。

| 機能 | 説明 |
|---|---|
| 開始 | 変換位置開始キー |
| 代替 | 変換位置開始キーに代わってローマ字仮名変換に使用する |
| 送り | 辞書検索に使用する送りローマ字 |

* 例１）AZIK風に、ローマ字仮名変換表で「q ん ン ﾝ 0」と設定し、開始「Q」代替「q」送り「n」と設定する。

  * 「KaQ」と入力すると、表示「▽か\*ん」、辞書検索キー「かn」と出来ます。

* 例２）開始「（空）」代替「あ」送り「a」と設定する。

  * かな入力のとき、送り仮名の最初を「あ」の状態で辞書検索を開始すると、送りローマ字が「a」となります。


### ローマ字・仮名変換表

ローマ字、平仮名、片仮名、所謂半角片仮名、促音/撥音(ん)、待機の組み合せを指定します。

「促／ん」がONのとき、仮名が決定したあとに最後の入力文字が入力状態となります。

「待機」がONのとき、入力した文字をローマ字仮名変換した結果 (変換出来ないときは入力した文字そのまま) がローマ字として扱われ、辞書検索開始、確定、補完開始、ローマ字に設定されていない組み合わせ、のいずれかになるまで仮名の最終的な決定が遅延されます。

平仮名／片仮名変換では基本的に１文字ずつ変換されます。

例外として、「う゛」(う＋濁点)は「ウ゛」(ウ＋濁点)ではなく「ヴ」と変換されます。

* 例） 平仮名「きょう」を片仮名「キョウ」に変換する場合、「きょ」→「キョ」、「う」→「ウ」ではなく、「き」→「キ」、「ょ」→「ョ」、「う」→「ウ」と変換されます。

最大で32768行です。

「…」ボタンから、KanaTableファイルの読み込みと書き出しを行うことができます。


### KanaTableファイル

* 文字コード：UTF-16(LE,BOMあり) または UTF-8
* 改行：CR+LF または LF
* フォーマット：<ローマ字><\t><ひらがな><\t><カタカナ><\t><カタカナ(半角)><\t><[促/ん]/[待機]><\r><\n>
  * <ローマ字>、<ひらがな>、<カタカナ>、<カタカナ(半角)>は、それぞれUTF-16換算で最大14バイトです。
  * [促/ん]は、ONのとき1、OFFのとき0です。
  * [待機]は、ONのとき2、OFFのとき0です。
  * <[促/ん]|[待機]>は、[促/ん]と[待機]の両方がONのとき3となりますが、[待機]のほうが優先されます。 (0のときは無しでも可)
  * 空行やタブのみの行は読み飛ばされます。
  * <\t>、<\r>、<\n>は、それぞれタブ、改行コードに読み替えて下さい。
* 例１）a<\t>あ<\t>ア<\t>ｱ<\r><\n>
* 例２）nn<\t>ん<\t>ン<\t>ﾝ<\t>0<\r><\n>
* 例３）np<\t>ん<\t>ン<\t>ﾝ<\t>1<\r><\n>
* 例４）ｺ<\t>こ<\t>コ<\t>ｺ<\t>2<\r><\n>


### ASCII・全英変換表

ASCII、全英文字の組み合せを指定します。最大で128行です。



## その他


### Lua拡張

サーバープロセス (imcrvmgr.exe) の各機能の拡張、プログラム実行変換もどき、数値変換をLuaスクリプトで実装しています。

現在使用しているLuaのバージョンは5.3.1です。

詳細はこちらを参照下さい。http://www.lua.org/manual/5.3/manual.html

Lua内部の文字コードをUTF-8に決め打ちして、Unicode版のWindowsAPIとCランタイム関数を呼ぶようにパッチを当てています。

スクリプトファイルの文字コードはUTF-8のみに対応しています。

サーバープロセスのカレントディレクトリは、%AppData%\CorvusSKK になっています。

サーバープロセスの起動時にスクリプトファイル (init.lua) が下記の優先順位でロードされます。

1. %AppData%\CorvusSKK\init.lua
2. サーバープロセスと同じディレクトリのinit.lua
  * 通常、%SystemRoot%\System32\IME\IMCRVSKK\init.lua
  * または、%SystemRoot%\SysWOW64\IME\IMCRVSKK\init.lua

コンソールプログラムのlua.exeが %SystemRoot%\System32\IME\IMCRVSKK と %SystemRoot%\SysWOW64\IME\IMCRVSKK にあるので、カスタマイズする際のデバッグ用に使って下さい。


### プログラム実行変換もどき

Emacs Lispのプログラム実行変換に対応していますが、あくまで「もどき」なのでご了承下さい。

以下のシンボルに大体対応しています。

| 名称 | 説明 |
|---|---|
| nil |  |
| t |  |
| lambda |  |
| concat |  |
| substring |  |
| make-string |  |
| string-to-char |  |
| string-to-number |  |
| number-to-string |  |
| window-width | 80で固定 |
| window-height | 23で固定 |
| current-time-string |  |
| car | ほぼ skk-num-list 用 |
| cdr | ほぼ skk-num-list 用 |
| 1+ |  |
| 1- |  |
| + |  |
| - |  |
| \* |  |
| / |  |
| % |  |
| skk-version |  |
| skk-server-version |  |
| skk-gadget-units-conversion |  |
| skk-ad-to-gengo |  |
| skk-gengo-to-ad |  |
| skk-current-date |  |
| skk-default-current-date |  |
| skk-relative-date |  |
| skk-ignore-dic-word | デフォルト無効 |
| skk-omikuji | 独自実装<br>おみくじを引くことができます |
| fill-column | 70で固定 |
| comment-start | "/\*" |
| comment-end | "\*/" |
| skk-henkan-key | 変換する見出し語 |
| skk-num-list | 変換する見出し語に含まれる数値文字列のリスト |


### 数値変換

タイプ0〜3,5,8,9に対応しています。

タイプ3と5での数値は0〜10^68-1の整数に対応しています。

独自実装としてタイプ6(ローマ数字)が、1〜3999の整数に対応しています。

見出し語として # (ナンバーサイン)を含み、候補として # と数字を含むエントリが辞書に存在する必要があります。(例:「めいじ#ねん /明治#3年/」)

| 候補 | 説明 | 例 |
|---|---|---|
| #0 | タイプ０ 無変換            |「1234567890」→「1234567890」 |
| #1 | タイプ１ 全角              |「1234567890」→「１２３４５６７８９０」 |
| #2 | タイプ２ 漢数字 位取りあり |「1234567890」→「一二三四五六七八九〇」 |
| #3 | タイプ３ 漢数字 位取りなし |「1234567890」→「十二億三千四百五十六万七千八百九十」 |
| #5 | タイプ５ 大字              |「1234567890」→「拾弐億参千四百五拾六万七千八百九拾」 |
| #6 | タイプ６ ローマ数字(独自)  |「1234」→「MCCXXXIV」 |
| #8 | タイプ８ 桁区切り          |「1234567890」→「1,234,567,890」 |
| #9 | タイプ９ 将棋              |「12kin」→「１二金」 |


### Unicodeコードポイント変換

「U+XXXXXX」( コードポイント XXXXXX : 0000-FFFF または 10000-10FFFF ) または「uxxxxxx」( コードポイント xxxxxx : 0000-ffff または 10000-10ffff ) のフォーマットで変換して下さい。

* 例１）「▽U+30A2」→「▼ア」
* 例２）「▽u30a2」→「▼ア」


### JIS X 0213面区点番号変換

「X-YY-ZZ」( 面 X : 1-2、 区 YY : 01-94、点 ZZ: 01-94 ) のフォーマットで変換して下さい。Unicodeコードポイントが注釈として付加されます。

* 例）「▽1-05-02」→「▼ア;U+30A2」


### 文字コード表記変換

「?X」( X : 任意の1文字以上の文字列 ) のフォーマットで変換して下さい。

ASCII(hex), JIS X 0201(片仮名, 8bit, hex), JIS X 0213面区点番号のカンマ区切りの候補およびUnicodeコードポイントのカンマ区切りの候補に変換されます。

ASCII, JIS X 0201, JIS X 0213に変換できない文字が含まれていた場合、Unicodeコードポイントの候補のみとなります。

* 例１）「▽?ア」→「▼1-05-02」/「▼U+30A2」
* 例２）「▽?あアｱa」→「▼1-04-02,1-05-02,B1,61」/「▼U+3042,U+30A2,U+FF71,U+0061」
* 例３）「▽?🐧」→「▼U+1F427」


### 注釈の登録

辞書登録のとき、登録する候補の入力と同時に行います。

行頭以外の最後のセミコロン (いわゆる半角のセミコロン）以降が注釈となります。

注釈にセミコロンを含めることは出来ません。

* 例１）登録する見出し語「しょへい#ねん」、登録する候補「初平#3年」、登録する注釈「後漢」の場合
  * 「初平#3年;後漢」と入力する。

* 例２）登録する見出し語「なき」、登録する候補「(;_;)」、登録する注釈「顔文字」の場合
  * 「(;_;);顔文字」と入力する。

* 例３）登録する見出し語「せみころん」、登録する候補「;」、登録する注釈「セミコロン」の場合
  * 「;;セミコロン」と入力する。


### Windows 8, 8.1 のタッチキーボード

タッチパネルを搭載したマシンでハードウェアキーボードに準拠したレイアウトを使用するには、以下の操作を行って下さい。

* Windows 8 の場合
  * 「PC設定」の画面 → 「全般」を選択 → 「タッチキーボード」の項目 → 「ハードウェアキーボードに準拠したレイアウトを使えるようにする」をオン

* Windows 8.1 の場合
  * 「PC設定」の画面 → 「PCとデバイス」の画面 → 「入力」を選択 → 「ハードウェアキーボードに準拠したレイアウトをタッチキーボードオプションとして追加する」をオン

タッチパネルを搭載していないマシンでハードウェアキーボードに準拠したレイアウトを使用するには、レジストリに以下の値を設定して下さい。

    [HKEY_CURRENT_USER\SOFTWARE\Microsoft\TabletTip\1.7]
    "EnableCompatibilityKeyboard"=dword:00000001


### 開発環境

Visual Studio Express 2013 for Windows Desktop Update 4

WiX Toolset v3.9 R2
