#include <QMainWindow>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QMediaContent>
#include <QFileDialog>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>

#include "qpainter.h"
#include <QDir>

QImage blurImage (QImage source, int blurRadius)
{
    if(source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap (QPixmap::fromImage(source));
    //
    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius (blurRadius);
    item.setGraphicsEffect (blur);
    scene.addItem(&item);
    QImage result (source.size(), QImage::Format_ARGB32);
    result.fill(Qt:: transparent);
    QPainter painter (&result);
    scene.render(&painter, QRectF(),
                 QRectF( 0, 0, source.width(), source.height()));
                 return result;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *window=new QWidget;
    window->setFixedSize(640, 480);
    auto *layout =new QVBoxLayout;

    auto *image =new QLabel;


    auto *slider =new QSlider(Qt::Horizontal);
    slider->setMaximum(10);

    auto* openFile= new QPushButton;
    openFile->setText("Open");

    QString pathFile;
    // auto* player=new QMediaPlayer();
    QObject::connect(openFile,&QPushButton::clicked,[&slider,&pathFile,&image](){
        pathFile= QFileDialog::getOpenFileName(nullptr,"image","C:\\","Images (*.png *.xpm *.jpg)");
        QPixmap picture(pathFile);
        image->setPixmap(picture);
        slider->setValue(0);
    });

    QObject::connect(slider, &QSlider::valueChanged, [&slider,&pathFile, &image](int newValue) {
        QImage i(pathFile);
        image->setPixmap(QPixmap::fromImage(blurImage(i, newValue)));
    });


    layout->addWidget(image);
    layout->addWidget(openFile);
    layout->addWidget(slider);
    window->setLayout(layout);
    window->show();
    return a.exec();
}
