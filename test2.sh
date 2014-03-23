#./main -search-bool /media/DISK_E/index "the" | tee 1.log
./main -search-bool ../index "19 & ! 4" | tee 1.log
./main -search-phrase ../index "19 4" | tee 1.log
./main -search-phrase ../index "current \1 increase" | tee 1.log
./main -search-phrase ../index "gdp growth" | tee 1.log
