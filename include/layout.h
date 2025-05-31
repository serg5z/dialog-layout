/*
 * Copyright (c) 2003-2025, Sergey Zorin. All rights reserved.
 *
 * This software is distributable under the BSD license. See the terms
 * of the BSD license in the LICENSE file provided with this software.
 *
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include <windows.h>
#include <tchar.h>


/**
 * @brief Structure representing a dialog layout.
 *
 * This structure holds information about the size of the dialog and the layout
 * information for its controls. The details of the control layout array depend
 * on the specific implementation and resource data.
 */
typedef struct {
  int width;
  int height;
  int n_controls;
  void* control_layout;
} LAYOUT;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Attaches a layout to a dialog box from a layout resource.
 *
 * Loads the layout information from the specified resource and applies it
 * to the dialog, so its controls will resize and move according to the layout
 * rules when the dialog is resized.
 *
 * @param resource             Handle to the module containing the resource.
 * @param dialog               Handle to the dialog box (HWND).
 * @param layout_resource_name Name of the layout resource (e.g., TEXT("ID_MAINDIALOG_LAYOUT")).
 */
void attach_layout(HANDLE resource, HWND dialog, LPCTSTR layout_resource_name);

/**
 * @brief Detaches the layout from the dialog, disabling automatic control layout management.
 *
 * After calling this function, controls will no longer be automatically resized or
 * repositioned when the dialog is resized.
 *
 * @param dialog  Handle to the dialog box (HWND).
 */
void detach_layout(HWND dialog);

/**
 * @brief Applies the layout rules to the dialog immediately.
 *
 * Forces an immediate re-layout of the dialog controls according to the current layout.
 * Can be used to refresh layout after manual resizing or other changes.
 *
 * @param dialog  Handle to the dialog box (HWND).
 */
void layout(HWND dialog);

#ifdef __cplusplus
}
#endif

#endif /* LAYOUT_H */
