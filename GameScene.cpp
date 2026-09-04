#include "GameScene.h"
using namespace KamataEngine;

void GameScene::Initialize() 
{

    // プレイヤーモデルを読み込む
    playerModel_ = Model::CreateFromOBJ("player", true);

    // プレイヤーを生成
    player_ = new Player();

    // プレイヤーを初期化
    player_->Initialize(playerModel_);

    // カメラを初期化
    camera_.Initialize();

    // プレイヤーに近いカメラ位置
    camera_.translation_ = cameraOffset_;

    // カメラの向き
    camera_.rotation_ = 
    {
        0.0f,
        0.0f,
        0.0f
    };

    //デバックカメラ
    debugCamera_ = new DebugCamera(1280, 720);
	// モデル読み込み
	modelBlock_ = Model::CreateFromOBJ("cube");

	block_ = new block();
	block_->Initialize(modelBlock_, &camera_);
}

void GameScene::Update() 
{
    // 先にブロックを更新し、最新位置で衝突判定する
    block_->Update();

    // プレイヤーを更新してブロックとの衝突を解決
    player_->Update(block_);

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
        // プレイヤーの現在位置を取得
        const Vector3& playerPosition = player_->GetWorldPosition();

        // X方向は固定する。
        // Xまで完全追従すると、プレイヤーが止まってブロックが動くように見えるため。
        camera_.translation_.x = cameraOffset_.x;

        // 通常のジャンプ中はカメラを動かさない。
        // 高く積まれたブロックへ登ったときだけY方向へ追従する。
        if (playerPosition.y > kCameraFollowStartY)
        {
            camera_.translation_.y = playerPosition.y - kCameraPlayerScreenY;
        }
        else
        {
            camera_.translation_.y = cameraOffset_.y;
        }

        // Z方向は一定の距離を保つ
        camera_.translation_.z = playerPosition.z + cameraOffset_.z;

        //ビュープロジェクション行列の”更新”と転送
        camera_.UpdateMatrix();
    }

}

void GameScene::Draw()
{
    // 3Dモデルの描画開始
    Model::PreDraw();

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
    delete playerModel_;
    playerModel_ = nullptr;

    delete block_;
    block_ = nullptr;

    delete modelBlock_;
    modelBlock_ = nullptr;

    delete debugCamera_;
	debugCamera_ = nullptr;
}
