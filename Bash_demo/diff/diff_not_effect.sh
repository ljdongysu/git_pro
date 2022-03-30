#/bin/sbin
file1=./a.txt
file2=./b.txt
diff $file1 $file2 > /dev/null
if [ $0 == 0 ]; then
    echo "Both file are same"
else
    echo "Both file are different"
fi
