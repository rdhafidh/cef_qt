#include "windowbrowserwidget.h"
#include "cefosrwidget.h"
#include <QPushButton>


WindowBrowserWidget::WindowBrowserWidget(QWidget *parent) : QWidget{parent} {
  setObjectName("WindowBrowserWidget");
}

WindowBrowserWidget::~WindowBrowserWidget() {}

void WindowBrowserWidget::SetButtonCloseSetting(const QRect &rect,
                                                const QString &css,
                                                const QString &text) {
  m_closeButton.reset(new QPushButton(this));
  m_closeButton->setGeometry(rect);
  m_closeButton->setStyleSheet(css);
  m_closeButton->setText(text);
  connect(m_closeButton.data(), SIGNAL(clicked()), this, SIGNAL(OnClose()));
}

void WindowBrowserWidget::SetButtonReloadSetting(const QRect &rect,
                                                 const QString &css,
                                                 const QString &text) {
  m_reloadButton.reset(new QPushButton(this));
  m_reloadButton->setGeometry(rect);
  m_reloadButton->setStyleSheet(css);
  m_reloadButton->setText(text);
  connect(m_reloadButton.data(), SIGNAL(clicked()), this, SLOT(OnReload()));
}

void WindowBrowserWidget::SetButtonForwadSetting(const QRect &rect,
                                                 const QString &css,
                                                 const QString &text) {
  m_forwardButton.reset(new QPushButton(this));
  m_forwardButton->setGeometry(rect);
  m_forwardButton->setStyleSheet(css);
  m_forwardButton->setText(text);
  connect(m_forwardButton.data(), SIGNAL(clicked()), this, SLOT(OnForward()));
}

void WindowBrowserWidget::SetButtonBackwardSetting(const QRect &rect,
                                                   const QString &css,
                                                   const QString &text) {
  m_backButton.reset(new QPushButton(this));
  m_backButton->setGeometry(rect);
  m_backButton->setStyleSheet(css);
  m_backButton->setText(text);
  connect(m_backButton.data(), SIGNAL(clicked()), this, SLOT(OnBackWard()));
}

bool WindowBrowserWidget::SetShowBrowser(const QString &url,
                                         const QSize &size) {
  m_browserWidget.reset(new CefOSRWidget(this));
  m_browserWidget->setGeometry(0, 0, size.width(), size.height());
  return m_browserWidget->Show(url, size);
}

void WindowBrowserWidget::UpdateGotoSite(const QString &url) {
  if (m_browserWidget) {
    m_browserWidget->UpdateGotoSite(url);
  }
}

void WindowBrowserWidget::OnReload() {
  if (m_browserWidget) {
    m_browserWidget->OnReload();
  }
}

void WindowBrowserWidget::OnForward() {
  if (m_browserWidget) {
    m_browserWidget->OnForward();
  }
}

void WindowBrowserWidget::OnBackWard() {
  if (m_browserWidget) {
    m_browserWidget->OnBackWard();
  }
}
