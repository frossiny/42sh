rm -rf "/tmp/test_globbing"
mkdir "/tmp/test_globbing"
cd "/tmp/test_globbing"

touch a
touch \*
touch \[b
touch \[c\[
touch \!
touch \w
touch d]
touch \\a

echo \?
echo \*
echo \[?
echo \[??
echo [\!z]
echo d\]
echo [\!y]
ls \\\a*
