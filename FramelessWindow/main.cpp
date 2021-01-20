// main.cpp
#include "qframelesswidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFramelessWidget w(":/new/prefix1/images/magic.png");
    w.setTittle (QStringLiteral("美少女"));
    w.setBackgroundImage (":/new/prefix1/images/lady.jpg");
    //QQ login form size
    w.resize(430,330);
    w.show();

    return a.exec();
}

