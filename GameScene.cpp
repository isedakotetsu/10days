#include "GameScene.h"

void GameScene::Initialize() 
{
	model_ = Model::Create();
	worldTransform_.Initialize();
	camera_.Initialize();
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
	// 障害物の初期化
	obstacles_ = new obstacles();
	Obstaclesmodel_ = Model::CreateFromOBJ("cube");

	ObstaclesPosition_ = {0.0f, -70.0f, 40.0f};
	obstacles_->Initialize(Obstaclesmodel_, ObstaclesPosition_);
}

void GameScene::Update() 
{
    // プレイヤーを更新
    player_->Update();
    obstacles_->UpDate();

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
    
    // 障害物を描画
    obstacles_->Draw(camera_);

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
