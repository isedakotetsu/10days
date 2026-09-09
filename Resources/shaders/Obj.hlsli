#pragma pack_matrix(row_major)

cbuffer WorldTransform : register(b0) {
	matrix world; // ワールド行列
	matrix worldInverseTranspose; // 逆転置行列
};

cbuffer ViewProjection : register(b1) {
	matrix view;       // ビュー変換行列
	matrix projection; // プロジェクション変換行列
	float3 cameraPos;  // カメラ座標（ワールド座標）
};

cbuffer Material : register(b2) {
	float3 m_ambient : packoffset(c0);   // アンビエント係数
	float3 m_diffuse : packoffset(c1);   // ディフューズ係数
	float3 m_specular : packoffset(c2);  // スペキュラー係数
	float m_alpha : packoffset(c2.w);    // アルファ
	float3 m_uv_scale : packoffset(c3);  // UVスケール
	float m_wrap : packoffset(c3.w);     // ラップ係数
	float3 m_uv_offset : packoffset(c4); // UVオフセット
}

// 平行光源の数
static const int DIRLIGHT_NUM = 3;

struct DirLight {
	float3 direction;  // ライトへの方向の単位ベクトル
	float3 color;      // ライトの色(RGB)
	uint active;
};

// 点光源の数
static const int POINTLIGHT_NUM = 3;

struct PointLight {
	float3 color;      // ライトの色(RGB)
	float intensity;   // 輝度
	float3 position;   // ライト座標
	float radius;      // ライトの届く最大距離
	float decay;       // 減衰率
	uint active;       // 有効フラグ
};

// スポットライトの数
static const int SPOTLIGHT_NUM = 3;

struct SpotLight {
	float3 color;      // ライトの色(RGB)
	float intensity;   // 輝度
	float3 position;   // ライト座標
	float radius;      // ライトの届く最大距離
	float3 direction;  // ライトの光線方向の逆ベクトル（単位ベクトル）
	float decay;       // 減衰率
	float2 cosAngle;   // ライト減衰角度のコサイン
	uint active;       // 有効フラグ
};

// 丸影の数
static const int CIRCLESHADOW_NUM = 3;

struct CircleShadow {
	float3 direction;          // 投影方向の逆ベクトル（単位ベクトル）
	float3 position;           // キャスター座標
	float distanceCasterLight; // キャスターとライトの距離
	float3 atten;              // 距離減衰係数
	float2 cosAngle;           // 減衰角度のコサイン
	uint active;
};

cbuffer LightGroup : register(b3) {
	float3 ambientColor;
	DirLight dirLights[DIRLIGHT_NUM];
	PointLight pointLights[POINTLIGHT_NUM];
	SpotLight spotLights[SPOTLIGHT_NUM];
	CircleShadow circleShadows[CIRCLESHADOW_NUM];
}

cbuffer ObjectColor : register(b4)
{
    float4 color; // オブジェクトのアルファ
}

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput {
	float4 svpos : SV_POSITION; // システム用頂点座標
	float4 worldpos : POSITION; // ワールド座標
	float3 normal : NORMAL;     // 法線
	float2 uv : TEXCOORD;       // uv値
};
