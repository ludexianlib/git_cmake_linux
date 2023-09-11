#include "object.h"

Object::Object(int flag)
{
    initializeOpenGLFunctions();

    // 生成顶点缓冲对象、数组、元素缓冲对象
    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);
//    glGenBuffers(1, &mEBO);

    // 顶点缓冲对象的缓冲类型 ARRAY
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBindVertexArray(mVAO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 将用户定义的数据复制到当前绑定缓冲的函数
    if (flag == 0 || flag == 1)
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    else if (flag == 2)
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    // 位置属性
    // 如何解析顶点数据
    if (flag == 0)
    {
        glVertexAttribPointer(0,                    // 顶点属性位置
                              3,                    // 顶点属性大小 vec3
                              GL_FLOAT,             // 顶点类型
                              GL_FALSE,             // 归一化
                              8 * sizeof(float),    // 步长：连续顶点组间隔
                              (void*)0              // 起始数据偏移量
                             );
        // 启用顶点属性
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    else if (flag == 1)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    else if (flag == 2)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // 颜色坐标
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    // 纹理坐标
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);

}

Object::~Object()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}

void Object::getGLObectID(uint *ret, Object::ObjectType type)
{
    if (type == ObjectType::VBO)
        *ret = mVBO;
    else if (type == ObjectType::VAO)
        *ret = mVAO;
    else if (type == ObjectType::EBO)
        *ret = mEBO;
}

void Object::drawObject()
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Object::bindObjectArray()
{
    glBindVertexArray(mVAO);
}

void Object::bindObjectBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
}
