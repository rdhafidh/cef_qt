#ifndef WINDOWBROWSERWIDGET_H
#define WINDOWBROWSERWIDGET_H

#include <QScopedPointer>
#include <QWidget>

class CefOSRWidget;
class QPushButton;

class WindowBrowserWidget : public QWidget {
  Q_OBJECT
public:
  explicit WindowBrowserWidget(QWidget *parent = nullptr);
  ~WindowBrowserWidget();
  void SetButtonCloseSetting(const QRect &rect, const QString &css,
                             const QString &text);
  void SetButtonReloadSetting(const QRect &rect, const QString &css,
                              const QString &text);
  void SetButtonForwadSetting(const QRect &rect, const QString &css,
                              const QString &text);
  void SetButtonBackwardSetting(const QRect &rect, const QString &css,
                                const QString &text);

  bool SetShowBrowser(const QString &url, const QSize &size);

Q_SIGNALS:
  void OnClose();

public Q_SLOTS:
  void OnReload();
  void OnForward();
  void OnBackWard();

private Q_SLOTS:
  void UpdateGotoSite(const QString &url);

private:
  QScopedPointer<CefOSRWidget> m_browserWidget;

  QScopedPointer<QPushButton> m_closeButton;
  QScopedPointer<QPushButton> m_reloadButton;
  QScopedPointer<QPushButton> m_forwardButton;
  QScopedPointer<QPushButton> m_backButton;
};

#endif // WINDOWBROWSERWIDGET_H
