/**
 * @brief main
 * 
 * @file main.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "card.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#ifdef CONFIG_ENABLE_DEBUG_CLASS_MAIN
#define M_ERROR(...)		M_DEBUG_ERROR(__VA_ARGS__)
#define M_ENTRY(...)		M_DEBUG_ENTRY(__VA_ARGS__)
#else
#define M_ERROR(...)		M_DEBUG_ERROR(__VA_ARGS__)
#define M_ENTRY(...)
#endif /* CONFIG_ENABLE_DEBUG_CLASS_MAIN */

/**
 * @brief 
 * 
 * @param argc 未使用
 * @param argv 未使用
 * @return int 0
 */
int main(int argc, char* argv[])
{
	M_ENTRY();
	(void)argc;
	(void)argv;

	card_outOfBox(E_TRUE);
	card_shuffle();

	M_ERROR("finish");
	return 0;
}
