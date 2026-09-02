#pragma once
#include <KamataEngine.h>
#include "Fade.h"

using namespace KamataEngine;

class TitleScene {
public:

	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	~TitleScene();

	void Initialize();


	void UpDate();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	bool finished_ = false;

	// 02_13 12枚目
	Fade* fade_ = nullptr;

	//現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	uint32_t textureHandle_;

	Sprite* sprite_ = nullptr;
};