#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    explicit Camera(QVector3D pos, QVector3D front, QVector3D up);

    enum ParamType { POSITION, FRONT, UP };
    void getCameraParam(QVector3D *ret, ParamType type);
    void setCameraParam(QVector3D param, ParamType type);
    QMatrix4x4 createLookAtMatrix();

    enum MoveDirection{ FORWARD, BACKWARD, LEFT, RIGHT };
    void moveCamera(MoveDirection direction);

private:
    QVector3D position;
    QVector3D front;
    QVector3D up;

signals:

};

#endif // CAMERA_H
