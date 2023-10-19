#ifndef PLUGINMAINWINDOW_H
#define PLUGINMAINWINDOW_H

#include <QTWidgets\QMainWindow>

namespace Ui {
class PluginMainWindow;
}

class PluginMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PluginMainWindow(QWidget* parent = nullptr);
    ~PluginMainWindow();

    void Insert(const char* text);
    void Clear();

private:
    Ui::PluginMainWindow* ui;
};

#endif // PLUGINMAINWINDOW_H
