﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothUuid>
#include <QBluetoothSocket>
#include <QDockWidget>
#ifdef Q_OS_ANDROID
#include <QtAndroid>
#endif

#include "mysettings.h"
#include "plottab.h"
#include "ctrltab.h"
#include "datatab.h"
#include "devicetab.h"
#include "filetab.h"
#include "settingstab.h"
#include "serialpinout.h"
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void sendData(const QByteArray &data);
    void updateStatusBar();
    void updateWindowTitle(Connection::Type type);
    void updateRxTxLen(bool updateRx = true, bool updateTx = true);
    void clearSendedData();
    void clearReceivedData();
    void setTxDataRecording(bool enabled);
    void showUpTab(int id);
    void setFullScreen(bool isFullScreen);
    void onOpacityChanged(qreal value);
    void onDockTopLevelChanged(bool topLevel); // for opacity

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyReleaseEvent(QKeyEvent* e) override;
private slots:
    void readData();
    void onStateButtonClicked();
    void updateRxUI();

#ifndef Q_OS_ANDROID
    void onTopBoxClicked();
#endif

    void onIODeviceConnected();
    void onIODeviceDisconnected();
    void onIODeviceConnectFailed(const QString& info);
private:
    Ui::MainWindow *ui;
    void initUI();

    QMenu* contextMenu;
    QAction* dockAllWindows;
    QAction* myInfo;
    QAction* currVersion;
    QAction* checkUpdate;

    Connection* IOConnection = nullptr;

    QPushButton* stateButton;
    QLabel* TxLabel;
    QLabel* RxLabel;
    QLabel* connArgsLabel;
    SerialPinout* serialPinout;

    bool m_TxDataRecording = true;
    QByteArray rawReceivedData;
    qsizetype m_RxCount = 0;
    QByteArray rawSendedData;
    qsizetype m_TxCount = 0;
    QByteArray RxUIBuf;

    QTimer* updateUITimer;

    MySettings* settings;
    PlotTab* plotTab;
    CtrlTab* ctrlTab;
    DataTab* dataTab;
    DeviceTab* deviceTab;
    FileTab* fileTab;
    SettingsTab* settingsTab;
    QList<QDockWidget*> dockList;

#ifndef Q_OS_ANDROID
    QCheckBox* onTopBox;

#else
    qint64 m_keyBackTick = 0;
#endif

    void dockInit();
    void initTabs();
};
#endif // MAINWINDOW_H
