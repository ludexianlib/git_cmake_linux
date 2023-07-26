#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    vec3 ambient;       // 环境光照
//    vec3 diffuse;       // 漫反射光照

    sampler2D diffuse;  // 漫发射贴图
    sampler2D specular;      // 镜面光照
    float shininess;    // 反光度: 影响镜面高光的散射/半径
};
uniform Material material;

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 衰减系数
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

// 定向光
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

// 点光源
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform vec3 lightPos; // 计算漫反射光照

uniform vec3 viewPos; // 镜面光照

//in vec2 TexCoord;   // 纹理坐标：右下角为原点

//uniform sampler2D texture1; // 使用的内建数据类型Sampler把纹理赋值给该对象

void main() {

    // 属性
//    vec3 norm = normalize(Normal);
//    vec3 viewDir = normalize(viewPos - FragPos);

//    // 第一阶段：定向光照
//    vec3 result = CalcDirLight(dirLight, norm, viewDir);
//    // 第二阶段：点光源
//    for(int i = 0; i < NR_POINT_LIGHTS; i++)
//        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
//    // 第三阶段：聚光
//    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

//    FragColor = vec4(result, 1.0);

    float distance_    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance_ +
        light.quadratic * (distance_ * distance_)); // 衰减计算公式

    // 环境光
//    vec3 ambient  = light.ambient * material.ambient;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    ambient  *= attenuation;

    // 漫反射
    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightDir = normalize(-light.direction); // 平行光
    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    diffuse  *= attenuation;

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
