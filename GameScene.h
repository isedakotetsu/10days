#pragma once
#include <KamataEngine.h>

#include "bloc.h"
using namespace KamataEngine;

class GameScene {
public:
	void Initialize();

	void Update();

	void Camera();

	void Draw();

	~GameScene();

private:

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;
	
	// デバックカメラ有効
	bool isDebugCameraActive = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera = nullptr;

	bloc* bloc_ = nullptr;

	KamataEngine::Model* modelBloc_ = nullptr;

	
	
};