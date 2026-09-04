#include "GameScene.h"
#include <cmath>

using namespace KamataEngine;

//障害物＆プレイヤーの当たり判定処理
bool IsCollisionAABB(const KamataEngine::Vector3& posA, const KamataEngine::Vector3& sizeA, const KamataEngine::Vector3& posB, const KamataEngine::Vector3& sizeB) 
{
	if (std::abs(posA.x - posB.x) > sizeA.x + sizeB.x) 
    {
		return false;
	}

	if (std::abs(posA.y - posB.y) > sizeA.y + sizeB.y) 
    {
		return false;
	}

	if (std::abs(posA.z - posB.z) > sizeA.z + sizeB.z)
    {
		return false;
	}

	return true;
}

void GameScene::Initialize() 
{
	model_ = Model::Create();
	worldTransform_.Initialize();
	camera_.Initialize();
   

    // プレイヤーを生成
    player_ = new Player();
	// プレイヤーモデルを読み込む
	playerModel_ = Model::CreateFromOBJ("player", true);
	
    // プレイヤーを初期化
    player_->Initialize(playerModel_);

    // カメラを初期化
    camera_.Initialize();

    // カメラの位置
    camera_.translation_ = 
    {
        0.0f,
        3.0f,
        -10.0f
    };


    // カメラの向き
    camera_.rotation_ = 
    {
        0.0f,
        0.0f,
        0.0f
    };

    cameraStartY_ = camera_.translation_.y;

    //デバックカメラ
    debugCamera_ = new DebugCamera(1280, 720);
	// 障害物の初期化
	obstacles_ = new obstacles();
	Obstaclesmodel_ = Model::CreateFromOBJ("cube");

	ObstaclesPosition_ = {0.0f, -70.0f, 0.0f};
	obstacles_->Initialize(Obstaclesmodel_, ObstaclesPosition_);

	// モデル読み込み
	modelBloc_ = Model::CreateFromOBJ("cube");

	bloc_ = new bloc();
	bloc_->Initialize(modelBloc_, &camera_);

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
	// ゲームプレイ中だけ更新
	if (phase_ == Phase::kPlay) 
    {
		
		obstacles_->UpDate();
		player_->Update();
        bloc_->Update();
	

		if (IsCollisionAABB(player_->GetPosition(), player_->GetHalfSize(),
            obstacles_->GetPosition(), obstacles_->GetHalfSize()))
        {
			
			phase_ = Phase::kDeath;
		}
	}

    // カメラを更新
    camera_.UpdateMatrix();

   // 背景の位置をカメラの移動に合わせて更新
	float cameraMoveY = camera_.translation_.y - cameraStartY_;
	float scrollY = cameraMoveY;
	float backgroundY1 = scrollY;
	float backgroundY2 = scrollY - 720.0f;

	
	if (backgroundY1 >= 720.0f) 
    {
		backgroundY1 -= 1440.0f;
	}

	if (backgroundY2 >= 720.0f) 
    {
		backgroundY2 -= 1440.0f;
	}

	haikei_->SetPosition({0.0f, backgroundY1});
	haikei2_->SetPosition({0.0f, backgroundY2});

    //デバックカメラの更新
    debugCamera_->Update();
#ifdef _DEBUG
    if (Input::GetInstance()->TriggerKey(DIK_0))
    {
        isDebugCameraActive_ = !isDebugCameraActive_;
    }
#endif // _DEBUG

    //カメラの処理
    if (isDebugCameraActive_)
    {
        //デバックカメラの更新
        debugCamera_->Update();
        //デバックカメラのビュー行列
        camera_.matView = debugCamera_->GetCamera().matView;
        //デバックカメラのプロジェクション行列
        camera_.matProjection = debugCamera_->GetCamera().matProjection;
        //ビュープロジェクション行列と転送
        camera_.TransferMatrix();
    } 
    else
    {
        //ビュープロジェクション行列の”更新”と転送
        camera_.UpdateMatrix();
    }

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
    bloc_->Draw();
    
    

    // 3Dモデルの描画終了
    Model::PostDraw();

   
}

GameScene::~GameScene()
{
    // プレイヤーを解放
    delete player_;
    player_ = nullptr;

    // プレイヤーモデルを解放
    delete playerModel_;
    playerModel_ = nullptr;

    delete debugCamera_;
    Obstaclesmodel_ = nullptr;
}
