# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# don't put duplicate lines in the history. See bash(1) for more options
# ... or force ignoredups and ignorespace
HISTCONTROL=ignoredups:ignorespace

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
#if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
#    . /etc/bash_completion
#fi

export LANG=ko_KR.UTF-8

export HOME=/root
export BASICAPP=${HOME}/basicapp

export PATH="$PATH:/root/depot_tools"
export PATH="$PATH:/usr/local/go/bin"
export PATH="$PATH:${HOME}/go/bin"

LS_COLORS='rs=0:di=1;35:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31:*.taz=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lz=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.axv=01;35:*.anx=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.axa=00;36:*.oga=00;36:*.spx=00;36:*.xspf=00;36:';
export LS_COLORS

#PS1='\e[37;1m\u@\e[35m\W\e[0m\$ ' # this will change your prompt format
PS1='\[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;35m\]\w\[\033[00m\]\$'

alias memtest='valgrind --leak-check=full --log-file=memcheck.txt -v --error-limit=no'

alias basic='cd ${BASICAPP}'
alias bm='sudo make -C ${BASICAPP}/'
alias clean0='sudo make clean-all -C ~/tos_build/binary_debug/'
alias clean1='sudo rm -rf /system /tos /rsmdata /windata'
alias build0='sudo apt-get update'
alias build1='cd ~/trunk/pkg/'
alias build2='sudo ./install_linux_pkg.sh -a -d'
alias build3='cd ~/trunk/build/'
alias build4='sudo ./init_debug.sh'
alias build5='sudo make install -j7 -C ~/tos_build/binary_debug/'
alias build6='sudo make install -j7 -C ~/tos_build/binary_debug/src/core/'
alias build7='sudo make install -j7 -C ~/tos_build/binary_debug/'

alias pm='${BASICAPP}/config_basicapp.py -cM'
alias pppm='cd ~/basicapp; ./config_basicapp.py -cM; cd ${OLDPWD}'
alias sm='cd ${BASICAPP}/src/tmemo'
alias sm_exe='${BASICAPP}/out/tmemo.tap/bin/tmemo'
alias esm='${BASICAPP}/out/tmemo.tap/bin/tmemo'
alias gsm='gdb ${BASICAPP}/out/tmemo.tap/bin/tmemo'
alias memo='vim ~/.config/tmemo_Preference'

alias cd='cd'
alias cdt='cd ~/trunk/'
alias cdb='cd ~/browser/src'
alias cdn='cd /zone/normal/rootfs/tos/users'
alias twk='cd ~/trunk/src/lib/twk'
alias taf='cd ~/trunk/src/lib/taf'
alias mk='make install -j7'
alias mk2='sudo cmake --build . --target install -- -j'
alias pkg='sudo ~/trunk/pkg/install_linux_pkg.sh -a'
alias ib='sudo ~/trunk/build/init_debug.sh'
alias tbb='cd ~/tos_build/binary_debug/'
alias tb='sudo make install -j -C ~/tos_build/binary_debug/'
alias tbr='sudo make install -j7 -C ~/tos_build/binary_release/'
alias lxc='lxc-attach -n normal'
alias ci1='ssh gitlab-runner@192.168.11.92 -p 12368'
alias ci2='ssh gitlab-runner@192.168.11.92 -p 12369'
alias TGDB='cd /zone/normal/rootfs/tos/users/AllUsers/ToGate/out/Debug && gdb --args ./ToGate'
alias GDBS='gdb --args /zone/normal/rootfs/tos/users/AllUsers/ToGate/out/Debug/ToGate --user-data-dir=/zo
ne/normal/rootfs/tos/users/sangseok/UserData'
alias zone='cd /zone/normal/rootfs/home/AllUsers/AppList'

alias tgconfig='~/browser/src/config_togate.py -cm'
alias tg='cd ~/browser/src'
alias tgb='cd ~/browser/src/togate/browser/ui'
alias tgu='cd ~/browser/src/togate_ui'
alias tg_exe='~/browser/out/Debug/ToGate'
alias gtg='gdb --args ~/browser/out/Debug/ToGate'

alias chconfig='~/togate-version-up/src/config_chrome.py -cm'
alias ch='cd ~/togate-version-up/src'
alias chb='cd ~/togate-version-up/src/chrome/browser/ui'
alias chu='cd ~/togate-version-up/src/ui/'
alias ch_exe='~/togate-version-up/out/Debug/chrome --no-sandbox --disable-features=VizDisplayCompositor'
alias gch='gdb --args ~/togate-version-up/out/Debug/chrome --no-sandbox --disable-features=VizDisplayCompositor'
alias res='cd ~/togate-version-up/src/chrome/browser/resources'
alias ui='cd ~/togate-version-up/src/ui/webui/resources'
alias html_exe='~/togate-version-up/out/Debug/chrome --no-sandbox --disable-features=VizDisplayCompositor --args ~/togate-version-up/src/chrome/browser/resources/md_history/history.html'

alias memcheck='sudo valgrind --log-file=output.valgrind --leak-check=yes'
alias membug='sudo valgrind --log-file=output.valgrind --track-origins=yes'
alias memcal='sudo valgrind --tool=callgrind'
alias memmass='sudo valgrind --tool=massif'

alias blog="git log --author='baekkie_song@tmax.co.kr'"
alias blog2='blog -10 --pretty=format:"===START===   %h,   %ad,   %s"'
alias blog3='blog -30 --pretty=format:"===START===   %h,   %ad,   %s"'
alias blog4='blog -100 --pretty=format:"===START===   %h,   %ad,   %s"'
alias log20='git log --pretty=format:"%s"'
alias mtnef="sudo make all -C ~/CPPCODE/"
alias gtnef="gdb --args ~/CPPCODE/tneflib"

alias cal_heap='LD_PRELOAD=/usr/local/lib/libtcmalloc.so HEAPPROFILE=/tmp/profile/calculator /system/app/
calculator.tap/bin/calculator'
alias cal='cd ${BASICAPP}/src/calculator/'
alias gcal='gdb --args /system/app/calculator.tap/bin/calculator'
alias cal_exe='/system/app/calculator.tap/bin/calculator'
alias mcal='sudo make install -j7 -C ~/tos_build/binary_debug/src/app/basic/calculator/'
alias rcal='sudo make install -j7 -C ~/tos_build/binary_release/src/app/basic/calculator/'
alias j7='sudo make install -j7'
alias t='tmux new'

alias te='cd ${BASICAPP}/src/texteditor/src'
alias te_exe='/system/app/texteditor.tap/bin/texteditor'
alias mte='sudo make install -j7 -C ~/tos_build/binary_debug/src/app/basic/texteditor'
alias rte='sudo make install -j7 -C ~/tos_build/binary_release/src/app/basic/texteditor'
alias gte='gdb --args /system/app/texteditor.tap/bin/texteditor'

alias cap_heap='LD_PRELOAD=/usr/local/lib/libtcmalloc.so HEAPPROFILE=/tmp/profile/capturetool /system/app
/capturetool.tap/bin/capturetool'
alias cap='cd ${BASICAPP}/src/capturetool'
alias cap_exe='/system/app/capturetool.tap/bin/capturetool'
alias mcap='sudo make install -j7 -C ~/tos_build/binary_debug/src/app/basic/capturetool'
alias rcap='sudo make install -j7 -C ~/tos_build/binary_release/src/app/basic/capturetool'
alias gcap='gdb --args /system/app/capturetool.tap/bin/capturetool'

alias iv='cd ${BASICAPP}/src/imageviewer'
alias iv_exe='/system/app/imageviewer.tap/bin/imageviewer'
alias miv='sudo make install -j7 -C ~/tos_build/binary_debug/src/app/basic/imageviewer'
alias giv='gdb --args /system/app/imageviewer.tap/bin/imageviewer'

alias bs='source ~/.bashrc'
alias bashrc='vim ~/.bashrc'

export PATH="$PATH:/root/trunk/src/webview/depot_tools"
export PATH="$PATH:/root/test_newgate/depot_tools"
#export GOOGLE_API_KEY="AIzaSyAA6TqfS29Rz-WoayYDX8uPTT7om4nNX-4"
#export GOOGLE_DEFAULT_CLIENT_ID="16046116174-koavd8rk45of5spi7igfel9sfgn2jgfk.apps.googleusercontent.com"
#export GOOGLE_DEFAULT_CLIENT_SECRET="UEe2AnzgiO9j1e6vIXxvhI70"
alias swapon="swapon -a"
alias swapoff="swapoff -a"
alias kzombie="ps -ef | grep defunct | awk '{print $3}' | xargs kill -9"

export CPUPROFILE_FREQUENCY=1000
export LD_LIBRARY_PATH="$HOME/googletest-release-1.8.1"

