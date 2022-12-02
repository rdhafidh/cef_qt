#include "cefosrwidget.h"
#include "internal/cef_string.h"
#include "qmessagebox.h"
#include "qwidget.h"
#include "update_events.h"

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QRect>
#include <QResizeEvent>
#include <QTimer>
#include <string>

CefOSRWidget::CefOSRWidget(QWidget *parent) : QWidget(parent) {}
void CefOSRWidget::showEvent(QShowEvent *event) {
  QWidget::showEvent(event);
  m_afterShow = true;
}
void CefOSRWidget::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  OnResized();

  /*CefRefPtr<CefBrowser> pBrower = getBrowser();
  if (m_afterShow) {
    if (pBrower) {
      m_afterShow = false;
      QTimer::singleShot(50, this,SLOT(OnResized()));
    }
  } else {
    if (pBrower)
      pBrower->GetHost()->WasResized();
  }*/
}

void CefOSRWidget::OnResized() {
  m_browserHander->setWindowRect(rect());
  CefRefPtr<CefBrowser> pBrower = getBrowser();
  if (pBrower) {
    pBrower->GetHost()->WasResized();
    //pBrower->GetHost()->SetMouseCursorChangeDisabled(false);
  }
}

void CefOSRWidget::OnReload() {
  CefRefPtr<CefBrowser> pBrower = getBrowser();
  if (pBrower) {
    if (pBrower->IsLoading()) {
      pBrower->StopLoad();
    }
    pBrower->Reload();
  }
}

void CefOSRWidget::OnForward() {
  CefRefPtr<CefBrowser> pBrower = getBrowser();
  if (pBrower) {
    if (pBrower->CanGoForward()) {
      if (pBrower->IsLoading()) {
        pBrower->StopLoad();
      }
      pBrower->GoForward();
    }
  }
}

void CefOSRWidget::OnBackWard() {
  CefRefPtr<CefBrowser> pBrower = getBrowser();
  if (pBrower) {
    if (pBrower->CanGoBack()) {
      if (pBrower->IsLoading()) {
        pBrower->StopLoad();
      }
      pBrower->GoBack();
    }
  }
}

void CefOSRWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter painter(this);
  QRect rect = this->rect();
  painter.drawImage(QRect(rect.left(), rect.top(), rect.width(), rect.height()),
                    m_image, m_image.rect());
}

bool CefOSRWidget::event(QEvent *event) {
  if (event->type() == UpdateEvent::eventType) {
    UpdateEvent *updateEvent = dynamic_cast<UpdateEvent *>(event);
    m_image = updateEvent->m_image;
    this->update();
    return true;
  }
  return QWidget::event(event);
}

CefRefPtr<CefBrowser> CefOSRWidget::getBrowser() {
  if (!m_browserHander.get()) {
    return nullptr;
  }
  std::list<CefRefPtr<CefBrowser>> cefBrowerList =
      m_browserHander->getCefBrowerList();
  if (cefBrowerList.size() == 0) {
    qDebug()
        << "cefBrowerList.size() == 0"; //浏览器是异步创建的，OnAfterCreated是在创建成功后调用的
    return nullptr;
  }
  return cefBrowerList.front();
}

CefOSRWidget::~CefOSRWidget() {
  if (cefWndInfo) {
    delete cefWndInfo;
  }
  if (cefBrowSetting) {
    delete cefBrowSetting;
  }
}

bool CefOSRWidget::Show(const QString &url, const QSize &size) {
  HWND wnd = (HWND)this->winId();
  // QString indexUrl =
  // "https://127.0.0.1:9443/opa?JwToken=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJuYW1laWQiOiIyNDIwNDYtNDk3Njg1LTA3MjM3MCIsIm5iZiI6MTY0NTc4MzA2OCwiZXhwIjoxNjQ1Nzg2NjY4LCJpYXQiOjE2NDU3ODMwNjh9.sdvEBpvdviWsCQuYK556swh5TGDn1nd1zXzmKdAVARA&SessionId=242046-497685-072370";
  RegisterTouchWindow(wnd, 0);
  cefWndInfo = new CefWindowInfo();
  // cefWndInfo->SetAsWindowless(wnd);
  cefWndInfo->SetAsChild((CefWindowHandle)winId(),
                         CefRect{0, 0, size.width(), size.height()});
  cefBrowSetting = new CefBrowserSettings();

  cefBrowSetting->windowless_frame_rate = 60;

  m_browserHander = CefRefPtr<SimpleHandler>(new SimpleHandler(false));
  m_browserHander->setReceiver(this);
  m_browserHander->setWindowRect(QRect(0, 0, size.width(), size.height()));

  CefString m_wUrl;
  m_wUrl.FromString(url.toStdString());
    
  bool isCreated = CefBrowserHost::CreateBrowser(*cefWndInfo, m_browserHander,
                                                 m_wUrl, *cefBrowSetting, nullptr,nullptr);
  return isCreated;
}

void CefOSRWidget::UpdateGotoSite(const QString &url) {
  if (!url.isEmpty())
    return;

  CefRefPtr<CefBrowser> pBrower = getBrowser();
  if (pBrower) {
    if (pBrower->IsLoading()) {
      pBrower->StopLoad();
    }
    pBrower->GetMainFrame()->LoadURL(url.toStdString());
  }
}
