syntax on
filetype on     "파일의 종류를 자동으로 인식
"filetype indent on "파일 종류에 따른 구문강조
"colorscheme torte
"colorscheme evening
"colorscheme desert
"set fencs=ucs-bom,utf-8,euc-kr,latin1
"set shiftwidth=2  "들여쓰기를 2칸으로 설정
"set tabstop=2     "tap 간격을 2칸으로 설정
"set sts=2         "tap 간격을 space로 변경
"set laststatus=2  "상태정보 라인 2줄
"set statusline=%h%F%m%r%=[%l:%c(%p%%)]   "상태정보라인 구성
"set backspace=eol, start, indent      "줄의 끝, 시작, 들여쓰기에서 백스페이스시 이전줄로
"set showcmd          " Show (partial) command in status line.
"set smartcase          " Do smart case matching
"set autowrite          " Automatically save before commands like :next and :make
"set hidden             " Hide buffers when they are abandoned
"set mouse=a          " Enable mouse usage (all modes)
set autoindent "자동 들여쓰기
set cindent "C프로그래밍용 자동 들여쓰기
"set smartindent "스마트한 들여쓰기
"set ruler "화면 우측하단에 현재 커서의 위치(줄,칸) 표시
"set number "행번호 표시, set nu도 가능
"set showmatch "가로닫기 괄호를 사용할 때 일치하는 가로 열기 괄호를 보여줌
"set hlsearch "검색어 강조, set hls도 가능
"set incsearch "검색어 입력하면서 결과도 보여줌
"set ignorecase "검색시 대/소문자 무시
"set nowrap "자동 줄바꿈기능 사용하지 않음
"set nocompatible "오리지날 vi와 호환하지 않음
"set nowrapscan "검색할 때 문서의 끝에서 처음으로 안돌아감
"set nobackup "백업파일 안만듬
"set history=1000 "vi 편집기록 기억갯수. viminfo에 기록
"-----------------------------"
" Common Configuration
"-----------------------------"
set ts=2 sw=2
set ci si ai
set nu ruler title
set sm
set wmnu
set expandtab
set hls ic incsearch
set encoding=utf-8
set fileencoding=utf-8
"set fdm=indent
"set fdl=1
set history=2000
set nowrapscan
set mouse=a
colorscheme koehler
"colorscheme neverland-darker

":e는 그냥 파일전환
"ctrl + w + f : 특정 파일 경로 찾아가서 열어서 split으로 보여주기
nnoremap <S-M> :e %:p:s,.h$,.X123X,:s,.cpp$,.h,:s,.X123X$,.cpp,<CR>
nnoremap <S-Z> :vs %<.h<CR>
nnoremap <S-X> :vs %<.cc<CR>

nmap <F2> <C-W>gf
nmap <F3> <C-W>T
nmap <F4> :tabclose<CR> gT
nmap <F5> gT
nmap <F6> gt
set path=.,,**
set path+=.,,;
set path+=/system/include,,
set path+=/usr/include,,

"-----------------------------"
" Macro Configuration
"-----------------------------"
let @q=':q!'
let @w=':w'

"-----------------------------"
" cscope Configuration
"-----------------------------"
set tags=./tags,tags
set csprg=/usr/local/bin/cscope
set csto=0
"set viminfo=
set cst
set nocsverb
cscope add /home/seok/trunk/src/cscope.out /home/seok/trunk/src
cscope add /home/seok/browser/src/cscope.out /home/seok/browser/src
cscope add ./cscope.out
"set viminfo=
"-----------------------------"
" Tag List Configuration
"-----------------------------"
nmap <F7> :TlistToggle<CR>
let Tlist_Use_Right_Window = 1
let Tlist_Ctags_Cmd="/usr/local/bin/exctags"
let Tlist_Inc_Winwidth=0
let Tlist_Exit_OnlyWindow=0
let Tlist_Auto_Open=0
let Tlist_Use_Right_Window=1

"-----------------------------"
" Source Explorer Configuration
"-----------------------------"
nmap <F8> :SrcExplToggle<CR>
nmap <C-H> <C-W>h
nmap <C-J> <C-W>j
nmap <C-K> <C-W>k
nmap <C-L> <C-W>l
let g:SrcExpl_winHeight = 10
let g:SrcExpl_refreshTime = 100
let g:SrcExpl_jumpKey = "<ENTER>"
let g:SrcExpl_gobackKey = "<SPACE>"
let g:SrcExpl_pluginList = [
         \ "__Tag_List__",
         \ "_NERD_tree_",
         \ "Source_Explorer"
         \ ]
let g:SrcExpl_isUpdateTags = 0

"-----------------------------"
" NERDTree Configuration
"-----------------------------"
let NERDTreeWinPos="left"
nmap <F9> :NERDTreeToggle<CR>

"------------------------------"
" Rid of White Space 
"------------------------------"
highlight ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace /\s\+$/
autocmd FileType c,cpp,java,php,javascript autocmd BufWritePre <buffer> :%s/\s\+$//e



