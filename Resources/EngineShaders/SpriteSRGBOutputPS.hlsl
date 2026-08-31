#include "Sprite.hlsli"

SamplerState smp : register(s0);

float3 ApplySRGBGamma(float3 linearColor)
{
    return select(linearColor < 0.0031308, 12.92 * linearColor, 1.055 * pow(abs(linearColor), 1.0 / 2.4) - 0.055);
}

float4 main(VSOutput input) : SV_TARGET {
    Texture2D tex = ResourceDescriptorHeap[input.textureDescriptorIndex];
    float4 output = tex.Sample(smp, input.uv) * input.color;
    output.rgb = ApplySRGBGamma(output.rgb);
    return output;
}