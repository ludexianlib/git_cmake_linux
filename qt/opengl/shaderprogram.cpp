#include "shaderprogram.h"
#include <QFile>
#include <QDebug>

ShaderProgram::ShaderProgram()
{

}

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(mShader);
}

void ShaderProgram::createShaderProgram(const QStringList &shaderFile)
{
    initializeOpenGLFunctions();
    // 编译顶点着色器和片段着色器

    uint shaders[2], i = 0;
    foreach(QString file, shaderFile)
    {
        QFile openFile(file);
        openFile.open(QFile::ReadOnly);

        QByteArray shaderCode = openFile.readAll();

        // 着色器
        const char* shaderRes = shaderCode.constData();

        // 创建着色器并附加到Shader对象上
        if (file.contains("shader.vs"))
            shaders[i] = glCreateShader(GL_VERTEX_SHADER);
        else if (file.contains("shader.fs"))
            shaders[i] = glCreateShader(GL_FRAGMENT_SHADER);
        else  {
            qDebug() << "error file: " << file;
            return;
        }

        glShaderSource(shaders[i], 1, &shaderRes, NULL);
        glCompileShader(shaders[i]);

        // 查看着色器是否编译成功
        int ret;
        glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &ret);
        if (!ret) {
            char log[512];
            glGetShaderInfoLog(shaders[i], 512, NULL, log);
            qDebug() << "vertexShader compile error: " <<log;
        }
        i++;
    }

    // 着色器程序：链接着色器
    mShader = glCreateProgram();
    glAttachShader(mShader, shaders[0]);
    glAttachShader(mShader, shaders[1]);
    glLinkProgram(mShader);

    int ret;
    glGetProgramiv(mShader, GL_LINK_STATUS, &ret);
    if (!ret) {
        char log[512];
        glGetProgramInfoLog(mShader, 512, NULL, log);
        qDebug() << "shaderProgram link error: " << log;
    }

    // 链接后可以删除顶点和片段着色器
    glDeleteShader(shaders[0]);
    glDeleteShader(shaders[1]);

}

void ShaderProgram::getShaderProgramId(uint *ret)
{
    *ret = mShader;
}

void ShaderProgram::enableShader()
{
    glUseProgram(mShader);
}

void ShaderProgram::setGLSLUniform1i(const char *uniformName, int value)
{
    // 获取GLSL的uniform全局属性并设置着色器
    int vertexLocation = glGetUniformLocation(mShader, uniformName);

    // 有1i, 1f, 3f, 4f等类型
    glUniform1i(vertexLocation, value);
}

void ShaderProgram::setGLSLUniform1f(const char *uniformName, float value)
{
    int vertexLocation = glGetUniformLocation(mShader, uniformName);
    glUniform1f(vertexLocation, value);
}

void ShaderProgram::setGLSLUniform3f(const char *uniformName, float *value)
{
    int vertexLocation = glGetUniformLocation(mShader, uniformName);
    glUniform3f(vertexLocation, value[0], value[1], value[2]);
}

void ShaderProgram::setGLSLUniform3f(const char *uniformName, float val1, float val2, float val3)
{
    int vertexLocation = glGetUniformLocation(mShader, uniformName);
    glUniform3f(vertexLocation, val1, val2, val3);
}

void ShaderProgram::setGLSLUniformMatrix4fv(const char *uniformName, float *value)
{
    int vertexLocation = glGetUniformLocation(mShader, uniformName);
    glUniformMatrix4fv(vertexLocation,
                       1,               // 矩阵数量
                       GL_FALSE,        // 矩阵是否需要转置
                       value);          // 矩阵数据
}
