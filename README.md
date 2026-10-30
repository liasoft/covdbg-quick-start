# covdbg Quick Start

Build a small C++ application and collect code coverage with the latest [covdbg](https://covdbg.com/) release on Windows.

## Prerequisites

* Windows 10 (x64) or Windows 11
* Visual Studio with the Desktop development with C++ workload
* CMake 3.20 or newer
* A covdbg account for signing in

## Installation

Download the [latest covdbg MSI installer](https://covdbg.com/download/latest/installer.msi) and run it. It installs covdbg for your Windows user and adds it to PATH. Open a new terminal and verify the version:

```powershell
covdbg --version
```

Alternatively, extract the [latest portable ZIP](https://covdbg.com/download/latest/portable.zip) and add its directory to PATH. Keep `covdbg.exe` and `libcovdbg.dll` together.

Sign in before collecting coverage:

```powershell
covdbg login
```

Follow the browser sign-in instructions printed by the command.

The browser sign-in ends with choosing the team to sign in for. Use `covdbg login --team personal` to skip the choice, and `covdbg whoami` to check (`Signed in as <email> for <team>`). Personal use covers one private repository at a time.

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

The included workflow builds the example on Windows x64 (`windows-latest`) and Windows ARM64 (`windows-11-arm`), installs covdbg 1.5.1 with `liasoft/setup-covdbg@v1`, and uploads the LCOV and Cobertura reports for each.

Public repositories are free and need no secret. With `permissions: id-token: write` on the job, covdbg presents the token GitHub issues to the run, which names the repository, and a public repository is licensed. The workflow runs on pushes and on pull requests opened from this repository: GitHub issues no token to a pull request from a fork, so the workflow skips those instead of failing.

A private repository still needs a project token. Add a repository Actions secret named `COVDBG_PROJECT_TOKEN` containing a project token from [app.covdbg.com](https://app.covdbg.com/), and pass it to the `Run Coverage` step through `env`. CI does not use the interactive `covdbg login` command.

> [!NOTE]
> covdbg 1.5.0 and newer license a public repository's GitHub Actions run without a token. The old `--fetch-license`, `COVDBG_LICENSE`, and `COVDBG_LICENSE_FILE` options are no longer supported.
