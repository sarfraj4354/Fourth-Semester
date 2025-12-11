#!C:\Perl64\bin\perl.exe
#input from user example  

print "your string to check :";
$string = <STDIN>;
if($string =~m/a+[1-5]bb/){
print"\nPattern matched in the string ";
}else {
	print"\n pattern not matched";
}