#include "Score3D.h"
#include <numbers>

using namespace KamataEngine;

void Score3D::Initialize(Model* model[10], Camera* camera) {
	camera_ = camera;

	// 5桁分の WorldTransform を事前に正しく初期化（定数バッファを生成）
	for (int i = 0; i < 5; i++) {
		digitTransforms_[i].Initialize();
	}

	for (int i = 0; i < 10; i++) {
		digitModels_[i] = model[i];
	}

	// 初期表示を 00000 に設定
	SetScore(0);
}

void Score3D::SetScore(int score) {
	digits_.clear();

	// 5桁固定で各桁の数値を格納
	digits_.push_back((score / 10000) % 10); // 万の桁
	digits_.push_back((score / 1000) % 10);  // 千の桁
	digits_.push_back((score / 100) % 10);   // 百の桁
	digits_.push_back((score / 10) % 10);    // 十の桁
	digits_.push_back(score % 10);           // 一の桁
}

void Score3D::Draw() {
	if (digits_.empty())
		return;

	// -------------------------------------------------------------
	// 5桁を右上に綺麗に並べる座標設定
	// -------------------------------------------------------------
	float offsetX = 7.0f;      // 画面右方向への距離
	float offsetY = 2.8f;      // 画面上方向への距離
	float distanceZ = 10.0f;   // カメラからの手前距離
	float digitSpacing = 0.5f; // 数字同士の横の間隔

	float totalWidth = static_cast<float>(digits_.size()) * digitSpacing;

	float startX = camera_->translation_.x + offsetX - totalWidth;
	float startY = camera_->translation_.y + offsetY;
	float startZ = camera_->translation_.z + distanceZ;

	for (int i = 0; i < static_cast<int>(digits_.size()); i++) {
		// メンバー変数の WorldTransform を安全に使用
		digitTransforms_[i].scale_ = {0.35f, 0.35f, 0.35f};
		digitTransforms_[i].rotation_.x = 0.0f;
		digitTransforms_[i].rotation_.y = std::numbers::pi_v<float>;
		digitTransforms_[i].rotation_.z = 0.0f;

		// 1桁ごとに X座標をずらしてセット
		digitTransforms_[i].translation_.x = startX + (static_cast<float>(i) * digitSpacing);
		digitTransforms_[i].translation_.y = startY;
		digitTransforms_[i].translation_.z = startZ;

		// 行列計算
		digitTransforms_[i].TransferMatrix();

		// 行列の並進成分を手動反転・反映
		digitTransforms_[i].matWorld_.m[3][0] = digitTransforms_[i].translation_.x;
		digitTransforms_[i].matWorld_.m[3][1] = digitTransforms_[i].translation_.y;
		digitTransforms_[i].matWorld_.m[3][2] = digitTransforms_[i].translation_.z;

		// 描画（各桁専用の WorldTransform を渡すことで重なりを防止）
		digitModels_[digits_[i]]->Draw(digitTransforms_[i], *camera_);
	}
}