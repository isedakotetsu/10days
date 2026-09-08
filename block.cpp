#include "block.h"
#include <numbers>

using namespace KamataEngine;

void block::Initialize(Model* model, Camera* camera) 
{
	assert(model);
	assert(camera);

	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {-15.0f, 1.0f, 0.0f};

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.TransferMatrix();

	// カメラの初期位置を保存
	cameraStartPosition_ = camera_->translation_;
}

void block::Move(const Vector3& playerPosition) 
{
	// ========================================
	// 落下中
	// ========================================
	if (isFalling_) 
	{
		worldTransform_.translation_.y -= fallSpeed_;

		// 画面外まで落ちたら止める
		if (worldTransform_.translation_.y < -20.0f) 
		{
			isFalling_ = false;

			// 積んでいたブロックを全部削除
			blocks_.clear();

			// 最初の位置に戻す
			worldTransform_.translation_ = {-15.0f, 1.0f, 0.0f};

			// カメラも初期位置へ
			camera_->translation_ = cameraStartPosition_;

			// コンボと速度をリセット
			comboCount_ = 0;
			moveSpeed_ = 0.05f;
			// 最初の移動方向に戻す
			moveDirection_ = 0.2f;
		}

		// updatetransform_->WorldTransformUpData(worldTransform_);

		worldTransform_.matWorld_.m[3][0] = worldTransform_.translation_.x;
		worldTransform_.matWorld_.m[3][1] = worldTransform_.translation_.y;
		worldTransform_.matWorld_.m[3][2] = worldTransform_.translation_.z;
		worldTransform_.TransferMatrix();

		return;
	}

	// ========================================
	// プレイヤーが移動中のブロック上面へ着地したら固定
	// ========================================
	if (playerPosition.x >= worldTransform_.translation_.x - blockkWidth_ / 2.0f &&
		playerPosition.x <= worldTransform_.translation_.x + blockkWidth_ / 2.0f &&
	    playerPosition.y - 0.635770f >= worldTransform_.translation_.y + blockHeight_ / 2.0f - 0.05f &&
		playerPosition.y - 0.635770f <= worldTransform_.translation_.y + blockHeight_ / 2.0f + 0.05f)
	{
		// ------------------------------------
		// 下にブロックがある場合
		// ------------------------------------
		if (!blocks_.empty()) 
		{

			// 一番最後に固定したブロック
			WorldTransform* bottomblockk = blocks_.back().get();

			// 現在のブロックの中心
			float currentCenterX = worldTransform_.translation_.x;

			// 下のブロックの中心
			float bottomCenterX = bottomblockk->translation_.x;

			// 下のブロックの左端・右端
			float bottomLeft = bottomCenterX - blockkWidth_ / 2.0f;

			float bottomRight = bottomCenterX + blockkWidth_ / 2.0f;

			// ====================================
			// 当たり判定を端から25%内側にする
			// ====================================

			float hitRange = blockkWidth_ * 0.25f;

			float hitLeft = bottomLeft + hitRange;

			float hitRight = bottomRight - hitRange;

			
			// 現在のブロックの中心が
			// 当たり判定範囲に入っているか


			bool isHit = currentCenterX >= hitLeft && currentCenterX <= hitRight;

			// 外れていたら落下
			// ====================================

			if (!isHit) 
			{

				isFalling_ = true;

				return;
			}
		}


		auto newblockk = std::make_unique<WorldTransform>();

		newblockk->Initialize();

		// 今のブロックの位置を保存
		newblockk->translation_ = worldTransform_.translation_;

		newblockk->rotation_ = worldTransform_.rotation_;

		newblockk->matWorld_.m[3][0] = newblockk->translation_.x;
		newblockk->matWorld_.m[3][1] = newblockk->translation_.y;
		newblockk->matWorld_.m[3][2] = newblockk->translation_.z;
		newblockk->TransferMatrix();

		// updatetransform_->WorldTransformUpData(*newBlock);
		//  newBlock->TransferMatrix();

		// 固定ブロックとして追加
		blocks_.push_back(std::move(newblockk));
		// ====================================
		// 次のブロックを1個上へ
		// ====================================
		worldTransform_.translation_.y += blockHeight_;

		// 次のブロックは現在の進行方向に合う画面端から出現させる
		if (moveDirection_ > 0.0f)
		{
			worldTransform_.translation_.x = -15.0f;
		}
		else
		{
			worldTransform_.translation_.x = 15.0f;
		}

		// コンボを増やす
		comboCount_++;
		// コンボ数に応じてスピードアップ
		if (comboCount_ % 3 == 0) {
			moveSpeed_ += 0.02f;
		}

		// 次のブロックを上へ
		worldTransform_.translation_.y += blockHeight_;
		
		// カメラがblocについていく
        // camera_->translation_.y += 2.0f;
		}
		worldTransform_.translation_.x += moveDirection_ * (moveSpeed_ / 0.05f);
	worldTransform_.translation_.x += moveDirection_;

	// 右端
	if (worldTransform_.translation_.x >= 5.0f) 
	{
		moveDirection_ = -0.05f;
	}

	// 左端
	if (worldTransform_.translation_.x <= -5.0f) 
	{
		moveDirection_ = 0.05f;
	}

	// 座標をワールド行列へ反映
	worldTransform_.matWorld_.m[3][0] = worldTransform_.translation_.x;
	worldTransform_.matWorld_.m[3][1] = worldTransform_.translation_.y;
	worldTransform_.matWorld_.m[3][2] = worldTransform_.translation_.z;
	worldTransform_.TransferMatrix();
	/*========================================
		 ブロックに合わせてカメラをゆるく追従
	 ========================================*/

	 // 積み上がったブロックの数に応じてカメラの目標Yを決める 
	float targetCameraY = cameraStartPosition_.y + blocks_.size() * blockHeight_ + 1.0f;

	// カメラをゆっくり目標位置へ近づける
	float cameraSpeed = 0.01f;

	camera_->translation_.y += (targetCameraY - camera_->translation_.y) * cameraSpeed;
	// updatetransform_->WorldTransformUpData(worldTransform_);
}

void block::Update(const Vector3& playerPosition) 
{ 
	Move(playerPosition); 
}

void block::Draw() 
{
	// 積み上げたブロック
	for (auto& block : blocks_) 
	{
		model_->Draw(*block, *camera_);
	}

	// 現在動いているブロック
	model_->Draw(worldTransform_, *camera_);
}