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

	// デバックカメラ
	debugCamera = new DebugCamera(1280, 720);

	// モデル読み込み
	modelBloc_ = Model::CreateFromOBJ("cube");

	bloc_ = new bloc();
	bloc_->Initialize(modelBloc_, &camera_);
}

void GameScene::Camera() {

	camera_.UpdateMatrix();

//	
//#ifdef _DEBUG
//	if (Input::GetInstance()->TriggerKey(DIK_0)) {
//		isDebugCameraActive = !isDebugCameraActive;
//	}
//#endif // DEBUG
//
//	// カメラの処理
//	if (isDebugCameraActive) {
//		// デバックカメラの更新
//		debugCamera->Update();
//		// デバックカメラのビュー行列
//		camera_.matView = debugCamera->GetCamera().matView;
//		// デバックカメラのプロジェクション行列
//		camera_.matProjection = debugCamera->GetCamera().matProjection;
//		// ビュープロジェクション行列と転送
//		camera_.TransferMatrix();
//	} else {
//		// ビュープロジェクション行列の”更新”と転送
//		camera_.UpdateMatrix();
//	}
}

void GameScene::Update() {
	bloc_->Update();

	Camera();
}

void GameScene::Draw() {
	Model::PreDraw();

	bloc_->Draw();

	Model::PostDraw();
}
