#include "presentW.h"

PresentWidget::PresentWidget(QWidget *parent) :QWidget(parent)
 //,ui(new Ui::TrnslateW)
{
    tW.setupUi(this);

    //поверх других окон
    PresentWidget::setWindowFlags(Qt::WindowStaysOnTopHint);

    //местоположение
    this->move(QApplication::desktop()->width()-this->width()-QApplication::desktop()->width()*0.01,
               QApplication::desktop()->height()-this->height()-QApplication::desktop()->height()*0.1);



    QPalette pall;
    pall.setBrush(this->backgroundRole(), QBrush(QPixmap("data/background")));
    this->setPalette(pall);
    this->setAutoFillBackground(true);

    QAction* pointMenu1=new QAction("&Показать новое слово сейчас",this);
    connect(pointMenu1, SIGNAL(triggered()), this, SLOT(show()));

    QAction* pointMenu2=new QAction("&Закрыть программу",this);
    connect(pointMenu2, SIGNAL(triggered()), this, SLOT(hideIconAndOut()));

    tIcMenu= new QMenu(this);
    tIcMenu->addAction(pointMenu1);
    tIcMenu->addAction(pointMenu2);

    tIc=new QSystemTrayIcon(this);
    tIc->setContextMenu(tIcMenu);
    tIc->setToolTip("English train 1.0");
    tIc->setIcon(QPixmap("data/icon"));



    QObject::connect(tW.okey,SIGNAL(clicked()),this,SLOT(sendToTranslation()));

    QObject::connect(tW.dontKnow,SIGNAL(clicked()),this,SLOT(dontKnowSlot()));

    QObject::connect(tW.Exit,SIGNAL(clicked()),this,SLOT(hideIconAndOut()));



}

void PresentWidget::sendToTranslation(){
    emit checkTranslation(tW.userTranslate->text());
    setVisible(false);
    emit sendTimer(tW.timer->text());
}


void PresentWidget::toPresentWidget(QString eWord){
    QString word='"'+eWord+'"';
    tW.wordToTranslate->setText(word);

}

void PresentWidget::dontKnowSlot(){
    emit dontKnowSignal(tW.userTranslate->text(),tW.timer->text());
    setVisible(false);
}

void PresentWidget::timeToW(QString time){
    tW.timer->setText(time);

}



//слоты/методы работы с треем
void PresentWidget::closeEvent(QCloseEvent * pe){

    if(tIc->isVisible()) hide();
}

void PresentWidget::hideIconAndOut(){
    emit toFile();
    tIc->hide();
    qApp->quit();
}
