#include <QtGui/QtGui>
#include <QApplication>
#include <QWebEngineView>
#include <QPlainTextEdit>
#include <QHBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *window=new QWidget;
    window->setFixedSize(1000, 580);
    auto *layout =new QHBoxLayout;

    auto *plainText= new QPlainTextEdit;
    layout->addWidget(plainText);
    plainText->setSizePolicy(QSizePolicy ::Preferred , QSizePolicy ::Preferred);

    auto *webView = new QWebEngineView;
    layout->addWidget(webView);
    webView->setSizePolicy(QSizePolicy ::Preferred , QSizePolicy ::Preferred);

    plainText->setPlainText("<h1>Hello world!!!</h1>");
    webView->setHtml(plainText->toPlainText());
    // webView->setHtml("<h1>hello world!!!</h1>");

    QObject::connect(plainText,&QPlainTextEdit::textChanged ,[webView,plainText](){ webView->setHtml(plainText->toPlainText());});
    window->setLayout(layout);
    window->show();
    return a.exec();
}
