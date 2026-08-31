#include "obstacles.h"

void obstacles::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) 
{
	assert(model);

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {70.0f, 50.0f, 1.0f};
	model_ = model;
}

void obstacles::UpDate()
{
	// Y座標を徐々に上げる
	worldTransform_.translation_.y += 0.2f;

	updatetransform_->WorldTransformUpData(worldTransform_);
}

void obstacles::Draw(KamataEngine::Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
