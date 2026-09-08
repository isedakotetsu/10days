#include "Score3D.h"

using namespace KamataEngine;

void Score3D::Initialize(Camera* camera) {

	camera_ = camera;

	// 0～9のモデルを読み込む
	for (int i = 0; i < 10; i++) {

		digitModels_[i] = Model::CreateFromOBJ("score/" + std::to_string(i));
	}
}

void Score3D::SetScore(int score) {

	digits_.clear();

	// 0の場合
	if (score == 0) {
		digits_.push_back(0);
		return;
	}

	// 下の桁から取り出す
	while (score > 0) {

		digits_.push_back(score % 10);

		score /= 10;
	}

	// 今は逆順なのでひっくり返す
	std::reverse(digits_.begin(), digits_.end());
}

void Score3D::Draw() {

	for (int i = 0; i < static_cast<int>(digits_.size()); i++) {

		WorldTransform worldTransform;
		worldTransform.Initialize();

		// 数字を横に並べる
		worldTransform.translation_ = {position_.x + i * digitSpacing_, position_.y, position_.z};

		worldTransform.TransferMatrix();

		digitModels_[digits_[i]]->Draw(worldTransform, *camera_);
	}
}