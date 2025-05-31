# Example Resource File for dialog-layout

This example demonstrates how to define both a dialog template and its corresponding layout anchors for use with the `dialog-layout` library in a Windows application.

## Contents

* **Dialog Resource**
  Defines the layout and controls of a Windows dialog using standard resource script syntax.

* **Layout Anchors (RCDATA)**
  Defines how each control should anchor and resize as the dialog is resized, using an RCDATA block that matches control IDs with anchor constants.

* **Resource ID Definitions (`resource.h`)**
  All control IDs must be defined with an `L` suffix to ensure they are DWORD sized constants. This is critical for resource compilers and for correct interpretation by the `dialog-layout` library.

## Sample `example.rc`

```rc
#include <windows.h>
#include "resource.h"

// Dialog definition
ID_MAINDIALOG DIALOGEX 0, 0, 250, 120
STYLE DS_SETFONT | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE
CAPTION "Example Dialog"
FONT 8, "MS Shell Dlg"
BEGIN
    LTEXT       "First Name:", IDC_STATIC, 10, 10, 60, 12
    EDITTEXT    IDC_EDIT_FIRSTNAME, 80, 10, 120, 12
    LTEXT       "Last Name:", IDC_STATIC, 10, 28, 60, 12
    EDITTEXT    IDC_EDIT_LASTNAME, 80, 28, 120, 12
    PUSHBUTTON  "OK",     IDOK,     80, 90, 50, 14
    PUSHBUTTON  "Cancel", IDCANCEL, 140, 90, 50, 14
END

// Layout anchors for dialog controls
ID_MAINDIALOG_LAYOUT RCDATA
BEGIN
    IDC_EDIT_FIRSTNAME, 3L, 6L,        // ANCOR_LEFT | ANCOR_TOP, ANCOR_RIGHT | ANCOR_TOP
    IDC_EDIT_LASTNAME,  3L, 6L,        // ANCOR_LEFT | ANCOR_TOP, ANCOR_RIGHT | ANCOR_TOP
    IDOK,              12L, 12L,       // ANCOR_RIGHT | ANCOR_BOTTOM, ANCOR_RIGHT | ANCOR_BOTTOM
    IDCANCEL,          12L, 12L        // ANCOR_RIGHT | ANCOR_BOTTOM, ANCOR_RIGHT | ANCOR_BOTTOM
END
```

* **Control IDs** like `IDC_EDIT_FIRSTNAME` must be defined in `resource.h` **with an `L` suffix** (e.g., `#define IDC_EDIT_FIRSTNAME 1001L`).
* **Anchor constants** (e.g., `3L`, `6L`, `12L`) correspond to bitmask values for anchoring (see `layout.h` documentation).

## Sample `resource.h`

```c
#define ID_MAINDIALOG        101L
#define IDC_EDIT_FIRSTNAME   1001L
#define IDC_EDIT_LASTNAME    1002L
#define IDOK                 1L
#define IDCANCEL             2L
#define ID_MAINDIALOG_LAYOUT 200L
```

> **Note:** The `L` suffix ensures that each constant is a 32-bit value, as required by both the Windows resource compiler and the dialog-layout library. Omitting the `L` may result in subtle bugs or resource parsing failures.

## Usage in Code

In your dialog’s `WM_INITDIALOG` handler, attach the layout:

```c
#include "layout.h"
attach_layout(GetModuleHandle(NULL), hDlg, MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT));
```

When the dialog is resized, controls will be anchored according to the rules in the RCDATA layout block.

---

For a complete, working example, see the main project README and `main.c`.

