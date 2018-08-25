/**
 * @brief Systemクラスヘッダー
 * 
 * @file system.h
 */
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	構造体定義																					*/
/************************************************************************************************/

/************************************************************************************************/
/*	関数プロトタイプ宣言																		*/
/************************************************************************************************/

/**
 * @brief	乱数生成初期化
 * @note	
 * @attention
 * system_random_init()呼び出し前に一度呼び出ししてください
 *
 */
void system_random_init(void);

/**
 * @brief	乱数生成
 * @note	int型の乱数を出力します
 * @attention
 * system_random_init()呼び出し後に呼び出してください
 *
 */
int system_random(void);

/**
 * @brief	画面クリア
 * @note	OSごとに制御を分ける
 * @attention
 * 
 */
void system_clear(void);




#endif /* __SYSTEM_H__ */