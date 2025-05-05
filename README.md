# biplup-run

A recreation of the offline dinosaur game made for the GBA, with a pokemon
twist.

## Looking To Just Run The Game?

The GBA ROM is available in Releases. You can download it from there and install an emulator to play it. Recommended emulator is [mGBA](https://mgba.io/downloads.html).

## How to Develop / Compile from Source

## What's Included

Libraries and tools can be accessed using the [`dependency`][meson-dependency]
and [`find_program`][meson-find_program] functions.

| Project               | Version            | Dependencies               | Programs                              |
| --------------------- | ------------------ | -------------------------- | ------------------------------------- |
| [agbabi]              | 2.1.7              | `agbabi`                   |
| [butano] [^1] [^2]    | 17.3.0             | `butano`                   |
| [gba-hpp]             | r180.e313a94       | `gba-hpp`                  |
| [gba-link-connection] | 6.2.3              | `gba-link-connection`      |
| [gbfs]                | 2002-02-07         | `gbfs`                     | `gbfs`, `insgbfs`, `lsgbfs`, `ungbfs` |
| [gbt-player]          | 4.4.1              | `gbt-player`               | `mod2gbt`, `s3m2gbt`, `s3msplit`      |
| [grit]                | 0.9.2              |                            | `grit`                                |
| [libfat] [^1]         | 1.1.5.r2.g69543f0  | `libfat`                   |
| [libgba]              | r136.0d46fc9       | `libgba`                   |
| [libsavgba]           | 3.3.2              | `libtonc`                  |
| [libseven]            | 0.22.3             | `libseven`                 |
| [libtonc]             | r15.cc862ce        | `libtonc`                  |
| [libugba/libsysgba]   | 0.3.0              | `libugba`, `libsysgba`     |
| [libutil]             | r1.743f5d1         | `libutil`                  |
| [maxmod]              | 1.0.15             | `maxmod`                   |
| [minrt]               | 0.12.0             | `minrt`, `minrt-multiboot` | `makerom`, `gbafix-py`, `bin2s-py`    |
| [mmutil]              | 1.10.1             |                            | `mmutil`                              |
| [posprintf]           | sdk-seven fork     | `posprintf`                |
| [superfamiconv]       | 0.9.2.r16.ga5027f3 |                            | `superfamiconv`                       |

[^1]: Only available with the devkitARM toolchain.
[^2]:
    Pulls in code from agbabi, gbt-player, libtonc, libugba, maxmod, posprintf
    and vgm-player. You may get linking errors if you try to combine those
    dependencies with butano. Use a [partial
    dependency][meson-partial_dependency] to access includes and build flags.

## Installation and Usage

As all the libraries and tools are compiled from source, the only things you
need to have installed and in your PATH are:

- meson (at least version 1.1.0 or later)
- git
- A compiler for your system (`cl.exe`, `gcc`, etc.)
- A compiler for the GBA (`arm-none-eabi-gcc`)
- ninja

See the [meson gba book](https://lunarlambda.github.io/meson-gba-book/) for more
information.

## Installing Meson

Here is the [meson installer](https://mesonbuild.com/Getting-meson.html), which
is the build system that is used for this project.

There are multiple ways of installing meson, but for most systems, installing it
through Python is the best way to install it for the purposes of this project.

### Windows

```powershell
pip install --user meson
```

### MacOS

```sh
pipx install meson
pipx ensurepath
```

### Ubuntu

```sh
pip3 install --user meson
```

### Adding to PATH

MacOS should automatically add meson to PATH.

Windows you have to search for, which if it is a user install, should be in

```powershell
C:\Users\<your username>\Roaming\Python\Python312\Scripts
```

Add this to your <ins>User</ins> environment variables.

For Ubuntu, you have to add it to PATH manually. Run this command:

```sh
export PATH=$PATH:~/.local/bin
```

## Installing Ninja

### Windows

```powershell
winget install Ninja-build.Ninja
```

### MacOS

```sh
brew install ninja
```

### Linux

#### Ubuntu

```sh
sudo apt install ninja-build
```

#### Other Linux distros

Either `ninja` or `ninja-build` for installation name. Use your system's package
manager for installation.

## Setting up your compiler

### (Windows, using Powershell)

#### GCC / Clang

Please follow [this guide](https://www.msys2.org/) for installing MSYS2. Take
note of the path that you installed it in.

You may also install LLVM if you only need `clang`. Through winget, running the
following command:

```powershell
winget install LLVM.LLVM
```

##### Adding to PATH

Open up your system environment variables. Find the PATH variable, and add this
new directory path:

```powershell
path\to\msys64\ucrt64\bin
```

where the `path\to\msys64` is the path leading up to your MSYS2 install. By
default, this should be:

```powershell
C:\msys64\ucrt64\bin
```

LLVM should be installed at `C:\Program Files\LLVM`. Add to your PATH variable:

```powershell
C:\Program Files\LLVM\bin
```

to have `clang` in PATH.

#### cl.exe (MSVC)

Please follow
[this guide](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170)
for installing MSVC. Make sure to install "Desktop Development with C++"
workload when installing Visual Studio.

Keep note of your directory where you installed Visual Studio.

##### Adding to PATH

You may have to find the path to `cl.exe` yourself just to make sure. It should
look something like this:

```powershell
path\to\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\<string of numbers>\bin\Hostx64\x64
```

An example one would look like this:

```powershell
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx64\x64
```

### MacOS

If you have installed X-code, `clang` should come installed by default on your
system. If you have not, run this command:

```sh
xcode-select --install
```

This should take a while, but it will install all basic requirements needed for
C/C++ programming.

## Setting up devkitPro

### Windows

Here is the [installer](https://github.com/devkitPro/installer/releases) file
for installing devkitPro. It will walk you through all the steps needed to
install it. Keep note of the path that you install it in.

Only the GBA Development is required for this project, and installation may take
a while and have some weird behavior, so be patient while it is installing.

#### Adding the ARM Compilers to PATH

devkitPro may have created some environment variables for you, so you have to go
and edit them to make sure they are existing paths.

Open up your System variables and change DEVKITARM to
`path\to\devkitPro\devkitARM`, and change DEVKITPRO to `path\to\devkitPro`.
Default installation would change the system variables to
`C:\devkitPro\devkitARM` and `C:\devkitPro` respectively.

Open up your PATH variable and add the path to the bin folder inside of your
devkitARM folder. For example, if you used the default installation it would be
`C:\devkitPro\devkitARM\bin`.

### MacOS

Here is the link for
[devkitPro pacman](https://github.com/devkitPro/pacman/releases/tag/v6.0.2),
which is the package manager for installing devkitPro.

Make sure to install this and double click to run it. It may not allow you to
the first time, so follow these steps:

1. click 'Done'
2. Head to Settings > Privacy and Security
3. Scroll to the 'Security' section
4. Under the "devkitPro ... " click "Open Anyway".

Once installed, restart your computer. Once you have restarted your computer,
open up your terminal and type in this command:

```sh
sudo dkp-pacman -S gba-dev
```

Running this command will give you options, choose the default option `all`.
This will install all your dependencies into /opt/devkitPro.

#### Adding the ARM Compilers to PATH

Run these commands:

```
export PATH="/opt/devkitpro/devkitARM/bin:$PATH"
export DEVKITARM="/opt/devkitpro/devkitARM"
```

You may have to refresh your terminal after doing these.

### Linux

Install the
[devkitPro pacman](https://github.com/devkitPro/pacman/releases/tag/v6.0.2)
package manager, following the steps closely given in the link. If on WSL,
follow the extra step provided first.

Restart your terminal or run `source ~/.bashrc` or whatever refresh command
there is for your given shell. Then type in the command:

```sh
sudo dkp-pacman -S gba-dev
```

and click enter through the installation.

Now it should be installed in your `/opt` folder.

#### Adding the ARM Compilers to PATH

Run these commands:

```
export PATH="/opt/devkitpro/devkitARM/bin:$PATH"
export DEVKITARM="/opt/devkitpro/devkitARM"
```

You may have to refresh your terminal after doing these.

## Using devkitPro

Use the following command in the directory to generate a suitable cross file,
which allows for cross compilation:

Windows, using Powershell:

```powershell
$f = Get-Content meson/gba.ini; $f[1] = "path = '$($Env:DEVKITARM)\bin'"; Set-Content dkarm.ini $f
```

Windows, using MSYS2:

```sh
sed "2s|.*|path = '$DEVKITARM/bin'|" meson/gba.ini > dkarm.ini
```

(Windows, using WSL) / Linux / MacOS:

```sh
sed "2s|.*|path = '$DEVKITARM/bin'|" meson/gba.ini > dkarm.ini
```

Make sure to check `dkarm.ini` for conformation that your path variable has a
proper path, in quotes. If it doesn't work, try readding your arm compilers to
PATH and recreating the DEVKITARM path variable, as shown above.

Then run:

```sh
meson setup --cross-file=dkarm.ini build
```

for the setup step.

To build, run:

```sh
ninja -C build
```

The built ROMs (.elf, .gba) will be in the `build` directory. For WSL users, it
may be difficult finding where your GBA ROM is in relation to mGBA. It should be
in `\\wsl.localhost\<distro>\path\to\biplup-run\build`.

## Running Multiple Times

Run this command after you have already built it once:
```sh
meson setup --cross-file=dkarm.ini --wipe --reconfigure build && ninja -C build
```

This should clear any build files in your build folder and should completely reconfigure your project.

## Emulator

Please install [mGBA](https://mgba.io/downloads.html). It has great debugging
tools and will make the process for developing a bit easier.

## License

biplup-run is licensed under the zlib license. See [LICENSE.txt](./LICENSE.txt)
for more information.

See the homepages of the bundled projects for their respective licensing.

This repository is based on the template made by
[LunarLambda](https://github.com/LunarLambda), repository in the link here:
[repo link](https://github.com/LunarLambda/meson-gba)

<!-- Subproject links -->

[agbabi]: https://github.com/felixjones/agbabi
[butano]: https://github.com/GValiente/butano
[gba-hpp]: https://github.com/felixjones/gba-hpp
[gba-link-connection]: https://github.com/rodri042/gba-link-connection
[gbfs]: https://pineight.com/gba/#gbfs
[gbt-player]: https://github.com/AntonioND/gbt-player
[grit]: https://github.com/devkitPro/grit
[libfat]: https://github.com/devkitPro/libfat
[libgba]: https://github.com/gbadev-org/libgba
[libsavgba]: https://github.com/aronson/libsavgba
[libseven]: https://github.com/sdk-seven/libseven
[libtonc]: https://github.com/gbadev-org/libtonc
[libugba/libsysgba]: https://github.com/AntonioND/libugba
[libutil]: https://github.com/sdk-seven/libutil
[maxmod]: https://github.com/devkitPro/maxmod
[minrt]: https://github.com/sdk-seven/runtime
[mmutil]: https://github.com/devkitPro/mmutil
[posprintf]: https://github.com/sdk-seven/posprintf
[superfamiconv]: https://github.com/Optiroc/SuperFamiconv

<!-- Meson links -->

[Meson]: https://mesonbuild.com/index.html
[meson-compiler]: https://mesonbuild.com/Reference-manual_returned_compiler.html
[meson-dependency]:
  https://mesonbuild.com/Reference-manual_functions.html#dependency
[meson-find_program]:
  https://mesonbuild.com/Reference-manual_functions.html#find_program
[meson-options]: https://mesonbuild.com/Build-options.html#using-build-options
[meson-partial_dependency]:
  https://mesonbuild.com/Reference-manual_returned_dep.html#deppartial_dependency
