#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication appl(argc, argv);
    MainWindow window;
    window.show();

    return appl.exec();
}
