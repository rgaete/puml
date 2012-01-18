
hgactivity is an extension for mercurial (http://mercurial.selenic.com/)
that creates an image displaying the activity for a repository.

The official homepage is http://labs.freehackers.org/projects/hgactivity

Design & Coding:
----------------
Thomas Capricelli <orzel@freehackers.org>
http://www.freehackers.org/thomas/free-software/


REQUIREMENTS
------------
hgactivity is tested with python 2.6 and 2.7, and mercurial 1.6.x and
1.7.x. It probably works with older versions of mercurial. Please report a
bug on http://labs.freehackers.org/projects/hgactivity/issues/new if you
have any issue.

You need to have matplotlib installed, check your distribution tools and
documentation to have it installed.

COMPILATION / INSTALLATION
--------------------------

You need to extract the source somewhere (in my setup i use
~/hg/hgactivity/) and to tell mercurial about it, by adding a line like
this one to ~/.hgrc:

    activity=/home/orzel/hg/hgactivity/activity.py

(use your actual path to the file, of course)

More information on the wiki
http://labs.freehackers.org/projects/hgactivity/wiki
and the documentation page
http://labs.freehackers.org/projects/hgactivity/wiki/documentation


enjoy,
Thomas Capricelli <orzel@freehackers.org>

