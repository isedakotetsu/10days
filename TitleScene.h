#pragma once
#include <KamataEngine.h>
#include "Fade.h"

using namespace KamataEngine;

class TitleScene 
{
public:
	enum class Phase 
	{
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	bool finished_ = false;

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;

	uint32_t textureHandle_;

	Sprite* sprite_ = nullptr;
};