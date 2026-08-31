#pragma once
#include <KamataEngine.h>
#include "Math.h"
#include "UpData.h"
 class obstacles 
{
public:
    
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position);

	void UpDate();

	void Draw(KamataEngine::Camera& camera);

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_;
	UpData* updatetransform_ = nullptr;
 
};