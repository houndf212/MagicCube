#include "glwidget.h"
#include <QKeyEvent>
#include <iostream>
#include "draganalysis.h"

GlWidget::GlWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    ,isInAnimation(false)
    ,animationAngle(0)
{
//    this->setMouseTracking(true);
//    this->setFixedSize(400, 400);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GlWidget::onTimeout);
}

GlWidget::~GlWidget()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void GlWidget::initializeGL()
{
//    glShadeModel(GL_SMOOTH);
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    bool b = ourShader.compile(":/shaders/vshader.glsl", ":/shaders/fshader.glsl");
    Q_ASSERT(b);
    initVertex();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    initTrans();

}

void GlWidget::paintGL()
{
    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw our first triangle
    ourShader.Use();
    glBindVertexArray(VAO);
    if (isInAnimation)
    {
        updateModel(animationModel);
        glDrawArrays(GL_TRIANGLES, 0, firstPlanrVertex);
        updateModel(model);
        glDrawArrays(GL_TRIANGLES, firstPlanrVertex, allvertex-firstPlanrVertex);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, allvertex);
    }
    glBindVertexArray(0);
}

void GlWidget::resizeGL(int width, int height)
{
    int h = qMin(width, height);
    h = qMax(100, h);
    glViewport(0, 0, h, h);
    updateProject();
}

void GlWidget::wheelEvent(QWheelEvent *event)
{
    constexpr const GLfloat cameraSpeed = 0.5f;
    QPoint d = event->angleDelta();
    if (d.y()>0)
        camera.zoom(cameraSpeed);
    else
        camera.zoom(-cameraSpeed);

    updateProject();
}


void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        constexpr const GLfloat s = 1.0f;
        static QPoint lastPos(0, 0);
        QPoint p = event->pos();
        if (p.x()>lastPos.x())
            camera.rotate(0, s);
        else
            camera.rotate(0, -s);

        if (p.y()>lastPos.y())
            camera.rotate(-s, 0);
        else
            camera.rotate(s, 0);

        lastPos = p;
        updateView();
    }
}

void GlWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button()  == Qt::LeftButton)
    {
        startPos = event->pos();
    }
}

void GlWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()  == Qt::LeftButton)
    {
        QPoint endPos = event->pos();
        std::pair<int, Rotate> p;
//        bool b = DragAnalysis::analysis(width(), height(), startPos, endPos, &p);
//        qDebug() << "is drag: "<<b;
        if (DragAnalysis::analysis(width(), height(), startPos, endPos, camera.Horizontal, &p))
        {
//            qDebug() << p.first<<":"<<int(p.second);
            animate(p);
        }
    }
}

void GlWidget::keyPressEvent(QKeyEvent *event)
{
    int planr = DragAnalysis::getFrontPlanr(camera.Horizontal);
    switch(event->key())
    {
    case Qt::Key_A:
        animate({planr, Rotate::Anti_Clock});
        break;
    case Qt::Key_D:
        animate({planr, Rotate::Clock_Wise});
        break;
    }
}

void GlWidget::initVertex()
{
//    magic.setFirstPaintPlanr(5);
    std::vector<GLfloat> buffer;
    magic.writeToBuffer(&buffer);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);

//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO
}

void GlWidget::rebuildMagic()
{
    std::vector<GLfloat> buffer;
    magic.writeToBuffer(&buffer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void GlWidget::initTrans()
{
    // Create transformations

    view = camera.GetViewMatrix();
    projection = glm::perspective(camera.getZoom(), (GLfloat)this->width() / (GLfloat)this->height(), 0.1f, 100.0f);

    // Get their uniform location
    ourShader.Use();
    modelLoc = glGetUniformLocation(ourShader.Program, "model");
    viewLoc = glGetUniformLocation(ourShader.Program, "view");
    projLoc = glGetUniformLocation(ourShader.Program, "projection");
    Q_ASSERT(modelLoc!=-1);
    Q_ASSERT(viewLoc!=-1);
    Q_ASSERT(projLoc!=-1);
    // Pass them to the shaders
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void GlWidget::updateView()
{
    ourShader.Use();
    view = camera.GetViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    update();
}

void GlWidget::updateModel(const glm::mat4 &m)
{
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m));
}

void GlWidget::updateProject()
{
    ourShader.Use();
    projection = glm::perspective(camera.getZoom(), (float)this->width()/(float)this->height(), 0.1f, 1000.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    update();
}

void GlWidget::animate(std::pair<int, Rotate> p)
{
    if (!isInAnimation)
    {
        isInAnimation = true;
        rotateSurface = p;
        animationAngle = 0;
        magic.setFirstPaintPlanr(rotateSurface.first);
        rebuildMagic();
        timer->start(500/90);
    }
}

void GlWidget::onTimeout()
{
//    qDebug() << "angle: "<<animationAngle;
    if (animationAngle!=90 && animationAngle!=-90)
    {
        glm::mat4 m;
        animationModel = glm::rotate(m, glm::radians(GLfloat(animationAngle)),
                        planr_normal_vec[rotateSurface.first]);

//        ourShader.Use();
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        update();
        animationAngle += int(rotateSurface.second);
    }
    else
    {
        isInAnimation = false;
        timer->stop();
        magic.rotate(rotateSurface.first, rotateSurface.second);
        rebuildMagic();
        update();
    }
}
