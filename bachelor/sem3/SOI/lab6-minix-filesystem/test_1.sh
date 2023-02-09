file="file.txt"
text="lorem ipsum lalsdasldkadkadslasldlasdasldlasdlkadsadsadasdsadsadsadafdfadasda"

make || {
	echo Error
	exit 1
}
echo $text > $file
./fs create 10		|| exit 1

echo PRZED 
./fs ls			|| exit 1
./fs printMap		|| exit 1
./fs copyTo $file	|| exit 1

echo PO 
./fs ls			|| exit 1
./fs printMap		|| exit 1

rm file.txt
./fs copyFrom $file 	|| exit 1
./fs remove $file	|| exit 1

echo PO USUNIECIU
./fs ls			|| exit 1
./fs printMap		|| exit 1
./fs delete		|| exit 1

rm fs $file
echo Test completed
