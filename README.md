# covdbg Quick Start

Build a small C++ application and collect code coverage with [covdbg](https://covdbg.com/) 1.3.0 on Windows.

## Prerequisites

* Windows 10 (x64) or Windows 11
* Visual Studio with the Desktop development with C++ workload
* CMake 3.20 or newer
* A covdbg account for signing in

## Installation

Download the [covdbg 1.3.0 MSI installer](https://downloads.covdbg.com/covdbg-1.3.0-x64.msi) and run it. It installs covdbg for your Windows user and adds it to PATH. Open a new terminal and verify the version:

```powershell
covdbg --version
# covdbg 1.3.0
```

Alternatively, extract the [portable ZIP](https://downloads.covdbg.com/covdbg-1.3.0-x64.zip) and add its directory to PATH. Keep `covdbg.exe` and `libcovdbg.dll` together.

Sign in before collecting coverage:

```powershell
covdbg login
```

Follow the browser sign-in instructions printed by the command.

## Build

Clone this example and build it with debug symbols (PDB files):

```powershell
git clone https://github.com/liasoft/covdbg-quick-start.git
cd covdbg-quick-start
cmake -S . -B build
cmake --build build --config Debug
```

The build produces `test_app.exe` and `test_app.pdb` in `build/Debug`.

## Running covdbg

Collect coverage while running the application:

```powershell
covdbg --config .covdbg.yaml --output .\build\Debug\test_app.covdb .\build\Debug\test_app.exe
```

Convert the coverage database to LCOV for use with other tools:

```powershell
covdbg convert --format LCOV --input .\build\Debug\test_app.covdb --output .\build\Debug\test_app.lcov
```

## GitHub Actions

The included workflow builds the example, installs the latest covdbg release with `liasoft/setup-covdbg@v0`, and uploads the LCOV report.

Public repositories are free, but CI still authenticates with a project token. A token from your personal team at [app.covdbg.com](https://app.covdbg.com/) is sufficient.

Add a repository Actions secret named `COVDBG_PROJECT_TOKEN` containing a covdbg project token authorized for your repository. The workflow passes it to covdbg through the environment; CI does not use the interactive `covdbg login` command.

> [!NOTE]
> covdbg 1.3.0 uses `covdbg login` or `COVDBG_PROJECT_TOKEN`. The old `--fetch-license`, `COVDBG_LICENSE`, and `COVDBG_LICENSE_FILE` options are no longer supported.
