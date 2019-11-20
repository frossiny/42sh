rm -rf "/tmp/test_globbing"
mkdir "/tmp/test_globbing"
cd "/tmp/test_globbing"

touch a

ls [!b-z]
ls [!a]
ls [!u]
ls []a]
ls [a]
