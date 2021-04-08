#include <QApplication>
#include <QScreen>
#include <QGuiApplication>

#include "mainWindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();

    mainWindow window;
    
    window.setWindowTitle("FFcharts");
    window.resize(screen->availableSize().width()/3, screen->availableSize().height()/2.5);
    window.show();
    
    return app.exec();
}
