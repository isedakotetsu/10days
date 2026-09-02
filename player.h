#pragma once
#include <KamataEngine.h>

class Player
{
public:
    // 初期化
    void Initialize(KamataEngine::Model* model);

    // 更新
    void Update();

    // 描画
    void Draw(const KamataEngine::Camera& camera);

private:
    // プレイヤーモデル
    KamataEngine::Model* model_ = nullptr;

    // 座標・回転・大きさ
    KamataEngine::WorldTransform worldTransform_;

    // 入力
    KamataEngine::Input* input_ = nullptr;

    // 左右の移動速度
    static inline const float kMoveSpeed = 0.1f;

    // ジャンプ開始時の上昇速度
    static inline const float kJumpPower = 0.25f;

    // 重力
    static inline const float kGravity = 0.015f;

    // Y方向の速度
    float velocityY_ = 0.0f;

    // 地面に着いているか
    bool isOnGround_ = true;

    // 地面の高さ
    static inline const float kGroundY = 0.0f;
};