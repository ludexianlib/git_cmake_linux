#include "glwidget.h"
#include <QDebug>
#include <QTime>
#include <math.h>
#include <QFile>
#include <QImage>
#include <QTimer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QGLWidget>

#define PI 3.141592695

const QVector3D objPos[5] =
{
    QVector3D(0.0f,  0.0f,  0.0f),
    QVector3D(2.0f,  5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D(2.4f, -0.4f, -3.5f)
};

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() { update(); });
    timer->start(20);

}

GLWidget::~GLWidget()
{
    delete mShaderProgram;
    delete mObj;
    delete camera;
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    mShaderProgram = new ShaderProgram;
    lightShaderProgram = new ShaderProgram;
    skyShaderProgram = new ShaderProgram;
    mShaderProgram->createShaderProgram(QStringList() << ":/res/shader.vs" << ":/res/shader.fs");
    lightShaderProgram->createShaderProgram(QStringList() << ":/res/lightshader.vs" << ":/res/lightshader.fs");
    skyShaderProgram->createShaderProgram(QStringList() << ":/res/skyshader.vs" << ":/res/skyshader.fs");

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE); // 面剔除
//    glCullFace(GL_BACK);

    loadTexture(":/res/container2.png", &texture[0], 0);
    loadTexture(":/res/container2_specular.png", &texture[1], 1);
    loadTexture3D(&texture[2]);

    mObj = new Object;
    lightObj = new Object(1);
    skyObj = new Object(2);

    // 使着色器调用和渲染调用都会使用该着色器程序对象


    // 初始化摄相机参数
    camera = new Camera(QVector3D(0, 0, 3), QVector3D(0, 0, -1), QVector3D(0, 1, 0));
}

void GLWidget::resizeGL(int /*w*/, int /*h*/)
{

}

void GLWidget::paintGL()
{
    // 设置窗口颜色
    glClearColor(0.5f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mObj->bindObjectArray();
//    mObj->bindObjectBuffer();

    mShaderProgram->enableShader();
    QVector3D cameraPos;
    camera->getCameraParam(&cameraPos, Camera::POSITION);
    mShaderProgram->setGLSLUniform3f("viewPos",  cameraPos.x(),  cameraPos.y(),  cameraPos.z());

    mShaderProgram->setGLSLUniform3f("material.ambient",  1.0f, 0.5f, 0.31f);
    mShaderProgram->setGLSLUniform1i("material.diffuse",  0);
    mShaderProgram->setGLSLUniform1i("material.specular", 1);
    mShaderProgram->setGLSLUniform1f("material.shininess", 32.0f);

    mShaderProgram->setGLSLUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
    mShaderProgram->setGLSLUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    mShaderProgram->setGLSLUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    mShaderProgram->setGLSLUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

    mShaderProgram->setGLSLUniform3f("pointLights[0].position", -0.7, -0.7, 1);
    mShaderProgram->setGLSLUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    mShaderProgram->setGLSLUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    mShaderProgram->setGLSLUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    mShaderProgram->setGLSLUniform1f("pointLights[0].constant", 1.0f);
    mShaderProgram->setGLSLUniform1f("pointLights[0].linear", 0.09f);
    mShaderProgram->setGLSLUniform1f("pointLights[0].quadratic", 0.032f);


    // 使用第0个纹理
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // 以线框模式绘制
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 透视投影
    QMatrix4x4 projection;
    projection.perspective(zoom, (float)width() / (float)height(), 0.1f, 100.0f);
    mShaderProgram->setGLSLUniformMatrix4fv("projection", projection.data());

    // 摄像机视角
    QMatrix4x4 view = camera->createLookAtMatrix();
    mShaderProgram->setGLSLUniformMatrix4fv("view", view.data());

    // 物体旋转
    for (int i = 0; i < 5; i++)
    {
        QMatrix4x4 model;
        model.translate(objPos[i]);
        model.rotate(mRotation); // model根据鼠标旋转，四元数旋转方法
        mShaderProgram->setGLSLUniformMatrix4fv("model", model.data());
        mObj->drawObject();
    }

    lightShaderProgram->enableShader();
    lightObj->bindObjectArray();
    lightShaderProgram->setGLSLUniformMatrix4fv("projection", projection.data());
    lightShaderProgram->setGLSLUniformMatrix4fv("view", view.data());
    QMatrix4x4 model2;
    model2.translate(QVector3D(-0.7, -0.7, 1));
    model2.rotate(35, QVector3D(1, 1, 0));
    lightShaderProgram->setGLSLUniformMatrix4fv("model", model2.data());
    lightObj->drawObject();

    glDepthFunc(GL_LEQUAL);
    skyShaderProgram->enableShader();
    skyShaderProgram->setGLSLUniform1i("skybox", 2);

    QMatrix4x4 skyView;
    memcpy(skyView.data(), view.data(), sizeof(float) * 3);
    memcpy(skyView.data() + 4, view.data() + 4, sizeof(float) * 3);
    memcpy(skyView.data() + 8, view.data() + 8, sizeof(float) * 3);

    skyShaderProgram->setGLSLUniformMatrix4fv("view", skyView.data());
    skyShaderProgram->setGLSLUniformMatrix4fv("projection", projection.data());
    skyObj->bindObjectArray();
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture[2]);
    skyObj->drawObject();
    glDepthFunc(GL_LESS);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
        camera->moveCamera(Camera::FORWARD);
    if (event->key() == Qt::Key_Down)
        camera->moveCamera(Camera::BACKWARD);
    if (event->key() == Qt::Key_Left)
        camera->moveCamera(Camera::LEFT);
    if (event->key() == Qt::Key_Right)
        camera->moveCamera(Camera::RIGHT);
}

QPointF GLWidget::pixelPosToViewPos(const QPointF& p)
{
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPressedPos = event->pos();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 物体旋转
    QPointF convertPos = pixelPosToViewPos(lastPressedPos);
    QVector3D lastPos3D = QVector3D(convertPos.x(),
                                    convertPos.y(),
                                    0);
    float sqrZ = 1 - QVector3D::dotProduct(lastPos3D, lastPos3D);
    if (sqrZ > 0)
        lastPos3D.setZ(std::sqrt(sqrZ));
    else
        lastPos3D.normalize();

    QPointF p = pixelPosToViewPos(event->pos());
    QVector3D currentPos3D = QVector3D(p.x(), p.y(), 0.0f);
    sqrZ = 1 - QVector3D::dotProduct(currentPos3D, currentPos3D);
    if (sqrZ > 0)
        currentPos3D.setZ(std::sqrt(sqrZ));
    else
        currentPos3D.normalize();

    QVector3D axis = QVector3D::crossProduct(lastPos3D, currentPos3D);
    float angle = asin(axis.length()) * (180 / PI) * 1.2; // 弧度转角度 * 转动速度
    axis.normalize();
    mRotation = QQuaternion::fromAxisAndAngle(axis, angle) * mRotation;

    // 摄像头旋转
    QPointF offset = event->pos() - lastPressedPos;
    offset = offset * 0.05f;

    yaw += offset.x();
    pitch += offset.y();

    if (pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    // 偏航角和俯仰角计算前向量
    float x = cos(yaw * (PI / 180.0f)) * cos(pitch * (PI / 180.0f));
    float y = sin(pitch * (PI / 180.0f));
    float z = sin(yaw * (PI / 180.0f)) * cos(pitch * (PI / 180.0f));
    QVector3D temp(x, y, z);
    temp.normalize();
    camera->setCameraParam(temp, Camera::FRONT);

    lastPressedPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    // 设置透视矩阵，缩放画面
    float scale = 0.02f;
    zoom -= event->delta() * scale;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 90.0f)
        zoom = 90.0f;
}

void GLWidget::loadTexture(QString imgPath, unsigned int *textureID, int textureUnit)
{
    // 纹理对象
    glGenTextures(1, textureID);
    glActiveTexture(GL_TEXTURE0 + textureUnit); // 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, *textureID);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage textureImg;
    textureImg.load(imgPath);
    textureImg = QGLWidget::convertToGLFormat(textureImg);
    glTexImage2D(GL_TEXTURE_2D,         // 纹理目标
                 0,                     // 多级渐远纹理的级别
                 GL_RGBA,               // 纹理储存格式
                 textureImg.width(),
                 textureImg.height(),
                 0,
                 GL_RGBA,               // 源图的格式
                 GL_UNSIGNED_BYTE,      // 源图数据类型
                 textureImg.bits());
    glGenerateMipmap(GL_TEXTURE_2D);    // 处理多级渐远纹理
}

void GLWidget::loadTexture3D(unsigned int *textureID)
{
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *textureID);

    QStringList skyPiture = QStringList() << ":/res/skybox/right.jpg"
                                          << ":/res/skybox/left.jpg"
                                          << ":/res/skybox/top.jpg"
                                          << ":/res/skybox/bottom.jpg"
                                          << ":/res/skybox/front.jpg"
                                          << ":/res/skybox/back.jpg";
    QImage img;
    for(int i = 0; i < skyPiture.size(); i++) {
        img.load(skyPiture.at(i));
        img = img.convertToFormat(QImage::Format_RGB32);
        QImage textureImg = QGLWidget::convertToGLFormat(img);
        textureImg = textureImg.mirrored();
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, textureImg.width(), textureImg.height(),
                     0, GL_RGBA, GL_UNSIGNED_BYTE, textureImg.bits());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
