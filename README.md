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

### Logicals operator `&&` and `||` and separator `;`
`&&` executes the right-hand command of `&&` only if the previous one succeeded.

`||` executes the right-hand command of `||` only it the previous one failed.

`;`  executes the right-hand command of ; always regardless whether the previous command succeeded or failed.
```
Example: make && ./42sh
         ls  ; cd /tmp
         cd /stuff || mkdir /stuff && cd /stuff         
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

### Internal variables handling and expansions
```
Example: MYVAR=MyValue
```
Possibility to export them with the builtin [export](#export).
Possibility to print them
```
Example: echo $USER
```
See [set](#set) and [unset](#unset) for more details

### Hash-table
 - Load all binary found in $PATH
 - Hash-table will be updated:
 - If $PATH's value changes
 - If the content of a directory referenced in $PATH is changed
 - Hash binary
         - for more informations about hash binary, see [here](#hash)
         
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

### Job control
Possibility to put command in background
```
Example: ls -R / &
```
Can be managed with builtins: [jobs](#jobs), [fg](#fg), [bg](#bg)

### Arithmetic expansion
COMLETE HERE

### Builtins [Posix compliant]

#### cd
Change directory
```
[-P], Handle the operand dot-dot physically; symbolic link components shall be resolved before dot-dot components are processed.
[-L], Handle the operand dot-dot logically; symbolic link components shall not be resolved before dot-dot components are processed
```

#### <a name="set">set</a>
List all internal variables
```
Example: set
```

#### <a name="unset">unset</a>
Remove a variable from environnement
```
Example: unset PWD
```

#### alias
Allow to set aliases
```
Usage: alias key1=value1
```
Aliases can expand recursively.

#### unalias
Delete aliases with the alias builtin
```
Usage: unalias key1 key2 key3 ...
```

#### <a name="fc">fc</a>
Offer a more complete way to handle history
```
Usage: fc [-e ename] [-nlr] [first] [last] or fc -s [pat=rep] [cmd]
```

#### <a name="History">history</a>
```
Usage: [-c] [-d offset] or history -awr
```
History is loaded at startup, and is located at `$HOME/.42sh_history`

#### <a name="jobs">jobs</a>
List all jobs.
```
Usage: jobs [-l|-p] [job_id]
```

#### <a name="bg">bg</a>
Allows to relaunch a process stoped in background
```
Usage: fg [job_id]
```

#### <a name="fg">fg</a>
Relaunch a job put in background into foreground
```
Usage: fg [job_id]
```

#### <a name="hash">hash</a>
Handle hash table
```
Usage: hash [-r]
```

#### type
The type utility shall indicate how each argument would be interpreted if used as a command name.
```
Usage: type name
```

#### test
Test conditions and return true or false
```
Usage: test     test expression
                [ expression ]
                ! expression
                If expression is an integer, it becames the value returned.
        -h      -h:             Print this help with all the options listed.
        -b      -b file:        True if file exists and is a block special file.
        -c      -c file:        True if file exists and is a character special file.
        -d      -d file:        True if file exists and is a directory.
        -e      -e file:        True if file exists (regardless of type).
        -f      -f file:        True if file exists and is a regular file.
        -k      -k file:        True if file exists and its sticky bit is set.
        -p      -p file:        True if file is a named pipe (FIFO).
        -r      -r file:        True if file exists and is readable.
        -s      -s file:        True if file exists and has a size greater than zero.
        -u      -u file:        True if file exists and its set user ID flag is set.
        -w      -w file:        True if file exists and is writable.
                                True indicates only that the write flag is on.
                                The file is not writable on a read-only file system even if this test indicates true.
        -x      -x file:        True if file exists and is executable.
                                True indicates only that the execute flag is on.
                                The file is not executable on a read-only file system even if this test indicates true.
        -L      -L file:        True if file exists and is a symbolic link.
        -S      -S file:        True if file exists and is a socket.
        ---------------------------
        =       s1 = s2:        True if the strings s1 and s2 are identical.
        !=      s1 != s2:       True if the strings s1 and s2 are not identical.
        ---------------------------
        -eq     n1 -eq n2:      True if the intengers n1 and n2 are algebraically equal.
        -ne     n1 -ne n2:      True if the intengers n1 and n2 are not algebraically equal.
        -gt     n1 -gt n2:      True if the intengers n1 is algebraically greater than the integer n2.
        -ge     n1 -ge n2:      True if the intengers n1 is algebraically greater than or equal to the integer n2.
        -lt     n1 -lt n2:      True if the intengers n1 is algebraically less than the integer n2.
        -le     n1 -le n2:      True if the intengers n1 is algebraically less than or equal to the integer n2.
```

#### exit
Exit our shell
```
When a valid numeric argument is specified, exit with passed value

If multiple arguments are specified, an too many arguments error will be printed

If a non-numeric value is specified as argument, return code will be set to 255 and an invalid arguments error will be printed
```

### Prompt expansions
PS1 can be exported to set custom prompt
```
COLOR CODES:
{black}, {white}, {red}, {green}, {brown}, {blue}, {cyan}, {purple}, {lgray}
POSSIBLE EXPANSIONS:
\u : the username of the current user
\v : the version of 42sh (e.g., 2.00)
\w : the current working directory, with $HOME abbreviated with a tilde
\j : the number of jobs currently managed by the shell
\h : the hostname up to the first ‘.’
\H : the hostname
```

## **References:**

Posix Norm: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

Bash manual: https://www.gnu.org/software/bash/manual/bash.html
