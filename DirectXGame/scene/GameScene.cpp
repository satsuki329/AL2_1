#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MathUtilityForText.h"

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	delete spriteBG_;
	delete modelstage;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureBG = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureBG, {0, 0});

	viewProjection_.Initialize();
	texturestage = TextureManager::Load("stage.jpg");
	modelstage = Model::Create();
	worldTranceformstage_.Initialize();

	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	worldTranceformstage_.translation_ = {0, -1.5f, 0};
	worldTranceformstage_.scale_ = {4.5f, 1, 40};

	worldTranceformstage_.matWorld_ = MakeAffineMatrix(
	    worldTranceformstage_.scale_, 
		worldTranceformstage_.rotation_,
	    worldTranceformstage_.translation_);

	worldTranceformstage_.TransferMatrix();
}

void GameScene::Update() {}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	spriteBG_->Draw();
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	modelstage->Draw(worldTranceformstage_, viewProjection_, texturestage);
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
