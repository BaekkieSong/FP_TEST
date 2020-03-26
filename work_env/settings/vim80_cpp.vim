" Vim syntax file
" Language:	C++
" Current Maintainer:	vim-jp (https://github.com/vim-jp/vim-cpp)
" Previous Maintainer:	Ken Shan <ccshan@post.harvard.edu>
" Last Change:	2017 Jun 05

" quit when a syntax file was already loaded
if exists("b:current_syntax")
  finish
endif

" Read the C syntax to start with
runtime! syntax/c.vim
unlet b:current_syntax

" C++ extensions
syn keyword cppStatement	new delete this friend using
syn keyword cppAccess		public protected private
syn keyword cppModifier		inline virtual explicit export
syn keyword cppType		bool wchar_t
syn keyword cppExceptions	throw try catch
syn keyword cppOperator		operator typeid
syn keyword cppOperator		and bitor or xor compl bitand and_eq or_eq xor_eq not not_eq
syn match cppCast		"\<\(const\|static\|dynamic\|reinterpret\)_cast\s*<"me=e-1
syn match cppCast		"\<\(const\|static\|dynamic\|reinterpret\)_cast\s*$"
syn keyword cppStorageClass	mutable
syn keyword cppStructure	class typename template namespace
syn keyword cppBoolean		true false
syn keyword cppConstant		__cplusplus

" C++ 11 extensions
if !exists("cpp_no_cpp11")
  syn keyword cppModifier	override final
  syn keyword cppType		nullptr_t auto
  syn keyword cppExceptions	noexcept
  syn keyword cppStorageClass	constexpr decltype thread_local
  syn keyword cppConstant	nullptr
  syn keyword cppConstant	ATOMIC_FLAG_INIT ATOMIC_VAR_INIT
  syn keyword cppConstant	ATOMIC_BOOL_LOCK_FREE ATOMIC_CHAR_LOCK_FREE
  syn keyword cppConstant	ATOMIC_CHAR16_T_LOCK_FREE ATOMIC_CHAR32_T_LOCK_FREE
  syn keyword cppConstant	ATOMIC_WCHAR_T_LOCK_FREE ATOMIC_SHORT_LOCK_FREE
  syn keyword cppConstant	ATOMIC_INT_LOCK_FREE ATOMIC_LONG_LOCK_FREE
  syn keyword cppConstant	ATOMIC_LLONG_LOCK_FREE ATOMIC_POINTER_LOCK_FREE
  syn region cppRawString	matchgroup=cppRawStringDelimiter start=+\%(u8\|[uLU]\)\=R"\z([[:alnum:]_{}[\]#<>%:;.?*\+\-/\^&|~!=,"']\{,16}\)(+ end=+)\z1"+ contains=@Spell
endif

" C++ 14 extensions
if !exists("cpp_no_cpp14")
  syn case ignore
  syn match cppNumber		display "\<0b[01]\('\=[01]\+\)*\(u\=l\{0,2}\|ll\=u\)\>"
  syn match cppNumber		display "\<[1-9]\('\=\d\+\)*\(u\=l\{0,2}\|ll\=u\)\>" contains=cFloat
  syn match cppNumber		display "\<0x\x\('\=\x\+\)*\(u\=l\{0,2}\|ll\=u\)\>"
  syn case match
endif

syn match  cCustomParen "(" contains=cParen,cCppParen
syn match  cCustomFunc  "\w\+\s*(" contains=cCustomParen  "\u
hi def cCustomFunc guifg=yellowgreen ctermfg=226
 syn match  cCustomScope "::"
 syn match  cCustomClass "\w\+\s*::" contains=cCustomScope
 hi def cCustomClass guifg=yellowgreen ctermfg=166
" syntax match myMatch "\v\.\zs\w+\ze\("
" highlight link myMatch Function
syn match cCustomParen2 ")" contains=cParen,cCppParen
hi def cCustomParen2 ctermbg=0

syn match myClassScope "class" contains=Structure,cStructure
syn match myClassScopee "\s[:{]" "contains=Type
"syn match myClassScopeee "\s{" "contains=Type
syn match myClass "\s\u\w\+ [:{]" contains=myClassScope,myClassScopee
"syn match myClasss "\s\u\w\+ {" contains=myClassScope,myClassScopeee
hi def myClass ctermfg=3"9"27
"hi def myClasss ctermfg=27
"syn region myClass start="class\w\+\s" end="\s\:" contains=Structure
"hi def myClass ctermfg=3


" syn match cCustomFunc "\w\+\s\+[a-zA-z]\+[a-zA-Z0-9]*("
"syn match className "class "
" syn match cCustomClass "class \v\s\zs\w+\ze" contains=Type
"syn match cCustomClass "class *\w\+" contains=Type,Identifier
"hi def cCustomClass ctermfg=1 guifg=yellowgreen

" syn match methodCall /\(#\)\@<=\w*/ contains=cParen
" hi methodCall ctermfg=6
" syn match className /\w*\(#\)\@=/ contains=cParen
" hi className ctermfg=1

" The minimum and maximum operators in GNU C++
syn match cppMinMax "[<>]?"

" Default highlighting
hi def link cppAccess		cppStatement
hi def link cppCast		cppStatement
hi def link cppExceptions		Exception
hi def link cppOperator		Operator
hi def link cppStatement		Statement
hi def link cppModifier		Type
hi def link cppType		Type
hi def link cppStorageClass	StorageClass
hi def link cppStructure		Structure
hi def link cppBoolean		Boolean
hi def link cppConstant		Constant
hi def link cppRawStringDelimiter	Delimiter
hi def link cppRawString		String
hi def link cppNumber		Number

let b:current_syntax = "cpp"

" vim: ts=8
