#ifndef ___RONA_CONTROLLER_H___
#define ___RONA_CONTROLLER_H___

#include "ComponentBase.h"
#include <memory>
#include <DirectXMath.h>
#include "ObjectBase.h"
#include "Sound.h"
#include "RonaAnimator.h"
#include "Status.h"

//-------------------
// コンポーネント
//-------------------
// 所属キャラクター：ロナ
class RonaController : public ComponentBase {
public:
	// コンストラクタ
	RonaController();
	// デストラクタ
	~RonaController();
	// 初期化
	void Start() override final;
	// 更新
	void Update() override final;
	// 当たり判定
	void OnCollisionEnter(ObjectBase* _pObject) override final;
	void OnCollisionStay(ObjectBase* _pObject) override final;

private:
	// コンポーネントのポインタ
	std::shared_ptr<Status> m_pStatus;
	std::shared_ptr<RonaAnimator> m_pAnimtor;

	float m_TargetRotY;
	float m_lateRotY;	// 遅れてついてくるY角度

	//--- サウンド
	XAUDIO2_BUFFER* m_pWalkSEData;
	IXAudio2SourceVoice* m_pWalkSESource;

private:
	// 所属オブジェクトのポインタ
	std::shared_ptr<ObjectBase> m_pOwner;
};

#endif //!___TERA_CONTROLLER_H___