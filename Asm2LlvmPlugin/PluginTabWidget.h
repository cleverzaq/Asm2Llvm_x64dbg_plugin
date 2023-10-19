#ifndef PLUGINTABWIDGET_H
#define PLUGINTABWIDGET_H

#include <QtWidgets\QWidget>
#include "PluginMainWindow.h"

class PluginTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PluginTabWidget(QWidget* parent = 0);

    void Insert(const char* text);
    void Clear();

protected:
    void closeEvent(QCloseEvent* event);

private:
    PluginMainWindow* mPluginMainWindow;
};

#endif // PLUGINTABWIDGET_H
