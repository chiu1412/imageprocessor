#ifndef GTRANSFORM_H
#define GTRANSFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QSpacerItem>
#include <QDial>
#include <QHBoxLayout>
#include<QVBoxLayout>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>

class gTransform : public QWidget
{
    Q_OBJECT

public:
    gTransform(QWidget *parent = nullptr);
    ~gTransform();
    QLabel          *inWin;
    QGroupBox       *mirrorGroup;
    QCheckBox       *hCheckBox;
    QCheckBox       *vCheckBox;
    QPushButton     *mirrorButton;
    QPushButton     *saveButton;
    QDial           *rotateDial;
    QSpacerItem     *vSpacer;
    QHBoxLayout     *mainLayout;
    QVBoxLayout     *groupLayout;
    QVBoxLayout     *leftLayout;
    QImage          srcImg;
    QImage          dstImg;
private slots:
    void mirroredImage();
    void rotatedImage();
    void saveImage();
};
#endif // GTRANSFORM_H
