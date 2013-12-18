#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>
#include <QMap>
#include <QList>
#include <QFile>
#include <QTextStream> //передоставляет методы для считывания текстового файла
#include <QTime>
#include <QtXml>
//сеть
#include <QObject>
#include <QUrl>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>

//таймер
#include <QTimer>

//виджеты
#include "presentW.h"


class QNetworkAccessManager;
class QNetworkReply;

class Translation :public QObject{
Q_OBJECT

    int numberOfWord; //позиция слова, посылаемого для перевода
    bool error;

    QString lastedTranslate;

    //yandex API
    QString yandexKey;
    QNetworkAccessManager* translater;

    //для формирование словаря:
    QMap<QString,bool> swearWords; //список запрещенных слов
    QMap<QString,bool> bookWordsMap;
    //словарь
    QList<QString> bookWords;

public:
    void initialization(const QString,const QString,const QString,const QString, const QString);
    void loadListOfWords(const QString&); //если словарь сформирован - загружает
    void loadSwearWords(const QString&);
    void loadBook(const QString&);
    void bookStrToWords(const QString&);
    void sortAndMixBook();                //формируют словарь
    void xmlAnalysis(const QString);
    void xmlAnalysisAndSendWord(const QString); //анализ полученного перевода
    void sendWordToTranslate();
    void translate();

private slots:
    void slotDownloadFinished(QNetworkReply*);
    void slotCheckTranslation(QString); //проверка перевода
    void slotSendToTranslate(); //отсылка слова в виджет для пользовательского перевода
    void slotDontKnow(QString,QString);
    void writeSystemAndListFiles();
signals:
    void sendWordSignal(QString);
    void translationSignal(QString);
    void rightTranslationSignal(QString);
    void wrongTranslationSignal(QString);
    void dontKnowTranslationSignal(QString);
    void errorSignal(const QString);
};


#endif // TRANSLATION_H
