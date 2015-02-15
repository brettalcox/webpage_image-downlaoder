#define CURL_STATICLIB
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

size_t writeToFile(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t writtenToFile;
    writtenToFile = fwrite(ptr, size, nmemb, stream);
    return writtenToFile;
}

QString urlData;

QString getData() {

    return urlData;
}

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        urlData.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

void MainWindow::on_pushButton_clicked()
{
    QString threadPath = "/home/brettalcox/Pictures/4chan/Threads/" + ui->lineEdit_3->text();
    QString imagePath = "/home/brettalcox/Pictures/4chan/" + ui->lineEdit_3->text();

    if (!ui->lineEdit->text().isEmpty()) {
        threadUrl = ui->lineEdit->text();
    } else {}

    downloadImageFile(threadUrl);


/*
    QString filePath = threadPath + ui->lineEdit_3->text();
    QFile outFile("anus");
    outFile.open(QIODevice::WriteOnly);
    outFile.write(downloadedData());
    outFile.close();
*/

}

void MainWindow::downloadImageFile(QString url) {



    QNetworkAccessManager *m_WebCtrl = new QNetworkAccessManager;
    connect(m_WebCtrl, SIGNAL(finished(QNetworkReply*)), SLOT(fileDownloaded(QNetworkReply*)));
    QUrl theUrl = url;
    QNetworkRequest request(theUrl);
    m_WebCtrl->get(request);

}

void MainWindow::fileDownloaded(QNetworkReply *pReply)
{
    QByteArray downloadedFile = NULL;
    downloadedFile = pReply->readAll();
    emit downloaded();

    QString filePath = threadPath + ui->lineEdit_3->text();
    QFile outFile(filePath);
    outFile.open(QIODevice::WriteOnly);
    outFile.write(downloadedFile);
    outFile.close();

    pReply->deleteLater();


}

QByteArray MainWindow::downloadedData()
{
    return *m_DownloadedData;
}











    /*

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            //curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            //fclose(file);

        }
    QString dataFromUrl = getData();
    char *threadHtml = new char[dataFromUrl.length() + 1];
    strcpy(threadHtml, dataFromUrl.toStdString().c_str());

    char* imgtag = NULL;
     for (imgtag = strstr(threadHtml, "<meta ");
          imgtag != NULL;
          imgtag = strstr(imgtag+4, "<meta "))
       {
         char* srcattr = strstr(imgtag, "src=");

         if (srcattr) {
                QString theUrl = strtok(srcattr+7, "\"");
                char *parsedUrl = new char[theUrl.length() + 1];
                strcpy(parsedUrl, theUrl.toStdString().c_str());

             // parse the src just after srcattr+4
             // build an URL for the image using snprintf
             // retreive that image using libcurl

                CURL *curl;
                CURLcode res;
                FILE *file;
                QString name = "doody.jpg";
                path += name;
                char *outputFile = new char[path.length() + 1];
                strcpy(outputFile, path.toStdString().c_str());
                file = fopen(outputFile, "wb");

                curl = curl_easy_init();
                    if(curl) {
                        curl_easy_setopt(curl, CURLOPT_URL, parsedUrl);
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToFile);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
                        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
                        res = curl_easy_perform(curl);
                        curl_easy_cleanup(curl);
                        fclose(file);

                   }
                delete [] parsedUrl;
                delete [] outputFile;
         }
        }

     delete [] threadHtml;
*/





void MainWindow::downloadImage(char *url, QString path) {

    CURL *curl;
    CURLcode res;
    FILE *file;

    char *outputFile = new char[path.length() + 1];
    strcpy(outputFile, path.toStdString().c_str());
    file = fopen(outputFile, "wb");

    curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToFile);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(file);

        }
}

void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::close();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}
