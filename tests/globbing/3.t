rm -rf "/tmp/test_globbing"
mkdir "/tmp/test_globbing"
cd "/tmp/test_globbing"
mkdir \]
touch \]/yes
touch a\[b
touch c\[\]

ls []]
echo a[!]]?
echo c[[][]]
