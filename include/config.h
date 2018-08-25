/**
 * @brief config
 * 
 * @file config.h
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
/**
 * @enum	E_DEBUG
 * @brief	デバッグ出力有効無効
 */
typedef enum {
	E_DEBUG_DISABLE = 0,
	E_DEBUG_ENABLE = 1,
} E_DEBUG;

/************************************************************************************************/
/*	Configuration																				*/
/************************************************************************************************/
/** @name デバッグ出力有効無効
 */
/*@{*/
#define CONFIG_ENABLE_DEBUG_PRINT			/**< デバッグ出力を有効にする */
/*@}*/

/** @name デバッグ出力用クラスID
 */
/*@{*/
#define D_DEBUG_CLASS_MAIN					(E_DEBUG_DISABLE)
#define D_DEBUG_CLASS_SYSTEM				(E_DEBUG_DISABLE)
#define D_DEBUG_CLASS_CARD					(E_DEBUG_DISABLE)
#define D_DEBUG_CLASS_PLAYER				(E_DEBUG_DISABLE)
#define D_DEBUG_CLASS_POKER					(E_DEBUG_DISABLE)
#define D_DEBUG_CLASS_GAME					(E_DEBUG_DISABLE)
#define D_DEBUG_CLASS_UI					(E_DEBUG_DISABLE)
/*@}*/

/************************************************************************************************/
/*	マクロ																						*/
/************************************************************************************************/
#ifdef CONFIG_ENABLE_DEBUG_PRINT
	/* デバッグ出力マクロ有効 */
	#include "debug.h"
#else /* CONFIG_ENABLE_DEBUG_PRINT */
	/* デバッグ出力マクロ無効化 */
	#define M_DEBUG_ERROR(classId, format, ...)
	#define M_DEBUG_ENTRY(classId, format, ...)
	#define M_DEBUG_INFO(classId, format, ...)
#endif /* CONFIG_ENABLE_DEBUG_PRINT */

#endif /* __CONFIG_H__ */