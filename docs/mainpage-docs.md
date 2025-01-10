# **UniProject:**

This project has been developed by [Giulio Salvi](https://github.com/GiulioSalvi) e [Jacopo Paradisi](https://github.com/jajo-coder) on [GitHub](https://github.com/GiulioSalvi/UniProject), with the related [commit history](https://github.com/GiulioSalvi/UniProject/commits/working-branch/).

### Code Organization:

The source code of the project is organized in modules, in particular:

* *ANSI* module: it is formed by the files `h/ansi.h`, `h/ansi_const.h` and `src/ansi.c`; it provides implementations of the most popular ANSI escape codes.
* *Utility* module: it is formed by the files `h/utility.h` and `src/utility.c`; it provides various utility functions for strings and numbers.
* *CLI* module: it is formed by the files `h/cli.h` and `src/cli.c`; it provides a command-line interface for the program with which users can manipulate the game configuration.
* *Game Configuration* module: it is formed by the files `h/config.h`, `h/config_file.h`, `h/game_configuration.h`, `src/config.c` and `src/config_file.c`; it provides function for saving game configuration to a file, load the game configuration file, load the game configuration from the CLI options and for asking to the user the setting of the game configuration in the terminal.
* *Vector* module: it is formed by the files `h/vector.h` and `src/vector.c`; it provides a dynamically-allocated vector structure and function for its manipulation.
* Main module: it is formed by the files `h/main.h` and `src/main.c`; it is the implementation for the game.

Notice that the files `h/includes.h` and `h/consts.h` are just preprocessor files which are used by the other modules.
