# SUBHELION TEMPLATE LIBRARY

## Requirements

### Build requirements
- MSVC (included in [Visual Studio 2019 Build Tools](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2019)) or Clang (WIP)

### Development requirements
- [Visual Studio Code](https://code.visualstudio.com/)
- Bash (included in [Git for Windows](https://gitforwindows.org))

### Optional development tools (scripts)
- [ShellCheck](https://www.shellcheck.net)

### Optional development tools (cpp)
- [Visual Studio Code Cpp Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

## Templates

### List of templates
```
- base
- cpp
- cpp_msvc
- cpp_mvsc_cmd
- cpp_vcpkg
- cpp_win32
- cpp_win32_dx11
- cpp_win32_nocrt
```

### Scripts (WIP)

```sh
# (re)start code with tools
start

# install vcpkg
vcpkg

# install dependencies with vcpkg
install

# rebuild local/vend
vend

# building

build

# running

run
run --debug
run --headless
```

## API (WIP)

```
void main_init();
void main_size();
void main_idle();
void main_start();
void main_step();
void main_draw();
void main_on_system_event( app_system_event );
void main_exit();
void main_midi( midi_event event );
```
