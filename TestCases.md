
---

## Stickman-o-genesis ##
This tests the basic creation and selection of objects.
Test case author: Logan
History of test:
  1. Zach 2/02/12
    * Changeset: 145
    * Pass
    * The toolbar doesn't work. Options needed to be selected from pull-down menu.
#### Location ####
  * Executable is at: puml/src/pUMLTest2
  * Prerequisite: Run `cd puml/ ; make` to make the executable.

#### Test steps ####
  * Input
    1. Create stickman1
    1. Create stickman2
    1. Select stickman1
    1. Move stickman1
    1. Change tabs
    1. Return to first tab
    1. Both stickmen should still be in the first tab

#### Log ####
  * The log will be a signed test log from a tester
  * Questions for tester to answer:
    1. Could you create both stickmen?
    1. Could you move stickman1?
    1. Could you change tabs?
    1. Did both stickmen reappear in the first tab?
    1. Did you notice anything strange?

#### Priority ####
  * Low. This is the basic test that we always perform to make sure the code still works. We only need to formally execute the test before major testing milestones.