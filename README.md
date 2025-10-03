# Project for Academic Course 'Introduction to Computer Programming' [CT0665] @ Computer Science [CT3] - University of Venice Ca' Foscari

*Survival Royale, a very simple yet funny card game*

## Welcome:

This is the project of [Giulio Salvi](https://github.com/GiulioSalvi) and [Jacopo Paridisi](https://github.com/jajo-coder) for the academic [course Introduction to Computer Programming [CT0665]](https://www.unive.it/data/course/521402) in the bachelor's degree program in [Computer Science [CT3]](https://www.unive.it/web/en/12090/home) at the [University of Venice Ca&#39; Foscari](https://unive.it).

The project offers two interfaces at run-time:

1. *Terminal User Interface* (*TUI*): it aims to simulate a *Graphical User Interface* (*GUI*) with the features available in modern terminals via [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code), like [coloring](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors) and [text styling](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters), and [Unicode characters](https://en.wikipedia.org/wiki/Unicode). On Windows systems, it requires the project to be run on the [Windows Terminal app](https://apps.microsoft.com/detail/9n0dx20hk701).
2. The *Classic Mode*: it uses plain text printed on the terminal for interacting with the user.

A logging utility, for debugging purposes, can be activated at run-time using the option `--verbose` or its alias `-v` in the *CLI* (*Command Line Interface*) and it will produce log files in the directory `logs`.

## How to Compile and Run:

The project is designed to be cross-platform on Windows, macOS and Linux. Note that for Windows systems you might use some [toolchain](https://en.wikipedia.org/wiki/Toolchain) that serves you a Unix-like environment, such as *[Windows Subsystem for Linux 2](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux)* (*WSL2*) (which is the most recommended and versatile), *MSYS2*, *Cygwin*, *MinGW* and many others.

The main tool to compile and run the project is the [GNU Make](https://en.wikipedia.org/wiki/Make_(software)) file that is placed in the root folder: when cloning this repository for the first time it is **mandatory** to run the target `setup` that will set up your workspace for you. Then you might want to run the target `all` for compiling all the modules of the project. Alternatively, you can run any of the targets starting with `go` which will compile and run the project for you: the project can be run with several interactive modes and configurations.

On Windows systems, the project's *TUI* requires to be run on the [Windows Terminal app](https://apps.microsoft.com/detail/9n0dx20hk701).

If you desire to regenerate the [Doxygen](https://en.wikipedia.org/wiki/Doxygen) documentation, you can run the target `gen-docs` but you need to have Doxygen installed on your system.

## About the Code Organization:

The source code of the project is organized in modules, in particular:

* *ANSI* module: it is formed by the files `h/ansi.h`, `h/ansi_const.h` and `src/ansi.c`; it provides implementations of the most popular ANSI escape codes.
* *Utility* module: it is formed by the files `h/utility.h` and `src/utility.c`; it provides various utility functions for strings and numbers.
* *CLI* module: it is formed by the files `h/cli.h` and `src/cli.c`; it provides a command-line interface for the program with which users can manipulate the game configuration.
* *Game Configuration* module: it is formed by the files `h/config.h`, `h/config_file.h`, `h/game_configuration.h`, `src/config.c` and `src/config_file.c`; it provides function for saving game configuration to a file, load the game configuration file, load the game configuration from the CLI options and for asking to the user the setting of the game configuration in the terminal.
* *Vector* module: it is formed by the files `h/vector.h` and `src/vector.c`; it provides a dynamically-allocated vector structure and function for its manipulation.
* *TUI* module: it is formed by the files `h/tui.h` and `src/tui.c`; it provides a graphical user interface on the terminal.
* *Logs* module: it is formed by the files `h/logs_configuration.h`, `h/logs.h` and `src/logs.c`; it provides a dynamic way for the program for printing debug informations, either to the terminal or to a log file, in a verbose behavior.
* *Main* module: it is formed by the files `h/main.h` and `src/main.c`; it is the implementation for the game.

## Need help?

If you need any help about the code and the project, please feel free to start a thread in [Q&amp;A category](https://github.com/GiulioSalvi/SurvivalRoyale/discussions/categories/q-a) in the discussion section.

## Documentation:

The full documentation can be found [at this link on GitHub Pages](https://giuliosalvi.github.io/SurvivalRoyale).

## License:

The whole content of this repository (project source code, documentation, specification, report and icon) is licensed under the *GNU General Public License 3.*

You can find the original and complete copy of the license in the *[COPYING](COPYING)* file or [at the original website](https://www.gnu.org/licenses/).

## Acknowledgements:

The *Project Specifications* file is available under the license as a courtesy of [Professor Giulio Ermanno Pibiri](https://github.com/jermp) and of Professor Luca Olivieri.

The *Project Report* file is available under the license and it was redacted with [Jacopo Paridisi](https://github.com/jajo-coder).

The *TUI module* was developed by [Jacopo Paridisi](https://github.com/jajo-coder) and integrated with his help.

If you would like to see more about the team's organization, check the related section in the *Project Report* file.

## Thank you:

A special thank you to my colleague [Jacopo Paridisi](https://github.com/jajo-coder) for his significant contribute and to the professors for the fruitful stimulus.
