#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "shaderprogram.h"

class Model
{
public:
    Model(QString path);

    void draw(ShaderProgram shade);

private:
    void loadModel(QString path);

    QVector<Mesh> meshes;
    QString directory;

};

#endif // MODEL_H
