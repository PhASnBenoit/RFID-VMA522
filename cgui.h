#ifndef CGUI_H
#define CGUI_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class CGui;
}

class CGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit CGui(QWidget *parent = nullptr);
    ~CGui();

private:
    Ui::CGui *ui;
    QTimer _tmr;

signals:
    void sig_isCard();
    void sig_test();

public slots:
    void on_afficher(QString txt);
    void on_timeout();

private slots:
    void on_pbSS_clicked();
    void on_pbTest_clicked();
};

#endif // CGUI_H
