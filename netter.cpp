#include "netter.h"
#include <QNetworkSession>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkAccessManager>
#include <QCoreApplication>
#include <QStringList>
Netter::Netter(QObject *parent) :
    QObject(parent)
{
    if (QCoreApplication::arguments().count() > 1) {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        manager->get(QNetworkRequest(QUrl("http://qt-project.org")));

    } else {

        QNetworkConfigurationManager *m_nmanager = new QNetworkConfigurationManager(this);
        connect(m_nmanager,SIGNAL(onlineStateChanged(bool)),
                this,SLOT(onlineStateChanged(bool)));
        QNetworkConfiguration defaultConfig = m_nmanager->defaultConfiguration();

        // If default configuration is not valid, look for a valid one
        qDebug() << Q_FUNC_INFO << "number of configs" << m_nmanager->allConfigurations().count();
        qDebug() << "default cofig" << defaultConfig.name();

        foreach (const QNetworkConfiguration& cfg, m_nmanager->allConfigurations()) {
            qDebug() << "Found" << cfg.name();
//            if (!defaultConfig.isValid()) {
//                if (cfg.isValid()) {
//                    defaultConfig = cfg;
//                }
//            }
        }

        if (!defaultConfig.isValid()) {
            qWarning() << Q_FUNC_INFO << "No valid  network configuration found.";
        } else {
            qDebug() << defaultConfig.name()
                     << defaultConfig.bearerTypeName()
                     <<  defaultConfig.state()
                      <<  defaultConfig.type();
            if ((defaultConfig.state() & QNetworkConfiguration::Defined) == QNetworkConfiguration::Defined)
                qDebug() << "Defined";
            if ((defaultConfig.state() & QNetworkConfiguration::Discovered) == QNetworkConfiguration::Discovered)
                qDebug() << "Discovered";
            if ((defaultConfig.state() & QNetworkConfiguration::Active) == QNetworkConfiguration::Active)
                qDebug() << "Active";
            QNetworkSession *m_networkSession = new QNetworkSession(defaultConfig);
            connect(m_networkSession,SIGNAL(opened()),this,SLOT(opened()));
            m_networkSession->open();

        }
    }

}

void Netter::onlineStateChanged(bool isOnline)
{
    qDebug() << Q_FUNC_INFO << isOnline;
}

void Netter::opened()
{
    qDebug() << Q_FUNC_INFO << "<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>";
}

void Netter::replyFinished(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO << reply->error();
}
