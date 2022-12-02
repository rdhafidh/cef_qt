#ifndef CEFOSRWIDGET_H
#define CEFOSRWIDGET_H
#include "internal/cef_ptr.h"
#include "simple_handler.h"
#include <QScopedPointer>
#include <QWidget>

class CefWindowInfo;
class QPushButton;

class CefOSRWidget : public QWidget {
  Q_OBJECT
public:
  CefOSRWidget(QWidget *parent = nullptr);
  ~CefOSRWidget() override;

  bool Show(const QString &url, const QSize &size);

public Q_SLOTS:
  void UpdateGotoSite(const QString &url);
  void OnReload();
  void OnForward();
  void OnBackWard();

protected:
  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  bool event(QEvent *event) override;
  void showEvent(QShowEvent *event) override;
  CefRefPtr<CefBrowser> getBrowser();

private Q_SLOTS:
  void OnResized();

private:
  CefBrowserSettings *cefBrowSetting = nullptr;
  CefWindowInfo *cefWndInfo = nullptr;
  CefRefPtr<SimpleHandler> m_browserHander;
  QImage m_image;
  bool m_afterShow = false;
};

#endif
