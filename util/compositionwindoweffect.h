#ifndef COMPOSITIONWINDOWEFFECT_H
#define COMPOSITIONWINDOWEFFECT_H

#include <Windows.h>

class CompositionWindowEffect
{
public:
    enum class WINDOWCOMPOSITIONATTRIB
    {
        WCA_UNDEFINED,
        WCA_NCRENDERING_ENABLED,
        WCA_NCRENDERING_POLICY,
        WCA_TRANSITIONS_FORCEDISABLED,
        WCA_ALLOW_NCPAINT,
        WCA_CAPTION_BUTTON_BOUNDS,
        WCA_NONCLIENT_RTL_LAYOUT,
        WCA_FORCE_ICONIC_REPRESENTATION,
        WCA_EXTENDED_FRAME_BOUNDS,
        WCA_HAS_ICONIC_BITMAP,
        WCA_THEME_ATTRIBUTES,
        WCA_NCRENDERING_EXILED,
        WCA_NCADORNMENTINFO,
        WCA_EXCLUDED_FROM_LIVEPREVIEW,
        WCA_VIDEO_OVERLAY_ACTIVE,
        WCA_FORCE_ACTIVEWINDOW_APPEARANCE,
        WCA_DISALLOW_PEEK,
        WCA_CLOAK,
        WCA_CLOAKED,
        WCA_ACCENT_POLICY,
        WCA_FREEZE_REPRESENTATION,
        WCA_EVER_UNCLOAKED,
        WCA_VISUAL_OWNER,
        WCA_HOLOGRAPHIC,
        WCA_EXCLUDED_FROM_DDA,
        WCA_PASSIVEUPDATEMODE,
        WCA_USEDARKMODECOLORS,
        WCA_CORNER_STYLE,
        WCA_PART_COLOR,
        WCA_DISABLE_MOVESIZE_FEEDBACK,
        WCA_LAST
    };
    enum class ACCENT_STATE
    {
        ACCENT_DISABLED,                   // 黑色无效果
        ACCENT_ENABLE_GRADIENT,            // 直接设置颜色
        ACCENT_ENABLE_TRANSPARENTGRADIENT, // 跟随系统主题色(需要窗口透明)
        ACCENT_ENABLE_AERO_BLUR,           // Aero模糊
        ACCENT_ENABLE_AERO_BLUR_COLOR,     // Aero模糊,但可直接设置颜色
        ACCENT_ENABLE_HOSTBACKDROP,        // 黑色无效果
        ACCENT_INVALID_STATE               // 全透明
    };
    struct ACCENT_POLICY
    {
        ACCENT_STATE AccentState; // 指定窗口的效果
        DWORD AccentFlags;        // 可以用于控制无边框时的窗口阴影(参考值：480 影响因素未知)
        COLORREF GradientColor;   // 控制透明效果的颜色，取决于AccentState
        DWORD AnimationId;
    };

    struct WINDOWCOMPOSITIONATTRIBDATA
    {
        WINDOWCOMPOSITIONATTRIB Attribute;
        ACCENT_POLICY *Data;
        SIZE_T SizeOfData;
    };

    static void setAreoEffect(const HWND hwnd);

    static BOOL(WINAPI *SetWindowCompositionAttributePtr)(HWND, WINDOWCOMPOSITIONATTRIBDATA *);
};

#endif // COMPOSITIONWINDOWEFFECT_H
