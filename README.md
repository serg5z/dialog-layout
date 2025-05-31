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
attach_layout(GetModuleHandle(NULL), hDlg, MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT));
```

* See [`include/layout.h`](include/layout.h) for full API.

---

**Quick Start – dialog-layout**

---

## 🚀 Quick Start

### 1. Clone and Build the Library

```sh
git clone https://github.com/serg5z/dialog-layout.git
cd dialog-layout
mkdir build && cd build
cmake ..
cmake --build .
```

This produces the static library in `build/`.

---

### 2. Add to Your Project with CMake

\*\*A. Using \*\***`add_subdirectory()`**

```cmake
add_subdirectory(path/to/dialog-layout)
target_link_libraries(yourapp PRIVATE dialog-layout::dialog-layout)
```

\*\*B. Using \*\***`FetchContent`**

```cmake
include(FetchContent)
FetchContent_Declare(
  dialog-layout
  GIT_REPOSITORY https://github.com/serg5z/dialog-layout.git
  GIT_TAG main
)
FetchContent_MakeAvailable(dialog-layout)

target_link_libraries(yourapp PRIVATE dialog-layout::dialog-layout)
```

**C. Using ****`find_package()`**** (after install)**

```cmake
find_package(dialog-layout REQUIRED)
target_link_libraries(yourapp PRIVATE dialog-layout::dialog-layout)
```

---

### 3. Basic Usage Example

In your code:

```c
#include "layout.h"
attach_layout(GetModuleHandle(NULL), hDlg, MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT));
```

Add a matching `RCDATA` layout resource to your `.rc` file as shown in the documentation.

---

You’re ready to use dialog-layout! For more details and advanced usage, see the full documentation.

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

* [Example resource file usage](docs/example-rc.md)
* [API documentation](https://serg5z.github.io/dialog-layout/)
