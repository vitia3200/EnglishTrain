
#include <QApplication>
#include "translationApp.h"




int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"russian");

    QApplication englishTrain(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    TranslationApp a;

   return englishTrain.exec();
}
