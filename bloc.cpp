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

	// カメラの初期位置を保存
	cameraStartPosition_ = camera_->translation_;
}

void bloc::Move() {

	// ========================================
	// 落下中
	// ========================================
	if (isFalling_) {

		worldTransform_.translation_.y -= fallSpeed_;

		// 画面外まで落ちたら止める
		if (worldTransform_.translation_.y < -20.0f) {
			isFalling_ = false;

			// 積んでいたブロックを全部削除
			blocks_.clear();

			// 最初の位置に戻す
			worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

			// カメラも初期位置へ
			camera_->translation_ = cameraStartPosition_;

			// 最初の移動方向に戻す
			moveDirection_ = 0.2f;
		}

		updatetransform_->WorldTransformUpData(worldTransform_);
		

		return;
	}

	// ========================================
	// SPACEを押したら固定
	// ========================================
	if (Input::GetInstance()->TriggerKey(DIK_E)) {

		// ------------------------------------
		// 下にブロックがある場合
		// ------------------------------------
		if (!blocks_.empty()) {

			// 一番最後に固定したブロック
			WorldTransform* bottomBlock = blocks_.back().get();

			// 現在のブロックの中心
			float currentCenterX = worldTransform_.translation_.x;

			// 下のブロックの中心
			float bottomCenterX = bottomBlock->translation_.x;

			// 現在のブロックの左端・右端
			// float currentLeft = currentCenterX - blockWidth_ / 2.0f;

			// float currentRight = currentCenterX + blockWidth_ / 2.0f;

		// 下のブロックの左端・右端
			float bottomLeft = bottomCenterX - blockWidth_ / 2.0f;

			float bottomRight = bottomCenterX + blockWidth_ / 2.0f;

			// ====================================
			// 当たり判定を端から25%内側にする
			// ====================================

			float hitRange = blockWidth_ * 0.25f;

			float hitLeft = bottomLeft + hitRange;

			float hitRight = bottomRight - hitRange;

			
			// 現在のブロックの中心が
			// 当たり判定範囲に入っているか
			

			bool isHit = currentCenterX >= hitLeft && currentCenterX <= hitRight;

			// 外れていたら落下
			
			if (!isHit) {

				isFalling_ = true;

				return;
			}
		}


		auto newBlock = std::make_unique<WorldTransform>();

		newBlock->Initialize();

		// 今のブロックの位置を保存
		newBlock->translation_ = worldTransform_.translation_;

		newBlock->rotation_ = worldTransform_.rotation_;

		updatetransform_->WorldTransformUpData(*newBlock);
		//newBlock->TransferMatrix();

		// 固定ブロックとして追加
		blocks_.push_back(std::move(newBlock));
		
		worldTransform_.translation_.y += 2.0f;

		//カメラがblocについていく
		camera_->translation_.y += 2.0f;
	}


	worldTransform_.translation_.x += moveDirection_;

	// 右端
	if (worldTransform_.translation_.x >= 15.0f) {
		moveDirection_ = -0.2f;
	}

	// 左端
	if (worldTransform_.translation_.x <= -15.0f) {
		moveDirection_ = 0.2f;
	}
	
	updatetransform_->WorldTransformUpData(worldTransform_);
	
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