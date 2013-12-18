#ifndef CHECKW_H
#define CHECKW_H
#include <QDesktopWidget>
#include <QWidget>
#include "ui_checkW.h"
#include "translation.h"
#include  <QPalette>

class CheckWidget : public QWidget{
    Q_OBJECT


public:
    Ui::CheckW cW;

    CheckWidget( const QString ,const QString);

public slots:
    void showRight(QString);
    void sendCloseSlot();


signals:
    void sendCloseSignal();

};

#endif // CHECKW_H
