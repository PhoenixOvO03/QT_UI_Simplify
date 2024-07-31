#include "compositionwindoweffect.h"

BOOL(WINAPI *CompositionWindowEffect::SetWindowCompositionAttributePtr)(HWND, WINDOWCOMPOSITIONATTRIBDATA *) =
    (BOOL(WINAPI *)(HWND, WINDOWCOMPOSITIONATTRIBDATA *))GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "SetWindowCompositionAttribute");

void CompositionWindowEffect::setAreoEffect(const HWND hwnd)
{
    ACCENT_POLICY accent = {ACCENT_STATE::ACCENT_ENABLE_AERO_BLUR, 0, 0, 0};
    WINDOWCOMPOSITIONATTRIBDATA data{WINDOWCOMPOSITIONATTRIB::WCA_ACCENT_POLICY, &accent, sizeof(ACCENT_POLICY)};
    SetWindowCompositionAttributePtr(hwnd, &data);
}
