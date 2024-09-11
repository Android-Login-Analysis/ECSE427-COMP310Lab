**Hello everyone!**

Before our tutorial this Friday, please make sure to have GDB or LLDB installed on your system for the debugging exercises. Here’s how to set it up depending on your operating system:

---

### **For macOS Users (Apple Silicon and Intel)**

- **Apple Silicon (M1/M2)**: You should use **LLDB**, which comes pre-installed with Xcode or the Command Line Tools on macOS. You can check if LLDB is already installed by running the following in your terminal:

  ```bash
  lldb --version
  ```

  If LLDB is not installed, you can install Xcode Command Line Tools with this command:

  ```bash
  xcode-select --install
  ```
  
- **Intel-based macOS**: You can either use **LLDB** (which comes with Xcode, as described above), or install **GDB** via Homebrew:
  1. Install Homebrew if you haven’t:

     ```bash
     /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
     ```

  2. Then, install GDB:

     ```bash
     brew install gdb
     ```

  3. If you install GDB, you’ll need to [code-sign](https://sourceware.org/gdb/wiki/BuildingOnDarwin) it to comply with macOS security requirements.

---

### **For Linux Users**

- On Linux, GDB is often pre-installed. You can check if it’s available by running:

  ```bash
  gdb --version
  ```

  If GDB is not installed, you can install it with your distribution’s package manager:
  - **Ubuntu/Debian**:

    ```bash
    sudo apt install gdb
    ```

  - **Fedora**:

    ```bash
    sudo dnf install gdb
    ```

  - **Arch Linux**:

    ```bash
    sudo pacman -S gdb
    ```

---

### **For Windows Users**

- For Windows, I recommend using **WSL (Windows Subsystem for Linux)** to run GDB in a Linux-like environment:
  1. Install WSL by following [this guide](https://docs.microsoft.com/en-us/windows/wsl/install).
  2. Once WSL is installed and running, you can install GDB inside your WSL distribution (e.g., Ubuntu) using:

     ```bash
     sudo apt install gdb
     ```

Alternatively, you can use **MinGW** to install GDB natively on Windows:

  1. Download and install MinGW from [here](https://sourceforge.net/projects/mingw/).
  2. During installation, make sure to select the GDB package.
  3. After installation, add the MinGW `bin` directory to your system’s PATH.

---

Please make sure to test your installation by running `gdb --version` or `lldb --version` before Friday to ensure everything works.
