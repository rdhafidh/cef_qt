// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"

#include <list>
#include <QObject>
#include <QRect>

class SimpleHandler : public CefClient,
                      public CefDisplayHandler,
                      public CefLifeSpanHandler,
                      public CefLoadHandler,
					  public CefRenderHandler {
 public:
  explicit SimpleHandler(bool use_views);
  ~SimpleHandler();

  // Provide access to the single global instance of this object.
  static SimpleHandler* GetInstance();

  // CefClient methods:
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override {
    return this;
  }
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
    return this;
  }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

  // CefDisplayHandler methods:
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) override;

  // CefLifeSpanHandler methods:
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  // CefLoadHandler methods:
  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl) override;
						   
  virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                       PaintElementType type,
                       const RectList& dirtyRects,
                       const void* buffer,
                       int width,
                       int height) override;
					   
  virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;

  // Request that all existing browser windows close.
  void CloseAllBrowsers(bool force_close);

  bool IsClosing() const { return is_closing_; }
  
  std::list<CefRefPtr<CefBrowser> > getCefBrowerList(){
	  return browser_list_;
  }
  
  void setWinHandle(HWND hwnd){
	m_hwnd = hwnd;
  }
  
  void setReceiver(QObject *receiver){
	m_receiver = receiver;
  }
  
  void setWindowRect(QRect &rc){
	m_windowRect = rc;
  }

 private:
  float GetDeviceScaleFactor(){
	  return 1.0;
  }
  inline int LogicalToDevice(int value, float device_scale_factor) {
    float scaled_val = static_cast<float>(value) * device_scale_factor;
    return static_cast<int>(std::floor(scaled_val));
  }
  inline int DeviceToLogical(int value, float device_scale_factor) {
    float scaled_val = static_cast<float>(value) / device_scale_factor;
    return static_cast<int>(std::floor(scaled_val));
  }
  // Platform-specific implementation.
  void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                           const CefString& title);
						   
   // True if mouse cursor change is disabled.
  bool m_bMouseCursorChangeDisabled = false;
  HWND m_hwnd;
  QObject *m_receiver;
  QRect m_windowRect;


  // True if the application is using the Views framework.
  const bool use_views_;

  // List of existing browser windows. Only accessed on the CEF UI thread.
  typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
  BrowserList browser_list_;

  bool is_closing_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleHandler);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
