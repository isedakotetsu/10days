#include "GameScene.h"

void GameScene::Initialize() 
{
	model_ = Model::Create();
	worldTransform_.Initialize();
	camera_.Initialize();

	// 障害物の初期化
	obstacles_ = new obstacles();
	Obstaclesmodel_ = Model::CreateFromOBJ("cube");

	ObstaclesPosition_ = {0.0f, -70.0f, 40.0f};
	obstacles_->Initialize(Obstaclesmodel_, ObstaclesPosition_);
}

void GameScene::UpDate() 
{
	
	obstacles_->UpDate();
}

void GameScene::Draw()
{
	Model::PreDraw();

	obstacles_->Draw(camera_);

	Model::PostDraw();
}

GameScene::~GameScene() 
{
	Obstaclesmodel_ = nullptr;
}
