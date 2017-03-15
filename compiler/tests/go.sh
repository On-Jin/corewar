#FILES=`find ../.. | grep "\.s$"`
FILES=`find ../../samples_files/champions | grep "\.s$"`
for path in $FILES
do
	cp $path zaz.s
	cp $path me.s
	../../samples_files/asm zaz.s
	../a.out me.s
	hexdump zaz.cor > zaz.txt
	hexdump me.cor > me.txt
	diff me.txt zaz.txt
	if [ $? != 0 ]
	then
		echo $path
		exit;
	fi
done
