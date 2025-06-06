/*
 * Copyright (c) 2003-2025, Sergey Zorin. All rights reserved.
 *
 * This software is distributable under the BSD license. See the terms
 * of the BSD license in the LICENSE file provided with this software.
 *
 */
#include <stdio.h>
#include "layout.h"


static const int LAYOUT_ATOM = 0x0b00;
static const int DIALOG_PROCEDURE_ATOM = 0x0b01;


typedef struct {
  int x;
  int y;
  WORD anchor;
} LAYOUT_COORD;

typedef struct {
  DWORD id;
  LAYOUT_COORD top_left;
  LAYOUT_COORD bottom_right;
} LAYOUT_ITEM;

typedef struct LAYOUT_ITEM_LIST {
  LAYOUT_ITEM item;
  struct LAYOUT_ITEM_LIST* next;
} LAYOUT_ITEM_LIST;

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
  LAYOUT_ITEM_LIST* control_layout;
} LAYOUT;

typedef struct {
  DWORD id;
  WORD top_left_anchor;
  WORD bottom_right_anchor;
} LAYOUT_ITEM_RC;

struct LAYOUT_CHILD_PARAM {
  LAYOUT* layout;
  LAYOUT_ITEM_RC* layout_table;
  unsigned int n;
  RECT dialog_rect;
};

static void __detach_layout__(HWND dialog);

static int
is_legal_anchor(int anchor) {
  return !(((anchor & ANCOR_TOP) && (anchor & ANCOR_BOTTOM)) ||
           ((anchor & ANCOR_LEFT) && (anchor & ANCOR_RIGHT)));
}

static void
__layout__(HWND dialog) {
  LAYOUT* layout = (LAYOUT*)GetProp(dialog, MAKEINTATOM(LAYOUT_ATOM));
  
  if(layout != 0) {
    LAYOUT_ITEM_LIST* current = layout->control_layout;
  
    RECT dialog_rect;
    HWND current_control;
    
    HDWP position_handle = BeginDeferWindowPos(layout->n_controls); /* store number of controls inside LAYOUT structure */
    
    GetClientRect(dialog, &dialog_rect);
  
    while(current != 0) {
      RECT rect;
      LAYOUT_ITEM* item = &(current->item);

      if(is_legal_anchor(item->top_left.anchor) && is_legal_anchor(item->bottom_right.anchor)) {
        int x;
        int y;
        int w;
        int h;
        
        current_control = GetDlgItem(dialog, item->id);
    
        rect.left = item->top_left.x;
        rect.top = item->top_left.y;
        rect.right = item->bottom_right.x;
        rect.bottom = item->bottom_right.y;
          
        if(item->top_left.anchor & ANCOR_RIGHT) {
          rect.left += dialog_rect.right;
        }
    
        if(item->top_left.anchor & ANCOR_LEFT) {
          rect.left += dialog_rect.left;
        }
    
        if(item->top_left.anchor & ANCOR_TOP) {
          rect.top += dialog_rect.top;
        }
    
        if(item->top_left.anchor & ANCOR_BOTTOM) {
          rect.top += dialog_rect.bottom;
        }
    
        if(item->bottom_right.anchor & ANCOR_RIGHT) {
          rect.right += dialog_rect.right;
        }
    
        if(item->bottom_right.anchor & ANCOR_LEFT) {
          rect.right += dialog_rect.left;
        }
    
        if(item->bottom_right.anchor & ANCOR_TOP) {
          rect.bottom += dialog_rect.top;
        }
    
        if(item->bottom_right.anchor & ANCOR_BOTTOM) {
          rect.bottom += dialog_rect.bottom;
        }
    
        w = rect.right-rect.left;
        h = rect.bottom-rect.top;
        x = rect.left;
        y = rect.top;
    
        position_handle = DeferWindowPos(position_handle, current_control, 0, x, y, w, h, SWP_NOZORDER);
      }
      
      current = current->next;
    }
    
    EndDeferWindowPos(position_handle);
  }
}

static LRESULT
__layout_dialog_procedure__(HWND dialog, UINT message, WPARAM w_param, LPARAM l_param) {
  LRESULT result = 0;
  WNDPROC original_procedure = *((WNDPROC*)GetProp(dialog, MAKEINTATOM(DIALOG_PROCEDURE_ATOM)));
  
  if(message == WM_GETMINMAXINFO) {
    LAYOUT* layout = (LAYOUT*)GetProp(dialog, MAKEINTATOM(LAYOUT_ATOM));
    MINMAXINFO* min_max_info = (MINMAXINFO*)l_param;
    RECT client;

    if(layout != 0) {
      client.top = 0;
      client.bottom = layout->height;
      client.left = 0;
      client.right = layout->width;
    } else {
      GetClientRect(dialog, &client);
    }

    min_max_info->ptMinTrackSize.x = client.right-client.left;
    min_max_info->ptMinTrackSize.y = client.bottom-client.top;
  } else {
    if(message == WM_SIZE) {
      __layout__(dialog);
    } else if(message == WM_DESTROY) {
      __detach_layout__(dialog);
    }
    
    result = CallWindowProc(original_procedure, dialog, message, w_param, l_param);
  }

  return result;
}

// For top left anchor
static void 
__compute_top_left_offset__(
    const RECT* control_rect,
    const RECT* dialog_rect,
    WORD anchor,
    int* out_x,
    int* out_y
) {
  int dialog_width = dialog_rect->right - dialog_rect->left;
  int dialog_height = dialog_rect->bottom - dialog_rect->top;
  
  // Defaults
  *out_x = control_rect->left - dialog_rect->left;
  *out_y = control_rect->top - dialog_rect->top;

  if(anchor & ANCOR_RIGHT) {
    *out_x = control_rect->left - dialog_rect->left - dialog_width;
  }

  if(anchor & ANCOR_BOTTOM) {
    *out_y = control_rect->top - dialog_rect->top - dialog_height;
  } 
}

// For bottom right anchor
static void 
__compute_bottom_right_offset__(
    const RECT* control_rect,
    const RECT* dialog_rect,
    WORD anchor,
    int* out_x,
    int* out_y
) {
  int dialog_width = dialog_rect->right - dialog_rect->left;
  int dialog_height = dialog_rect->bottom - dialog_rect->top;

  // Defaults
  *out_x = control_rect->right - dialog_rect->left;
  *out_y = control_rect->bottom - dialog_rect->top;

  if(anchor & ANCOR_RIGHT) {
    *out_x = control_rect->right - dialog_rect->left - dialog_width;
  }
  
  if(anchor & ANCOR_BOTTOM) {
    *out_y = control_rect->bottom - dialog_rect->top - dialog_height;
  }    
}

static BOOL CALLBACK 
__layout_child__(HWND control, LPARAM l_param) {
  struct LAYOUT_CHILD_PARAM* param = (struct LAYOUT_CHILD_PARAM*)l_param;
  DWORD item_id = GetDlgCtrlID(control);
  RECT control_rect;
  unsigned int i;
  
  GetWindowRect(control, &control_rect);

  param->layout->n_controls++;
  
  for(i = 0; i < param->n; i++) {
    if(param->layout_table[i].id == item_id) {
      if(is_legal_anchor(param->layout_table[i].top_left_anchor) && is_legal_anchor(param->layout_table[i].bottom_right_anchor)) {
        LAYOUT_ITEM_LIST* item = (LAYOUT_ITEM_LIST*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (sizeof(LAYOUT_ITEM_LIST)));
        
        item->item.id = item_id;
        item->item.top_left.anchor = param->layout_table[i].top_left_anchor;
        item->item.bottom_right.anchor = param->layout_table[i].bottom_right_anchor;
        item->next = param->layout->control_layout;    
        param->layout->control_layout = item;

        __compute_top_left_offset__(
            &control_rect, &param->dialog_rect,
            item->item.top_left.anchor, &item->item.top_left.x, &item->item.top_left.y
        );

        __compute_bottom_right_offset__(
            &control_rect, &param->dialog_rect,
            item->item.bottom_right.anchor, &item->item.bottom_right.x, &item->item.bottom_right.y
        );
      }
    }
  }
  
  return TRUE;
}

static void
__client_to_screen__(HWND dialog, RECT* out_rect) {
  RECT client;
  POINT p;

  GetClientRect(dialog, &client);

  // Convert right/bottom corner
  p.x = client.right;
  p.y = client.bottom;
  ClientToScreen(dialog, &p);
  client.right = p.x;
  client.bottom = p.y;

  // Convert left/top corner
  p.x = 0;
  p.y = 0;
  ClientToScreen(dialog, &p);
  client.left = p.x;
  client.top = p.y;

  *out_rect = client;
}

static LAYOUT*
__create_layout__(HANDLE resource, HWND dialog, LPCTSTR layout_name) {
  HGLOBAL layout_table_handle;
  HRSRC resource_handle;
  DWORD layout_resource_size;
  LAYOUT* layout;
  LAYOUT_ITEM_RC* layout_table;
  struct LAYOUT_CHILD_PARAM l_param;
  RECT dialog_rect;

  resource_handle = FindResource(resource, layout_name, RT_RCDATA);
  layout_table_handle = LoadResource(resource, resource_handle);
  layout_resource_size = SizeofResource(resource, resource_handle);
  layout_table = (LAYOUT_ITEM_RC*)LockResource(layout_table_handle);
  
  layout = (LAYOUT*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LAYOUT));
  
  l_param.layout = layout;
  l_param.layout_table = layout_table;
  l_param.n = layout_resource_size/sizeof(LAYOUT_ITEM_RC);
  __client_to_screen__(dialog, &l_param.dialog_rect);
  GetWindowRect(dialog, &dialog_rect);
  layout->width = dialog_rect.right - dialog_rect.left;
  layout->height = dialog_rect.bottom - dialog_rect.top;
  layout->n_controls = 0;

  layout->control_layout = 0;
  
  EnumChildWindows(dialog, __layout_child__, (LPARAM)&l_param);
  
  return layout;
}

static void
__attach_layout__(HWND dialog, LAYOUT* layout) {
  WNDPROC* original_procedure = (WNDPROC*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WNDPROC));
  
  *original_procedure = (WNDPROC)SetWindowLongPtr(dialog, GWLP_WNDPROC, (LONG_PTR)__layout_dialog_procedure__);
  
  SetProp(dialog, MAKEINTATOM(DIALOG_PROCEDURE_ATOM), original_procedure);
  SetProp(dialog, MAKEINTATOM(LAYOUT_ATOM), layout);
}

static void
__detach_layout__(HWND dialog) {
  WNDPROC* original_procedure = (WNDPROC*)GetProp(dialog, MAKEINTATOM(DIALOG_PROCEDURE_ATOM));
  LAYOUT* layout = (LAYOUT*)GetProp(dialog, MAKEINTATOM(LAYOUT_ATOM));
  LAYOUT_ITEM_LIST* current;
  LAYOUT_ITEM_LIST* next;
  
  SetWindowLongPtr(dialog, GWLP_WNDPROC, (LONG_PTR)(*original_procedure));
  
  RemoveProp(dialog, MAKEINTATOM(DIALOG_PROCEDURE_ATOM));
  RemoveProp(dialog, MAKEINTATOM(LAYOUT_ATOM));
  
  HeapFree(GetProcessHeap(), 0, original_procedure);

  current = (LAYOUT_ITEM_LIST*)(layout->control_layout);

  while(current != 0) {
    next = current->next;
    HeapFree(GetProcessHeap(), 0, current);
    current = next;
  }

  HeapFree(GetProcessHeap(), 0, layout);
}

void 
attach_layout(HANDLE resource, HWND dialog, LPCTSTR layout_name) {
  LAYOUT* layout = __create_layout__(resource, dialog, layout_name);

  __attach_layout__(dialog, layout);
}

void
init_layout(HWND dialog) {
  LAYOUT* layout = (LAYOUT*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LAYOUT));
  RECT dialog_rect;

  GetWindowRect(dialog, &dialog_rect);
  layout->width = dialog_rect.right - dialog_rect.left;
  layout->height = dialog_rect.bottom - dialog_rect.top;
  layout->n_controls = 0;

  __attach_layout__(dialog, layout);
}

BOOL 
anchor_control(HWND dialog, DWORD control_id, WORD anchor_topleft, WORD anchor_bottomright) {
  LAYOUT* layout = (LAYOUT*)GetProp(dialog, MAKEINTATOM(LAYOUT_ATOM));
  HWND control = GetDlgItem(dialog, control_id);
  
  if(!is_legal_anchor(anchor_topleft) || !is_legal_anchor(anchor_bottomright)) {
    return FALSE;
  }

  if(layout != 0 && control != 0) {
    LAYOUT_ITEM_LIST* current = layout->control_layout;
    LAYOUT_ITEM* item = 0;
    RECT control_rect;
    RECT dialog_rect;

    GetWindowRect(control, &control_rect);
    __client_to_screen__(dialog, &dialog_rect);

    while(current) {
      item = &(current->item);

      if(item->id == control_id) {
        item->top_left.anchor = anchor_topleft;
        item->bottom_right.anchor = anchor_bottomright;
        break;
      }

      current = current->next;
    }

    if(current == 0) { 
      LAYOUT_ITEM_LIST* layout_item_list = (LAYOUT_ITEM_LIST*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LAYOUT_ITEM_LIST));
      
      layout_item_list->item.id = control_id;
      layout_item_list->item.top_left.anchor = anchor_topleft;
      layout_item_list->item.bottom_right.anchor = anchor_bottomright;
      layout_item_list->next = layout->control_layout;

      layout->n_controls++;
      layout->control_layout = layout_item_list;
      item = &(layout_item_list->item);
    }

    // Top left:
    __compute_top_left_offset__(
        &control_rect, &dialog_rect,
        anchor_topleft, &item->top_left.x, &item->top_left.y
    );

    // Bottom right:
    __compute_bottom_right_offset__(
        &control_rect, &dialog_rect,
        anchor_bottomright, &item->bottom_right.x, &item->bottom_right.y
    );

    return TRUE;
  } else {
	  return FALSE;
  }
}
