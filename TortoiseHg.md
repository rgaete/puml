<h2> Setup </h2>
You can download TortoiseHg from http://tortoisehg.bitbucket.org/download/index.html. Once you have it downloaded and installed, do the following:

  * Create a folder on your computer(mines named puml) and this folder will become your local copy of the repository.
  * Open TortoiseHg Workbench
  * In Workbench, go File > Clone Repository
  * Now go to http://puml.net and click on the Source Tab
    * You should see an hg command in a blue box (hg clone).
    * Copy only the url part of the command
  * Go back to Workbench
    * Paste the url into the "Source:" section
    * Browse for the folder you created earlier and put that in the "Destination:" section
    * Press the Clone button (it should start downloading all the files from the repository)
      * If you get an error check to make sure you copied the url correctly? (if you aren't logged in, it wont have the right url)
      * for example the url from the hg clone command should look like https://yourusername@code.google.com/p/puml/

You should now have a local copy of the repository and can browse through and open/edit everything locally.

<h2> Using Tortoise </h2>
If you want to add a new file to the repository:
  * Place the file into your local repository folder
  * Right click on the file and go TortoiseHg > Add Files.

To push your local repository to the real one:
  * Right click on the repository folder(in my case puml) and click on Hg Commit
  * Then right click on the folder again and go TortoiseHg > Synchronize (this should pop up a GUI)
  * At the top of this window click the Pull (to make sure you have most up to date version of the repository)
  * Then click the Push button (The changes you made should now be uploaded to the repository)

If you get any errors while trying to push it means you probably need to merge or update your repository