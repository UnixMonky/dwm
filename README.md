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
- Per Tag Layouts
  - https://dwm.suckless.org/patches/pertag/
- Colored Status Text
  - https://dwm.suckless.org/patches/statuscolors/
- Fancy Bar
  - https://dwm.suckless.org/patches/fancybar/


## Keyboard Customizations
Meta Key (⊞) is reset to the Windows key

Added Volume Up/Down/Mute functions mapped to volume keys

Function | Keybinding
------------ | -------------
dmenu | [⊞]+[Space]
Menu Bar Toggle | [⊞]+[b]
Terminal | [⊞]+[t]
Surf web browser | [⊞]+[w]
Next Window | [ALT]+[Tab]
Previous Window | [ALT]+[SHIFT]+[TAB]
Add to Master  | [⊞]+[=]
Remove from Master | [⊞]+[-]
Widen client | [⊞]+[ALT]+[=]
Narrow client | [⊞]+[ALT]+[-]
Zoom to Master | [⊞]+[Enter]
Rotate Clients | [⊞]+[[]
Rotate Clients | [⊞]+[]]
View Previous Tag | [⊞]+[Tab]
Kill Client | [ALT]+[F4]
Layout: Tiled | [⊞]+[ALT]+[t]
Layout: Floating | [⊞]+[ALT]+[f]
Layout: Monocle | [⊞]+[ALT]+[m]
Layout: Centered Master | [⊞]+[ALT]+[u]
Layout: Centered Floating Master | [⊞]+[ALT]+[o]
Layout: Grid | [⊞]+[ALT]+[g]
Cycle through Layouts | [⊞]+[ALT]+[]]
Cycle through Layouts | [⊞]+[ALT]+[[]
Toggle Last Layout | [⊞]+[ALT]+[0]
Float Window | [⊞]+[\]
Apply Tag 1..9 | [⊞]+[ALT]+[1..9]
Apply All Tags | [⊞]+[ALT]+[0]
Show Tag 1..9 | [⊞]+[1..9]
Show All Tags | [⊞]+[0]
Focus to next Display | [⊞]+[.]
Focus to previous Display | [⊞]+[,]
Move client to next Display | [⊞]+[➡]
Move Client to previous Display | [⊞]+[⬅]
Lock Screen | [⊞]+[l]
Quit dwm | [CRTL]+[ALT]+[DEL]

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


