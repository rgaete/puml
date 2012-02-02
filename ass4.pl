#/usr/bin/perl
use Cwd;
use File::Copy;
use File::Compare;
$currpath=getcwd;
$trashdir=$ENV{"HOME"}."/trashbin";
$flag=0;
$ARGC=@ARGV;
if (-d "$trashdir")
{

}
else
{
   mkdir "$trashdir";
   print "trashbin directory has been added to your home path \n";
}

if($ARGV[0] eq "-l")
{
   opendir (DIR, $trashdir);
   @files = grep("*", readdir (DIR));
   foreach (@files)
   {
     print;
     print "
";
   }
}
if ($ARGV[0] eq "-e")
{
   opendir (DIR, $trashdir);
   @files = grep("*", readdir (DIR));
  foreach $file (@files)
  {
    unlink "$trashdir/$file";
  }
  $flag=1;
}
if ($ARGV[0] eq "-f")                                                            
{
  system('rm','-r', $trashdir);
  $flag=1;
}


if ($ARGV[0] eq "-i")
{
  opendir (DIR, $trashdir);
  @files = grep("*", readdir (DIR));
  foreach $file (@files)
  {
   if($file eq "." || $file eq "..")
   {

   }
   else
   {
    print "Do you want to delete ";
    print $file;
    print " y/n?";
    $choice=<STDIN>;
    print $choice;
    if($choice eq "y
")
    {
      unlink "$trashdir/$file";
    }
   }
  }
  $flag=1;
}

if($ARGV[0] eq "-r")
{
  for($i=1; $i <= $ARGC; $i++)
  {
     move($trashdir."/".@ARGV[$i], $currpath);
  }
}

if($flag==0 && $ARGC>0)
{
  for($i=0; $i <= $ARGC; $i++)
  {
     move($currpath."/".@ARGV[$i], $trashdir);
  }
}
