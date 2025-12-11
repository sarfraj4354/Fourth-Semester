#!C:\Perl64\bin\perl.exe

print "Enter your string: ";
my $string = <STDIN>;
chomp($string);

if ($string =~ m/ab/) {
    print "\nPattern matched in the string\n";
} else {
    print "\nPattern not matched\n";
}
