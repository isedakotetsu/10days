#pragma pack_matrix(row_major)

struct SpriteData {
	matrix mat;                  // ３Ｄ変換行列
	float2 uvOffset;             // UVオフセット
	float2 uvScale;              // UVスケール
	float4 color;                // 色(RGBA)
	uint textureDescriptorIndex; // デスクリプタインデックス
};

StructuredBuffer<SpriteData> gSpriteData : register(t0);

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput {
	float4 svpos : SV_POSITION; // システム用頂点座標
	float2 uv : TEXCOORD;       // uv値
	float4 color : COLOR;       // 色(RGBA)
	nointerpolation uint textureDescriptorIndex : TEXTURE_INDEX; // デスクリプタインデックス
};
