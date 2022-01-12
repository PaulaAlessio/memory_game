#include <QApplication>
#include "MemoryWindow.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    MemoryWindow window;
    return app.exec();
}
