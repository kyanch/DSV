#include "canvas.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // MainWindow w;
    // w.show();
    Canvas canvas;
    canvas.show();

    return a.exec();
}
