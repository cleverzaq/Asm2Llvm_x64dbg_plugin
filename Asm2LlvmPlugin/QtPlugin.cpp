#include "QtPlugin.h"
#include "PluginTabWidget.h"
#include "pluginmain.h"

#include <QtCore\QFile>
#include <QPlainTextEdit>

static PluginTabWidget* pluginTabWidget;
static HANDLE hSetupEvent;
static HANDLE hStopEvent;

static QByteArray getResourceBytes(const char* path)
{
    QByteArray b;
    QFile s(path);
    if(s.open(QFile::ReadOnly))
        b = s.readAll();
    return b;
}

static QWidget* getParent()
{
    return QWidget::find(WId(hwndDlg));
}

void QtPlugin::Init()
{
    hSetupEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
    hStopEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
}

void QtPlugin::Setup()
{
    QWidget* parent = getParent();

    pluginTabWidget = new PluginTabWidget(parent);
    GuiAddQWidgetTab(pluginTabWidget);

    SetEvent(hSetupEvent);
}

void QtPlugin::WaitForSetup()
{
    WaitForSingleObject(hSetupEvent, INFINITE);
}

void QtPlugin::Stop()
{
    GuiCloseQWidgetTab(pluginTabWidget);
    pluginTabWidget->close();

    delete pluginTabWidget;

    SetEvent(hStopEvent);
}

void QtPlugin::WaitForStop()
{
    WaitForSingleObject(hStopEvent, INFINITE);
}

void QtPlugin::ShowTab()
{
    GuiShowQWidgetTab(pluginTabWidget);
}

void QtPlugin::Insert(const char* text)
{
    pluginTabWidget->Insert(text);
}

void QtPlugin::Clear()
{
    pluginTabWidget->Clear();
}