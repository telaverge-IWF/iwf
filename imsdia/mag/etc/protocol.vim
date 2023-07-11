" Vim syntax file
" Language: protocol
" Maintainer:	W. Hu
" Last Change:	2005 Dec 2
" Bugs: The + operator should probably only be highlighted
"       when used as a part of a regex (not set construction)

" To install, put this file in ~/.vim/syntax/
" and add the lines
"   autocmd BufEnter *.sablecc set syntax=sablecc
"   au Syntax sablecc so $HOME/.vim/syntax/sablecc.vim
" to your ~/.vimrc file

" Remove any old syntax stuff hanging around.
syn clear
syn case match

syn keyword protocolKEYS protocol Diameter AVP Header
syn keyword protocolFLAG REQ PXY ERR
syn keyword protocolTYPE OctetString Integer32 Integer64 Unsigned32 Unsigned64 Float32 Float64 Grouped Address Time UTF8String DiamIdent DiamURI Enumerated IPFilterRule QoSFilterRule
syn keyword protocolOPRS ::=

highlight link protocolKEYS Keyword
highlight link protocolFLAG Constant
highlight link protocolTYPE Type
highlight link protocolOPRS Operator

" Numbers, characters.
"syn match Identifier	"[[a-zA-Z][a-zA-Z0-9_-]*\s*="
syn match Number	"[+-]\=[0-9][0-9]*\.\=[0-9]*"
"syn match Number	"0[x\|X][a-fA-F]*"
"syn match Structure	"\[\|\]\|(\|)\|?\|\*\|+\||"
"syn match String	"'.'"
"syn match Comment	"\/\/.*$"

" Strings, names, comments
" syn region String	start=.'. end=.'.
"syn region Label	start=.{. end=.}.
"syn region Transition	start=.{->. end=.}.
syn region Comment	oneline start=.//. end=.$.
syn region Comment	start=./\*. skip=./\*. end=.\*/.
syn region String   start=+"+ end=+"+

if !exists("did_sablecc_syntax_inits")
  let did_sablecc_syntax_inits = 1
  hi Comment ctermfg=Brown
  hi Transition ctermfg=Green
endif

let b:current_syntax = "sablecc"

" vim: ts=8
