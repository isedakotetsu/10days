#pragma once
#include <KamataEngine.h>
#include "obstacles.h"
#include "Player.h"

#include "bloc.h"




class GameScene 
{
public:
	void Initialize();

	void Update();

	void Camera();

	void Draw();

	~GameScene();

	bool IsFinished() const { return phase_ == Phase::kDeath || phase_ == Phase::kClear; }
	// 追加: 死亡したかどうかを判定する関数（main.cppで使用）
	bool IsDead() const { return phase_ == Phase::kDeath; }
	// クリアしたことを感知する関数
	bool IsClear() const { return phase_ == Phase::kClear; }

private:
	KamataEngine::Camera camera_;
	obstacles* obstacles_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* Obstaclesmodel_ = nullptr;
	KamataEngine::Vector3 ObstaclesPosition_;
	
	

    // プレイヤー
    Player* player_ = nullptr;
   
    // プレイヤーモデル
	KamataEngine::Model* playerModel_ = nullptr;


    //デバックカメラ有効
    bool isDebugCameraActive_ = false;

    //デバックカメラ
    KamataEngine::DebugCamera* debugCamera_ = nullptr;

	bloc* bloc_ = nullptr;

	KamataEngine::Model* modelBloc_ = nullptr;



	enum class Phase {
		kFadeIn,  
		kPlay,    
		kDeath,   
		kFadeOut, 
		kClear,   
	};
	Phase phase_ = Phase::kPlay;

	//背景
	float cameraStartY_ = 0.0f;
	KamataEngine::Sprite* haikei_ = nullptr;
	KamataEngine::Sprite* haikei2_ = nullptr;

};