#include "capp.h"

CApp::CApp(QObject *parent) : QObject(parent)
{
    _rfid.PCD_Init();
    _gui = new CGui(nullptr);
    _gui->show();
    connect(_gui, &CGui::sig_isCard, this, &CApp::on_isCard);
    connect(_gui, &CGui::sig_test, this, &CApp::on_test);
    connect(this, &CApp::sig_afficher, _gui, &CGui::on_afficher);
}

CApp::~CApp()
{
    delete _gui;
}

void CApp::on_isCard()
{
    bool is = _rfid.PICC_IsNewCardPresent();
    if (is) {
        emit sig_afficher("Card present !");
        if (_rfid.PICC_ReadCardSerial()) {
            QString id = QString::number(_rfid.uid.size);
            emit sig_afficher(id+" bytes read !");
        } // is
        QString ch;
        for(byte i = 0; i < _rfid.uid.size; ++i){
          if(_rfid.uid.uidByte[i] < 0x10){
             ch+=" 0";
             ch+=QString::number(_rfid.uid.uidByte[i],16);
          } else {
            ch+= " ";
            ch+= QString::number(_rfid.uid.uidByte[i], 16);
          } // else
        } // for i
        emit sig_afficher(ch);
    } // for id is
}

void CApp::on_test()
{
    if (_rfid.PCD_PerformSelfTest())
        emit sig_afficher("Test OK");
    else
        emit sig_afficher("Test_HS");
}
