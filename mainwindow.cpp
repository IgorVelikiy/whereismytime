#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <psapi.h>
#include <Strsafe.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(*getAppName()));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("00:00:00"));
    ui->tableWidget->resizeColumnsToContents();
}

std::unique_ptr<QString> MainWindow::getAppName()
{
    DWORD pid;
    auto result = std::make_unique<QString>();
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
                            std::wstring v(reinterpret_cast<wchar_t*>(value), reinterpret_cast<wchar_t*>(value + len*2));
                            *result = QString::fromStdWString(v);
                        }

                    }
                }
            }
        }
    }
    return result;
}

MainWindow::~MainWindow()
{
    delete ui;
}
