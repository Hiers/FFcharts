#include <QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    
    mainWindow window;
    
    window.setWindowTitle("FFmpeg Charts");
    window.resize(480, 340);
    window.show();
    
    return app.exec();
}
