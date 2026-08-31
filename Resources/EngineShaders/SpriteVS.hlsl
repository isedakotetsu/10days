#include "Sprite.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD, uint instanceID : SV_InstanceID) {
	VSOutput output;
	output.svpos = mul(pos, gSpriteData[instanceID].mat);
	output.uv = uv * gSpriteData[instanceID].uvScale + gSpriteData[instanceID].uvOffset;
	output.color = gSpriteData[instanceID].color;
	output.textureDescriptorIndex = gSpriteData[instanceID].textureDescriptorIndex;
	return output;
}