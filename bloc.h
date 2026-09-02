#pragma once
#include "KamataEngine.h"
#include <vector>
#include <memory>
using namespace KamataEngine;

class bloc {
	// 高さ410
public:
	/// 初期化
	void Initialize(Model* model, Camera* camera);

	//動き
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
};
