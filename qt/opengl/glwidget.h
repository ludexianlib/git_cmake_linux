#ifndef LIGHTGLWIDGET_H
#define LIGHTGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QQuaternion>
#include <QVector3D>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include "shaderprogram.h"
#include "object.h"
#include "camera.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

private:
    void loadTexture(QString imgPath, unsigned int *textureID, int textureUnit);

    QPointF pixelPosToViewPos(const QPointF& p);

private:
    Object *mObj;
    Object *lightObj;
    Camera *camera;
    ShaderProgram *mShaderProgram;
    ShaderProgram *lightShaderProgram;

    float zoom = 45.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    QQuaternion mRotation;
    QPointF lastPressedPos;
    unsigned int texture[2];
signals:

};

#endif // LIGHTGLWIDGET_H
