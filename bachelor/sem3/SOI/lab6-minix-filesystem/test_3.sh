f1="f1"
f2="f2"
text="to jest tekst to pliku, nie moze byc za krotki ale dlugi tez byc nie moze, mysle ze taki jest w sam raz"
make || {
	echo Error
	exit 1
}

cc -o tmp_test  compare.c || {
	echo Error
	exit 1
}

echo $text > $f1
./fs create 10 		|| exit 1
./fs copyTo $f1		|| exit 1
mv $f1 $f2 #changing name of file id order to not overwrite it
./fs copyFrom $f1	|| exit 1
./tmp_test $f1 $f2 	|| exit 1

echo Test completed

rm $f1 $f2 fs tmp_test disk
