#include "GameScene.h"
#include "KamataEngine.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// エンジン初期化
	Initialize(L"LE3D_02_イセダ_コテツ");
	// DirectX取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// シーン生成
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Initialize();

	// メインループ
	while (true) {

		// エンジン更新（終了チェック）
		if (Update()) {
			break;
		}

		// シーン更新
		gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// シーン描画
		gameScene->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	delete gameScene;
	gameScene = nullptr;

	// エンジン終了
	Finalize();

	return 0;
}