#include "GameOver.h"

using namespace KamataEngine;

GameOver::~GameOver() 
{
	delete fade_;
	
	
}

void GameOver::Initialize() 
{

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	textureHandle_ = TextureManager::Load("backGround/backGround3.png");

	sprite_ = Sprite::Create(textureHandle_, {0, 0});

	sprite_->SetSize({1280, 720});
}

void GameOver::UpDate() 
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		fade_->Update();

		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kMain:

		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kFadeOut;
		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
}




void GameOver::Draw() 
{ 
Sprite::PreDraw();

	if (sprite_) {
		sprite_->Draw();
	}

	Sprite::PostDraw();

	fade_->Draw();
}