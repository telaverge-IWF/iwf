" .protocol and .sablecc file type definition
" Link this file as or add its contents to ~/.vim/after/filetype.vim
augroup filetypedetect
au BufNewFile,BufRead *.protocol setf protocol
au BufNewFile,BufRead *.sablecc setf sablecc
augroup END
