#include <QApplication>
#include <QMainWindow>

#include <QMediaPlayer>
#include <QMediaContent>

#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto* playButton= new QPushButton();
    auto *player=new QMediaPlayer(playButton);
    bool isPlaying=false;
    QObject::connect(playButton,&QPushButton::clicked,[&isPlaying,player](){
        if(!isPlaying)
            {
            isPlaying=true;
            player->setMedia(QUrl::fromLocalFile("sound.mp3"));
            player->play();
            player->setVolume(100);
        }
        else {
            player->stop();
            isPlaying=false;
        }
    });

    playButton->show();
    return a.exec();
}
