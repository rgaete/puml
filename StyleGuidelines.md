# Introduction #

This project adheres to the Google C++ style guideline found [here](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml).

## cpplint.py setup ##
In order to make adhering to the style easier, Google has provided a python script, cpplint.py. These instructions outline how I am using this script.

  * Place cpplint.py in a standardized location.
    * `cp puml/doc/cpplint.py ~/Programming/misc`
  * Create a new alias. I added this line to my ~/.bashrc file.
    * alias CPPLINT="python ~/Programming/misc/cpplint.py"
  * Make sure that the shell session is using the updated settings.
    * `source ~/.bashrc`
  * Profit!
    * 
```
cd ~/Programming/puml/src
CPPLINT nodes.cpp
```

## vim settings ##
The Google style guidelines have decreed that tabs be 2 spaces. Here are some tips to use with the vim editor. Note that all of these tips can be placed in the ~/.vimrc file so that they never have to be typed in again. Alternatively, they can be typed in a vim session (just preface the commands with the ":" character).

  * Set the tabwidth to 2 spaces
    * set softtabstop=2
  * The shift-> and shift-< commands use a separate setting
    * set shiftwidth=2
  * Make sure that tabs are expanded into spaces!
    * set et
    * Alternatively: set expandtab
  * It is often helpful to be able to see trailing whitespace. Use both of these commands
    * set list
    * set listchars=tab:\|