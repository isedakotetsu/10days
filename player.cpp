#include "Player.h"
#include "block.h"

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
        0.635770f,
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

void Player::Update(const block* blockObject)
{
    // 衝突判定前の座標を保存
    Vector3 previousPosition = worldTransform_.translation_;

    // スタン時間を減らす
    if (stunTimer_ > 0.0f)
    {
        stunTimer_ -= 1.0f / 60.0f;

        // スタン中はその場で完全に停止する
        if (stunTimer_ > 0.0f)
        {
            return;
        }
    }

    // スタンしていない間だけ操作できる
    if (stunTimer_ <= 0.0f)
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
    }

    // 空中にいる間の処理
    if (!isOnGround_)
    {
        // Y方向の速度を座標へ加算
        worldTransform_.translation_.y += velocityY_;

        // 重力で下降速度を増やす
        velocityY_ -= kGravity;

    }

    // このフレームで地面またはブロックに接地したかを調べ直す
    isOnGround_ = false;

    if (blockObject != nullptr)
    {
        // 積み上げ済みブロックとの当たり判定
        for (const auto& blockWorldTransform : blockObject->GetBlocks())
        {
            ResolveBlockCollision(
                *blockWorldTransform,
                blockObject->GetBlockWidth(),
                blockObject->GetBlockHeight(),
                previousPosition);
        }

        // 現在左右に動いているブロックとの当たり判定
        if (!blockObject->IsFalling())
        {
            ResolveBlockCollision(
                blockObject->GetMovingBlock(),
                blockObject->GetBlockWidth(),
                blockObject->GetBlockHeight(),
                previousPosition);
        }
    }

    // 地面より下へ落ちないようにする
    if (worldTransform_.translation_.y <= kGroundY)
    {
        worldTransform_.translation_.y = kGroundY;
        velocityY_ = 0.0f;
        isOnGround_ = true;
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

void Player::ResolveBlockCollision(
    const WorldTransform& blockWorldTransform,
    float blockWidth,
    float blockHeight,
    const Vector3& previousPosition)
{
    // スタン中はブロックとの当たり判定を行わない
    if (stunTimer_ > 0.0f)
    {
        return;
    }

    const float blockHalfWidth = blockWidth / 2.0f;
    const float blockHalfHeight = blockHeight / 2.0f;

    const float blockLeft =
        blockWorldTransform.translation_.x - blockHalfWidth;
    const float blockRight =
        blockWorldTransform.translation_.x + blockHalfWidth;
    const float blockBottom =
        blockWorldTransform.translation_.y - blockHalfHeight;
    const float blockTop =
        blockWorldTransform.translation_.y + blockHalfHeight;

    float playerLeft =
        worldTransform_.translation_.x - kPlayerHalfWidth;
    float playerRight =
        worldTransform_.translation_.x + kPlayerHalfWidth;
    float playerBottom = worldTransform_.translation_.y - 0.635770f;
    float playerTop = playerBottom + kPlayerHeight;

    const bool overlapsX =
        playerRight > blockLeft && playerLeft < blockRight;

    // ブロックの上にちょうど立っている状態も接地として扱う
    constexpr float kContactTolerance = 0.05f;
    if (overlapsX &&
        playerBottom >= blockTop - kContactTolerance &&
        playerBottom <= blockTop + kContactTolerance &&
        velocityY_ <= 0.0f)
    {
        worldTransform_.translation_.y = blockTop + 0.635770f;
        velocityY_ = 0.0f;
        isOnGround_ = true;
        return;
    }

    const bool overlapsY =
        playerTop > blockBottom && playerBottom < blockTop;

    if (!overlapsX || !overlapsY)
    {
        return;
    }

    const float previousBottom = previousPosition.y - 0.635770f;
    const float previousTop = previousBottom + kPlayerHeight;

    // 上から着地
    // 前のフレームで足元がブロック上面以上にあった場合だけ着地させる
    if (previousBottom >= blockTop - kContactTolerance &&
        velocityY_ <= 0.0f)
    {
        worldTransform_.translation_.y = blockTop + 0.635770f;
        velocityY_ = 0.0f;
        isOnGround_ = true;
        return;
    }

    // 下からぶつかった場合
    if (previousTop <= blockBottom + kContactTolerance && velocityY_ > 0.0f)
    {
        worldTransform_.translation_.y = blockBottom - (kPlayerHeight - 0.635770f);
        velocityY_ = 0.0f;
        return;
    }

    // 左右からぶつかった場合は1.5秒間スタン
    if (stunTimer_ <= 0.0f)
    {
        stunTimer_ = 1.5f;
    }

    // X座標を補正しないことでブロックをすり抜けさせる
    return;
}

void Player::Draw(const Camera& camera)
{
    // スタン中は表示と非表示を交互に切り替える
    if (stunTimer_ <= 0.0f || static_cast<int>(stunTimer_ * 10.0f) % 2 == 0)
    {
        model_->Draw(worldTransform_, camera);
    }
}
