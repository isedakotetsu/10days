#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"

TitleScene* titleScene = nullptr;
GameScene* gameScene = nullptr;

enum class Scene 
{
	kUnknown = 0,
	kTitle,
	kGame,
};

// 現在シーン（型）
Scene scene = Scene::kTitle;
void ChangeScene() 
{
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
	/*	if (gameScene->IsDead()) 
		{
			scene = Scene::kGameOver;

			delete gameScene;
			gameScene = nullptr;

			gameOverScene = new GameOver;
			gameOverScene->Initialize();
		}*/
		break;
	}
}

void DrawScene() 
{
	switch (scene) 
	{
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// エンジン初期化
	Initialize(L"3062");
	// DirectX取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	titleScene = new TitleScene;
	titleScene->Initialize();

	// メインループ
	while (true) 
	{

		// エンジン更新（終了チェック）
		if (KamataEngine::Update()) 
		{
			break;
		}
		// シーンごとにUpdate
		switch (scene) 
		{
		case Scene::kTitle:
			titleScene->Update();
			break;
		case Scene::kGame:
			// ImGuiの開始処理
			gameScene->Update();

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