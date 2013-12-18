#include "errorW.h"

ErrorWidget::ErrorWidget(const QString picture, const QString errorText) :QWidget(0){
    //поверх других окон
    ErrorWidget::setWindowFlags(Qt::WindowStaysOnTopHint);

    //местоположение

    eW.setupUi(this);

    this->move(QApplication::desktop()->width()-this->width()-QApplication::desktop()->width()*0.01,
               QApplication::desktop()->height()-this->height()-QApplication::desktop()->height()*0.1);

    QPixmap pict;
    pict.load(picture);

    eW.pic->setPixmap(pict);

    this->eW.textOfError->setText(errorText);

}

void ErrorWidget::closeEvent(QCloseEvent * pe){

    this->close();
    qApp->quit();
}
