#./main -search /media/DISK_E/index "the" | tee 1.log
#./main -search /media/DISK_E/index "19 & ! 4" | tee 1.log
#./main -search /media/DISK_E/index "19 4" | tee 1.log
#./main -search /media/DISK_E/index "current \1 increase" | tee 1.log
#./main -search /media/DISK_E/index "gdp growth" | tee 1.log
#./main -search /media/DISK_E/index "german marks" | tee 1.log
./main -search-batch /media/DISK_E/index2 benchmark/rcv1/queries.txt 2>&1 | tee 2.log

#./main -search-batch ../index1 test.queries.log 2>&1 | tee small-test1.log
#./main -search-batch ../index2 test.queries.log 2>&1 | tee small-test2.log

