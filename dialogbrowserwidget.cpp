#include "dialogbrowserwidget.h"
#include "cefosrwidget.h"
#include "qnamespace.h"
#include <QPushButton>


DialogBrowserWidget::DialogBrowserWidget(QWidget *parent) : QDialog{parent} {
  setObjectName("DialogBrowserWidget");
  setWindowState(Qt::WindowFullScreen);
  
}

DialogBrowserWidget::~DialogBrowserWidget() {}

void DialogBrowserWidget::SetButtonCloseSetting(const QRect &rect,
                                                const QString &css,
                                                const QString &text) {
  m_closeButton.reset(new QPushButton(this));
  m_closeButton->setGeometry(rect);
  m_closeButton->setStyleSheet(css);
  m_closeButton->setText(text);
  connect(m_closeButton.data(), SIGNAL(clicked()), this, SLOT(reject()));
  connect(m_closeButton.data(), SIGNAL(clicked()), this, SIGNAL(OnClose()));
}

void DialogBrowserWidget::SetButtonReloadSetting(const QRect &rect,
                                                 const QString &css,
                                                 const QString &text) {
  m_reloadButton.reset(new QPushButton(this));
  m_reloadButton->setGeometry(rect);
  m_reloadButton->setStyleSheet(css);
  m_reloadButton->setText(text);
  connect(m_reloadButton.data(), SIGNAL(clicked()), this, SLOT(OnReload()));
}

void DialogBrowserWidget::SetButtonForwadSetting(const QRect &rect,
                                                 const QString &css,
                                                 const QString &text) {
  m_forwardButton.reset(new QPushButton(this));
  m_forwardButton->setGeometry(rect);
  m_forwardButton->setStyleSheet(css);
  m_forwardButton->setText(text);
  connect(m_forwardButton.data(), SIGNAL(clicked()), this, SLOT(OnForward()));
}

void DialogBrowserWidget::SetButtonBackwardSetting(const QRect &rect,
                                                   const QString &css,
                                                   const QString &text) {
  m_backButton.reset(new QPushButton(this));
  m_backButton->setGeometry(rect);
  m_backButton->setStyleSheet(css);
  m_backButton->setText(text);
  connect(m_backButton.data(), SIGNAL(clicked()), this, SLOT(OnBackWard()));
}

bool DialogBrowserWidget::SetShowBrowser(const QString &url,
                                         const QSize &size) {
  m_browserWidget.reset(new CefOSRWidget(this));
  m_browserWidget->setGeometry(0, 0, size.width(), size.height());
  return m_browserWidget->Show(url, size);
}

void DialogBrowserWidget::UpdateGotoSite(const QString &url) {
  if (m_browserWidget) {
    m_browserWidget->UpdateGotoSite(url);
  }
}

void DialogBrowserWidget::OnReload() {
  if (m_browserWidget) {
    m_browserWidget->OnReload();
  }
}

void DialogBrowserWidget::OnForward() {
  if (m_browserWidget) {
    m_browserWidget->OnForward();
  }
}

void DialogBrowserWidget::OnBackWard() {
  if (m_browserWidget) {
    m_browserWidget->OnBackWard();
  }
}
