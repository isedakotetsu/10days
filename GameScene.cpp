#include "GameScene.h"
#include <cmath>

#include <Windows.h>
#include <string>

using namespace KamataEngine;

void GameScene::Initialize() {
	// プレイヤーモデルを読み込む
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	// プレイヤーを生成
	player_ = new Player();
	// プレイヤーを初期化
	player_->Initialize(modelPlayer_);

	// カメラを初期化
	camera_.Initialize();

	// プレイヤーに近いカメラ位置
	camera_.translation_ = {0.0f, 0.0f, -10.0f};

	// カメラの向き
	camera_.rotation_ = {0.0f, 0.0f, 0.0f};

	// モデル読み込み
	modelBlock_ = Model::CreateFromOBJ("block");
	// ブロックを生成
	block_ = new block();
	// ブロックを初期化
	block_->Initialize(modelBlock_, &camera_);
}

void GameScene::Update() {
	// 前のフレームでプレイヤーが着地していればブロックを固定する
	block_->Update(player_->GetWorldPosition());


	// 積み上がったブロック数を取得
	int currentBlockCount = static_cast<int>(block_->GetBlocks().size());

	// ブロックが1個増えた
	if (currentBlockCount > previousBlockCount_) {

		// コンボ増加
		combo_++;

		// スコア加算
		score_ += 100 * combo_;

		// ブロック数を更新
		previousBlockCount_ = currentBlockCount;

		// コンボ確認
		OutputDebugStringA(("Combo: " + std::to_string(combo_) + "  Score: " + std::to_string(score_) + "\n").c_str());
	}

	//コンボリセット
	if (block_->IsFalling()) {
		combo_ = 0;
	}

	// プレイヤーを更新してブロックとの衝突を解決
	player_->Update(block_);

	// 変更したカメラ位置と向きを反映
	camera_.UpdateMatrix();
}

void GameScene::Draw() {
	// 3Dモデルの描画開始
	Model::PreDraw();
	// プレイヤーを描画
	player_->Draw(camera_);

	block_->Draw();

	// 3Dモデルの描画終了
	Model::PostDraw();
}

GameScene::~GameScene() {
	// プレイヤーを解放
	delete player_;
	player_ = nullptr;

	// プレイヤーモデルを解放
	delete modelPlayer_;
	modelPlayer_ = nullptr;

	delete block_;
	block_ = nullptr;

	delete modelBlock_;
	modelBlock_ = nullptr;
}
