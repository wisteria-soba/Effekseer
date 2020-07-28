#version 300 es

struct VS_Input
{
    vec3 Pos;
    vec3 Normal;
    vec3 Binormal;
    vec3 Tangent;
    vec2 UV;
    vec4 Color;
};

struct VS_Output
{
    vec4 Pos;
    vec2 UV;
    vec3 Normal;
    vec3 Binormal;
    vec3 Tangent;
    vec4 Color;
};

struct VS_ConstantBuffer
{
    mat4 mCameraProj;
    mat4 mModel;
    vec4 fUV;
    vec4 fModelColor;
    vec4 fLightDirection;
    vec4 fLightColor;
    vec4 fLightAmbient;
    vec4 mUVInversed;
};

uniform VS_ConstantBuffer CBVS0;

layout(location = 0) in vec3 Input_Pos;
layout(location = 1) in vec3 Input_Normal;
layout(location = 2) in vec3 Input_Binormal;
layout(location = 3) in vec3 Input_Tangent;
layout(location = 4) in vec2 Input_UV;
layout(location = 5) in vec4 Input_Color;
out vec2 _VSPS_UV;
out vec3 _VSPS_Normal;
out vec3 _VSPS_Binormal;
out vec3 _VSPS_Tangent;
out vec4 _VSPS_Color;

VS_Output _main(VS_Input Input)
{
    vec4 uv = CBVS0.fUV;
    vec4 modelColor = CBVS0.fModelColor * Input.Color;
    VS_Output Output = VS_Output(vec4(0.0), vec2(0.0), vec3(0.0), vec3(0.0), vec3(0.0), vec4(0.0));
    vec4 localPosition = vec4(Input.Pos.x, Input.Pos.y, Input.Pos.z, 1.0);
    vec4 cameraPosition = localPosition * CBVS0.mModel;
    Output.Pos = cameraPosition * CBVS0.mCameraProj;
    Output.Color = modelColor;
    Output.UV.x = (Input.UV.x * uv.z) + uv.x;
    Output.UV.y = (Input.UV.y * uv.w) + uv.y;
    mat3 lightMat = mat3(CBVS0.mModel[0].xyz, CBVS0.mModel[1].xyz, CBVS0.mModel[2].xyz);
    vec4 localNormal = vec4(0.0, 0.0, 0.0, 1.0);
    vec3 _102 = normalize(Input.Normal * lightMat);
    localNormal = vec4(_102.x, _102.y, _102.z, localNormal.w);
    vec4 localBinormal = vec4(0.0, 0.0, 0.0, 1.0);
    vec3 _109 = normalize(Input.Binormal * lightMat);
    localBinormal = vec4(_109.x, _109.y, _109.z, localBinormal.w);
    vec4 localTangent = vec4(0.0, 0.0, 0.0, 1.0);
    vec3 _116 = normalize(Input.Tangent * lightMat);
    localTangent = vec4(_116.x, _116.y, _116.z, localTangent.w);
    Output.Normal = localNormal.xyz;
    Output.Binormal = localBinormal.xyz;
    Output.Tangent = localTangent.xyz;
    Output.UV.y = CBVS0.mUVInversed.x + (CBVS0.mUVInversed.y * Output.UV.y);
    return Output;
}

void main()
{
    VS_Input Input;
    Input.Pos = Input_Pos;
    Input.Normal = Input_Normal;
    Input.Binormal = Input_Binormal;
    Input.Tangent = Input_Tangent;
    Input.UV = Input_UV;
    Input.Color = Input_Color;
    VS_Output flattenTemp = _main(Input);
    gl_Position = flattenTemp.Pos;
    _VSPS_UV = flattenTemp.UV;
    _VSPS_Normal = flattenTemp.Normal;
    _VSPS_Binormal = flattenTemp.Binormal;
    _VSPS_Tangent = flattenTemp.Tangent;
    _VSPS_Color = flattenTemp.Color;
}
