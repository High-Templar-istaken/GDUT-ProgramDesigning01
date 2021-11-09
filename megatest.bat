mycheck display
pause
mycheck display -c
pause

echo inited
mycheck init
pause
mycheck display
pause
mycheck header -n a first
mycheck header -n b second
mycheck header -n c third
mycheck display
mycheck display -c
pause
mycheck row -n 1 2 3
mycheck row -n 4 5 6
mycheck row -n 7 8 9
mycheck row -n
mycheck display -c
pause
mycheck header -m c ,a
mycheck header -m b .c
mycheck display -c
pause
mycheck header -c=name c cc
mycheck header -c=name a aa
mycheck header -c=name b bb
mycheck display
mycheck display -c
pause
mycheck header -c=default b b
mycheck display -c
pause
mycheck row -d 3
mycheck display -c
pause
mycheck row -m 3 ,2
mycheck row -m 1 .4
mycheck row -m 2 ,1
mycheck display -c
pause
mycheck row -r 1 c F
mycheck row -r 1 b I
mycheck row -r 1 a R
mycheck display -c
pause
