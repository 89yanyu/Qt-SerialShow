#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_TimerId = startTimer(1000);
}

void MainWindow::UpdateComboList()
{
    QList<QSerialPortInfo> PortList = QSerialPortInfo::availablePorts();
    ui->comboBox->clear();
    foreach (auto i, PortList)
    {
        ui->comboBox->addItem(i.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    killTimer(m_TimerId);
}

void MainWindow::on_pushButton_clicked()
{
//    ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);
//    ui->textBrowser->insertPlainText(ui->textEdit->toPlainText());
//    ui->textEdit->setPlainText("");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (ui->comboBox->isEnabled()) return;
    UpdateComboList();
}
