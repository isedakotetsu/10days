#include "GameScene.h"
using namespace KamataEngine;
GameScene::~GameScene() {}

void GameScene::Initialize() {
	// ワールドトランスフォーム
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();
	
	// カメラを固定
	camera_.translation_ = {0.0f, 0.0f, -50.0f};

	camera_.rotation_ = {0.0f, 0.0f, 0.0f};
	
	// モデル読み込み
	modelBloc_ = Model::CreateFromOBJ("cube");

	bloc_ = new bloc();
	bloc_->Initialize(modelBloc_, &camera_);
}

void GameScene::Update() {
	bloc_->Update();

	camera_.UpdateMatrix();
}

void GameScene::Draw() {
	Model::PreDraw();

	bloc_->Draw();

	Model::PostDraw();
}
