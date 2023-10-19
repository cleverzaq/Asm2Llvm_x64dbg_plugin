#include "PluginMainWindow.h"
#include "ui_PluginMainWindow.h"

PluginMainWindow::PluginMainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::PluginMainWindow)
{
    ui->setupUi(this);
}

void PluginMainWindow::Insert(const char* text)
{
    ui->editText->insertPlainText(QApplication::translate("PluginMainWindow", text, nullptr));
}

void PluginMainWindow::Clear()
{
    ui->editText->clear();
}

PluginMainWindow::~PluginMainWindow()
{
    delete ui;
}
