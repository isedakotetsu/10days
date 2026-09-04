#include "Skydome.h"



void Skydome::Initialize(Model* model, Camera* camera) { 
	
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	
}

void Skydome::Update() 
{ 
	worldTransform_.TransferMatrix();
}

void Skydome::Draw()
{
	
	DirectXCommon* dxcommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxcommon->GetCommandList());
	model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
	
}