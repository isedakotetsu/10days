#pragma once
#include "KamataEngine.h"


/// <summary>
/// フェード
/// </summary>
class Fade {

public:
	// 02_13 16枚目 フェードの状態
	enum class Status {
		None,    // フェードなし
		FadeIn,  // フェードイン中
		FadeOut, // フェードアウト中
	};

	void Initialize();
	void Update();
	void Draw();

	// 02_13 18枚目 フェード開始
	void Start(Status status, float duration);

	// 02_13 24枚目 フェード停止
	void Stop();

	// 02_13 26枚目 フェード終了判定
	bool IsFinished() const;

private:
	KamataEngine::Sprite* sprite_ = nullptr;

	// 02_13 16枚目 現在のフェードの状態
	Status status_ = Status::None;

	// 02_13 17枚目 フェードの持続時間
	float duration_ = 0.0f;
	// 02_13 17枚目 経過時間カウンター
	float counter_ = 0.0f;
};
