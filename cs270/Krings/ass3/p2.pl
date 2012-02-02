#!/usr/bin/perl

$numargs = $#ARGV + 1;   #setting numargs to be number of command line arguments

for ($i=0;$i<$numargs;$i++)            #for how many files on command line
{
    $ext = substr($ARGV[$i], -6);        #remove last 6 chars from file name
    if($ext eq ".ascii")                 #if 6 chars are ".ascii"
    {
	$file_name=substr($ARGV[$i], 0, -6);   #strip extension off
	$new_file=$file_name . ".txt";         #add new .txt extension
        rename($ARGV[$i], $new_file);          #rename old file with new file
    }
}
