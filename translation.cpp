#include "translation.h"
#include <QDebug>


///////////////////////////////////////методы//////////////////////////////////////////////////////////////////////////////////////
void Translation::initialization(const QString systemFilePath, const QString yandexKeyPath, const QString swearWordsPath,
                         const QString bookPath,  const QString listOfWordsPath){
    error=false;
    //загрузка(иницилизация доунлаундера):
    translater=new QNetworkAccessManager;
    connect(translater,SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotDownloadFinished(QNetworkReply*))
            );



    QString wasStart;
    QFile systemFile(systemFilePath);


    if(!systemFile.open(QIODevice::ReadOnly)) emit errorSignal("Error of reading system file");
    else{
        QTextStream stream(&systemFile);
        wasStart=stream.readLine();
        //если ранее программа не запускалась(или кончились все слова в списке)
        if(wasStart=="0"){
            numberOfWord=0;

            this->loadSwearWords(swearWordsPath);
            this->loadBook(bookPath);
            this->sortAndMixBook();
            //this->writeSystemAndListFiles(systemFilePath,listOfWordsPath);

        }
        //если программа уже запускалась
        if(wasStart=="1"){
            numberOfWord=(stream.readLine()).toInt();
            this->loadListOfWords(listOfWordsPath);
        }
        systemFile.close();
        systemFile.setFileName(yandexKeyPath);
        if(!systemFile.open(QIODevice::ReadOnly)){emit errorSignal("Error of reading yandex key file"); error=true;}
        else yandexKey=stream.readLine();
        systemFile.close();

    }


}

void Translation::loadListOfWords(const QString& path){

    QFile listOfWordsFile(path);
    if(!listOfWordsFile.open(QIODevice::ReadOnly))
        emit errorSignal("Error list of words file reading");
    else{
        QTextStream stream(&listOfWordsFile);
        QString wordStr;

        while(!stream.atEnd()){
            wordStr=stream.readLine();
            bookWords<<wordStr;

        }
        listOfWordsFile.close();
    }


}

void Translation::loadSwearWords(const QString& path){

    QFile swearWordsFile(path);
    if(!swearWordsFile.open(QIODevice::ReadOnly))
        emit errorSignal("Error swear words file reading");
    else{
        QTextStream sWStream(&swearWordsFile);
        QString swearWordStr;

        while(!sWStream.atEnd()){
            swearWordStr=sWStream.readLine();
            this->swearWords[swearWordStr]=true;
        }
        swearWordsFile.close();
    }
}

void Translation::loadBook(const QString& path){

    QFile bookWordsFile(path);
    if(!bookWordsFile.open(QIODevice::ReadOnly))
        emit errorSignal("Error swear words file reading");
    else{
        QTextStream bStream(&bookWordsFile);
        QString bookStr;


        while(!bStream.atEnd()){
            bookStr=bStream.readLine();
            bookStrToWords(bookStr);

        }

        this->bookWords=this->bookWordsMap.keys();
        this->bookWordsMap.clear();

        bookWordsFile.close();


    }

}

void Translation::bookStrToWords(const QString& bookStr){


    QString bookWord="";


    for(int i=0; i<bookStr.size(); ++i){
       bool wordRightFlag=(((bookStr.at(i)>='a')&&(bookStr.at(i)<='z'))||(bookStr.at(i)=='-'));

       bool signWordBegin;
       if(i==0) signWordBegin=true;
       else signWordBegin=((bookStr.at(i-1)==' ')||(bookStr.at(i-1)=='\n'));

        if(wordRightFlag&&signWordBegin){
            while(wordRightFlag){
                bookWord=bookWord+bookStr.at(i);

                if(i<bookStr.size()-1){
                ++i;
                wordRightFlag=(((bookStr[i]>='a')&&(bookStr[i]<='z'))||(bookStr[i]=='-'));
                }else wordRightFlag=false;
            }

            if((bookWord.size()>2)&&(!this->swearWords.contains(bookWord)))
                this->bookWordsMap[bookWord]=true;
            bookWord="";

        }


    }


}

void Translation::xmlAnalysis(const QString path){

    QDomDocument xmlCompliteTranslate;
    QFile xmlFile(path);

    if(!xmlFile.open(QIODevice::ReadOnly))
        emit errorSignal("Error of reading xml translate file");
    else{
        xmlCompliteTranslate.setContent(&xmlFile);
        QDomElement nodeTranslateFile=xmlCompliteTranslate.documentElement(); //Возвращает ссылку на корневой элемент xml файла

        while(nodeTranslateFile.tagName()!="Translation")
            nodeTranslateFile=(nodeTranslateFile.firstChild()).toElement();

        if(nodeTranslateFile.attribute("code")=="200") xmlAnalysisAndSendWord(path);
        else emit errorSignal("Error of yandex translation API");

        xmlFile.close();

    }

}


void Translation::xmlAnalysisAndSendWord(const QString path){

    QDomDocument xmlCompliteTranslate;
    QFile xmlFile(path);

    if(!xmlFile.open(QIODevice::ReadOnly))
        emit errorSignal("Error od reading xml translate file");
    else{
        xmlCompliteTranslate.setContent(&xmlFile);
        QDomElement nodeTranslateFile=xmlCompliteTranslate.documentElement(); //Возвращает ссылку на корневой элемент xml файла

        while(nodeTranslateFile.tagName()!="text")
            nodeTranslateFile=(nodeTranslateFile.firstChild()).toElement();

        emit translationSignal(bookWords.at(numberOfWord));
        lastedTranslate=nodeTranslateFile.text();

        xmlFile.close();



    }

}


void Translation::sortAndMixBook(){

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    qSort(this->bookWords.begin(),this->bookWords.end());

    for(int i=bookWords.size()-1;i>=0;--i){
        int numberForSwap=qrand()%this->bookWords.size();
        bookWords.swap(i,numberForSwap);

    }

}


void Translation::translate(){

    QString path="https://translate.yandex.net/api/v1.5/tr/translate?key="+yandexKey+"&text="+bookWords.at(numberOfWord)+"&lang=en-ru";
    QNetworkRequest request=QNetworkRequest(QUrl(path));
    QNetworkReply* complitingRequest=translater->get(request);

}


///////////////////////////////////////слоты//////////////////////////////////////////////////////////////////////////////////////
void Translation::writeSystemAndListFiles(){

    QFile file("data/system.txt");

    if(!file.open(QIODevice::WriteOnly)) emit errorSignal("Error of open system file for writing");
    else{
        QTextStream stream(&file);
        stream<<"1"<<"\r\n";
        stream<<QString::number(numberOfWord);
        file.close();
        }

    file.setFileName("data/words_list.txt");
    if(!file.open(QIODevice::WriteOnly)) emit errorSignal("Error of open list file for writing");
    else{
        QTextStream stream(&file);

        QList<QString>::iterator it;
        for(it=bookWords.begin(); it!=bookWords.end()-1; ++it) stream<<(*it)<<"\r\n";
        stream<<(*it);
        file.close();



    }
}


void Translation::slotDownloadFinished(QNetworkReply* complitingRequest){
    if(complitingRequest->error()!=QNetworkReply::NoError) emit errorSignal("Error of connection to server");
    else{
        QFile translateFile("data/last_translation.xml");
        if(translateFile.open(QIODevice::WriteOnly)){
            translateFile.write(complitingRequest->readAll());
            translateFile.close();
            xmlAnalysis("data/last_translation.xml");

        }


    }

}

void Translation::slotCheckTranslation(QString userTranslation){

     if(numberOfWord<bookWords.size()-1) ++numberOfWord;
    else numberOfWord=0;



    if(userTranslation==lastedTranslate) emit rightTranslationSignal(lastedTranslate);
    else emit wrongTranslationSignal(lastedTranslate);
    slotSendToTranslate();


}

void Translation::slotSendToTranslate(){

    translate();



}

void Translation::slotDontKnow(QString text,QString userTimer){

    if(numberOfWord<bookWords.size()-1) ++numberOfWord;
    else numberOfWord=0;

    emit dontKnowTranslationSignal(lastedTranslate);
    slotSendToTranslate();



}
