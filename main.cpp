#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include "GameClear.h"
#include "GameOver.h"



TitleScene* titleScene = nullptr;
GameScene* gameScene = nullptr;
GameClear* gameClearScene = nullptr;
GameOver* gameOverScene = nullptr;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
	kGameOver,
	kGameClear,
};

// 現在シーン（型）
Scene scene = Scene::kTitle;
void ChangeScene() {

	switch (scene)
	{
	case Scene::kTitle:
		

		if (titleScene->IsFinished()) 
		{

			
			scene = Scene::kGame;

			

			delete titleScene;
			titleScene = nullptr;

			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;

	case Scene::kGame:
		
		if (gameScene->IsDead()) {
			scene = Scene::kGameOver;

			delete gameScene;
			gameScene = nullptr;

			gameOverScene = new GameOver;
			gameOverScene->Initialize();
		}

		break;

	case Scene::kGameOver:
		

		break;

	case Scene::kGameClear:
		

		break;
	}
}

void DrawScene() 
{
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kGameOver:
		gameOverScene->Draw();
		break;
	case Scene::kGameClear:
		gameClearScene->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// エンジン初期化
	Initialize(L"LE3D_02_イセダ_コテツ");
	// DirectX取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	titleScene = new TitleScene;
	titleScene->Initialize();

	// メインループ
	while (true) 
	{

		// エンジン更新（終了チェック）
		if (Update()) 
		{
			break;
		}
		// シーンごとにUpdate
		switch (scene) {
		case Scene::kTitle:
			titleScene->UpDate();
			break;
		case Scene::kGame:
			// ImGuiの開始処理
			gameScene->Update();

			break;
		case Scene::kGameOver:
			gameOverScene->UpDate();
			break;
		case Scene::kGameClear:
			gameClearScene->UpDate();
			break;
		}

		ChangeScene();

		// 描画開始
		dxCommon->PreDraw();

		DrawScene();

		// 描画終了
		dxCommon->PostDraw();
	}

	delete gameScene;
	gameScene = nullptr;

	// エンジン終了
	Finalize();

	return 0;
}