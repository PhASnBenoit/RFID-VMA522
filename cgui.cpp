#include "cgui.h"
#include "ui_cgui.h"

CGui::CGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CGui)
{
    ui->setupUi(this);
    _tmr.setInterval(1000);
    connect(&_tmr, &QTimer::timeout, this, &CGui::on_timeout);
}

CGui::~CGui()
{
    _tmr.stop();
    delete ui;
}

void CGui::on_afficher(QString txt)
{
    ui->textEdit->append(txt);
}

void CGui::on_timeout()
{
    on_afficher("Test présence...");
    emit sig_isCard();
}

void CGui::on_pbSS_clicked()
{
    if (_tmr.isActive()) {
        _tmr.stop();
    } else {
        _tmr.start();
    }
}

void CGui::on_pbTest_clicked()
{
    emit sig_test();
}
