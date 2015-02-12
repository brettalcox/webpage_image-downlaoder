#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <QString>
#include <curl/curl.h>

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
    void downloadFile(char*, QString);

    private slots:
        void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString urlName;
    QString threadUrl;
    QString imageUrl;
};

#endif // MAINWINDOW_H
