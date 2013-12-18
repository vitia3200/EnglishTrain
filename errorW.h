#ifndef ERRORW_H
#define ERRORW_H
#include <QDesktopWidget>
#include <QWidget>
#include "ui_errorW.h"
#include "translation.h"
#include  <QPalette>

class ErrorWidget : public QWidget{
    Q_OBJECT


public:
    Ui::errorW eW;

    ErrorWidget(const QString, const QString);

protected:
    //перегрузка ф-ии закрытия
    virtual void closeEvent(QCloseEvent *);

public slots:



signals:


};

#endif // ERRORW_H
