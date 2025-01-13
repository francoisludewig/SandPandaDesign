#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle("fusion");
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(26, 117, 173));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::AlternateBase, QColor(26, 117, 117));
    qApp->setPalette(p);
    MainWindow w;
    w.show();
    return app.exec();
}
