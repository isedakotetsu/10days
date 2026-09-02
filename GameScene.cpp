#include "GameScene.h"
using namespace KamataEngine;
GameScene::~GameScene() {}

void GameScene::Initialize() 
{

    // ワールドトランスフォーム
    worldTransform_.Initialize();

    // プレイヤーモデルを読み込む
    playerModel_ = Model::CreateFromOBJ("player", true);

    // プレイヤーを生成
    player_ = new Player();

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

    //デバックカメラ
    debugCamera_ = new DebugCamera(1280, 720);
	// カメラを固定
	camera_.translation_ = {0.0f, 0.0f, -50.0f};

	camera_.rotation_ = {0.0f, 0.0f, 0.0f};

	// デバックカメラ
	debugCamera = new DebugCamera(1280, 720);

	// モデル読み込み
	modelBloc_ = Model::CreateFromOBJ("cube");

	bloc_ = new bloc();
	bloc_->Initialize(modelBloc_, &camera_);
}

void GameScene::Update() 
{
    // プレイヤーを更新
    player_->Update();

    bloc_->Update();

    // カメラを更新
    camera_.UpdateMatrix();

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
    // 3Dモデルの描画開始
    Model::PreDraw();

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
}
