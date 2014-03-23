#./main -search /media/DISK_E/index "the" | tee 1.log
#./main -search /media/DISK_E/index "19 & ! 4" | tee 1.log
#./main -search /media/DISK_E/index "19 4" | tee 1.log
#./main -search /media/DISK_E/index "current \1 increase" | tee 1.log
#./main -search /media/DISK_E/index "gdp growth" | tee 1.log
#./main -search /media/DISK_E/index "german marks" | tee 1.log
./main -search-batch /media/DISK_E/index benchmark/rcv1/queries.txt 2>&1 | tee 1.log

