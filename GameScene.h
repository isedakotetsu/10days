#pragma once
#include <KamataEngine.h>
#include "Player.h"
#include "block.h"

using namespace KamataEngine;
class GameScene
{
public:

    ~GameScene();

    void Initialize();

	void Update();

	void Draw();


private:
    // プレイヤー
    Player* player_ = nullptr;
   
    block* block_ = nullptr;

    KamataEngine::Model* modelBlock_ = nullptr;

    KamataEngine::Model* modelPlayer_ = nullptr;

    KamataEngine::Camera camera_;

    //デバックカメラ有効
	// ワールドトランスフォーム
    // この高さを超えたら、積み上げたブロックに合わせてカメラを上げる
    static inline const float kCameraFollowStartY = 4.0f;

    // 追従中、プレイヤーを画面中央より少し上に表示する値
    static inline const float kCameraPlayerScreenY = 1.0f;

};