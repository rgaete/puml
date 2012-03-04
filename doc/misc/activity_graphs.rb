%x/hg activity --showtags --datemin=2012-01-15 --datemax=2012-03-04/
%x/mv activity.png activity_overall.png/
%x/hg activity --showtags --split=authors --maxcaptions=9 --datemin=2012-01-15 --datemax=2012-03-04/
%x/mv activity.png activity_authors.png/
%x/hg activity --showtags --split=files --maxcaptions=9 --datemin=2012-01-15 --datemax=2012-03-04/
%x/mv activity.png activity_files.png/
%x/hg activity --showtags --split=directories --datemin=2012-01-15 --datemax=2012-03-04/
%x/mv activity.png activity_directories.png/
