#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager())
{
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

Downloader::Downloader(const QString &url, QObject *parent) : QObject(parent), manager(new QNetworkAccessManager())
{
    this->URL = url;
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

Downloader::Downloader(const QString &url, const QString &filename, QObject *parent)
{
    this->URL = url;
   this->fileout = filename;
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData()
{
    QNetworkRequest request;
    request.setUrl(URL);
    manager->get(request);
}

void Downloader::loadData(const std::string &url, const std::string &outfile)
{
    setURL(QUrl(QString::fromStdString(url)));
    setFileout(QString::fromStdString(outfile));
    getData();
}

void Downloader::onResult(QNetworkReply *reply)
{
    qDebug() << "onResult()";
    // If an error occurs in the process of obtaining data
    if(reply->error()){
        // We inform about it and show the error information
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        // Otherwise we create an object file for use with
        QFile *file = new QFile(fileout);
        // Create a file, or open it to overwrite ...
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());  // ... and write all the information from the page file
            file->close();                  // close file
        emit onReady(fileout); // Sends a signal to the completion of the receipt of the file
        }
    }
}

const QString &Downloader::getFileout() const
{
    return fileout;
}

void Downloader::setFileout(const QString &newFileout)
{
    fileout = newFileout;
}

const QUrl &Downloader::getURL() const
{
    return URL;
}

void Downloader::setURL(const QUrl &newURL)
{
    URL = newURL;
}
