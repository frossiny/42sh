alias ls="ls -l"
touch a
ls

alias echo="echo a" a="echo"
echo
a

alias b="echo" echo="echo"
b echo
