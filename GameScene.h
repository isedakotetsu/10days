#pragma once
#include <KamataEngine.h>
#include "Player.h"
#include "block.h"

using namespace KamataEngine;

class GameScene 
{
public:
	void Initialize();

	void Update();

	void Draw();

	~GameScene();

private:

    // プレイヤー
    Player* player_ = nullptr;
   
    // プレイヤーモデル
    Model* playerModel_ = nullptr;

    // カメラ
    Camera camera_;

    //デバックカメラ有効
    bool isDebugCameraActive_ = false;

    //デバックカメラ
    KamataEngine::DebugCamera* debugCamera_ = nullptr;

    block* block_ = nullptr;

    KamataEngine::Model* modelBlock_ = nullptr;

    // 通常時のカメラ位置
    KamataEngine::Vector3 cameraOffset_ = {0.0f, 3.0f, -12.0f};

    // この高さを超えたら、積み上げたブロックに合わせてカメラを上げる
    static inline const float kCameraFollowStartY = 4.0f;

    // 追従中、プレイヤーを画面中央より少し上に表示する値
    static inline const float kCameraPlayerScreenY = 1.0f;

};
