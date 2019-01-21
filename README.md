# dwm
dynamic window manager (by suckless) [customized]
Original: https://dwm.suckless.org/

## Patches/Customizations in use
- Active Tag Indicator Bar
  - https://dwm.suckless.org/patches/activetagindicatorbar/
- systray
  - https://dwm.suckless.org/patches/systray/
- Centered Master
  - https://dwm.suckless.org/patches/centeredmaster/

## Keyboard Customizations
Meta Key (⊞) is reset to the Windows key

Function | Keybinding
------------ | -------------
dmenu | ⊞+<Space>
Menu Bar Toggle | ⊞+b
Terminal | ⊞+t
Next Window | ⊞+j
Previous Window | ⊞+k
Add to Master  | ⊞+i
Remove from Master | ⊞+d
Zoom to Master | ⊞+<Enter>
_view | ⊞+<Tab>
Kill Client | ⬆+⊞+c
Layout: Tiled | ⬆+⊞+t
Layout: Floating | ⬆+⊞+f
Layout: Monocle | ⬆+⊞+m
Layout: Centered Master | ⬆+⊞+u
Layout: Centered Floating Master | ⬆+⊞+o
Cycle Layout | ⊞+<=>
Float Window | ⬆+⊞+<->
Apply Tag 1..9 | ⬆+⊞+[1..9]
Apply All Tags | ⬆+⊞+0
Show Tag 1..9 | ⊞+[1..9]
Show All Tags | ⊞+0
_focusmon+ | ⊞+.
_focusmon- | ⊞+,
_tagmon+ | ⬆+⊞+.
_tagmon- | ⬆+⊞+,
Quit dwm | ⬆+⊞+q

## Patching process
My patching strategy:
    master branch is pulled and in sync with suckless upstream
    live is my normal current running version
    dev is the testing version

to apply a new patch:
    checkout master
    branch master to newpatch
    apply patch to newpatch name
    commit and push, resolving any conflicts
    checkout stage
    merge newpatch, resolving any conflicts
    push netpatch
    test stage branch for functionality
    merge stage into live
    test live


