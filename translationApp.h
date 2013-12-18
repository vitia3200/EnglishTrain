#ifndef TRANSLATIONAPP_H
#define TRANSLATIONAPP_H

#include <QApplication>
#include <QSystemTrayIcon>
#include "translation.h"
#include "presentW.h"
#include "checkW.h"
#include "errorW.h"
#include <QTimer>

class Translation;
class PresentWidget;

class TranslationApp :public QObject{
Q_OBJECT

    int time;
    QTimer *timer;
    bool wasError;

    Translation* t;
    PresentWidget* pW;
    CheckWidget* right;
    CheckWidget* wrong;
    CheckWidget* dontKnow;
    ErrorWidget* error;

signals:
    void allIsReady();
    void dontKnowSignaltoTranslte(QString,QString);
    void timeSignal(QString);
    void timerTimeout();
public:
    TranslationApp();

public slots:
    void dontKnowSlot(QString, QString);
    void rightTranslationSlot(QString);
    void wrongTranslationSlot(QString);
    void readyDontKnow(QString);
    void showAgain();
    void toTimer(QString);
    void timerStart();
    void errorSlot(QString);
};
#endif // TRANSLATIONAPP_H
