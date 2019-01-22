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
- AutoStart
  - https://dwm.suckless.org/patches/autostart/
- Cycle Layouts
  - https://dwm.suckless.org/patches/cyclelayout/


## Keyboard Customizations
Meta Key (⊞) is reset to the Windows key

Function | Keybinding
------------ | -------------
dmenu | [Space]
Menu Bar Toggle | b
Terminal | t
Next Window | [
Previous Window | ]
Add to Master  | =
Remove from Master | -
Widen client | [CTRL]+=
Narrow client | [CTRL]+-
Zoom to Master | [Enter]
View Previous Tag | [Tab]
Kill Client | [CRTL]+c
Layout: Tiled | [ALT]+t
Layout: Floating | [ALT]+f
Layout: Monocle | [ALT]+m
Layout: Centered Master | [ALT]+u
Layout: Centered Floating Master | [ALT]+o
Cycle through Layouts | [ALT]++
Cycle through Layouts | [ALT]+-
Toggle Last Layout | [ALT]+0
Float Window | [ALT]+[-]
Apply Tag 1..9 | [CRTL]+[F1..F9]
Apply All Tags | [F11]
Show Tag 1..9 | [F1..F9]
Show All Tags | [F12]
Focus to next Display | .
Focus to previous Display | ,
Move client to next Display | ➡
Move Client to previous Display | ⬅
Quit dwm | [CRTL]+q

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


