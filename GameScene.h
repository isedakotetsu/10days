#pragma once
#include "Player.h"
#include "block.h"
#include <KamataEngine.h>
#include "Player.h"
#include "block.h"
#include "obstacles.h"

using namespace KamataEngine;
class GameScene
{
public:

    ~GameScene();

    void Initialize();

	void Update();

	void Draw();

    bool IsFinished() const { return phase_ == Phase::kFadeOut || phase_ == Phase::kClear; }
    // 追加: 死亡したかどうかを判定する関数（main.cppで使用）
    bool IsDead() const { return phase_ == Phase::kDeath; }
    // クリアしたことを感知する関数
    bool IsClear() const { return phase_ == Phase::kClear; }

private:
    // プレイヤー
    Player* player_ = nullptr;
   
    block* block_ = nullptr;

    KamataEngine::Model* model_ = nullptr;

    KamataEngine::Model* modelBlock_ = nullptr;

    KamataEngine::Model* modelPlayer_ = nullptr;

    KamataEngine::Camera camera_;

    //デバックカメラ有効
	// ワールドトランスフォーム
    // この高さを超えたら、積み上げたブロックに合わせてカメラを上げる
    static inline const float kCameraFollowStartY = 4.0f;

    // 追従中、プレイヤーを画面中央より少し上に表示する値
    static inline const float kCameraPlayerScreenY = 1.0f;

    obstacles* obstacles_ = nullptr;
    KamataEngine::WorldTransform worldTransform_;
    KamataEngine::Model* Obstaclesmodel_ = nullptr;
    KamataEngine::Vector3 ObstaclesPosition_;

    // コンボ
    int combo_ = 0;

    // スコア
    int score_ = 0;

    // 前回のブロック数
    int previousBlockCount_ = 0;

    enum class Phase {
        kFadeIn,
        kPlay,
        kDeath,
        kFadeOut,
        kClear,
    };
    Phase phase_ = Phase::kPlay;


    // 背景
    float cameraStartY_ = 0.0f;
    KamataEngine::Sprite* haikei_ = nullptr;
    KamataEngine::Sprite* haikei2_ = nullptr;

    // playerとobstacleの衝突判定用のフラグ
    bool isObstacleStopped_ = false;
    bool isPlayerStopped_ = false;

    // ゲームシーンBGM
    uint32_t bgmHandle_ = 0;
    uint32_t voiceHandle_ = 0;
};
