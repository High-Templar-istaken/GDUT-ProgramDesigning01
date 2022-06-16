mycheck display
pause
mycheck display -c
pause

echo inited
mycheck init
pause
pause
mycheck header -n a first
mycheck header -n b second
mycheck header -n c third
mycheck header -n -k err
mycheck header -n #k err2
pause
mycheck row -n 1 2 3
mycheck row -n 4 5 6
mycheck row -n 7 8 9
mycheck row -n
pause
mycheck header -m c ,a
mycheck header -m b .c
pause
mycheck header -c=name c cc
mycheck header -c=name a aa
mycheck header -c=name b bb
pause
mycheck header -c=default b b
pause
mycheck row -d 3
pause
mycheck row -m 3 ,2
mycheck row -m 1 .4
mycheck row -m 2 ,1
pause
mycheck row -r 1 -c F
mycheck row -r 1 b I
mycheck row -r 1 a R
pause
mycheck row -n 1 2 3
mycheck row -n 4 5 6
mycheck row -n 7 8 9
mycheck row -d 4
pause
mycheck sort -smaller b
mycheck sort -bigger c
pause
mycheck query ( -between c 1 3 -and -equal b I ) -or -not ( -between b 2 5 )
pause
mycheck refresh
mycheck config -list
mycheck config -m 1 1
mycheck sum -add c
mycheck config -m 1 0
mycheck sum -add a
pause
mycheck config -m 2 101
mycheck config -m 4 1
mycheck sum -add c
mycheck config -m 3 0
mycheck sum -add c
mycheck config -reset
mycheck sum -add c
mycheck sum -num c
pause
mycheck port -e porttest.txt
mycheck row -n
mycheck row -n
mycheck row -n
mycheck row -n
mycheck display -c
mycheck port -i porttest.txt
mycheck display -c
pause
echo 测试结束
pause