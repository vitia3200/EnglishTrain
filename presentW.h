#ifndef PRESENTWIDGET_H
#define PRESENTWIDGET_H

#include <QDesktopWidget>
#include <QWidget>
#include "ui_translateW.h"
#include "translation.h"
#include  <QPalette>
#include <QSystemTrayIcon>
#include <QMenu>
//#include <QTimer>


class PresentWidget : public QWidget{
    Q_OBJECT
    Ui::TranslateW tW;



public:
    QSystemTrayIcon* tIc;
    QMenu* tIcMenu;

PresentWidget(QWidget* parent=0);

protected:
    //перегрузка ф-ии закрытия
    virtual void closeEvent(QCloseEvent *);


public slots:
   void toPresentWidget(QString);
   void sendToTranslation();
   void dontKnowSlot();
   void timeToW(QString);
   void hideIconAndOut();
signals:
    void checkTranslation(QString);
    void dontKnowSignal(QString,QString);
    void sendTimer(QString);
    void toFile();
};

#endif // ETWIDGET_H
