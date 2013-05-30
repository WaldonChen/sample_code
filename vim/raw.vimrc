"===========================================
" General
"===========================================
" Let VIM not compatible with VI
set nocompatible

" How many lines of history VIM has to remember, default is 20
set history=100

" Enable filetype plugins
filetype plugin indent on
syntax on

" Set to auto read when a file is changed from the outside
" set autoread

" Map <leader> to ','
let mapleader=','

" Map jj to <ESC> in insert mode
imap jj <esc>


" Fast saving
nmap <leader>w :w!<CR>

"===========================================
" VIM user interface
"===========================================
" Set 7 lines to the cursor when moving vertically using j/k
set so=7

" Tune on the WiLd menu
set wildmenu

" Ignore compiled files
set wildignore=*.o,*~,*.pyc

" Always show current position on right-bottom
set ruler

" Height of the command bar
set cmdheight=1

" Configure backspace so it acts as it should act
set backspace=eol,start,indent
set whichwrap+=b,s,<,>,[,] " ,h,l

" search {
" Ignore case when searching
set ignorecase

" When searching try to be smart about cases
set smartcase

" Hightlight search results
set hlsearch

" Makes search act like search in modern browsers
set incsearch
" }

" Don't redraw while executing macros, registers and other cmds
" that have not been typed.
set lazyredraw

" For regular expressions turn magic on
set magic

" Show matching brackets when text indicator is over them
set showmatch
" How many tenths of a second to blink when matching brackets
set mat=2

" Status line {
set laststatus=2
set ruler
set statusline=[%F]%y%r%m%*%=[CWD:\ %r%{getcwd()}%h\ ][Line:%l/%L,Column:%c][%p%%]
" }


"===========================================
" Colors and Fonts
"===========================================
" Enable syntax hightlighting
syntax enable

" Sets color scheme
colo desert
set colorcolumn=81
set t_Co=256
set cursorline

" Encoding settings {
set fileencodings=utf-8,gb18030,gbk,big5,latin1
set termencoding=utf-8
set encoding=utf-8
" }


"===========================================
" Text, tab and indent related
"===========================================
" tab settings {
set smarttab
set tabstop=4
set shiftwidth=4
set softtabstop=4
" }

" Line break on xx characters
" set linebreak
" set textwidth=80

" indent settings {
set autoindent
set smartindent
set cindent
" set wrap
" }

" line number settings {
set nu
set nuw=5
set isk+=-
" }


"===========================================
" Moving around, tabs, windows and buffers
"===========================================
map j gj
map k gk

" smart way to move between windows
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

" useful mappings for managing tabs
map <leader>tn :tabnew<cr>
map <leader>tnn :tabnew
map <leader>to :tabonly<cr>
map <leader>tc :tabclose<cr>
map <leader>tm :tabmove

map <leader>te :tabedit <c-r>=expand("%:p:h")<cr>/

" Switch CWD to the directory of the open buffer
map <leader>cd :cd %:p:h<cr>:pwd<cr>

" Specify the behavior when switching between buffers
try
	set switchbuf=useopen,usetab,newtab
	set stal=2
catch
endtry

" Return to last edit position when opening files
autocmd BufReadPost *
	\ if line("'\"") > 0 && line("'\"") <= line("$") |
	\	exe "normal! g'\'' |
	\ endif
" Remember info about open buffers on close
set viminfo^=%


"===========================================
" Editing mappings
"===========================================
" Move a line of text using ALT+[jk]
nmap <M-j> mz:m+<cr>`z
nmap <M-k> mz:m-2<cr>`z
vmap <M-j> :m'>+<cr>`<my`>mzgv`yo`z
vmap <M-k> :m'<-2<cr>`>my`<mzgv`yo`z

" ctags settings {
set tags=tags;
" }

" When .vimrc is modified, reload it
autocmd! bufwritepost .vimrc source ~/.vimrc

" Delete trailing white space on save
func! DeleteTrailingWS()
	exe "normal mz"
	%s/\s\+$//ge
	exe "normal `z"
endfunc
func! DisplayTrailingWS()
	silent! /\s\+$
endfunc
nmap ;m :call DeleteTrailingWS()<CR>
nmap ;d :call DisplayTrailingWS()<CR>
autocmd BufWrite *.py :call DeleteTrailingWS()
" autocmd BufWrite *.[ch] :call DeleteTrailingWS()
