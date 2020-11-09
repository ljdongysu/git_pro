#!/bin/bash
#set -e
#set -e
echo "PID of this script: $$"
function return1()
{
        return 1
}
function return0()
{
        return 0
}
function returnf()
{
        return $1
}

echo "run start"
return1
if [ $? -ne 0 ];then
        echo "cmd error"
fi
echo "run end !"
