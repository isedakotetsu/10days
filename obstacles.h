#pragma once
#include <KamataEngine.h>
#include "Math.h"
#include "Update.h"
 class obstacles 
{
public:
    
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	KamataEngine::Vector3 GetPosition() const { return worldTransform_.translation_; }

	KamataEngine::Vector3 GetHalfSize() const { return halfSize_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_;
	::Update* updatetransform_ = nullptr;
	KamataEngine::Vector3 halfSize_ = {70.0f, 50.0f, 1.0f};

 
};