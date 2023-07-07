#ifndef ___DIRECTION_LIGHT_H___
#define ___DIRECTION_LIGHT_H___

#include "ComponentBase.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>

class DirectionLight : public ComponentBase
{
public:
	struct Info {
		// 光の方向ベクトル
		DirectX::XMFLOAT3 m_Direction;
		float padding0;
		DirectX::XMFLOAT4X4 m_matView;
		DirectX::XMFLOAT4X4 m_matProj;
	};
public:
	// コンストラクタ
	DirectionLight();
	// デストラクタ
	~DirectionLight();

	void Start();

	void SetLight();
private:
	Info m_Info;
	ConstantBuffer* m_pLightBuf;
};

#endif //!___DIRECTIONLIGHT_H___