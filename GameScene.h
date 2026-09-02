#pragma once
#include <KamataEngine.h>
#include "obstacles.h"
#include "Player.h"



class GameScene 
{
public:
	void Initialize();

	void Update();

	void Draw();

	~GameScene();

private:
	KamataEngine::Camera camera_;
	obstacles* obstacles_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* Obstaclesmodel_ = nullptr;

	 Vector3 ObstaclesPosition_;
	

    // プレイヤー
    Player* player_ = nullptr;
   
    // プレイヤーモデル
	KamataEngine::Model* playerModel_ = nullptr;


    //デバックカメラ有効
    bool isDebugCameraActive_ = false;

    //デバックカメラ
    KamataEngine::DebugCamera* debugCamera_ = nullptr;

};