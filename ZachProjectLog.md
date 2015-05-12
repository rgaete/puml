# Zach's  Project Log #


## Monday 5/7/2012 ##
  * Made Gource video up to date to everything as of 6 pm today.

## Saturday 3/24/2012 ##
  * Fixed Collaboration Self Connectors.  They are now the only ones to connect to a single object.

## Tuesday 3/20/2012 ##
  * Finished Collaboration Self Connectors

## Wednesday, Thursday 3/14/2012, 3/15/2012 ##
  * Updated Collaboration Diagram Connectors, self connector mostly works, they still need a second object in order to be drawn so far though.

## Thursday 3/8/2012 ##
  * Updated Collaboration Diagram objects, but was getting undefined reference error.  Makefile is not including UMLnodes\_collab.cpp


## Monday 3/5/2012 ##
  * Uploaded my pair programming paragraph's onto the hw file.
  * Changed the default size of the gource video so that it would default to 720p.

## Sunday 3/4/2012 ##
  * Got Gource file rendered and converted to wmv format.  Still working on getting it down to 8 minutes.
  * Got Gource down to 8 minutes (7:55 ish) and added some background music, it should be fairly quiet.  There is something for right before David's push on Feb 1.
  * Uploaded video to the repository.

## Saturday 3/3/2012 ##
  * Tried to render Gource file.  Took 3 hours to do and more HDD space than my computer had.  Switching to something less than 1920x1080.
    * Let's just say that a 150+ GB file was only 3/4 of the repository up 'till now.

## Tuesday 2/21/2012 ##
  * Fixed issues with the uploading of icons. Got the dialog working correctly.
  * Note: addremove, commit, push

## Monday 2/20/2012 ##
  * Managed to get values sent to parent objects, this allows the dialog to close instead of just the page.
  * Updated icons
  * Spent some time trying to get Gource to work in (order to get a higher quality video).  Little success.  It outputs to it's own file type but converting that on linux is rather difficult.

## Sunday 2/19/2012 ##
  * Continued work on the new dialog.
  * Fixed random runtime issue, there was a lot of cleaning and recompiling to do to get it to work.
  * As a result, the open section works "correctly" now.

## Tuesday 2/14/2012 ##
  * Started work on the new dialog.  It doesn't close correctly yet....



## Tuesday 2/7/2012 ##
  * Added red gloves to stickman.  Still kinda sloppy, may work on adjusting values later.
  * Stickman now moves with every redraw. ie every other stickman is punching
  * Issue, apparently making time variables somehow screws with a random other variable I made.
  * Issue solved by putting double conditional at beginning of function.// if a {if b{do something}}
  * Managed to get the time stamps working for the stickman animation.  Still need to figure out how to update every second.  Mostly just there where do I put things.