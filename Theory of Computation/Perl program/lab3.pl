# example pattern matching three operators  
$string = "Due to covid-19 Fifth semester students in online";
$string =~ m/semester students/;
print "Befor:$`\n"; # To print before by match text[fifth]
print "Match:$&\n"; # To print exact match of text 
print "After:$'\n"; # To print after match
