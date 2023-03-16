#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(const QString &url, QObject *parent = 0);
    Downloader(const QString &url, const QString &filename, QObject *parent = 0);

    const QUrl &getURL() const;
    void setURL(const QUrl &newURL);

    const QString &getFileout() const;
    void setFileout(const QString &newFileout);

signals:
    void onReady();

public slots:
    void getData();
    void onResult(QNetworkReply *reply);

private:
    QUrl URL;
    QString fileout;
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADER_H
