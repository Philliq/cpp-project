#include "mainwindow.h"
#include "jitteryinput.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    jitteryInput input;
    MainWindow w;

    QObject::connect(&input, &jitteryInput::newData, &w, &MainWindow::setInputText );
    QObject::connect(&input, &jitteryInput::newData, &w, &MainWindow::setOutputText );

    w.show();

    input.start(10);

    return a.exec();
}
