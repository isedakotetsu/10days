#pragma once
#include <KamataEngine.h>
#include "Fade.h"

using namespace KamataEngine;

class GameClear {
public:

	// 02_12 27枚目 シーンのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	void Initialize();

	void UpDate();

	void Draw();

	~GameClear();

	bool IsFinished() const { return finished_; }

private:

	// 02_12 26枚目
	bool finished_ = false;

	// 02_13 12枚目
	Fade* fade_ = nullptr;

	// 02_13 27枚目 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;
};
