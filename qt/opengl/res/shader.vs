#version 330 core
layout (location = 0) in vec3 aPos;      // 位置变量的属性位置值为 0
layout (location = 1) in vec3 aNormal;      // 位置变量的属性位置值为 0
layout (location = 2) in vec2 aTexCoords;
//layout (location = 1) in vec2 aTexCoord;    // 纹理坐标变量的属性位置值为 1

//out vec2 TexCoord;

uniform mat4 model;         // 模型矩阵
uniform mat4 view;          // 观察矩阵
uniform mat4 projection;    // 投影矩阵

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
//    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal; // 法线矩阵，避免不等比例缩放法线方向改变
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
}
