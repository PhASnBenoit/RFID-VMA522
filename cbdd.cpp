#include "cbdd.h"

CBdd::CBdd(QObject *parent) : QObject(parent)
{

}

int CBdd::badgeLu(QString id)
{
    if (!_db.open())
        return -1;
    int nbBip=1; // arrivée de l'étudiant
    QSqlQuery q;
    QDateTime dt = QDateTime::currentDateTime();
    // contrôle existence du badge


    // vérification entrée
    q.prepare("SELECT * FROM presences "
              "WHERE idBadge=:id "
              "AND date_deb=:dd "
              "AND date_fin IS NULL;");
    q.bindValue(":id", QVariant(id));
    q.bindValue(":dd", QVariant(dt));
    q.exec();
    if (q.size()==0) { // création de l'enregistrement
        q.prepare("INSERT INTO presences "
                  "VALUES (0, :id, :dd); ");
        q.bindValue(":id", QVariant(id));
        q.bindValue(":dd", QVariant(dt));
    } else { // mise à jour de l'enregistrement
        q.next();
        int pk = q.value(0).toInt();
        q.prepare("UPDATE presences "
                  "SET idBadge=:ide, date_fin=:dd "
                  "WHERE idPresence=:idp;");
        q.bindValue(":idp", pk);
        q.bindValue(":id", QVariant(id));
        q.bindValue(":dd", QVariant(dt));
        nbBip = 2; // sortie de l'étudiant
    } // else
    q.exec();
    _db.close();
    return nbBip;
}

QStringList CBdd::quiEtaitPresent(QDateTime dt)
{
    QSqlQuery q;
    QStringList presents;
    if (!_db.open())
        return QStringList(nullptr);
    q.prepare("SELECT nom, prenom, date_deb, date_fin "
              "FROM etudiants, presences "
              "WHERE etudiant.idBadge = presences.idBadge "
              "AND date_deb=:dd;");
    q.bindValue(":dt", QVariant(dt));
    q.exec();
    for(int i=0 ; i<q.size() ; i++) {
        q.next();
        presents.append(q.value(0).toString()+" "+
                        q.value(1).toString()+" "+
                        q.value(2).toString()+" "+
                        q.value(3).toString()+" ");
    } // for i
    _db.close();
    return presents;
}

bool CBdd::open(QString host, QString login, QString passwd, QString bdd)
{
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName(host);
    _db.setUserName(login);
    _db.setPassword(passwd);
    _db.setDatabaseName(bdd);
    return _db.open();
}
