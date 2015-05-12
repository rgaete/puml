# hg command line guide #
**This is a tutorial to get started with using the command line utility hg to commit to the pUML project.**

An alternative to using the command line is to use TortoiseHg.

## Setting up the repo ##
  1. Download hg
    * sudo apt-get install mercurial
  1. Created the ~/.hgrc file.
    * touch ~/.hgrc
  1. Edit the ~/.hgrc file using your favorite text editor.
```
[ui]
username = User Name <username@email.com>
```
  1. Clone the puml repository. To find the proper command, do:
    * Log into your googlecode account
    * Click Source tab (the fifth one)
    * Copy the command to your clipboard. It should read something like:
      * hg clone https://username@code.google.com/p/puml/
    * Copy this command into your terminal.
      * Note: you can pick a name other than "puml" by instead entering
        * hg clone https://username@code.google.com/p/puml/ different\_folder\_name
  1. To enable modification to the central repository, you need do something with your password. There are two methods you can use.
    1. Go to the Profile (very top right of the googlecode page) tab, Click the settings tab, and then select the checkbox in the security area.
    1. Alternatively, in the Profile -> Setting -> GoogleCode.com password field, there is a randomly generated password.
      * Copy this RANDOM\_PASSWORD to your clipboard.
      * Open the file puml/.hg/hgrc in a text editor.
      * Modify this file so that it reads like this:
```
[paths]
default = https://username:RANDOM_PASSWORD@code.google.com/p/puml/
```
  1. You can now work with the repository.
  1. ???
  1. Profit!

## Wiki repo ##
There is a repo for the wiki. From here you can easily modify the names of all the pages, see the changelog for the wiki pages, and generally do anything you can normally do with a repository. To clone this repo, use the following command:
  * hg clone https://username@wiki.puml.googlecode.com/hg optional\_folder\_rename --insecure


## Common commands ##
  * To pull the central repo's current state, use:
    * hg pull
  * Once you've pulled down the changes, you can update your local repo to reflect the 'tip' of the remote repo:
    * hg update
  * Once you have added or removed files from your repo, you can start tracking them with the command:
    * hg addremove
  * You can commit a changeset by using the command:
    * hg com -m "My commit message."
    * Note: If you leave off the -m "message" portion, you will be prompted to enter a message with some text editor.
  * While you are working on a local copy of the repo, you can see what changes others have made to the remote repo with the command:
    * hg incoming
  * Push the changes back to the remote repo with the command:
    * hg push
  * Frequently, someone will have modified the files and committed their change while you were working. Frequently, this will fix the issue:
    * hg merge
    * Occasionally, you will need to use the following to make an explicit merge:
      * hg merge -r REV
      * REV is the number of a revision you want to merge into the current version of the repo.
  * You can get some basic information (such as date, commit message, rev number) with the command:
    * hg log | less
  * Read up on [this](http://mercurial.selenic.com/wiki/NamedBranches) page if you want to make a named branch.