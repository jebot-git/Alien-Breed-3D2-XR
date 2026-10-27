#include "xr.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#ifdef TEMPEST_OPENXR
#include <SDL_syswm.h>
#define XR_USE_PLATFORM_XLIB
#define XR_USE_PLATFORM_EGL
#define XR_USE_GRAPHICS_API_OPENGL
#include <EGL/egl.h>
#include <GL/glx.h>
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

namespace ab3d2 {
static void check(XrResult r, const char *name) {
  if (XR_FAILED(r))
    throw std::runtime_error(std::string(name) + " (OpenXR " +
                             std::to_string(r) + ")");
}
#define XR_CHECK(call) check(call, #call)
struct XR::Impl {
  XrInstance instance = XR_NULL_HANDLE;
  XrSession session = XR_NULL_HANDLE;
  XrSpace space = XR_NULL_HANDLE;
  XrSystemId system = XR_NULL_SYSTEM_ID;
  bool running = false, hasAnchor = false, quit = false, isFocused = false,
       visible = true;
  XrEnvironmentBlendMode blend = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
  struct Eye {
    XrSwapchain chain = XR_NULL_HANDLE;
    int width = 0, height = 0;
    std::vector<XrSwapchainImageOpenGLKHR> images;
    GLuint depth = 0;
  };
  std::vector<Eye> eyes;
  GLuint fbo = 0;
  XrVector3f anchor{};
  bool heightCalibrated = false;
  float standingY = 0;
  float yaw = 0;
  std::string runtime;
  uint64_t frames = 0, stereoFrames = 0;
  Tracking tracking;
  SDL_Window *window = nullptr;
  bool frameOpen = false, renderFrame = false;
  XrTime displayTime = 0;
  std::array<XrView, 2> views{{{XR_TYPE_VIEW}, {XR_TYPE_VIEW}}};
  bool touchPro = false;
  XrActionSet actions = XR_NULL_HANDLE;
  XrAction pose = XR_NULL_HANDLE, trigger = XR_NULL_HANDLE,
           stick = XR_NULL_HANDLE, operate = XR_NULL_HANDLE,
           menu = XR_NULL_HANDLE, previous = XR_NULL_HANDLE,
           next = XR_NULL_HANDLE, select = XR_NULL_HANDLE,
           haptic = XR_NULL_HANDLE;
  XrAction jump = XR_NULL_HANDLE;
  XrAction gripPose = XR_NULL_HANDLE, supportHold = XR_NULL_HANDLE,
           supportClick = XR_NULL_HANDLE;
  XrPath handPaths[2]{};
  XrSpace handSpaces[2]{};
  XrSpace gripSpaces[2]{};
  ~Impl() {
    if (instance)
      std::cerr << "OpenXR frames=" << frames
                << " stereo_frames=" << stereoFrames << '\n';
    if (fbo)
      glDeleteFramebuffers(1, &fbo);
    for (auto &e : eyes) {
      if (e.depth)
        glDeleteRenderbuffers(1, &e.depth);
      if (e.chain)
        xrDestroySwapchain(e.chain);
    }
    for (auto hand : handSpaces)
      if (hand)
        xrDestroySpace(hand);
    for (auto hand : gripSpaces)
      if (hand)
        xrDestroySpace(hand);
    if (space)
      xrDestroySpace(space);

    if (session)
      xrDestroySession(session);
    if (actions)
      xrDestroyActionSet(actions);
    if (instance)
      xrDestroyInstance(instance);
  }
};
XR::XR() : p(std::make_unique<Impl>()) {}
XR::~XR() = default;
void XR::initialize(SDL_Window *window) {
  SDL_SysWMinfo wm{};
  SDL_VERSION(&wm.version);
  auto &x = *p;
  x.window = window;
  bool useEgl = eglGetCurrentContext() != EGL_NO_CONTEXT;
  bool hasWindowInfo = SDL_GetWindowWMInfo(window, &wm);
  if (!useEgl && !hasWindowInfo)
    throw std::runtime_error("SDL could not identify the native window");
  if (!useEgl && wm.subsystem != SDL_SYSWM_X11)
    throw std::runtime_error(
        "XR requires a native EGL or X11/GLX OpenGL context");
  uint32_t extensionCount = 0;
  XR_CHECK(xrEnumerateInstanceExtensionProperties(nullptr, 0, &extensionCount,
                                                  nullptr));
  std::vector<XrExtensionProperties> available(extensionCount,
                                               {XR_TYPE_EXTENSION_PROPERTIES});
  XR_CHECK(xrEnumerateInstanceExtensionProperties(
      nullptr, extensionCount, &extensionCount, available.data()));
  std::vector<const char *> extensions{XR_KHR_OPENGL_ENABLE_EXTENSION_NAME};
  if (useEgl)
    extensions.push_back(XR_MNDX_EGL_ENABLE_EXTENSION_NAME);
  x.touchPro =
      std::any_of(available.begin(), available.end(), [](const auto &item) {
        return std::strcmp(item.extensionName, "XR_FB_touch_controller_pro") ==
               0;
      });
  if (x.touchPro)
    extensions.push_back("XR_FB_touch_controller_pro");
  XrInstanceCreateInfo ci{XR_TYPE_INSTANCE_CREATE_INFO};
  std::strcpy(ci.applicationInfo.applicationName, "Alien Breed 3D II XR");
  ci.applicationInfo.apiVersion = XR_MAKE_VERSION(1, 0, 0);
  ci.enabledExtensionCount = extensions.size();
  ci.enabledExtensionNames = extensions.data();
  XR_CHECK(xrCreateInstance(&ci, &x.instance));
  XrInstanceProperties properties{XR_TYPE_INSTANCE_PROPERTIES};
  XR_CHECK(xrGetInstanceProperties(x.instance, &properties));
  x.runtime = properties.runtimeName;
  XrSystemGetInfo si{XR_TYPE_SYSTEM_GET_INFO};
  si.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
  XR_CHECK(xrGetSystem(x.instance, &si, &x.system));
  PFN_xrGetOpenGLGraphicsRequirementsKHR requirementsFn = nullptr;
  XR_CHECK(xrGetInstanceProcAddr(
      x.instance, "xrGetOpenGLGraphicsRequirementsKHR",
      reinterpret_cast<PFN_xrVoidFunction *>(&requirementsFn)));
  XrGraphicsRequirementsOpenGLKHR requirements{
      XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR};
  XR_CHECK(requirementsFn(x.instance, x.system, &requirements));
  GLint major = 0, minor = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
  auto version = XR_MAKE_VERSION(major, minor, 0);
  if (version < requirements.minApiVersionSupported ||
      version > requirements.maxApiVersionSupported)
    throw std::runtime_error(
        "OpenGL version is outside the OpenXR runtime's supported range");
  XrGraphicsBindingOpenGLXlibKHR binding{
      XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR};
  XrGraphicsBindingEGLMNDX eglBinding{XR_TYPE_GRAPHICS_BINDING_EGL_MNDX};
  if (useEgl) {
    eglBinding.display = eglGetCurrentDisplay();
    eglBinding.context = eglGetCurrentContext();
    eglBinding.getProcAddress =
        reinterpret_cast<PFN_xrEglGetProcAddressMNDX>(eglGetProcAddress);
    EGLint configId = 0, found = 0;
    eglQueryContext(eglBinding.display, eglBinding.context, EGL_CONFIG_ID,
                    &configId);
    EGLint attributes[] = {EGL_CONFIG_ID, configId, EGL_NONE};
    if (!eglChooseConfig(eglBinding.display, attributes, &eglBinding.config, 1,
                         &found) ||
        !found)
      throw std::runtime_error("Could not identify SDL's EGL configuration");
  } else {
    Display *display = wm.info.x11.display;
    GLXContext context = glXGetCurrentContext();
    int id = 0;
    glXQueryContext(display, context, GLX_FBCONFIG_ID, &id);
    int count = 0;
    auto configs = glXGetFBConfigs(display, DefaultScreen(display), &count);
    GLXFBConfig config = nullptr;
    VisualID visual = 0;
    for (int i = 0; i < count; i++) {
      int candidate = 0;
      glXGetFBConfigAttrib(display, configs[i], GLX_FBCONFIG_ID, &candidate);
      if (candidate == id) {
        config = configs[i];
        auto vi = glXGetVisualFromFBConfig(display, config);
        if (vi) {
          visual = vi->visualid;
          XFree(vi);
        }
        break;
      }
    }
    XFree(configs);
    if (!config || !context)
      throw std::runtime_error("Could not identify the SDL GLX context");
    binding.xDisplay = display;
    binding.visualid = visual;
    binding.glxFBConfig = config;
    binding.glxDrawable = glXGetCurrentDrawable();
    binding.glxContext = context;
  }
  XrSessionCreateInfo sessionInfo{XR_TYPE_SESSION_CREATE_INFO};
  sessionInfo.next =
      useEgl ? static_cast<void *>(&eglBinding) : static_cast<void *>(&binding);
  sessionInfo.systemId = x.system;
  XR_CHECK(xrCreateSession(x.instance, &sessionInfo, &x.session));
  XrReferenceSpaceCreateInfo ri{XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
  ri.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
  ri.poseInReferenceSpace.orientation.w = 1;
  XR_CHECK(xrCreateReferenceSpace(x.session, &ri, &x.space));
  uint32_t n = 0;
  XR_CHECK(xrEnumerateEnvironmentBlendModes(
      x.instance, x.system, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &n,
      nullptr));
  std::vector<XrEnvironmentBlendMode> blends(n);
  XR_CHECK(xrEnumerateEnvironmentBlendModes(
      x.instance, x.system, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, n, &n,
      blends.data()));
  if (blends.empty())
    throw std::runtime_error("No OpenXR blend modes");
  x.blend = blends.front();
  XR_CHECK(xrEnumerateSwapchainFormats(x.session, 0, &n, nullptr));
  std::vector<int64_t> formats(n);
  XR_CHECK(xrEnumerateSwapchainFormats(x.session, n, &n, formats.data()));
  int64_t format = 0;
  for (auto wanted : {GL_RGBA8, GL_SRGB8_ALPHA8})
    if (std::find(formats.begin(), formats.end(), wanted) != formats.end()) {
      format = wanted;
      break;
    }
  if (!format)
    throw std::runtime_error("No supported OpenGL RGBA swapchain format");
  XR_CHECK(xrEnumerateViewConfigurationViews(
      x.instance, x.system, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &n,
      nullptr));
  std::vector<XrViewConfigurationView> views(n,
                                             {XR_TYPE_VIEW_CONFIGURATION_VIEW});
  XR_CHECK(xrEnumerateViewConfigurationViews(
      x.instance, x.system, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, n, &n,
      views.data()));
  if (n != 2)
    throw std::runtime_error("Prototype requires stereo OpenXR views");
  x.eyes.resize(n);
  for (size_t i = 0; i < x.eyes.size(); i++) {
    auto &e = x.eyes[i];
    e.width = int(views[i].recommendedImageRectWidth);
    e.height = int(views[i].recommendedImageRectHeight);
    XrSwapchainCreateInfo sc{XR_TYPE_SWAPCHAIN_CREATE_INFO};
    sc.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
    sc.format = format;
    sc.sampleCount = 1;
    sc.width = e.width;
    sc.height = e.height;
    sc.faceCount = 1;
    sc.arraySize = 1;
    sc.mipCount = 1;
    XR_CHECK(xrCreateSwapchain(x.session, &sc, &e.chain));
    XR_CHECK(xrEnumerateSwapchainImages(e.chain, 0, &n, nullptr));
    e.images.resize(n, {XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR});
    XR_CHECK(xrEnumerateSwapchainImages(
        e.chain, n, &n,
        reinterpret_cast<XrSwapchainImageBaseHeader *>(e.images.data())));
    glGenRenderbuffers(1, &e.depth);
    glBindRenderbuffer(GL_RENDERBUFFER, e.depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, e.width,
                          e.height);
  }
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  initializeActions();
  glGenFramebuffers(1, &x.fbo);
  std::cerr << "OpenXR initialized: " << x.runtime << " / " << x.eyes[0].width
            << "x" << x.eyes[0].height << " per eye\n";
}
void XR::initializeActions() {
  auto &x = *p;
  auto path = [&](const char *name) {
    XrPath value;
    XR_CHECK(xrStringToPath(x.instance, name, &value));
    return value;
  };
  x.handPaths[0] = path("/user/hand/left");
  x.handPaths[1] = path("/user/hand/right");
  XrActionSetCreateInfo set{XR_TYPE_ACTION_SET_CREATE_INFO};
  std::strcpy(set.actionSetName, "gameplay");
  std::strcpy(set.localizedActionSetName, "Gameplay");
  XR_CHECK(xrCreateActionSet(x.instance, &set, &x.actions));
  auto action = [&](XrAction &out, const char *name, XrActionType type) {
    XrActionCreateInfo info{XR_TYPE_ACTION_CREATE_INFO};
    info.actionType = type;
    std::strcpy(info.actionName, name);
    std::strcpy(info.localizedActionName,
                std::strcmp(name, "use") == 0 ? "Use / Operate" : name);
    info.countSubactionPaths = 2;
    info.subactionPaths = x.handPaths;
    XR_CHECK(xrCreateAction(x.actions, &info, &out));
  };
  action(x.pose, "aim_pose", XR_ACTION_TYPE_POSE_INPUT);
  action(x.gripPose, "grip_pose", XR_ACTION_TYPE_POSE_INPUT);
  action(x.supportHold, "support_hold", XR_ACTION_TYPE_FLOAT_INPUT);
  action(x.supportClick, "support_click", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.trigger, "trigger", XR_ACTION_TYPE_FLOAT_INPUT);
  action(x.stick, "move_turn", XR_ACTION_TYPE_VECTOR2F_INPUT);
  action(x.operate, "use", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.menu, "pause", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.jump, "jump", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.previous, "previous_weapon", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.next, "next_weapon", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.select, "select", XR_ACTION_TYPE_BOOLEAN_INPUT);
  action(x.haptic, "feedback", XR_ACTION_TYPE_VIBRATION_OUTPUT);
  std::vector<const char *> profiles{
      "/interaction_profiles/oculus/touch_controller",
      "/interaction_profiles/valve/index_controller",
      "/interaction_profiles/htc/vive_controller",
      "/interaction_profiles/khr/simple_controller"};
  if (x.touchPro)
    profiles.push_back("/interaction_profiles/facebook/touch_controller_pro");
  for (auto profile : profiles) {
    bool simple = std::strstr(profile, "simple"),
         vive = std::strstr(profile, "vive");
    std::vector<XrActionSuggestedBinding> bindings;
    auto bind = [&](XrAction a, const std::string &b) {
      bindings.push_back({a, path(b.c_str())});
    };
    for (int h = 0; h < 2; ++h) {
      std::string hand = h ? "/user/hand/right" : "/user/hand/left";
      bind(x.pose, hand + "/input/aim/pose");
      bind(x.gripPose, hand + "/input/grip/pose");
      bind(x.haptic, hand + "/output/haptic");
      if (simple)
        bind(x.select, hand + "/input/select/click");
      else {
        bind(x.trigger, hand + "/input/trigger/value");
        bind(x.stick, hand + (vive ? "/input/trackpad" : "/input/thumbstick"));
      }
      if (!simple && (!vive || h))
        bind(x.operate, hand + (vive ? "/input/squeeze/click"
                                : h  ? "/input/a/click"
                                     : "/input/x/click"));
    }
    if (!simple)
      bind(vive ? x.supportClick : x.supportHold,
           "/user/hand/left/input/squeeze/" +
               std::string(vive ? "click" : "value"));
    bind(x.menu, "/user/hand/left/input/menu/click");
    if (!simple && !vive) {
      bind(x.previous, "/user/hand/left/input/y/click");
      bind(x.next, "/user/hand/right/input/b/click");
    }
    if (!simple && !vive)
      bind(x.jump, "/user/hand/right/input/thumbstick/click");
    // Index has no menu path or A/X naming distinction; use its A/B buttons.
    if (std::strstr(profile, "index")) {
      bindings.clear();
      for (int h = 0; h < 2; ++h) {
        std::string hand = h ? "/user/hand/right" : "/user/hand/left";
        bind(x.pose, hand + "/input/aim/pose");
        bind(x.gripPose, hand + "/input/grip/pose");
        bind(x.haptic, hand + "/output/haptic");
        bind(x.trigger, hand + "/input/trigger/value");
        bind(x.stick, hand + "/input/thumbstick");
        bind(x.operate, hand + "/input/a/click");
      }
      bind(x.jump, "/user/hand/right/input/thumbstick/click");
      bind(x.supportHold, "/user/hand/left/input/squeeze/value");
      bind(x.menu, "/user/hand/left/input/thumbstick/click");
      bind(x.previous, "/user/hand/left/input/b/click");
      bind(x.next, "/user/hand/right/input/b/click");
    }
    XrInteractionProfileSuggestedBinding info{
        XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};
    info.interactionProfile = path(profile);
    info.countSuggestedBindings = bindings.size();
    info.suggestedBindings = bindings.data();
    auto result = xrSuggestInteractionProfileBindings(x.instance, &info);
    if (XR_FAILED(result))
      std::cerr << "Controller profile unavailable: " << profile << " ("
                << result << ")\n";
  }
  XrSessionActionSetsAttachInfo attach{XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO};
  attach.countActionSets = 1;
  attach.actionSets = &x.actions;
  XR_CHECK(xrAttachSessionActionSets(x.session, &attach));
  for (int h = 0; h < 2; ++h) {
    XrActionSpaceCreateInfo info{XR_TYPE_ACTION_SPACE_CREATE_INFO};
    info.action = x.pose;
    info.subactionPath = x.handPaths[h];
    info.poseInActionSpace.orientation.w = 1;
    XR_CHECK(xrCreateActionSpace(x.session, &info, &x.handSpaces[h]));
    info.action = x.gripPose;
    XR_CHECK(xrCreateActionSpace(x.session, &info, &x.gripSpaces[h]));
  }
}
void XR::sampleActions(XrTime time) {
  auto &x = *p;
  auto &t = x.tracking;

  bool wasSupport = t.supportHeld;
  t.fire = t.use = t.menu = t.previousWeapon = t.nextWeapon = t.jump = false;
  t.supportHeld = false;
  t.supportAvailable = false;
  t.move = {};
  t.turn = {};
  t.valid[0] = t.valid[1] = false;
  t.gripValid[0] = t.gripValid[1] = false;
  XrActiveActionSet active{x.actions, XR_NULL_PATH};
  XrActionsSyncInfo sync{XR_TYPE_ACTIONS_SYNC_INFO};
  sync.countActiveActionSets = 1;
  sync.activeActionSets = &active;
  XR_CHECK(xrSyncActions(x.session, &sync));
  if (!x.isFocused || !x.visible || !t.headValid)
    return;
  for (int h = 0; h < 2; ++h) {
    XrActionStateGetInfo get{XR_TYPE_ACTION_STATE_GET_INFO};
    get.subactionPath = x.handPaths[h];
    get.action = x.pose;
    XrActionStatePose pose{XR_TYPE_ACTION_STATE_POSE};
    XR_CHECK(xrGetActionStatePose(x.session, &get, &pose));
    XrSpaceLocation location{XR_TYPE_SPACE_LOCATION};
    XR_CHECK(xrLocateSpace(x.handSpaces[h], x.space, time, &location));
    auto required = XR_SPACE_LOCATION_POSITION_VALID_BIT |
                    XR_SPACE_LOCATION_ORIENTATION_VALID_BIT;
    t.valid[h] =
        pose.isActive && (location.locationFlags & required) == required;
    t.hands[h] = location.pose;
    get.action = x.gripPose;
    XrActionStatePose grip{XR_TYPE_ACTION_STATE_POSE};
    XR_CHECK(xrGetActionStatePose(x.session, &get, &grip));
    XrSpaceLocation gripLocation{XR_TYPE_SPACE_LOCATION};
    XR_CHECK(xrLocateSpace(x.gripSpaces[h], x.space, time, &gripLocation));
    t.gripValid[h] =
        grip.isActive && (gripLocation.locationFlags & required) == required &&
        (gripLocation.locationFlags & XR_SPACE_LOCATION_POSITION_TRACKED_BIT);
    t.grips[h] = gripLocation.pose;
    get.action = x.stick;
    XrActionStateVector2f stick{XR_TYPE_ACTION_STATE_VECTOR2F};
    XR_CHECK(xrGetActionStateVector2f(x.session, &get, &stick));
    if (stick.isActive) {
      if (h)
        t.turn = stick.currentState;
      else
        t.move = stick.currentState;
    }
    auto boolean = [&](XrAction action) {
      get.action = action;
      XrActionStateBoolean state{XR_TYPE_ACTION_STATE_BOOLEAN};
      XR_CHECK(xrGetActionStateBoolean(x.session, &get, &state));
      return state.isActive && state.currentState;
    };
    bool clicked = boolean(x.select);
    if (h)
      t.fire = clicked;
    else
      t.use = clicked;
    t.use = t.use || boolean(x.operate);
    t.menu = t.menu || boolean(x.menu);
    if (h)
      t.jump = boolean(x.jump);
    t.previousWeapon = t.previousWeapon || boolean(x.previous);
    t.nextWeapon = t.nextWeapon || boolean(x.next);
    if (!h) {
      get.action = x.supportClick;
      XrActionStateBoolean click{XR_TYPE_ACTION_STATE_BOOLEAN};
      XR_CHECK(xrGetActionStateBoolean(x.session, &get, &click));
      get.action = x.supportHold;
      XrActionStateFloat squeeze{XR_TYPE_ACTION_STATE_FLOAT};
      XR_CHECK(xrGetActionStateFloat(x.session, &get, &squeeze));
      t.supportAvailable = click.isActive || squeeze.isActive;
      t.supportHeld = (click.isActive && click.currentState) ||
                      (squeeze.isActive &&
                       squeeze.currentState > (wasSupport ? .35f : .65f));
    }
    get.action = x.trigger;
    XrActionStateFloat trigger{XR_TYPE_ACTION_STATE_FLOAT};
    XR_CHECK(xrGetActionStateFloat(x.session, &get, &trigger));
    if (h && t.valid[h])
      t.fire = t.fire || (trigger.isActive && trigger.currentState > .55f);
  }
  if (!t.valid[1])
    t.fire = false;
}
bool XR::beginFrame() {
  auto &x = *p;
  x.frameOpen = false;
  x.tracking.headValid = false;
  XrEventDataBuffer event{XR_TYPE_EVENT_DATA_BUFFER};
  XrResult result;
  while ((result = xrPollEvent(x.instance, &event)) == XR_SUCCESS) {
    if (event.type == XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED) {
      auto state =
          reinterpret_cast<XrEventDataSessionStateChanged &>(event).state;
      x.isFocused = state == XR_SESSION_STATE_FOCUSED;
      if (state == XR_SESSION_STATE_READY) {
        XrSessionBeginInfo info{XR_TYPE_SESSION_BEGIN_INFO};
        info.primaryViewConfigurationType =
            XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
        XR_CHECK(xrBeginSession(x.session, &info));
        x.running = true;
      }
      if (state == XR_SESSION_STATE_STOPPING) {
        x.running = false;
        XR_CHECK(xrEndSession(x.session));
      }
      if (state == XR_SESSION_STATE_EXITING ||
          state == XR_SESSION_STATE_LOSS_PENDING)
        x.quit = true;
    } else if (event.type == XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING)
      x.quit = true;
    event = {XR_TYPE_EVENT_DATA_BUFFER};
  }
  if (result != XR_EVENT_UNAVAILABLE)
    check(result, "xrPollEvent");
  if (x.quit)
    return false;
  if (!x.running)
    return true;
  XrFrameWaitInfo wait{XR_TYPE_FRAME_WAIT_INFO};
  XrFrameState state{XR_TYPE_FRAME_STATE};
  XR_CHECK(xrWaitFrame(x.session, &wait, &state));
  XrFrameBeginInfo begin{XR_TYPE_FRAME_BEGIN_INFO};
  XR_CHECK(xrBeginFrame(x.session, &begin));
  x.frameOpen = true;
  x.displayTime = state.predictedDisplayTime;
  XrViewLocateInfo locate{XR_TYPE_VIEW_LOCATE_INFO};
  locate.viewConfigurationType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
  locate.displayTime = x.displayTime;
  locate.space = x.space;
  XrViewState valid{XR_TYPE_VIEW_STATE};
  uint32_t count = 0;
  XR_CHECK(
      xrLocateViews(x.session, &locate, &valid, 2, &count, x.views.data()));
  x.renderFrame = x.visible && state.shouldRender && count == 2 &&
                  (valid.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) &&
                  (valid.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT);
  x.tracking.headValid = x.renderFrame;
  if (x.renderFrame)
    x.tracking.headPosition = {
        (x.views[0].pose.position.x + x.views[1].pose.position.x) * .5f,
        (x.views[0].pose.position.y + x.views[1].pose.position.y) * .5f,
        (x.views[0].pose.position.z + x.views[1].pose.position.z) * .5f};
  sampleActions(x.displayTime);
  return true;
}
void XR::endFrame(
    const std::function<void(const XrView &, int, int, int)> &draw) {
  auto &x = *p;
  if (!x.frameOpen)
    return;
  std::array<XrCompositionLayerProjectionView, 2> views{
      {{XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW},
       {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW}}};
  if (x.renderFrame)
    for (int eye = 0; eye < 2; eye++) {
      auto &e = x.eyes[eye];
      uint32_t image = 0;
      XrSwapchainImageAcquireInfo acquire{XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};
      XR_CHECK(xrAcquireSwapchainImage(e.chain, &acquire, &image));
      XrSwapchainImageWaitInfo wait{XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
      wait.timeout = XR_INFINITE_DURATION;
      XR_CHECK(xrWaitSwapchainImage(e.chain, &wait));
      glBindFramebuffer(GL_FRAMEBUFFER, x.fbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             GL_TEXTURE_2D, e.images.at(image).image, 0);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                GL_RENDERBUFFER, e.depth);
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Incomplete native XR framebuffer");
      glViewport(0, 0, e.width, e.height);
      glDisable(GL_FRAMEBUFFER_SRGB);
      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      draw(x.views[eye], eye, e.width, e.height);
      if (x.window) {
        int width, height;
        SDL_GL_GetDrawableSize(x.window, &width, &height);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, x.fbo);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, e.width, e.height, eye * width / 2, 0,
                          (eye + 1) * width / 2, height, GL_COLOR_BUFFER_BIT,
                          GL_NEAREST);
      }
      glFlush();
      XrSwapchainImageReleaseInfo release{XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};
      XR_CHECK(xrReleaseSwapchainImage(e.chain, &release));
      views[eye].pose = x.views[eye].pose;
      views[eye].fov = x.views[eye].fov;
      views[eye].subImage.swapchain = e.chain;
      views[eye].subImage.imageRect.extent = {int32_t(e.width),
                                              int32_t(e.height)};
    }
  XrCompositionLayerProjection layer{XR_TYPE_COMPOSITION_LAYER_PROJECTION};
  layer.space = x.space;
  layer.viewCount = 2;
  layer.views = views.data();
  const XrCompositionLayerBaseHeader *layers[] = {
      reinterpret_cast<const XrCompositionLayerBaseHeader *>(&layer)};
  XrFrameEndInfo end{XR_TYPE_FRAME_END_INFO};
  end.displayTime = x.displayTime;
  end.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
  end.layerCount = x.renderFrame ? 1 : 0;
  end.layers = x.renderFrame ? layers : nullptr;
  XR_CHECK(xrEndFrame(x.session, &end));
  x.frames++;
  if (x.renderFrame)
    x.stereoFrames++;
  x.frameOpen = false;
}
const Tracking &XR::tracking() const { return p->tracking; }
XrPosef XR::headPose() const {
  XrPosef pose = p->views[0].pose;
  pose.position = p->tracking.headPosition;
  return pose;
}
bool XR::focused() const { return p->isFocused; }
void XR::setVisible(bool value) { p->visible = value; }
void XR::recenter() { p->tracking.anchor = p->tracking.headPosition; }
bool XR::resetHeight() {
  recenter();
  return p->tracking.headValid;
}
std::string XR::description() const { return p->runtime; }
void XR::haptic(float amplitude, int milliseconds) {
  if (!p->isFocused)
    return;
  XrHapticActionInfo info{XR_TYPE_HAPTIC_ACTION_INFO};
  info.action = p->haptic;
  info.subactionPath = p->handPaths[1];
  XrHapticVibration vibration{XR_TYPE_HAPTIC_VIBRATION};
  vibration.amplitude = std::clamp(amplitude, 0.f, 1.f);
  vibration.duration = milliseconds * 1000000LL;
  vibration.frequency = XR_FREQUENCY_UNSPECIFIED;
  xrApplyHapticFeedback(p->session, &info,
                        reinterpret_cast<XrHapticBaseHeader *>(&vibration));
}
} // namespace ab3d2
#endif
