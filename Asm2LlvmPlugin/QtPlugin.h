#ifndef QTPLUGIN_H
#define QTPLUGIN_H

namespace QtPlugin
{
    void Init();
    void Setup();
    void WaitForSetup();
    void Stop();
    void WaitForStop();
    void ShowTab();

    void Insert(const char* text);
    void Clear();
} //QtPlugin

#endif // QTPLUGIN_H
