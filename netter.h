#ifndef NETTER_H
#define NETTER_H

#include <QObject>
#include <QNetworkReply>

class Netter : public QObject
{
    Q_OBJECT
public:
    explicit Netter(QObject *parent = 0);
    
signals:
    
public slots:
    void onlineStateChanged(bool isOnline);
    void opened();
    void replyFinished(QNetworkReply*);
};

#endif // NETTER_H
