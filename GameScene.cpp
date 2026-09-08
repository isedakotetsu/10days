#include "GameScene.h"
#include <cmath>

#include <Windows.h>
#include <string>



// 障害物＆プレイヤーの当たり判定処理
bool IsCollisionAABB(const KamataEngine::Vector3& posA, const KamataEngine::Vector3& sizeA, const KamataEngine::Vector3& posB, const KamataEngine::Vector3& sizeB)
{
	
	const float collisionMargin = 6.0f;

	if (std::abs(posA.x - posB.x) > sizeA.x + sizeB.x + collisionMargin) {
		return false;
	}

	if (std::abs(posA.y - posB.y) > sizeA.y + sizeB.y + collisionMargin) {
		return false;
	}

	if (std::abs(posA.z - posB.z) > sizeA.z + sizeB.z + collisionMargin) {
		return false;
	}

	return true;
}

void GameScene::Initialize() 
{
	model_ = Model::Create();
	// プレイヤーモデルを読み込む
	modelPlayer_ = Model::CreateFromOBJ("chicken", true);
	// プレイヤーを生成
	player_ = new Player();
	// プレイヤーを初期化
	player_->Initialize(modelPlayer_);

	// カメラを初期化
	camera_.Initialize();
	worldTransform_.Initialize();

	// プレイヤーに近いカメラ位置
	camera_.translation_ = {0.0f, 3.0f, -10.0f};

	// カメラの向き
	camera_.rotation_ = {0.0f, 0.0f, 0.0f};

	cameraStartY_ = camera_.translation_.y;

	// モデル読み込み
	modelBlock_ = Model::CreateFromOBJ("block");
	// ブロックを生成
	block_ = new block();
	// ブロックを初期化
	block_->Initialize(modelBlock_, &camera_);

	// 障害物の初期化
	obstacles_ = new obstacles();
	Obstaclesmodel_ = Model::CreateFromOBJ("cube");

	ObstaclesPosition_ = {0.0f, -70.0f, 0.0f};
	obstacles_->Initialize(Obstaclesmodel_, ObstaclesPosition_);



	// 3Dスコアを生成
	score3D_ = new Score3D();

	// スコア用の0～9のモデルを読み込む
	for (int i = 0; i < 10; i++) {
		number_[i] = Model::CreateFromOBJ(std::to_string(i));
	}

	// 10個全部読み込んだ「あと」に初期化
	score3D_->Initialize(number_, &camera_);

	//score3D_->SetPosition({5.0f, 5.0f, 0.0f});

	// 初期スコア
	score3D_->SetScore(score_);
	
	 // 背景の初期化
	uint32_t haikeiTextureHandle_ = TextureManager::Load("school.png");
	haikei_ = Sprite::Create(haikeiTextureHandle_, {0, 0});

	haikei_->SetSize({1280, 720});
	haikei_->SetPosition({0, 0});

	haikei2_ = Sprite::Create(haikeiTextureHandle_, {0, -720});

	haikei2_->SetSize({1280, 720});


	

}

void GameScene::Update() 
{
	


	
	  if (phase_ == Phase::kPlay)
	  {
		
		if (!isObstacleStopped_)
		{
			obstacles_->Update();
		}

		
		if (!isPlayerStopped_)
		{
			player_->Update(block_);
		}

		// プレイヤーと障害物の衝突判定
		if (IsCollisionAABB(player_->GetWorldPosition(),
			player_->GetHalfSize(), obstacles_->GetPosition(),
			obstacles_->GetHalfSize())) 
		{
			
			isObstacleStopped_ = true;
			isPlayerStopped_ = true;
		}
	}

	block_->Update(player_->GetWorldPosition());



	// 積み上がったブロック数を取得
	int currentBlockCount = static_cast<int>(block_->GetBlocks().size());

	// ブロックが1個増えた
	if (currentBlockCount > previousBlockCount_) {

		// コンボ増加
		combo_++;

		// スコア加算
		score_ += 100 * combo_;
		// 初期スコア
		score3D_->SetScore(score_);
		
		// ブロック数を更新
		previousBlockCount_ = currentBlockCount;

		// コンボ確認
		OutputDebugStringA(("Combo: " + std::to_string(combo_) + "  Score: " + std::to_string(score_) + "\n").c_str());
	}

	//コンボリセット
	if (block_->IsFalling()) {
		combo_ = 0;
	}

	 // 背景の位置をカメラの移動に合わせて更新
	float cameraMoveY = camera_.translation_.y - cameraStartY_;
	float scrollY = cameraMoveY;
	float backgroundY1 = scrollY;
	float backgroundY2 = scrollY - 720.0f;

	if (backgroundY1 >= 720.0f) {
		backgroundY1 -= 1440.0f;
	}

	if (backgroundY2 >= 720.0f) {
		backgroundY2 -= 1440.0f;
	}

	haikei_->SetPosition({0.0f, backgroundY1});
	haikei2_->SetPosition({0.0f, backgroundY2});

	

	// 変更したカメラ位置と向きを反映
	camera_.UpdateMatrix();
}

void GameScene::Draw() 
{

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw();
	haikei_->Draw();
	haikei2_->Draw();
	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	// 3Dモデルの描画開始
	Model::PreDraw();

	// 障害物を描画
	obstacles_->Draw(camera_);
	// プレイヤーを描画
	player_->Draw(camera_);

	block_->Draw();

	// スコア
	score3D_->Draw();

	// 3Dモデルの描画終了
	Model::PostDraw();
}

GameScene::~GameScene() {
	// プレイヤーを解放
	delete player_;
	player_ = nullptr;

	// プレイヤーモデルを解放
	delete modelPlayer_;
	modelPlayer_ = nullptr;

	delete block_;
	block_ = nullptr;
	delete score3D_;
	for (int i = 0; i < 10; i++) {
		delete number_[i];
	}
	delete modelBlock_;
	modelBlock_ = nullptr;
}
