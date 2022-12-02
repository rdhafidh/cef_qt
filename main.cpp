#include "simple_app.h"
#include "simple_handler.h"
#include <QDesktopWidget>
#include <QApplication>
#include "windowbrowserwidget.h"
#include <QFile>
#include "dialogbrowserwidget.h"

void QCefInitSettings(CefSettings & settings)
{ 
	settings.multi_threaded_message_loop = true;//多线程消息循环
 
  	settings.log_severity = cef_log_severity_t::LOGSEVERITY_VERBOSE;
	settings.windowless_rendering_enabled = true;
	settings.no_sandbox = true;//沙盒 
}

int QCefInit(int& argc, char** argv)
{
	{
        //remove file debug.log if any
        QFile fn("debug.log");
        fn.remove();
    }
	HINSTANCE hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));
	CefMainArgs mainArgs(hInstance);
	CefRefPtr<SimpleApp> app(new SimpleApp); //CefApp实现，用于处理进程相关的回调。
	int exit_code = CefExecuteProcess(mainArgs, app.get(), nullptr);
	if (exit_code >= 0) {
		return exit_code;
	} 

	CefSettings settings;
	QCefInitSettings(settings);
	CefInitialize(mainArgs, settings, app, nullptr);
	return -1;
}

void CefQuit()
{
	//makesure SimpleHandler get closed before 
	//calling this function 
	CefShutdown();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	int result = QCefInit(argc, argv);
	if (result >= 0) {
		return result;
    } 
#if 0
    WindowBrowserWidget widget;
	widget.setStyleSheet("#WindowBrowserWidget { background-color: blue; }");
#else 
	{

	DialogBrowserWidget widget;
	widget.setStyleSheet("#DialogBrowserWidget { background-color: blue; }");
#endif
    auto rectBrowser = qApp->desktop()->screenGeometry();
    rectBrowser.setHeight(rectBrowser.height()-90);
    QString css= "QPushButton{ background-color: green; font-color: white; }";

    widget.SetShowBrowser("https://google.com",
		rectBrowser.size());
    QRect b_labelRect(rectBrowser.bottomLeft().x(),
          rectBrowser.bottomLeft().y(),
          rectBrowser.width(),90);
    widget.SetButtonCloseSetting(QRect(1135,690,220,64),css,"Close");
    widget.SetButtonReloadSetting(QRect(912,690,220,64),css,"Reload");
    widget.SetButtonForwadSetting(QRect(689,690,220,64),css,"Forward");
    widget.SetButtonBackwardSetting(QRect(466,690,220,64),css,"Back");

#if 0
    widget.showFullScreen(); 
	a.exec();
#else  
	widget.exec();
	
	}
#endif
	CefQuit();
	return 0;
}
