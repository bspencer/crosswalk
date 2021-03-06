// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef XWALK_APPLICATION_BROWSER_APPLICATION_TIZEN_H_
#define XWALK_APPLICATION_BROWSER_APPLICATION_TIZEN_H_

#include <string>

#include "base/event_types.h"
#include "xwalk/application/browser/application.h"
#include "xwalk/application/common/tizen/cookie_manager.h"

#if defined(USE_OZONE)
#include "ui/events/platform/platform_event_observer.h"
#include "ui/events/platform/platform_event_types.h"
#endif

namespace xwalk {
namespace application {

class ApplicationTizen :  // NOLINT
#if defined(USE_OZONE)
  public ui::PlatformEventObserver,
#endif
  public Application {
 public:
  virtual ~ApplicationTizen();
  void Hide();
  void Suspend();
  void Resume();

  void RemoveAllCookies();
  void SetUserAgentString(const std::string& user_agent_string);

 private:
  friend class Application;
  ApplicationTizen(scoped_refptr<ApplicationData> data,
                   RuntimeContext* context);
  virtual bool Launch(const LaunchParams& launch_params) OVERRIDE;

  virtual base::FilePath GetSplashScreenPath() OVERRIDE;

#if defined(USE_OZONE)
  virtual void WillProcessEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual void DidProcessEvent(const ui::PlatformEvent& event) OVERRIDE;
#endif

  scoped_ptr<CookieManager> cookie_manager_;
  bool is_suspended_;
};

inline ApplicationTizen* ToApplicationTizen(Application* app) {
  return static_cast<ApplicationTizen*>(app);
}

}  // namespace application
}  // namespace xwalk

#endif  // XWALK_APPLICATION_BROWSER_APPLICATION_TIZEN_H_
