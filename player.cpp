#include "Player.h"

using namespace KamataEngine;


void Player::Initialize(Model* model)
{
    // GameSceneからモデルを受け取る
    model_ = model;

    // キーボード入力を取得
    input_ = Input::GetInstance();

    // ワールドトランスフォームを初期化
    worldTransform_.Initialize();

    // プレイヤーの大きさ
    worldTransform_.scale_ = 
    {
        1.0f,
        1.0f,
        1.0f
    };

    // X=0で左右中央
    // Y=0で地面に配置
    worldTransform_.translation_ = 
    {
        0.0f,
        0.0f,
        0.0f
    };

    // Y軸方向に180度回転
    worldTransform_.rotation_ = 
    {
        0.0f,
        3.141592f,
        0.0f
    };

    // 座標をワールド行列へ設定
    worldTransform_.matWorld_.m[3][0] =
        worldTransform_.translation_.x;

    worldTransform_.matWorld_.m[3][1] =
        worldTransform_.translation_.y;

    worldTransform_.matWorld_.m[3][2] =
        worldTransform_.translation_.z;

    // Y軸方向に180度回転
    worldTransform_.matWorld_.m[0][0] = -1.0f;
    worldTransform_.matWorld_.m[0][2] = 0.0f;

    worldTransform_.matWorld_.m[2][0] = 0.0f;
    worldTransform_.matWorld_.m[2][2] = -1.0f;


    // GPUへ送る
    worldTransform_.TransferMatrix();
    
}

void Player::Update()
{
    // Aキーで左へ移動
    if (input_->PushKey(DIK_A))
    {
        worldTransform_.translation_.x -= kMoveSpeed;
    }

    // Dキーで右へ移動
    if (input_->PushKey(DIK_D))
    {
        worldTransform_.translation_.x += kMoveSpeed;
    }

    // 地面にいるとき、スペースキーでジャンプ
    if (isOnGround_ && input_->TriggerKey(DIK_SPACE))
    {
        velocityY_ = kJumpPower;
        isOnGround_ = false;
    }

    // 空中にいる間の処理
    if (!isOnGround_)
    {
        // Y方向の速度を座標へ加算
        worldTransform_.translation_.y += velocityY_;

        // 重力で下降速度を増やす
        velocityY_ -= kGravity;

        // 地面より下へ落ちないようにする
        if (worldTransform_.translation_.y <= kGroundY)
        {
            worldTransform_.translation_.y = kGroundY;
            velocityY_ = 0.0f;
            isOnGround_ = true;
        }
    }

    // 座標をワールド行列へ設定
    worldTransform_.matWorld_.m[3][0] =
        worldTransform_.translation_.x;

    worldTransform_.matWorld_.m[3][1] =
        worldTransform_.translation_.y;

    worldTransform_.matWorld_.m[3][2] =
        worldTransform_.translation_.z;

    // Y軸方向に180度回転
    worldTransform_.matWorld_.m[0][0] = -1.0f;
    worldTransform_.matWorld_.m[0][2] = 0.0f;

    worldTransform_.matWorld_.m[2][0] = 0.0f;
    worldTransform_.matWorld_.m[2][2] = -1.0f;


    // 更新した行列をGPUへ送る
    worldTransform_.TransferMatrix();
}

void Player::Draw(const Camera& camera)
{
    // プレイヤーを描画
    model_->Draw(worldTransform_, camera);
}