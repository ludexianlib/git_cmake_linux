#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QObject>
#include <QOpenGLFunctions_3_3_Core>

class ShaderProgram : protected QOpenGLFunctions_3_3_Core
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void createShaderProgram(const QStringList &shaderFile);
    void getShaderProgramId(uint *ret);
    void enableShader();

    void setGLSLUniform1i(const char *uniformName, int value);
    void setGLSLUniform1f(const char *uniformName, float value);
    void setGLSLUniform3f(const char *uniformName, float *value);
    void setGLSLUniform3f(const char *uniformName, float val1, float val2, float val3);
    void setGLSLUniformMatrix4fv(const char *uniformName, float *value);

private:
    uint mShader;
};

#endif // SHADERPROGRAM_H
