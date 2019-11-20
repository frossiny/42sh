rm -rf "/tmp/test_globbing"
mkdir "/tmp/test_globbing"
cd "/tmp/test_globbing"

touch \?a
ls \??

touch \*a
ls \*?
