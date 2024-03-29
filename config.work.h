/* See LICENSE file for copyright and license details. */

/* includes */
#include <X11/XF86keysym.h>
#include "selfrestart.c"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[]          = {
	"MesloLGSDZ Nerd Font:pixelsize=14",
};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";

// Solarized
static const char sol_blue[]        = "#002B36";
static const char sol_grey[]        = "#657b83";
static const char sol_ltgrey[]      = "#93a1a1";

// Dracula color theme
static const char drac_bg[]         = "#282a36";
static const char drac_fg[]         = "#f8f8f2";
static const char crac_currline[]   = "#44475a";
static const char drac_select[]     = "#44475a";
static const char drac_comment[]    = "#6272a4";
static const char drac_cyan[]       = "#8be9fd";
static const char drac_green[]      = "#50fa7b";
static const char drac_orange[]     = "#ffb86c";
static const char drac_pink[]       = "#ff79c6";
static const char drac_purple[]     = "#bd93f9";
static const char drac_red[]        = "#ff5555";
static const char drac_yellow[]     = "#f1fa8c";

// custom
static const char cst_purple[]      = "#360168";
static const char cst_pink[]        = "#690167";
static const char cst_green[]       = "#336901";
static const char col_mySel[]       = "#8b3e2f";

static const char *colors[][3]      = {
	/*					fg         bg          border   */
	// [SchemeNorm] =	 { col_gray3, col_gray1,  col_gray2 },
	// [SchemeSel]  =	 { col_gray4, col_cyan,   col_cyan },
	// Solarized
	// [SchemeNorm] =	 { sol_grey, sol_blue,    sol_blue   },
	// [SchemeSel]  =	 { sol_blue, sol_ltgrey,  sol_ltgrey },
	// Custom
	// [SchemeNorm] =	 { col_gray3,  col_gray1, col_black },
	// [SchemeSel]  =	 { col_yellow, col_mySel,   col_cyan   },
	// // other
	// [SchemeWarn] =	 { col_black, col_yellow, col_red    },
	// [SchemeUrgent]=	 { col_white, col_red,    col_red    },

  // Dracula theming
	[SchemeNorm] =	 { drac_fg, drac_bg, drac_bg },
	[SchemeSel]  =	 { drac_orange, drac_select,  drac_select },
	[SchemeWarn] =	 { drac_bg, drac_yellow, drac_yellow },
	[SchemeUrgent]=	 { drac_bg, drac_red, drac_red },

};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	// Display 1, tag 1 - Mail/Calendar
	// { "Mailspring",       NULL,       NULL,       1 << 0,       0,            0 },
	{ "Chromium",         "crx_pkooggnaalmfkidjmlhoelhdllpphaga",       NULL,      1 << 0,       0,            0 },
	{ "Thunderbird",      NULL,       NULL,       1 << 0,       0,            0 },
	// { "MineTime",         NULL,       NULL,       1 << 0,       0,            0 },
	// Display 1, tag 2 - Messaging clients
	{ "Hamster",          NULL,       NULL,       1 << 1,       0,            0 },
	{ "teams-for-linux",  NULL,       NULL,       1 << 1,       0,            0 },
	{ "Microsoft Teams - Preview", NULL, NULL,    1 << 1,       0,            0 },
	{ "Microsoft Teams - Preview", NULL, "Microsoft Teams Notification", ~0, 1, -1 },
	// { "Skype",            NULL,       NULL,       1 << 1,       0,            0 },
	{ "Slack",            NULL,       NULL,       1 << 1,       0,            0 },
	{ "discord",          NULL,       NULL,       1 << 1,       0,            0 },
	{ "Franz",            NULL,       NULL,       1 << 1,       0,            0 },
	// { "Surf ",            NULL,       "- Chat",   1 << 1,       0,            0 },
	// { "Ao ",              NULL,       NULL,       1 << 1,       0,            0 },
	// Display 1, tag 3 - Notes
	{ "Cherrytree",       NULL,       NULL,       1 << 2,       0,            0 },
	// Display 1, tag 4 - Jiras
	// { "tabbed",           NULL,       NULL,       1 << 3,       0,            0 },
	// Any display, tag 9
	{ "firefox",          NULL,       NULL,       1 << 8,       0,           -1 },
	// Any display, force floating
	{ "KeePass2",         NULL,       NULL,       0,            1,           -1 },
	{ "KeePassXC",        NULL,       NULL,       0,            1,           -1 },
	{ "Chatty",           NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* first entry is default */
	/* symbol     arrange function */
	{ "[]=",      tile }, 
	{ "|M|",      centeredmaster },          
	{ "><>",      NULL },                    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ ">M>",      centeredfloatingmaster },
	{ "[⊞]",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask  // Windows key for meta
#define AltMask Mod1Mask  // Alt key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                KEY,      view,           {.ui = 1 << TAG} }, \
	{ ControlMask|ShiftMask, KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|AltMask,        KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ControlMask|AltMask,   KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "st", NULL };
// static const char *slockcmd[]  = { "slock", NULL };
// static const char *surfcmd[]  = { "tabbed", "surf", "-pe", NULL };
// static const char *keepasscmd[] = { "keepass", NULL };
// static const char *keepassxccmd[] = { "keepassxc", NULL };
// static const char *keepassautotypecmd[] = { "keepass", "--auto-type", NULL };
// static const char *suspendcmd[] = { "systemctl", "suspend", NULL };
// static const char *vifmcmd[] = { "st", "vifm", NULL };
// static const char *thunarcmd[] = { "thunar", NULL };
// static const char *nemocmd[] = { "GTK_THEME=Dracula", "nemo", NULL };
// static const char *nemocmd[] = { "nemo", NULL };
// static const char *nnncmd[] = { "st", "-f", "'MesloLGSDZ Nerd Font:pixelsize=18'", "-e", "nnn", NULL };
// static const char *screenshotcmd[] = { "scrot", "--select", "/home/matt/Pictures/Screenshots/screenshot_%Y-%m-%d_%H-%M-%S.png", NULL };
// static const char *screenshotfocusedcmd[] = { "scrot", "--focused", "/home/matt/Pictures/Screenshots/screenshot_%Y-%m-%d_%H-%M-%S.png", NULL };
// static const char *screenshotfullcmd[] = { "scrot", "--multidisp", "~/Pictures/Screenshots/screenshot_%Y-%m-%d_%H-%M-%S.png", NULL };
// Media player controls by playerctl command (https://github.com/acrisci/playerctl)
// static const char *mediaplaycmd[] = { "playerctl", "play-pause", NULL };
// static const char *mediastopcmd[] = { "playerctl", "stop", NULL };
// static const char *medianextcmd[] = { "playerctl", "next", NULL };
// static const char *mediaprevcmd[] = { "playerctl", "previous", NULL };
// volume media keys
// static const char *volupcmd[]  = { "pactl", "set-sink-volume", "0", "+5%", NULL };
// static const char *voldowncmd[]  = { "pactl", "set-sink-volume", "0", "-5%", NULL };
// static const char *volmutecmd[]  = { "pactl", "set-sink-mute", "0", "toggle", NULL };
// backlight brightness keys
// static const char *brightnessupcmd[]  = { "xbacklight", "+5", NULL };
// static const char *brightnessdowncmd[]  = { "xbacklight", "-5", NULL };
// custom scripts for various things
// static const char *btheadset[] = { "/home/matt/scripts/bt.sh", "flip", NULL};
// static const char *screenchange[] = { "autorandr", "--change", NULL};
// static const char *screendocked[] = { "autorandr", "--load", "docked", "--force", NULL};
// static const char *screenmobile[] = { "autorandr", "--load", "mobile", "--force", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	// { ControlMask,                  XK_space,  spawn,          {.v = dmenucmd } },
	// { MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_bracketleft,  rotatestack, {.i = -1 } },
	{ MODKEY,                       XK_bracketright, rotatestack, {.i = +1 } },
	{ Mod1Mask,                     XK_Tab,    focusstack,     {.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY|AltMask,               XK_minus,  setmfact,       {.f = -0.05} },
	{ MODKEY|AltMask,               XK_equal,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|AltMask,               XK_o,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|AltMask,               XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|AltMask,               XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|AltMask,               XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|AltMask,               XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|AltMask,               XK_g,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|AltMask,		            XK_bracketleft, cyclelayout, {.i = -1 } },
	{ MODKEY|AltMask,               XK_bracketright, cyclelayout, {.i = +1 } },
	{ MODKEY|AltMask,               XK_0,      setlayout,      {0} },
	{ MODKEY,                       XK_backslash, togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|AltMask,               XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
 	TAGKEYS(                        XK_9,                      8)
	/* Media and special Keyboard Keys */
	// { 0,              XF86XK_AudioRaiseVolume,    spawn,          {.v = volupcmd } },
	// { 0,              XF86XK_AudioLowerVolume,    spawn,          {.v = voldowncmd } },
	// { 0,              XF86XK_AudioMute,           spawn,          {.v = volmutecmd } },
	// { 0,              XF86XK_AudioPlay,           spawn,          {.v = mediaplaycmd } },
	// { 0,              XF86XK_AudioPause,          spawn,          {.v = mediaplaycmd } },
	// { 0,              XF86XK_AudioStop,           spawn,          {.v = mediastopcmd } },
	// { 0,              XF86XK_AudioNext,           spawn,          {.v = medianextcmd } },
	// { 0,              XF86XK_AudioPrev,           spawn,          {.v = mediaprevcmd } },
	// { 0,              XF86XK_MonBrightnessUp,     spawn,          {.v = brightnessupcmd } },
	// { 0,              XF86XK_MonBrightnessDown,   spawn,          {.v = brightnessdowncmd } },
	// { 0,              XF86XK_Tools,            spawn,          {.v = btheadset } },
	/* Custom Commands */
	// { MODKEY,                       XK_l,      spawn,          {.v = slockcmd } },
	// { MODKEY,                       XK_w,      spawn,          {.v = surfcmd } },
	// { AltMask|ControlMask,          XK_k,      spawn,          {.v = keepassxccmd } },
	// { AltMask|ControlMask,          XK_a,      spawn,          {.v = keepassautotypecmd } },
	{ AltMask,                      XK_F4,     killclient,     {0} }, /* exit client */
	{ AltMask|ControlMask,          XK_Delete, quit,           {0} }, /* quit dwm */
	{ AltMask|ControlMask,          XK_R,      self_restart,   {0} }, /* restart dwm */
	// { MODKEY,                       XK_e,      spawn,          {.v = nemocmd } },
	// { 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },
	// { ControlMask,                  XK_Print,  spawn,          {.v = screenshotfocusedcmd } },
	// { ShiftMask|ControlMask,        XK_Print,  spawn,          {.v = screenshotfullcmd } },
	// { AltMask|ControlMask,          XK_Insert, spawn,          {.v = screenchange } }, /* autorandr reset */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	// { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

