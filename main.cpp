#include "voice_acting.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VOICE_ACTING w;
    w.show();
    return a.exec();
}
