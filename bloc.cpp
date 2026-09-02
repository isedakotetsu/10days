#include "bloc.h"
#include <numbers>

using namespace KamataEngine;

void bloc::Initialize(Model* model, Camera* camera) {

	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.TransferMatrix();
}

void bloc::Move() {

		// SPACEを押したら現在のブロックを固定
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {

		auto newBlock = std::make_unique<WorldTransform>();

		newBlock->Initialize();

		// 今のブロックの位置を保存
		newBlock->translation_ = worldTransform_.translation_;
		newBlock->rotation_ = worldTransform_.rotation_;

		newBlock->UpdateMatrix();
		newBlock->TransferMatrix();

		// 固定ブロックとして追加
		blocks_.push_back(std::move(newBlock));

		// 次のブロックを1個上へ
		worldTransform_.translation_.y += 2.0f;
	}

	// 現在のブロックを左右に動かす
	worldTransform_.translation_.x += moveDirection_;

	// 右端
	if (worldTransform_.translation_.x >= 15.0f) {
		moveDirection_ = -0.2f;
	}

	// 左端
	if (worldTransform_.translation_.x <= -15.0f) {
		moveDirection_ = 0.2f;
	}
	// ★ 行列を再計算する処理を追加
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void bloc::Update() { Move(); }

void bloc::Draw() {

	// 積み上げたブロック
	for (auto& block : blocks_) {

		model_->Draw(*block, *camera_);
	}

	// 現在動いているブロック
	model_->Draw(worldTransform_, *camera_);
}