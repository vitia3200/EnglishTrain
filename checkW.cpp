#include "checkW.h"

CheckWidget::CheckWidget(const QString check, const QString picture) :QWidget(0){
    //поверх других окон
    CheckWidget::setWindowFlags(Qt::WindowStaysOnTopHint);

    //местоположение

    cW.setupUi(this);

    this->move(QApplication::desktop()->width()-this->width()-QApplication::desktop()->width()*0.01,
               QApplication::desktop()->height()-this->height()-QApplication::desktop()->height()*0.1);


    cW.rightWrong->setText(check);
    QPixmap pict;
    pict.load(picture);

    cW.pic->setPixmap(pict);

    QObject::connect(cW.ok,SIGNAL(clicked()),this,SLOT(sendCloseSlot()));

}

void CheckWidget::showRight(QString word){
    cW.translate->setText(word);
    this->show();

}


void CheckWidget::sendCloseSlot(){

    emit sendCloseSignal();


}
