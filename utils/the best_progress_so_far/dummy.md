./watchdog_app.out 2 3 ./wd_test.out > log.txt 2>&1

./watchdog_app.out 2 3 ./wd_test.out > /mnt/data/run_log.txt 2>&1


./wd_test.out 3 2 ./watchdog_app.out > log.txt 2>&1


killall -9 watchdog_app.out


killall -9 wd_test.out

ps -ef | grep wd_test.out

strace -p <PID של wd_test>

chmod +x run_demo.sh

./run_demo.sh

gdb --args ./watchdog_app.out 2 3 ./wd_test.out

#after segfault type bt, backtrace, it will shoe you where line it crushed
bt

