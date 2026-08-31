#include "Sprite.hlsli"

SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET { 
    Texture2D tex = ResourceDescriptorHeap[input.textureDescriptorIndex];
    return tex.Sample(smp, input.uv) * input.color;
}