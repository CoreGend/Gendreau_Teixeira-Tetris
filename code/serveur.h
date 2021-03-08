#ifndef SERVEUR_H
#define SERVEUR_H

#include <QtWidgets>
#include <QtNetwork>


class Serveur : public QWidget
{
    Q_OBJECT

public:
        Serveur();
        void sendAll(const QString &message);
        int nbConnecte();

private slots:
        void joined();
        void receivedData();
        void clientDeconnection();

private:
        QTcpServer *server;
        QList<QTcpSocket *> clients;
        quint16 messageSize;
};

#endif // SERVEUR_H
