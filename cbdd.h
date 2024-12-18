#ifndef CBDD_H
#define CBDD_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>

class CBdd : public QObject
{
    Q_OBJECT
public:
    explicit CBdd(QObject *parent = nullptr);
    int badgeLu(QString id);
    QStringList quiEtaitPresent(QDateTime dt);

private:
    QSqlDatabase _db;
    bool open(QString host="192.167.7.100",
              QString login="badgeuse",
              QString passwd="badgeuse",
              QString bdd="badgeuse");
signals:

public slots:
};

#endif // CBDD_H
