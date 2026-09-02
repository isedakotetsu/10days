#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>
using namespace KamataEngine;

class bloc {
	// 高さ410
public:
	/// 初期化
	void Initialize(Model* model, Camera* camera);

	// 動き
	void Move();

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	KamataEngine::Model* model_ = nullptr;
	// カメラ
	Camera* camera_ = nullptr;

	// 今動いているブロック
	WorldTransform worldTransform_;
	// 積み上げたブロック
	std::vector<std::unique_ptr<WorldTransform>> blocks_;

	// 移動方向
	float moveDirection_ = 0.2f;
	// 停止しているか
	bool isStop_ = false;

	// ブロックの横幅
	float blockWidth_ = 4.0f;

	// 落下中か
	bool isFalling_ = false;

	// 落下速度
	float fallSpeed_ = 0.2f;


	// カメラの初期位置
	Vector3 cameraStartPosition_;
	//カメラ
	float cameraOffsetY_ = 0.0f;
	float cameraMoveY_ = 2.0f;

};