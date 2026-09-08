#pragma once

#include "KamataEngine.h"
#include <algorithm>
#include <vector>

class Score3D {

public:
	// 初期化
	void Initialize(
		KamataEngine::Model* model[10],
		KamataEngine::Camera* camera
	);

	// スコア設定
	void SetScore(int score);

	// 表示位置設定
	void SetPosition(const KamataEngine::Vector3& position) {
		position_ = position;
	}

	// 描画
	void Draw();

private:
	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// 数字モデルを表示するためのWorldTransform
	KamataEngine::WorldTransform worldTransform_;

	// 0～9の数字モデル
	KamataEngine::Model* digitModels_[10] = {};

	// スコアの各桁
	std::vector<int> digits_;

	// スコアの表示位置
	KamataEngine::Vector3 position_ = {0.0f, 0.0f, 0.0f};

	// 数字同士の間隔
	float digitSpacing_ = 5.0f;

	// 修正: 5桁分それぞれの WorldTransform をメンバー変数として保持する
	KamataEngine::WorldTransform digitTransforms_[5];
};