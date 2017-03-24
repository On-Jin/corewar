.name		"zdoh"
.comment	"w8 for da next one"

start:
zjmp	%:start
ld		%1, r4
ld		%0, r4
zjmp	%:start
