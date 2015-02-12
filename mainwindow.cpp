#define CURL_STATICLIB
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    QString threadPath = "/home/brettalcox/Pictures/4chan/Threads/" + ui->lineEdit_3->text();
    QString imagePath = "/home/brettalcox/Pictures/4chan/" + ui->lineEdit_3->text();

    if (!ui->lineEdit->text().isEmpty()) {
        threadUrl = ui->lineEdit->text();
        char *charThread = new char[threadUrl.length() + 1];
        strcpy(charThread, threadUrl.toStdString().c_str());
        downloadFile(charThread, threadPath);
        delete [] charThread;
    } else {}

    if (!ui->lineEdit_2->text().isEmpty()) {
        imageUrl = ui->lineEdit_2->text();
        char *charImage = new char[imageUrl.length() + 1];
        strcpy(charImage, imageUrl.toStdString().c_str());
        downloadFile(charImage, imagePath);
        delete [] charImage;
    } else {}

}

void MainWindow::downloadFile(char *url, QString path) {

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
