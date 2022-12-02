#ifndef DIALOGBROWSERWIDGET_H
#define DIALOGBROWSERWIDGET_H

#include <QScopedPointer>
#include <QDialog>

class CefOSRWidget;
class QPushButton;

class DialogBrowserWidget : public QDialog {
  Q_OBJECT
public:
  explicit DialogBrowserWidget(QWidget *parent = nullptr);
  ~DialogBrowserWidget();
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

#endif // DialogBROWSERWIDGET_H
