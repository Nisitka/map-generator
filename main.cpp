#include <QApplication>

#include "coreapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CoreApplication generatorMapMaster;
    generatorMapMaster.run();

    return a.exec();
}
