#include "mesh.h"

Mesh::Mesh(QVector<Vertex> vertices, QVector<uint> indices/*, QVector<Texture> textures*/)
    : vertices(vertices),
      indices(indices)/*,
      textures(textures)*/
{
    setupMesh();
}

void Mesh::draw(ShaderProgram shade, QHash<uint, const char*> textures)
{
    QHashIterator<uint, const char*> it(textures);
    while (it.hasNext()) {
        it.next();
        uint textureID = it.key();
        glActiveTexture(GL_TEXTURE0 + textureID);
        shade.setGLSLUniform1i(it.value(), textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    glActiveTexture(GL_TEXTURE0);

    // 绘制
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    initializeOpenGLFunctions();

    // 创建VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定VAO
    glBindVertexArray(VAO);

    // 绑定VBO顶点
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // 绑定EBO顶点索引
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // 启用绑定的数据
    // 位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 法向量
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 纹理
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
