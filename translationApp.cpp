#include "translationApp.h"

TranslationApp::TranslationApp(){
    wasError=false;
    time=0;
    timer=new QTimer(this);
    pW=new PresentWidget;
    right=new CheckWidget("Вы правы","data/right");
    wrong=new CheckWidget("Вы ошиблись","data/wrong");
    dontKnow=new CheckWidget("Запоминайте","data/wrong");

    t=new Translation;

    QObject::connect(this,SIGNAL(allIsReady()),t,
                     SLOT(slotSendToTranslate())
                     );

    QObject::connect(t,SIGNAL(translationSignal(QString)),
                        pW, SLOT(toPresentWidget(QString))
                     );

    QObject::connect(pW,SIGNAL(checkTranslation(QString)),
                     t, SLOT(slotCheckTranslation(QString))
                     );

    QObject::connect(pW, SIGNAL(dontKnowSignal(QString,QString)),
                    this,SLOT(dontKnowSlot(QString,QString))
                    );

    QObject::connect(t,SIGNAL(rightTranslationSignal(QString)),
                        this, SLOT(rightTranslationSlot(QString))
                     );

    QObject::connect(t,SIGNAL(wrongTranslationSignal(QString)),
                        this, SLOT(wrongTranslationSlot(QString))
                     );

    QObject::connect(this, SIGNAL(dontKnowSignaltoTranslte(QString, QString)),
                        t, SLOT(slotDontKnow(QString,QString))
                     );

    QObject::connect(t,SIGNAL(dontKnowTranslationSignal(QString)),
                        this, SLOT(readyDontKnow(QString))
                     );

    QObject::connect(pW,SIGNAL(sendTimer(QString)),
                     this, SLOT(toTimer (QString ))
                     );

    QObject::connect(this,SIGNAL(timeSignal(QString)),
                     pW, SLOT(timeToW(QString))
                     );

    QObject::connect(right,SIGNAL(sendCloseSignal()),
                     this, SLOT(timerStart())
                     );

    QObject::connect(timer,SIGNAL(timeout()),
                     this, SLOT(showAgain())
                     );

    QObject::connect(wrong,SIGNAL(sendCloseSignal()),
                     this, SLOT(timerStart())
                     );
    QObject::connect(dontKnow,SIGNAL(sendCloseSignal()),
                     this, SLOT(timerStart())
                     );

    QObject::connect(this,SIGNAL(timerTimeout()),
                     this, SLOT(showAgain())
                     );

    QObject::connect(t,SIGNAL(errorSignal(QString)),
                     this, SLOT(errorSlot(QString))
                     );

    QObject::connect(pW,SIGNAL(wrongConnection(QString)),
                     this, SLOT(errorSlot(QString))
                     );

    QObject::connect(pW,SIGNAL(toFile()),
                     t, SLOT(writeSystemAndListFiles())
                     );


    t->initialization("data/system.txt","data/key.txt","data/swear_words.txt", "data/book.txt","data/words_list.txt");
    emit timeSignal("0");
    emit allIsReady();
    if(!wasError){pW->setVisible(true);pW->tIc->show();}

}

void TranslationApp::showAgain(){

     pW->setVisible(true);

}

void TranslationApp::toTimer (QString timeResult){
    time=timeResult.toInt();

    emit timeSignal(timeResult);


}

void TranslationApp::dontKnowSlot(QString word,QString time){

    emit dontKnowSignaltoTranslte(word, time);
}

void TranslationApp::rightTranslationSlot(QString word){
    right->cW.translate->setText(word);

    right->show();

}
void TranslationApp::wrongTranslationSlot(QString word){

    wrong->cW.translate->setText(word);

    wrong->show();

}

void TranslationApp::readyDontKnow(QString word){

    dontKnow->cW.translate->setText(word);

    dontKnow->show();



}


void TranslationApp::timerStart(){
    if(time!=0){
        timer->setInterval(time*60*1000);
        timer->start();
    }else emit timerTimeout();
}

void TranslationApp::errorSlot(QString err){
    wasError=true;
    error=new ErrorWidget("data/error",err);
     pW->setVisible(false);
     pW->tIc->hide();

     error->show();

}
