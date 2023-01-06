#version 460
#extension GL_EXT_nonuniform_qualifier : enable

layout(set = 0, binding = 2) uniform sampler2D textures[];

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in flat uint inTextureID;

layout(location = 0) out vec4 outColor;

void main() {
	vec4 textureColor = texture(textures[inTextureID], inUV);
	outColor = vec4(textureColor.rgb, 1.0);
}