#pragma once
#include <KamataEngine.h>
#include "Player.h"

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

};