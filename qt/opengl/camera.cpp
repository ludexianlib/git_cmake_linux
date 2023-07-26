#include "camera.h"

const float moveSpeed = 0.2f;

Camera::Camera(QVector3D pos, QVector3D front, QVector3D up)
    : position(pos),
      front(front),
      up(up)
{

}

void Camera::getCameraParam(QVector3D *ret, Camera::ParamType type)
{
    if (type == POSITION)
        *ret = position;
    else if (type == FRONT)
        *ret = front;
    else if (type == UP)
        *ret = up;
}

void Camera::setCameraParam(QVector3D param, Camera::ParamType type)
{
    if (type == POSITION)
        position = param;
    else if (type == FRONT)
        front = param;
    else if (type == UP)
        up = param;
}

QMatrix4x4 Camera::createLookAtMatrix()
{
    QMatrix4x4 view;
    view.lookAt(position, position + front, up);
    return view;
}

void Camera::moveCamera(Camera::MoveDirection direction)
{
    if (direction == FORWARD)
        position += front * moveSpeed;
    else if (direction == BACKWARD)
        position -= front * moveSpeed;
    else if (direction == LEFT) {
        QVector3D cross = QVector3D::crossProduct(front, up);
        cross.normalize();
        position -= cross * moveSpeed;
    }
    else if (direction == RIGHT) {
        QVector3D cross = QVector3D::crossProduct(front, up);
        cross.normalize();
        position += cross * moveSpeed;
    }
}
