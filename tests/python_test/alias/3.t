alias ls="ls -l"
touch a
ls

alias echo="echo a" a="echo"
echo
a

alias a="echo" echo="echo"
a echo
