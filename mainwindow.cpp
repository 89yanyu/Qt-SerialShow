#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serialport(new QSerialPort)
{
    ui->setupUi(this);
    UpdateComboList();
    ui->textBrowser->setLineWrapMode(QTextBrowser::NoWrap);
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
    delete m_serialport;
}

void MainWindow::ProcRecvMsg()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
    ui->textBrowser->insertPlainText(QString(m_serialport->readAll()));
}

void MainWindow::on_RefreshButton_clicked()
{
    UpdateComboList();
}

void MainWindow::on_OpenButton_clicked()
{
    if (ui->OpenButton->text() == "打开端口")
    {
        m_serialport->setPortName(ui->comboBox->currentText());
        if (!m_serialport->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, "错误", "串口打开失败");
            return;
        }

        m_serialport->setBaudRate(QSerialPort::Baud115200);
        m_serialport->setStopBits(QSerialPort::OneStop);
        m_serialport->setDataBits(QSerialPort::Data8);
        m_serialport->setParity(QSerialPort::NoParity);
        m_serialport->setFlowControl(QSerialPort::NoFlowControl);
        connect(m_serialport, SIGNAL(readyRead()), this, SLOT(ProcRecvMsg()));
        ui->OpenButton->setText("关闭端口");
    }
    else if (ui->OpenButton->text() == "关闭端口")
    {
        if (m_serialport->isOpen())
        {
            m_serialport->close();
        }
        ui->OpenButton->setText("打开端口");
    }
}

void MainWindow::on_SendButton_clicked()
{
    if (m_serialport->isOpen())
    {
        QByteArray buff = ui->textEdit->toPlainText().toLocal8Bit();
        if (m_serialport->write(buff) != buff.length())
        {
            if (m_serialport->isOpen())
            {
                m_serialport->close();
            }
            ui->OpenButton->setText("打开端口");
            UpdateComboList();
        }
        ui->textEdit->clear();
    }
    else
    {
        QMessageBox::critical(this, "错误", "串口未打开");
    }
}
