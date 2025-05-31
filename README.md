# dialog-layout

A lightweight C library for flexible dialog anchoring and layout management in native Windows applications.

---

## Features

* **Dynamic dialog layout:** Easily anchor and resize dialog controls for responsive Windows UI.
* **Minimal dependencies:** Written in pure C, only requires Windows headers.
* **Embeddable:** Integrate as a CMake subproject, via FetchContent, or as a system package.
* **Small API:** Simple functions for attaching, detaching, and applying layouts.

---

## Getting Started

### Building with CMake

```sh
git clone https://github.com/youruser/dialog-layout.git
cd dialog-layout
mkdir build && cd build
cmake ..
cmake --build .
```

### Installing (for find\_package integration)

```sh
cmake --install . --prefix=/your/install/prefix
```

---

## Using in Your Project

### 1. As a Subdirectory

Add to your CMake project:

```cmake
add_subdirectory(path/to/dialog-layout)
target_link_libraries(myapp PRIVATE dialog-layout::dialog-layout)
```

### 2. With FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(
  dialog-layout
  GIT_REPOSITORY https://github.com/youruser/dialog-layout.git
  GIT_TAG v1.0.2
)
FetchContent_MakeAvailable(dialog-layout)

target_link_libraries(myapp PRIVATE dialog-layout::dialog-layout)
```

### 3. Via find\_package (after installation)

```cmake
find_package(dialog-layout REQUIRED)
target_link_libraries(myapp PRIVATE dialog-layout::dialog-layout)
```

If installed in a custom location, set `CMAKE_PREFIX_PATH`.

---

## Example Usage

```c
#include "layout.h"

// Attach layout to dialog, for example in WM_INITDIALOG
attach_layout(GetModuleHandle(NULL), hDlg, TEXT("ID_MAINDIALOG_LAYOUT"));
```

* See [`include/layout.h`](include/layout.h) for full API.

---

## License

This software is distributable under the BSD license.
See the [LICENSE](LICENSE) file for details.

---

## Contributing

Pull requests and issue reports are welcome!

---

## Authors

* Sergey Zorin (c) 2003-2010, 2025

---

## Resources

* [Example resource file usage](docs/example-rc.md) *(optional, add if you create one)*
* [API documentation](include/layout.h)
