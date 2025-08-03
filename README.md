# Switchblade

## Switches keyboard layout with the Caps Lock key. Just like [Switchy](https://github.com/erryox/Switchy)!

This code is basically **refactored** and **modernized** version of **Switchy**. Logic was mostly borrowed from there.
This version, **stabler than Switchy**

## Installation

### Step 1: Get `switchblade.exe`

You have two options. Downloading the release is the easiest.

#### Option A: Download Latest Release (Recommended)
1.  Go to the [**Releases**](https://github.com/0xKarinyash/switchblade/releases) page.
2.  Download `switchblade.exe` from the latest release assets.

#### Option B: Build from Source
You will need a C compiler (MSVC via Visual Studio is the easiest way) and CMake.
```bash
# Clone the repository
git clone https://github.com/0xKarinyash/switchblade.git
cd switchblade

# Configure and build the project
cmake -S . -B build
cmake --build build --config Release
```
The executable will be in the build/Release/ directory

### Step 2: Set Up to Run on Startup

To have Switchblade launch automatically when you start Windows:
1.  Press `Win+R` to open the Run dialog.
2.  Type `shell:startup` and press Enter.
3.  Copy or move your `switchblade.exe` file into this folder.

> **Important: Administrator Privileges**
> For layout switching to work in programs running with administrator privileges (like games or system tools), 
> **Switchblade** must also be run as an administrator. You can automate this by creating a task in the Windows Task Scheduler.

## Usage
Same as in switchy:
* **CapsLock** to change keyboard layout
* **Shift+CapsLock** to toggle CapsLock state
* **Alt+CapsLock** to enable/disable Switchy

## Future plans
* Nice installer that adds in task schedule
* Config
* Remapping default shortcuts (that listed above i mean)
* Taskbar icon (that can be disabled in config)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.