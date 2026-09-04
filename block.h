#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>
#include "Update.h"

using namespace KamataEngine;

class block 
{
public:
	/// 初期化
	void Initialize(Model* model, Camera* camera);

	// 動き
	void Move(const Vector3& playerPosition);

	/// 更新
	void Update(const Vector3& playerPosition);

	/// 描画
	void Draw();

	// 固定済みブロックを取得
	const std::vector<std::unique_ptr<WorldTransform>>& GetBlocks() const
	{
		return blocks_;
	}

	// 現在動いているブロックを取得
	const WorldTransform& GetMovingBlock() const
	{
		return worldTransform_;
	}

	float GetBlockWidth() const { return blockkWidth_; }
	float GetBlockHeight() const { return blockHeight_; }
	bool IsFalling() const { return isFalling_; }

private:
	KamataEngine::Model* model_ = nullptr;
	// カメラ
	Camera* camera_ = nullptr;

	// 今動いているブロック
	WorldTransform worldTransform_;
    ::Update* updatetransform_ = nullptr;
	// 積み上げたブロック
	std::vector<std::unique_ptr<WorldTransform>> blocks_;

	// 移動方向
	float moveDirection_ = 0.2f;

	// ブロックの横幅
	float blockkWidth_ = 2.0f;
	// ブロックの高さ
	float blockHeight_ = 2.0f;

	// 落下速度
	float fallSpeed_ = 0.2f;

	//////////////フラグ////////////
	// 停止しているか
	bool isStop_ = false;
	// 落下中か
	bool isFalling_ = false;

};
