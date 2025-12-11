#example pattern matching three operators  
$string = "aabbbaabbbabab";
$string =~ m/baa/;
print "Befor:$`\n"; # To print before by text
print "Match:$&\n"; # To print exact match of text 
print "After:$'\n"; # To print after match
