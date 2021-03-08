#include "serveur.h"
#include "includers.h"

Serveur::Serveur()
{
    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, 37250)) // On veut pouvoir jouer en local, sur la même machine (IA) ou par internet donc on prend Any
    {
        // Si le serveur n'a pas été démarré correctement
        qDebug() << server->errorString();
    }
    else
    {
        // Si le serveur a été démarré correctement
        qDebug() << "Serveur démarré sur le port " + QString::number(server->serverPort());
        connect(server, SIGNAL(newConnection()), this, SLOT(joined()));
    }

    messageSize = 0;
}

void Serveur::joined()
{
    QTcpSocket *newClient = server->nextPendingConnection();
    clients << newClient;

    connect(newClient, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(newClient, SIGNAL(disconnected()), this, SLOT(clientDeconnection()));
}

void Serveur::receivedData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) //si on ne trouve pas l'envoyeur on arrête
        return;

    QDataStream in(socket);

    if (messageSize == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) // on n'a pas reçu la taille du message en entier
             return;

        in >> messageSize; // on récupère la taille du message
    }

    // Vérification si on a reçu le message en entier
    if (socket->bytesAvailable() < messageSize)
        return;

    // le message est reçu en entier
    QString message;
    in >> message;

    // on le renvoie à tout le monde
    sendAll(message);

    // réinitialisation de la taille
    messageSize = 0;
}

void Serveur::clientDeconnection()
{
    qDebug() << "Client déconnecté";

    //détermination du client déconnecté pour le retirer
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si le client à l'origine du signal n'est pas trouvé, on arrête la méthode
        return;

    clients.removeOne(socket);

    socket->deleteLater();
}

void Serveur::sendAll(const QString &message)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // Réservation de la place pour mettre la taille du message
    out << message; // Ajout du message
    out.device()->seek(0); // Curseur replacé
    out << (quint16) (paquet.size() - sizeof(quint16)); // Ajout de la taille du message


    // Envoi du message à tout le monde
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->write(paquet);
    }

}

int Serveur::nbConnecte(){ return clients.size(); }
