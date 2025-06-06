/*
 * Copyright (c) 2003-2025, Sergey Zorin. All rights reserved.
 *
 * This software is distributable under the BSD license. See the terms
 * of the BSD license in the LICENSE file provided with this software.
 *
 */

/**
 * @file layout.h
 * @brief Win32 dialog dynamic layout engine API.
 *
 * This header provides functions and macros for attaching, detaching, and managing
 * dynamic layouts in Win32 dialog boxes. Controls in a dialog can be anchored to
 * dialog edges to provide responsive resizing behavior.
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include <windows.h>
#include <tchar.h>


/**
 * @name Anchor flags
 * @brief Anchor bitmasks used to define control layout behavior in a dialog.
 * @{
 */
/** @brief Anchor control to the left edge. */
#define ANCOR_LEFT          0x0001
/** @brief Anchor control to the top edge. */
#define ANCOR_TOP           0x0002
/** @brief Anchor control to both left and top edges. */
#define ANCOR_LEFT_TOP      (ANCOR_LEFT | ANCOR_TOP)
/** @brief Anchor control to the right edge. */
#define ANCOR_RIGHT         0x0004
/** @brief Anchor control to both right and top edges. */
#define ANCOR_RIGHT_TOP     (ANCOR_RIGHT | ANCOR_TOP)
/** @brief Anchor control to the bottom edge. */
#define ANCOR_BOTTOM        0x0008
/** @brief Anchor control to both left and bottom edges. */
#define ANCOR_LEFT_BOTTOM   (ANCOR_LEFT | ANCOR_BOTTOM)
/** @brief Anchor control to both right and bottom edges. */
#define ANCOR_RIGHT_BOTTOM  (ANCOR_RIGHT | ANCOR_BOTTOM)
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Attach a dynamic layout to a dialog box using a layout resource.
 *
 * Loads the layout information from the specified resource and applies it
 * to the dialog, so its controls will resize and move according to the layout
 * rules when the dialog is resized.
 *
 * @param resource             Handle to the module containing the resource.
 * @param dialog               Handle to the dialog box (HWND).
 * @param layout_resource_name Name of the layout resource (e.g., MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT)).
 * 
 * @note
 * Call this function in WM_INITDIALOG after creating the dialog.
 *
 * Example usage:
 * @code
 * attach_layout(hInstance, hDlg, MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT));
 * @endcode
 */
void attach_layout(HANDLE resource, HWND dialog, LPCTSTR layout_resource_name);

void init_layout(HWND dialog);
BOOL anchor_control(HWND dialog, DWORD control_id, WORD anchor_topleft, WORD anchor_bottomright);

/**
 * @brief Detaches the layout from the dialog, disabling automatic control layout management.
 *
 * After calling this function, controls will no longer be automatically resized or
 * repositioned when the dialog is resized.
 *
 * @param dialog  Handle to the dialog box (HWND).
 * 
 * @note
 * Call this function before destroying the dialog to clean up any resources.
 */
void detach_layout(HWND dialog);

#ifdef __cplusplus
}
#endif

#endif /* LAYOUT_H */
