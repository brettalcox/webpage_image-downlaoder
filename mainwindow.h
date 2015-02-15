#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <QString>
#include <curl/curl.h>

#include <QObject>
#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //size_t writeToFile(void *ptr, size_t size, size_t nmemb, FILE *stream);
    void downloadImageFile(QString);
    void downloadImage(char*, QString);
    QByteArray downloadedData();

signals:
    void downloaded();

    private slots:
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_3_clicked();
        void fileDownloaded(QNetworkReply* pReply);

private:
    Ui::MainWindow *ui;
    QString urlName;
    QString threadUrl;
    QString imageUrl;

    QString threadPath = "/home/brettalcox/Pictures/4chan/Threads/";
    //QNetworkAccessManager m_WebCtrl;
    QByteArray *m_DownloadedData;
};

#endif // MAINWINDOW_H
