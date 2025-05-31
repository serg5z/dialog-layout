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

typedef struct {
  int width;
  int height;
  int n_controls;
  void* control_layout;
} LAYOUT;

#ifdef __cplusplus
extern "C" {
#endif

void attach_layout(HANDLE resource, HWND dialog, LPCTSTR layout_resource_name);
void detach_layout(HWND dialog);
void layout(HWND dialog);

#ifdef __cplusplus
}
#endif

#endif /* LAYOUT_H */
