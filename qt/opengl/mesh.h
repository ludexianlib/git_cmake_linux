#ifndef MESH_H
#define MESH_H

#include "shaderprogram.h"
#include <QHash>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions_3_3_Core>

struct Vertex {
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};

/*struct Texture {
    uint id;
    QString type;
};*/

class Mesh : protected QOpenGLFunctions_3_3_Core
{
public:
    Mesh(QVector<Vertex> vertices, QVector<uint> indices/*, QVector<Texture> textures*/);
    void draw(ShaderProgram shader, QHash<uint, const char*> textures);

    QVector<Vertex> vertices;
    QVector<uint> indices;
    /*QVector<Texture> textures;*/

private:
    uint VAO, VBO, EBO;
    void setupMesh();
};

#endif // MESH_H
