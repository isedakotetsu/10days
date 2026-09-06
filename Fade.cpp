#include "Fade.h"
#include <algorithm>

using namespace KamataEngine;

void Fade::Initialize() {
	// 02_13 10枚目
	sprite_ = Sprite::Create(0, Vector2{});

	sprite_->SetSize(Vector2(WinApp::kWindowWidth, WinApp::kWindowHeight));
	sprite_->SetColor(Vector4(0, 0, 0, 1));
}

void Fade::Update() {

	// 02_13 19枚目 フェード状態による分岐
	switch (status_) {
	case Status::None:

		break;
	case Status::FadeIn:
		// 02_13 21枚目

		// 1フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;
		// フェード継続時間に達したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		// 0.0fから1.0fの間で、経過時間がフェード継続時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(1.0f - counter_ / duration_, 0.0f, 1.0f)));

		break;
	case Status::FadeOut:
		// 02_13 20枚目

		// 1フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;
		// フェード継続時間に達したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		// 0.0fから1.0fの間で、経過時間がフェード継続時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;
	}
}

void Fade::Draw() {

	// 02_13 24枚目
	if (status_ == Status::None) {
		return;
	}

	// 02_13 11枚目
	Sprite::PreDraw(DirectXCommon::GetInstance()->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();
}

// 02_13 18枚目 フェード開始
void Fade::Start(Status status, float duration) {

	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

// 02_13 24枚目 フェード停止
void Fade::Stop() { status_ = Status::None; }

// 02_13 26枚目 フェード終了判定
bool Fade::IsFinished() const {

	// フェード状態による分岐
	switch (status_) {
	case Status::FadeIn:
	case Status::FadeOut:

		/*  if (counter_ >= duration_) {
			  //return true;
		  //}
		  //else {
			  //return false;
		  //}*/

		  // 1行バージョン 3項演算子
		return (counter_ >= duration_) ? true : false;
	}

	return true;
}