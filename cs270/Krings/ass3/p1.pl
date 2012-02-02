#!/usr/bin/perl


$FILE=$ARGV[0];                            #pass in file as command line arg
open (FILE);
use Scalar::Util qw(looks_like_number);    #funtion to detect if a character is a number or not


@file_name=<FILE>;                       #reads all file names from file and stores them into an array
$num_files=scalar @file_name;            #stores number of file names in num_files
print "\n"; 

for($i=0;$i<$num_files;$i++)            #for how many file names that are in the file
{
  $numeric_val = substr(@file_name[$i],0, 1);       #takes first char off of a file name
  $k=1; 
  if(looks_like_number($numeric_val))               #if the first char is a number then remove the number
  {
      while(looks_like_number($numeric_val))
      {
          $num_length=$k-1;                          #adjusts for 1 less than total numbers plus exit condition
          $numeric_val = substr(@file_name[$i],0, $k);             
	  $k++;
      }
      @file_name[$i] = substr(@file_name[$i], $num_length);  
  }
  else                                               #if first char is NOT a number then add one
  {
      $num=$i+1;                                     #allows numbering to start with "01" instead of "00"
      if($i<9)
      {
	  @file_name[$i]= "0" . $num . " " .  @file_name[$i];           #concatonation of 0+number+file name
      }
      else
      {
      
	  @file_name[$i]= $num . " " .  @file_name[$i];                 #if it is the tenth file then dont concatonate a 0 before number
      }
  }
    print "@file_name[$i]\n";                                          #print out result
  
}

