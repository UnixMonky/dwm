# dwm
dynamic window manager (by suckless) [customized]


My patching strategy:
* master branch is pulled and in sync with suckless upstream
* live is my normal current running version
* stage is the testing version

to apply a new patch:
- checkout master
- branch master to newpatch
- apply patch to newpatch name
- commit and push, resolving any conflicts
- checkout stage
- merge newpatch, resolving any conflicts
- push netpatch
- test stage branch for functionality
- merge stage into live
- test live
