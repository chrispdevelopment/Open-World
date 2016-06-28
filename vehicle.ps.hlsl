/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture : register(t0);
SamplerState SampleType;

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float specularPower;
	float4 specularColor;
};

//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 VehiclePixelShader(PixelInputType input) : SV_TARGET
{
	float3	lightDir;
	float	lightIntensity;
	float3	reflection;
	float4	specular;
	float4	lightColor;

	float4	diffuseTextColor;

	float4 outputColor;

	////////////////////////////////////////////////////////////////////////////////
	// Texture Operations
	////////////////////////////////////////////////////////////////////////////////

	// Get the pixel color from the first texture.
	diffuseTextColor = shaderTexture.Sample(SampleType, input.tex);

	////////////////////////////////////////////////////////////////////////////////
	// Light Operations
	////////////////////////////////////////////////////////////////////////////////

	// Set the default output color to the ambient light value for all pixels.
	lightColor = ambientColor;

	// Initialize the specular color.
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	if (lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		lightColor += (diffuseColor * lightIntensity);

		// Saturate the ambient and diffuse color.
		lightColor = saturate(lightColor);

		// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
		reflection = normalize(2 * lightIntensity * input.normal - lightDir);

		// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
		specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
	}

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	outputColor = lightColor * diffuseTextColor;

	// Add the specular component last to the output color.
	outputColor = saturate(outputColor + specular);

	return outputColor;
}