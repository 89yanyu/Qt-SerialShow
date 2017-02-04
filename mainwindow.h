#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void UpdateComboList();
    int m_TimerId;

private slots:
    void on_RefreshButton_clicked();

    void on_OpenButton_clicked();

    void on_SendButton_clicked();

public slots:
    void ProcRecvMsg();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serialport;
};

#endif // MAINWINDOW_H
