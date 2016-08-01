#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtCore>
#include <QOpenGLWidget>

#include "shader.h"
#include "camera.h"
#include "magiccube.h"

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GlWidget(QWidget *parent = 0);
    ~GlWidget();
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;

    void virtual wheelEvent(QWheelEvent *event) override;
    void virtual mouseMoveEvent(QMouseEvent *event) override;

    QPoint startPos;
    void virtual mousePressEvent(QMouseEvent *event) override;
    void virtual mouseReleaseEvent(QMouseEvent *event) override;

    void virtual keyPressEvent(QKeyEvent *event) override;
private:
    void initVertex();
    void rebuildMagic();
    void initTrans();
    void updateView();
    void updateModel(const glm::mat4& m);
    void updateProject();

    void animate(std::pair<int, Rotate> p);
    Q_SLOT void onTimeout();
private:
    MagicCube magic;

    Shader ourShader;
    GLuint VBO, VAO;

    glm::mat4 animationModel;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    GLint modelLoc, viewLoc, projLoc;

    Camera camera;

    QTimer *timer;
    bool isInAnimation;
    int animationAngle;
    std::pair<int, Rotate> rotateSurface;
    static constexpr int allvertex = 6*9*6;
    static constexpr int firstPlanrVertex = 6*(9+3*4);
};

#endif // GLWIDGET_H
