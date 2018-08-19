#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db()
{
    this->setWindowIcon(QIcon(":/images/icon.xpm"));
    ui->setupUi(this);
    ui->tableView->setModel(db.tableModel.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->show();
}

QString MainWindow::getAppName() const
{
    DWORD pid;
    QString appName;
    GetWindowThreadProcessId(GetForegroundWindow(),&pid);
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    wchar_t fileName[256];
    GetModuleFileNameEx(hProc,NULL,fileName,256);
    CloseHandle(hProc);
    const DWORD infoSize = GetFileVersionInfoSizeW(fileName, NULL);
    if (infoSize > 0)
    {
        auto info = std::make_unique<BYTE[]>(infoSize);
        if (GetFileVersionInfoW(fileName, 0, infoSize, info.get()))
        {
            const Translation* translation;
            UINT translationSize;
            if (VerQueryValueW(info.get(), L"\\VarFileInfo\\Translation", (LPVOID*)&translation, &translationSize))
            {
                for (int i = 0; i < translationSize / sizeof(Translation); ++i)
                {
                    const size_t BUFFER_LEN = 64;
                    WCHAR subBlockName[BUFFER_LEN];
                    HRESULT hResult = StringCchPrintfW(subBlockName,
                        BUFFER_LEN,
                        L"\\StringFileInfo\\%04x%04x\\FileDescription",
                        translation[i].language,
                        translation[i].codePage);
                    if (SUCCEEDED(hResult))
                    {
                        LPBYTE value;
                        UINT len;
                        if (VerQueryValueW(info.get(), subBlockName, (LPVOID*)&value, &len))
                        {
                            appName = QString::fromStdWString(std::wstring(reinterpret_cast<wchar_t*>(value), reinterpret_cast<wchar_t*>(value + len*2 - 2)));
                        }

                    }
                }
            }
        }
    }
    return appName;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    this->hide();
}

void MainWindow::timeUpdater()
{
    using namespace std::chrono_literals;
    QString currentAppName, prevAppName = "";
    std::unique_ptr<Timer> appTimer;
    while (isWork)
    {
        std::this_thread::sleep_for(300ms);
        if ((currentAppName = getAppName()) != prevAppName)
        {
            if (!prevAppName.isEmpty())
                db.setAppTime(prevAppName, QString::fromStdString(appTimer->stop()));
            if ((appTimer = db.getAppTime(currentAppName)) == nullptr)
            {
                appTimer = std::make_unique<Timer>();
                if (!currentAppName.isEmpty())
                    db.addApp(currentAppName);
            }
            prevAppName = std::move(currentAppName);
        }
    }
    db.setAppTime(prevAppName, QString::fromStdString(appTimer->stop()));
}

void MainWindow::stopTimeUpdater()
{
    isWork = false;
}

void MainWindow::showOnDoubleClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::ActivationReason::DoubleClick)
    {
        db.tableModel->select();
        ui->tableView->setModel(db.tableModel.get());
        this->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
