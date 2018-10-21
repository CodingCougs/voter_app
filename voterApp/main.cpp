#include "voterappgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    voterAppGUI w;
    w.show();

    return a.exec();
}
