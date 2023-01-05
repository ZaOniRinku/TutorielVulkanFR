#version 460

layout(set = 0, binding = 0) uniform Camera {
	mat4 view;
	mat4 projection;
} camera;

layout(set = 0, binding = 1) restrict readonly buffer Objects {
	mat4 model[];
} objects;

layout(push_constant) uniform ObjectID {
	uint objectID;
} oID;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;

void main() {
	outNormal = normal;
	outUV = uv;
	gl_Position = camera.projection * camera.view * objects.model[oID.objectID] * vec4(position, 1.0);
}