#include "mainwindow.h"
#include "qqmlcontext.h"
#include "qqmlengine.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QQuickWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSender = new QUdpSocket(this);

    udpReceiver = new UDPReceiver(this);

    connect(udpReceiver, &UDPReceiver::signalReceived, this, &MainWindow::onSignalReceived);

    // Nhúng QML vào UI
    QQuickWidget *qmlWidget = new QQuickWidget(this);
    // Truyền SerialReader vào QML
    qmlWidget->engine()->rootContext()->setContextProperty("udpReceiver", udpReceiver);

    qmlWidget->setSource(QUrl("qrc:/main.qml"));
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);


    // Đưa vào layout của QWidget trong file .ui
    if (!ui->quickWidget->layout()) {
        ui->quickWidget->setLayout(new QVBoxLayout());
    }
    ui->quickWidget->layout()->addWidget(qmlWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "udpReceiver pointer:" << udpReceiver;

}

void MainWindow::onSignalReceived() {
    // Hiển thị MessageBox khi có tín hiệu từ cổng 12346
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Automatic Parking Mode",
                                  "Do you want to use automatic parking mode?",
                                  QMessageBox::Yes | QMessageBox::No,  // Các nút
                                  QMessageBox::No); // Nút mặc định

    if (reply == QMessageBox::Yes) {
        qDebug() << "User wants to use automatic parking mode";
        sendUdpMessage("Yes");  // Gửi "Yes" đến Python
    } else {
        qDebug() << "User does not want to use automatic parking mode";
        sendUdpMessage("No");  // Gửi "No" đến Python
    }

}
