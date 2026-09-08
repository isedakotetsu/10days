#include "obstacles.h"

void obstacles::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) 
{
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {25.0f, 35.0f, 1.0f};
	model_ = model;
}

void obstacles::Update()
{
	// Y座標を徐々に上げる
    worldTransform_.translation_.y += 0.02f;

	updatetransform_->WorldTransformUpdate(worldTransform_);
}

void obstacles::Draw(KamataEngine::Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
