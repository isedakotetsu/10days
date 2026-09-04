#pragma once
#include <KamataEngine.h>
#include "Player.h"
#include "block.h"

using namespace KamataEngine;

#include "bloc.h"
>>>>>>>>> Temporary merge branch 2
using namespace KamataEngine;

#include "bloc.h"
>>>>>>>>> Temporary merge branch 2
using namespace KamataEngine;



{
public:
	void Camera();
>>>>>>>>> Temporary merge branch 2

	void Update();

	void Camera();
>>>>>>>>> Temporary merge branch 2

	void Draw();


	bool IsFinished() const { return phase_ == Phase::kDeath || phase_ == Phase::kClear; }
	// 追加: 死亡したかどうかを判定する関数（main.cppで使用）

<<<<<<<<< Temporary merge branch 1
	bool IsClear() const { return phase_ == Phase::kClear; }

private:

<<<<<<<<< Temporary merge branch 1
    // プレイヤー
    Player* player_ = nullptr;
   
    block* block_ = nullptr;

    KamataEngine::Model* modelBlock_ = nullptr;

    //デバックカメラ有効
=========
	// ワールドトランスフォーム
    // この高さを超えたら、積み上げたブロックに合わせてカメラを上げる
    static inline const float kCameraFollowStartY = 4.0f;

    // 追従中、プレイヤーを画面中央より少し上に表示する値
    static inline const float kCameraPlayerScreenY = 1.0f;

};
	
	// デバックカメラ有効
	bool isDebugCameraActive = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera = nullptr;

	bloc* bloc_ = nullptr;
    KamataEngine::DebugCamera* debugCamera_ = nullptr;

=========
	// ワールドトランスフォーム
	
	
>>>>>>>>> Temporary merge branch 2
};	
	// デバックカメラ有効
	bool isDebugCameraActive = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera = nullptr;

	bloc* bloc_ = nullptr;

    // 通常時のカメラ位置
    KamataEngine::Vector3 cameraOffset_ = {0.0f, 3.0f, -12.0f};

	
	
>>>>>>>>> Temporary merge branch 2
};