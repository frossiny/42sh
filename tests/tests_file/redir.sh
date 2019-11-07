ls > ../redir_tmp
cat ../redir_tmp
#cat -e < ../../Makefile
#cat -e < ../../Makefile > ../redir_tmp
cat ../redir_tmp
echo "Test" > ../redir_tmp
echo "Test2" >> ../redir_tmp
cat ../redir_tmp
rm ../redir_tmp
