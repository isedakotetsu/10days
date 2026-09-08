#include "GameScene.h"
#include <cmath>
#include <Windows.h>
#include <string>

using namespace KamataEngine;

// 障害物＆プレイヤーの当たり判定処理
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
    // プレイヤーモデルを読み込む
    modelPlayer_ = Model::CreateFromOBJ("player", true);
    // プレイヤーを生成
    player_ = new Player();
    // プレイヤーを初期化
    player_->Initialize(modelPlayer_);

    // カメラを初期化
    camera_.Initialize();

    // プレイヤーに近いカメラ位置
    camera_.translation_ = { 0.0f, 3.0f, -10.0f };

    // カメラの向き
    camera_.rotation_ = 
    {
        0.0f,
        0.0f,
        0.0f
    };

	// モデル読み込み
	modelBlock_ = Model::CreateFromOBJ("block");
    //ブロックを生成
	block_ = new block();
    //ブロックを初期化
	block_->Initialize(modelBlock_, &camera_);

    // 障害物の初期化
    obstacles_ = new obstacles();
    Obstaclesmodel_ = Model::CreateFromOBJ("cube");

    ObstaclesPosition_ = { 0.0f, -70.0f, 0.0f };
    obstacles_->Initialize(Obstaclesmodel_, ObstaclesPosition_);

    // 背景の初期化
    uint32_t haikeiTextureHandle_ = TextureManager::Load("school.png");
    haikei_ = Sprite::Create(haikeiTextureHandle_, { 0, 0 });

    haikei_->SetSize({ 1280, 720 });
    haikei_->SetPosition({ 0, 0 });

    haikei2_ = Sprite::Create(haikeiTextureHandle_, { 0, -720 });
    haikei2_->SetSize({ 1280, 720 });
}

void GameScene::Update() 
{
    // ゲームプレイ中だけ更新
    if (phase_ == Phase::kPlay)
    {

        obstacles_->Update();
        // プレイヤーを更新してブロックとの衝突を解決
        player_->Update(block_);

        if (IsCollisionAABB(player_->GetWorldPosition(), player_->GetHalfSize(), obstacles_->GetPosition(), obstacles_->GetHalfSize()))
        {

            phase_ = Phase::kDeath;
        }
    }

    // 前のフレームでプレイヤーが着地していればブロックを固定する
    block_->Update(player_->GetWorldPosition());


    // 積み上がったブロック数を取得
    int currentBlockCount = static_cast<int>(block_->GetBlocks().size());

    // ブロックが1個増えた
    if (currentBlockCount > previousBlockCount_) 
    {

        // コンボ増加
        combo_++;

        // スコア加算
        score_ += 100 * combo_;

        // ブロック数を更新
        previousBlockCount_ = currentBlockCount;

        // コンボ確認
        OutputDebugStringA(("Combo: " + std::to_string(combo_) + "  Score: " + std::to_string(score_) + "\n").c_str());
    }

    //コンボリセット
    if (block_->IsFalling()) 
    {
        combo_ = 0;
    }

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


    haikei_->SetPosition({ 0.0f, backgroundY1 });
    haikei2_->SetPosition({ 0.0f, backgroundY2 });



    // 変更したカメラ位置と向きを反映
    camera_.UpdateMatrix();
}

void GameScene::Draw()
{
    Sprite::PreDraw();
    haikei_->Draw();
    haikei2_->Draw();
    Sprite::PostDraw();

  /*  dxCommon->ClearDepthBuffer();*/

    // 3Dモデルの描画開始
    Model::PreDraw();

    // 障害物を描画
    obstacles_->Draw(camera_);
    // プレイヤーを描画
    player_->Draw(camera_);

    block_->Draw();

    // 3Dモデルの描画終了
    Model::PostDraw();
}

GameScene::~GameScene()
{
    // プレイヤーを解放
    delete player_;
    player_ = nullptr;

    // プレイヤーモデルを解放
    delete modelPlayer_;
    modelPlayer_ = nullptr;

    delete block_;
    block_ = nullptr;

    delete modelBlock_;
    modelBlock_ = nullptr;
}
