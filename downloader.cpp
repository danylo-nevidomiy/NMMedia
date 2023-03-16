#include "downloader.h"

Downloader::Downloader(const QString &url, QObject *parent) : QObject(parent)
{
    this->URL = url;
    // Initialize manager ...
    manager = new QNetworkAccessManager();
    // ... and connect the signal to the handler
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

Downloader::Downloader(const QString &url, const QString &filename, QObject *parent) : Downloader(url)
{
   this->fileout = filename;
}

void Downloader::getData()
{
    QNetworkRequest request;
    request.setUrl(URL);
    manager->get(request);
}

void Downloader::onResult(QNetworkReply *reply)
{
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
        qDebug() << "Downloading is completed";
        emit onReady(); // Sends a signal to the completion of the receipt of the file
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
