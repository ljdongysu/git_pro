#!/bin/bash
# 1.两种执行另一个shell脚本区别为：直接执行"test_dir/set.h"会开启新的子进程去执行"set.h"；若 ". test_dir/set.h"不会开启新进程，会延用当前进程执行"set.h"
# 2."set -e"作用：就是当命令以非零状态退出时，则退出shell。set -e 的作用范围为同一个进程内。参考：https://blog.csdn.net/fc34235/article/details/76598448
set -e
echo "PID of this script: $$"
test_dir/set.h
. test_dir/set.h
