#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;
class Skydome
{
public:
	void Initialize(Model* model_, Camera* camera_);
	void Update();
	void Draw();
	

private:
	WorldTransform worldTransform_;
	Camera* camera_ = nullptr;
	Model* model_ = nullptr;

};
