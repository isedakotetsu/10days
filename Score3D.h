#pragma once
#include "KamataEngine.h"
#include <memory>
#include <vector>

class Score3D {
public:
	void Initialize(KamataEngine::Camera* camera);

	void SetScore(int score);

	void Draw();

private:
	KamataEngine::Camera* camera_ = nullptr;

	// 0～9のモデル
	KamataEngine::Model* digitModels_[10]{};

	// 表示する数字
	std::vector<int> digits_;

	// スコアを表示する位置
	KamataEngine::Vector3 position_ = {-3.0f, 3.0f, 0.0f};

	// 数字同士の間隔
	float digitSpacing_ = 1.0f;
};
