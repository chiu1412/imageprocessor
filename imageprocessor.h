#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include "gtransform.h"
#include "mouseevent.h"

class ImageProcessor : public MouseEvent
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();
    void createActions();
    void createMenus();
    void createToolbars();
    void loadFile(QString filename);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void showOpenFile();
    void getZoomOut();
    void getZoomIn();
    void showGeometryTransform();

private:
    gTransform *gWin;
    QWidget     *central;
    QMenu       *fileMenu;
    QToolBar    *fileTool;
    QImage      img;
    QString     filename;
    QLabel      *imgWin;
    QAction     *OpenFileAction;
    QAction     *exitAction;
    QAction     *zoomInAction;
    QAction     *zoomOutAction;
    QAction     *geometryAction;
};
#endif
