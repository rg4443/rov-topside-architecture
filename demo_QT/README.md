# QT Demostration
This is a demonstration frontend for experimenting and showcasing QT's features. This will not be used in the competition

# Building and Run
You may use [QT Creator](https://www.qt.io/product/development-tools) for development. Simply open this directory as a workspace.

Alternatively, you may follow the below instructions to setup a IDE agnostic environment:
1.  create build directory inside test_QT
```
mkdir build
```
2.  cd into build
```
cd build
```
3. run cmake and let it setup build workspace
```
cmake ..
```
4. now run gnu make
```
make
```

Clangd is also utilized to lint and make a consistent format. Your favorite text editor (Emacs, VSCode, Vim) should have LSP server functionality that handles and talk with clangd, so no additional configuration is needed to setup clangd, _except_ for the following: 
You need to export the compile commands that CMake uses, which includes all the headers and stuff that QT includes. Simply do the following: 
1. Run cmake with `CMAKE_EXPORT_COMPILE_COMMANDS` flag enabled
```
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```
In additional to setting up a build environment, CMake will also output a `compile_commands.json`, a JSON file containing the required commands to compile the project. This includes all the information clangd needs to know. It looks something like this
``` json
[
{
  "directory": "/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build",
  "command": "/usr/bin/c++ -DQT_CORE_LIB -DQT_GUI_LIB -DQT_NO_DEBUG -DQT_WIDGETS_LIB -I/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build/test_QT_autogen/include -isystem /opt/homebrew/lib/QtCore.framework/Headers -iframework /opt/homebrew/lib -isystem /opt/homebrew/share/qt/mkspecs/macx-clang -isystem /opt/homebrew/include -isystem /opt/homebrew/lib/QtWidgets.framework/Headers -isystem /opt/homebrew/lib/QtGui.framework/Headers -std=gnu++17 -arch arm64 -o CMakeFiles/test_QT.dir/test_QT_autogen/mocs_compilation.cpp.o -c /Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build/test_QT_autogen/mocs_compilation.cpp",
  "file": "/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build/test_QT_autogen/mocs_compilation.cpp",
  "output": "CMakeFiles/test_QT.dir/test_QT_autogen/mocs_compilation.cpp.o"
},
{
  "directory": "/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build",
  "command": "/usr/bin/c++ -DQT_CORE_LIB -DQT_GUI_LIB -DQT_NO_DEBUG -DQT_WIDGETS_LIB -I/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build/test_QT_autogen/include -isystem /opt/homebrew/lib/QtCore.framework/Headers -iframework /opt/homebrew/lib -isystem /opt/homebrew/share/qt/mkspecs/macx-clang -isystem /opt/homebrew/include -isystem /opt/homebrew/lib/QtWidgets.framework/Headers -isystem /opt/homebrew/lib/QtGui.framework/Headers -std=gnu++17 -arch arm64 -o CMakeFiles/test_QT.dir/main.cpp.o -c /Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/main.cpp",
  "file": "/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/main.cpp",
  "output": "CMakeFiles/test_QT.dir/main.cpp.o"
},
{
  "directory": "/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build",
  "command": "/usr/bin/c++ -DQT_CORE_LIB -DQT_GUI_LIB -DQT_NO_DEBUG -DQT_WIDGETS_LIB -I/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/build/test_QT_autogen/include -isystem /opt/homebrew/lib/QtCore.framework/Headers -iframework /opt/homebrew/lib -isystem /opt/homebrew/share/qt/mkspecs/macx-clang -isystem /opt/homebrew/include -isystem /opt/homebrew/lib/QtWidgets.framework/Headers -isystem /opt/homebrew/lib/QtGui.framework/Headers -std=gnu++17 -arch arm64 -o CMakeFiles/test_QT.dir/mainwindow.cpp.o -c /Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/mainwindow.cpp",
  "file": "/Users/raph/MATE2026/2025-26-MATE-Topside/demo_QT/mainwindow.cpp",
  "output": "CMakeFiles/test_QT.dir/mainwindow.cpp.o"
}
]
```
2. Now symlink this file at the root project directory (in this case 2025-26-MATE-Topside/demo_QT)
```
ln -s build/compile_commands.json .
```
