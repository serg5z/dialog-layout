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

/**
 * @brief Initialize dynamic layout management for a dialog.
 *
 * Prepares the dialog for dynamic layout by creating an internal layout structure.
 * Controls can then be anchored individually using anchor_control().
 * 
 * @param dialog  Handle to the dialog box (HWND).
 *
 * @note
 * Call this function in WM_INITDIALOG if you are not using a layout resource table,
 * and plan to manually anchor controls using anchor_control().
 *
 * Example usage:
 * @code
 * init_layout(hDlg);
 * anchor_control(hDlg, IDC_BUTTON_OK, ANCOR_RIGHT | ANCOR_BOTTOM, ANCOR_RIGHT | ANCOR_BOTTOM);
 * @endcode
 */
void init_layout(HWND dialog);

/**
 * @brief Anchor an individual control to specific edges of the dialog, overriding any previous anchor.
 *
 * Registers or overrides the anchor points for the specified control in the layout engine.
 * This function can be used after attach_layout() to override anchors loaded from a resource,
 * or after init_layout() to add anchors manually.
 *
 * @param dialog           Handle to the dialog box (HWND).
 * @param control_id       Control ID (e.g., IDC_BUTTON_OK).
 * @param anchor_topleft   Anchor flags for the control's top-left corner (see @ref Anchor flags).
 * @param anchor_bottomright Anchor flags for the control's bottom-right corner (see @ref Anchor flags).
 * @return                 TRUE if the anchor was set successfully, FALSE on error (e.g., illegal anchor or control not found).
 *
 * @note
 * It is safe to use anchor_control() after attach_layout() to override anchors set by the resource,
 * or to add anchors for additional controls at runtime.
 *
 * Example usage:
 * @code
 * attach_layout(hInstance, hDlg, MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT));
 * anchor_control(hDlg, IDC_MY_BUTTON, ANCOR_RIGHT | ANCOR_BOTTOM, ANCOR_RIGHT | ANCOR_BOTTOM); // override/add anchor
 * @endcode
 */
BOOL anchor_control(HWND dialog, DWORD control_id, WORD anchor_topleft, WORD anchor_bottomright);

#ifdef __cplusplus
}
#endif

#endif /* LAYOUT_H */
