no_exist="not_existing_file.we"
make || {
	echo Error
	exit 1
}

./fs create 1000 	&& exit 1 
./fs create 0		&& exit 1  
./fs create 10 		|| exit 1 
./fs ls			|| exit 1 
./fs copyTo $no_exist 	&& exit 1 
./fs copyFrom $no_exist	&& exit 1 
./fs remove $no_exist 	&& exit 1
./fs ls 		|| exit 1
./fs delete		|| exit 1 

rm fs
echo Test completed
