/////////////
// GLOBALS //
/////////////
Texture2D grassDiffuseTexture : register(t0);
Texture2D slopeDiffuseTexture : register(t1);

Texture2D grassNormalTexture : register(t3);
Texture2D slopeNormalTexture : register(t4);
Texture2D snowNormalTexture  : register(t5);

SamplerState SampleType;


//////////////////////
// CONSTANT BUFFERS //
//////////////////////
cbuffer LightBuffer
{
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float4 color : COLOR;
};

float4 getMaterial(PixelInputType input, float4 textureColor, float4 bumpMap, float3 lightDir)
{
	float3 bumpNormal;
	float lightIntensity;
	float4 material;

	bumpMap = (bumpMap * 2.0f) - 1.0f;
	bumpNormal = (bumpMap.x * input.tangent) + (bumpMap.y * input.binormal) + (bumpMap.z * input.normal);
	bumpNormal = normalize(bumpNormal);
	lightIntensity = saturate(dot(bumpNormal, lightDir));
	return material = saturate(textureColor * lightIntensity);
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TerrainPixelShader(PixelInputType input) : SV_TARGET
{
	float4 grassColor;
	float4 slopeColor;
	float4 snowColor;

	float4 grassBumpMap;
	float4 slopeBumpMap;
	float4 snowBumpMap;

	float4 textureColor;
	float4 color;

	float4 bumpMap;
	float3 bumpNormal;

	float3 lightDir;
	float lightIntensity;

	float slope;
	float blendAmount;

	float4 grassMaterial;
	float4 slopeMaterial;
	float4 snowMaterial;

	// Sample the grass color from the texture using the sampler at this texture coordinate location.
	grassColor = grassDiffuseTexture.Sample(SampleType, input.tex);

	// Sample the slope color from the texture using the sampler at this texture coordinate location.
	slopeColor = slopeDiffuseTexture.Sample(SampleType, input.tex);

	// Sample the rock color from the texture using the sampler at this texture coordinate location.
	snowColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Smaple the bump maps for each texture and get their material
	grassBumpMap = grassNormalTexture.Sample(SampleType, input.tex);
	grassMaterial = getMaterial(input, grassColor, grassBumpMap, lightDir);

	slopeBumpMap = slopeNormalTexture.Sample(SampleType, input.tex);
	slopeMaterial = getMaterial(input, slopeColor, slopeBumpMap, lightDir);

	snowBumpMap = snowNormalTexture.Sample(SampleType, input.tex);
	snowMaterial = getMaterial(input, snowColor, snowBumpMap, lightDir);

	// Calculate the slope of this point.
	slope = 1.0f - input.normal.y;

	// Determine which texture to use based on height.
	if (slope < 0.2)
	{
		blendAmount = slope / 0.2f;
		textureColor = lerp(grassMaterial, slopeMaterial, blendAmount);
	}

	if ((slope < 0.7) && (slope >= 0.2f))
	{
		blendAmount = (slope - 0.2f) * (1.0f / (0.7f - 0.2f));
		textureColor = lerp(slopeMaterial, snowMaterial, blendAmount);
	}

	if (slope >= 0.7)
	{
		textureColor = snowMaterial;
	}

	return textureColor;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
	color = saturate(diffuseColor * lightIntensity);

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	color = color * textureColor;

	return color;
}