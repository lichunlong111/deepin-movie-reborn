#ifndef _DMR_ONLINE_SUB_H
#define _DMR_ONLINE_SUB_H 

#include <QtWidgets>
#include <QtNetwork>


namespace dmr {
struct ShooterSubtitleMeta {
    int id; 
    int delay;
    QString desc;
    QString ext;
    QString link; // url to download
    QString local; // saved position when downloaded
};

class OnlineSubtitle: public QObject {
    Q_OBJECT
public:
    static OnlineSubtitle& get();
    QString storeLocation();

public slots:
    void requestSubtitle(const QUrl& url);

private slots:
    void replyReceived(QNetworkReply*);  
    void downloadSubtitles();

signals:
    void subtitlesDownloadedFor(const QUrl& url, const QList<QString>& filenames);

private:
    QString _defaultLocation;
    QNetworkAccessManager *_nam {nullptr};

    int _pendingDownloads {0}; // this should equal to _subs.size() basically
    QList<ShooterSubtitleMeta> _subs;
    QFileInfo _lastReqVideo;

    OnlineSubtitle();
};
}

#endif /* ifndef _DMR_ONLINE_SUB_H */