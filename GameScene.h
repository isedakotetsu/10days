#pragma once
#include <KamataEngine.h>
#include "obstacles.h"
using namespace KamataEngine;

class GameScene {
public:
	void Initialize();

	void UpDate();

	void Draw();

	~GameScene();

private:
	KamataEngine::Camera camera_;
	obstacles* obstacles_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* Obstaclesmodel_ = nullptr;

	 Vector3 ObstaclesPosition_;
	
};