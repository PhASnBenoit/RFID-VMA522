#ifndef CAPP_H
#define CAPP_H

#include <QObject>
#include <QString>
#include "cgui.h"
#include "CMFRC522.h"

class CApp : public QObject
{
    Q_OBJECT
public:
    explicit CApp(QObject *parent = nullptr);
    ~CApp();

private:
    CGui *_gui;
    CMFRC522 _rfid;

signals:
    void sig_afficher(QString txt);

public slots:
    void on_isCard();
    void on_test();

};

#endif // CAPP_H
