/**
 * @brief Systemクラス
 * 
 * @file system.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include "common.h"
#include "system.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(format, ...)		M_DEBUG_ERROR(D_DEBUG_CLASS_SYSTEM, format, ## __VA_ARGS__)
#define M_ENTRY(format, ...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_SYSTEM, format, ## __VA_ARGS__)
#define M_INFO(format, ...)			M_DEBUG_INFO(D_DEBUG_CLASS_SYSTEM, format, ## __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
#define D_UI_CONSOLE_BUFFER			(256)
#define D_UI_CONSOLE_IN_ERROR		(-1)
#define D_UI_BASE_10				(10)

/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	外部公開関数																				*/
/************************************************************************************************/
/**
 * @brief	乱数生成初期化
 * @note	
 * @attention
 * system_random_init()呼び出し前に一度呼び出ししてください
 *
 */
void system_random_init(void)
{
	M_ENTRY();
	srand((unsigned)time(NULL));
}

/**
 * @brief	乱数生成
 * @note	int型の乱数を出力します
 * @attention
 * system_random_init()呼び出し後に呼び出してください
 *
 */
int system_random(void)
{
	M_ENTRY();
	int r = rand();
	return r;
}

/**
 * @brief	メモリ初期化
 *
 */
void system_memset(void *ptr, U1 value, U4 len)
{
	memset(ptr, value, len);
}

/**
 * @brief	コンソール出力
 * @note	printfラッパー
 *
 * @param[in]	出力文字列
 */
void system_printf(const char *format, ...)
{
	va_list va;
	va_start(va, format);
	vprintf(format, va);
	va_end(va);
}

/**
 * @brief	コンソール入力
 * @note	str文字列出力後、ユーザー入力待ち状態
 *
 * @return	入力したコード
 */
E_UI_SELECT_CODE system_consoleInput(void)
{
	E_UI_SELECT_CODE selectCode = E_UI_ERROR;
	char buffer[D_UI_CONSOLE_BUFFER] = {};

	if (fgets(buffer, D_UI_CONSOLE_BUFFER, stdin) == NULL) {
		M_ERROR("fgets is NULL\n");
		return selectCode;
	}
	if (buffer[0] == '\n') {
		selectCode = E_UI_RETURN;
		return selectCode;
	}

	long value = strtol(buffer, NULL, D_UI_BASE_10);
	switch (value) {
	case 1:
		selectCode = E_UI_1;
		break;
	case 2:
		selectCode = E_UI_2;
		break;
	case 3:
		selectCode = E_UI_3;
		break;
	case 4:
		selectCode = E_UI_4;
		break;
	case 5:
		selectCode = E_UI_5;
		break;
	default:
		selectCode = E_UI_OTHER;
		break;
	}

	return selectCode;
}

/**
 * @brief	コンソール入力街
 * @note	ユーザー入力待ち状態
 *
 */
void system_consoleWait(void)
{
	char buffer[D_UI_CONSOLE_BUFFER] = {};
	fgets(buffer, D_UI_CONSOLE_BUFFER, stdin);
}

/**
 * @brief	画面クリア
 * @note	OSごとに制御を分ける
 * @attention
 * 
 *
 */
void system_clear(void)
{
#if (defined(OS_MAC) || (defined(OS_LINUX)))
	system("clear");
#elif (defined(OS_WINDOWS))
	system("cls");
#else
	#error "Unkown OS..."
#endif
}
