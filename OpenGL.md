## 光照模型

### 风氏光照模型

1. 环境光照
> 模拟全局照明：光照强度因子 * 光照颜色 * 物体颜色

2. 漫反射
> 1. 物体定义顶点的法向量
> * 通过计算两个向量的夹角计算
> * 如果物体进行旋转或进行缩放则需要修改法向量
> * 法线矩阵: 「模型矩阵左上角3x3部分的逆矩阵的转置矩阵」，Normal = mat3(transpose(inverse(model))) * Normal;（不应该在着色器里计算，性能弱，在CPU计算完再传入）
> 2. 计算物体的空间位置
> * 物体的顶点坐标 * 模型矩阵
> 3. 计算夹角
> * 物体的法向量.norm * （灯光位置 - 物体位置）.norm（即物体指向光源的向量）
> 4. 叠加光照
> * diffuse = max(dot(Normal, lightVec), 0) * lightColor;
> * color = (ambient + diffuse) * objectColor;

3. 镜面反射
> 1. 计算物体和光照的向量
> * viewDir =（观察者的位置 - 物体的位置）.norm
> * reflectDir = reflect(-lightDir, norm); -lightDir（即光源指向物体的向量）
> 2. 计算镜面分量
> * spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); 32为反光度（反光度越高，散射越少，高光点越小）
> * 反射强度因子 * spec * lightColor;

### 材质

1. 着色器定义结构体
```c
// 物体材质
struct
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// 灯光强度属性
struct Light
{
    vec3 Pos;

    // 强度因子
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

// 通过修改灯光的强度因子 修改不同的反射强度
vec3 ambient  = light.ambient * material.ambient;
vec3 diffuse  = light.diffuse * (diff * material.diffuse);
vec3 specular = light.specular * (spec * material.specular);
```

### 光照贴图
1. 漫反射贴图
> 只需将漫反射替换为纹理即可（这里环境光照和漫反射一样了，如需使用不同的环境光照，环境光照也需要单独的纹理）
```c
struct
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};
```
2. 镜面光贴图
> 将镜面光变成纹理
```c
struct
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// 最终效果
vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  
vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
FragColor = vec4(ambient + diffuse + specular, 1.0);
```

### 投光物（光源）
1. 平行光
```c
struct Light {
    // vec3 position; // 使用定向光就不再需要了
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
```
> 注意vec时w分量: 作为位置时为1，作为向量时为0（消除位移对向量方向的影响）

2. 点向光
> 1. 衰减 距离点光源近的强度越大
> * Fatt = 1 / (Kc + Kl * d + Kq * d^2)
```c
struct Light {
    // ...
    
    float constant;
    float linear;
    float quadratic;
};
```

3. 聚光灯
> 1. LightDir 片段指向光源的向量
> 2. SpotDir  聚光灯的指向
> 3. Phi      切光角（圆锥半径）
```c
struct Light {
    vec3  position;
    vec3  direction;
    float cutOff;
    ...
};
```
> 4. 边缘柔滑
> * 创建外圆锥，在内外圆锥之间的强度为0.0 - 1.0
> * I = （θ - γ） / ε 注: ε = 内圆锥ϕ - 外圆锥γ

### 合并光源
> 1. 片段着色器的定向光