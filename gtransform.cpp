#include "gtransform.h"
#include <QPixmap>
#include <QPainter>


gTransform::gTransform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout(this);
    mirrorGroup = new QGroupBox(QStringLiteral("鏡射"), this);
    groupLayout = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox(QStringLiteral("水平"), mirrorGroup);
    vCheckBox = new QCheckBox(QStringLiteral("垂直"), mirrorGroup);
    mirrorButton = new QPushButton(QStringLiteral("執行"), mirrorGroup);

    hCheckBox->setGeometry(QRect(13, 28, 87, 19));
    vCheckBox->setGeometry(QRect(13, 54, 87, 19));
    mirrorButton->setGeometry(QRect(13, 80, 93, 28));

    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);
    leftLayout->addWidget(mirrorGroup);
    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    saveButton = new QPushButton(QStringLiteral("存檔"),this);
    vSpacer = new QSpacerItem(20, 58, QSizePolicy::Minimum,
                              QSizePolicy::Expanding);

    leftLayout->addWidget(rotateDial);
    leftLayout->addItem(vSpacer);
    leftLayout->addWidget(saveButton);
    mainLayout->addLayout(leftLayout);

    inWin = new QLabel(this);
    inWin->setScaledContents(true);
    inWin->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));
    //--------------------------------------
    QPainter *paint = new QPainter(initPixmap);
    paint->setPen(*(new QColor(0,0,0)));
    paint->begin(initPixmap);
    paint->drawRect(15,15,60,60);
    paint->end();
    if(srcImg.isNull()){
        srcImg = initPixmap->toImage();
    }
    //--------------------------------------
    inWin->setPixmap(*initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (srcImg.isNull())
    {
        QPixmap *initPixmap = new QPixmap(300, 200);
        initPixmap->fill(QColor(255, 255, 255));
        inWin->setPixmap(*initPixmap);
    }

    mainLayout->addWidget(inWin);


    connect(mirrorButton, SIGNAL(clicked()), this, SLOT(mirroredImage()));
    connect(rotateDial, SIGNAL(valueChanged(int)), this, SLOT(rotatedImage()));
    connect(saveButton, SIGNAL(clicked()),this,SLOT(saveImage()));
}

gTransform::~gTransform()
{

}

void gTransform::mirroredImage()
{
    bool H,V;
    if (srcImg.isNull())
        return;
    H=hCheckBox->isChecked();
    V=vCheckBox->isChecked();
    dstImg = srcImg.mirrored(H,V);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
    srcImg = dstImg;
}

void gTransform::rotatedImage()
{
    QTransform tran;
    int angle;
    if (srcImg.isNull())
        return;
    angle = rotateDial->value();
    tran.rotate(angle);
    dstImg = srcImg.transformed(tran);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
}
void gTransform::saveImage(){
    QImage imageToSave = dstImg;
    if (imageToSave.isNull()) {
        if (!srcImg.isNull()) {
            imageToSave = srcImg;
        }else {
            return;
        }
    }
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QStringLiteral("儲存影像"),
                                                    "",
                                                    QStringLiteral("Images (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        if (!imageToSave.save(fileName)) {
            QMessageBox::warning(this, QStringLiteral("錯誤"), QStringLiteral("存檔失敗"));
        }
    }
}
