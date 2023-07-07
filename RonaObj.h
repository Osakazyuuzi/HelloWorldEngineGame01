#ifndef ___RONA_OBJ_H___
#define ___RONA_OBJ_H___

#include <cstdint>

//-------------------
// オブジェクト
//-------------------
// 種類：キャラクター
// ●魔王（ボス）
// 名前：ロナ
// 年齢：？？？（0歳）
// 性格：？？？（魔王軍と呼ばれる自分達をこよなく愛している。）
// コンプレックス：？？？
// 容姿：体が黒色で、赤い角が生えている。
// 目的：この世の中に自分たち（魔王軍）の居場所を創ろうとしている。
// 特技：？？？
class RonaObj {
public:
	// コンストラクタ
	RonaObj();
	// デストラクタ
	~RonaObj();

	// キャラクターのサイズ
	constexpr static float mc_sizeX = 1.0f;
	constexpr static float mc_sizeY = 1.5f;
	constexpr static float mc_sizeZ = 1.0f;

	// 登場時のステータス
	constexpr static uint8_t mc_nInitLevel = 1;
	constexpr static uint8_t mc_nInitExperienceMax = 12;
	constexpr static uint8_t mc_nInitAttack = 2;
	constexpr static uint8_t mc_nInitDefense = 2;
	constexpr static uint8_t mc_nInitSpeed = 2;
	constexpr static uint8_t mc_nInitMpMax = 1;
	constexpr static int16_t mc_nInitHpMax = 3;
};

#endif //!___RONA_OBJ_H___