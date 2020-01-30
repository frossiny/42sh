# 42sh

[![Build Status](https://travis-ci.com/frossiny/42sh.svg?token=GMLTFAz14akzGAbryz21&branch=dev_lubenard)](https://travis-ci.com/frossiny/42sh)

## How to build the project
```
git clone https://github.com/frossiny/42sh
cd 42sh
make
```

## How to launch our Shell
After building it, just type:
```
./42sh
```

## Launch our unit tests:
```
make tests
```

## Features

### Pipes:
```
Example: ls | cat -e
         ls | grep auteur | cat -e
```

### Redirections:
They include:
 - Simple redirections: `>` `<` 
 - Append to a file : `>>`
 - Heredoc : `<<`
 - File descriptor handling, including closing them : `2>&1` `1>&-`
```
Example: ls > file1 > file2
         cat -e < auteur > file 2>&-
```
### Inhibitors
 - Simple quotes: '
 - Double quotes: "
 - Backslashes (Escape character): \
```
Example: echo "Hello world"
         echo \
         salut
```

### History management
It include:
  - `!` token
    -  !! Becomes the last command executed
    - !n Becomes the command number n in historydevient la commande numero n de l'historique
    - !-n Becomes the command number n in history, starting at the end
    - !str Becomes the last command executed starting with str
  - history builtin
      - For more about history builtin, see [here](#History)
  - fc builtin
      - For more about fc builtin, see [here](#fc)
  - history shortcut in line edition
      - For more about history shortcut, see [here](#Shortcut)

### Internal variables
```
Example: MYVAR=MyValue
```

### Line Edition
  - Multi-line line edition with syntax highlighting

  - Subprompts with commands ending with \ " ' <<

### <a name="Shortcut">Shortcut</a>
```
arrow right : cursor moves right
arrow left : cursor moves left
arrow up : history previous
arrow down : history next
home : cursor goes to cmd first character
end : cursor goes to cmd last character
shift + arrow right : cursor moves to the next word
shift + arrow left : cursor moves to the previous word
backspace : delete the previous character
delete : delete the currently pointed character
shift + arrow up : cursor moves one line up
shift + arrow down : cursor moves one line down
ctrl + d : EOF / exit
ctrl + l : clear screen
ctrl + v : Go to visual mode (press again to deactivate)
ctrl + r : research into history
tabulation : launch autocompletion
IN VISUAL MODE
ctrl + y : copy selection
ctrl + x : cut selection
ctrl + p : replace the selection with the last copied selection
```

### Builtins [Posix compliant]

#### cd 
```
[-P], Handle the operand dot-dot physically; symbolic link components shall be resolved before dot-dot components are processed.
[-L], Handle the operand dot-dot logically; symbolic link components shall not be resolved before dot-dot components are processed
```

#### set
List all internal variables
```
Example: set
```

#### unset
Remove a variable from environnement
```
Example: unset PWD
```

#### alias
```
42sh: usage: alias key1=value1
```
Aliases can expand recursively.

#### unalias

Create/delete aliases with the alias builtin
```
unalias key1 key2 key3 ...
```

#### <a name="fc">fc</a>
```
fc: usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]
```

#### <a name="History">history</a>
```
42sh: history: usage: 						[-c] [-d offset] or history -awr
```
History is loaded at startup, and is located at `$HOME/42sh_history`

#### exit
```
When a valid numeric argument is specified, exit with passed value

If multiple arguments are specified, an too many arguments error will be printed

If a non-numeric value is specified as argument, return code will be set to 255 and an invalid arguments error will be printed
```

**References:**

Norme POSIX: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

Manuel bash: https://www.gnu.org/software/bash/manual/bash.html
