#ifndef ___CAMERA_BATTLE_H___
#define ___CAMERA_BATTLE_H___

#include "Camera.h"
#include <DirectXMath.h>
#include <memory>
#include "Transform.h"
#include "Sound.h"
#include <cstdint>

class CameraBattle : public Camera
{
public:
	// コンストラクタ
	CameraBattle();
	// デストラクタ
	~CameraBattle();

	// 初期化
	void Start() override final;
	// 更新
	void Update() override final;

	//--- セット関数
	void SetPosition(const DirectX::XMFLOAT3& _position);
	void SetLookPoint(const DirectX::XMFLOAT3& _lookPoint) {
		m_LookPoint = _lookPoint;
	}

private:

	std::shared_ptr<Transform> m_pTrans;

	//--- サウンド
	XAUDIO2_BUFFER* m_pBattleBGMData;
	IXAudio2SourceVoice* m_pBattleBGMSource;

	// 画面操作用カーソル座標
	DirectX::XMFLOAT2 m_CursorPos;
	std::float_t m_RotateSensitivity;	// 回転感度
	std::float_t m_radXZ, m_radY;		// 回り込み角度
	std::float_t m_radius;				// カメラと注視点の距離
};

#endif //!___CAMERA_BATTLE_H___