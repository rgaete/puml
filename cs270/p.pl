$INFILE="input.txt"; 
open(INFILE) or die "Cant open file\n"; 
open(OUTFILE, ">", "out.txt");
$INFILE=~s/in/cook/;
if($INFILE=~/co/)
{
  print $INFILE;
}
else
{
   print "yeh";
}
