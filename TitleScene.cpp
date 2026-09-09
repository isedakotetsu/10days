#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::~TitleScene() 
{
	if (voiceHandle_ != 0)
	{
		Audio::GetInstance()->StopWave(voiceHandle_);
		voiceHandle_ = 0;
	}

	delete fade_;
	delete sprite_;
}

void TitleScene::Initialize() 
{
	// タイトルBGMをループ再生
	bgmHandle_ = Audio::GetInstance()->LoadWave("sound/titleBGM.mp3");
	voiceHandle_ = Audio::GetInstance()->PlayWave(bgmHandle_, true, 0.15f);

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	textureHandle_ = TextureManager::Load("backGround/title.png");

	sprite_ = Sprite::Create(textureHandle_, { 0,0 });
	sprite_->SetSize({ 1280,720 });
}

void TitleScene::Update() 
{
	switch (phase_) 
	{
	case Phase::kFadeIn:
		fade_->Update();

		if (fade_->IsFinished()) 
		{
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kMain:
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) 
		{
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kFadeOut;
		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			// ゲームシーンへ切り替わる前にタイトルBGMを停止
			Audio::GetInstance()->StopWave(voiceHandle_);
			voiceHandle_ = 0;

			finished_ = true;
		}
		break;
	}
}

void TitleScene::Draw() 
{
	Sprite::PreDraw();
	
	if (sprite_) 
	{
		sprite_->Draw();
	}

	Sprite::PostDraw();

	fade_->Draw();
}
