if &cp | set nocp | endif
nmap  :let @" = expand("%")
nnoremap 	 gt
nnoremap  :cn
nmap  :T src/**/.h
nnoremap  :cp
nmap  :T **/*
nnoremap  
nnoremap < <
nnoremap > >
nnoremap H N
onoremap I ^
vnoremap I ^
nnoremap I ^
onoremap L $
vnoremap L $
nnoremap L $
nnoremap M O
vnoremap N 
nnoremap N 
vnoremap O 
nnoremap O 
vnoremap T I
nnoremap T I
nnoremap U 
let s:cpo_save=&cpo
set cpo&vim
xmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nnoremap h n
onoremap i h
vnoremap i h
nnoremap i h
onoremap k iw
nnoremap m o
onoremap n k
vnoremap n k
nnoremap n k
onoremap o j
vnoremap o j
nnoremap o j
xnoremap p pgvy
onoremap s w
vnoremap s w
nnoremap s w
onoremap t i
vnoremap t i
nnoremap t i
nnoremap vk viw
nnoremap x 
nnoremap zi h
nnoremap zl l
xnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
nnoremap <S-Tab> gT
nmap <C-G> :let @" = expand("%")
nmap <F4> :vimgrep // **/*<Left><Left><Left><Left><Left><Left>
nmap <F3> :vimgrep // **/*<Left><Left><Left><Left>
vmap <F2> y /"
nmap <C-O> :T src/**/.h
nmap <C-T> :T **/*
nnoremap <C-S-V> 
nnoremap <C-P> :cp
nnoremap <C-N> :cn
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set cpoptions=BceFs
set directory=~/.swp//
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hlsearch
set incsearch
set laststatus=2
set nomodeline
set printoptions=paper:a4
set report=10000
set ruler
set scrolloff=9999
set shiftwidth=2
set showcmd
set statusline=%F\ %l
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set switchbuf=usetab,newtab
set tabstop=2
set wildmenu
set wildoptions=pum
" vim: set ft=vim :
