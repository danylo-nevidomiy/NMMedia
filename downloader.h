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
    Downloader(QObject *parent = 0);
    explicit Downloader(const QString &url, QObject *parent = 0);
    Downloader(const QString &url, const QString &filename, QObject *parent = 0);

    const QUrl &getURL() const;
    void setURL(const QUrl &newURL);

    const QString &getFileout() const;
    void setFileout(const QString &newFileout);
    void loadData(const std::string &url, const std::string &outfile);
signals:
    void onReady(QString name);

public slots:
    void getData();

    void onResult(QNetworkReply *reply);

private:
    QUrl URL;
    QString fileout;
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADER_H
