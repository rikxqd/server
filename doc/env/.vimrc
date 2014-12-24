if has("autocmd")
      autocmd BufNewFile *.h exec ":call SetTitle()"
else

endif " has("autocmd")

function SetTitle()
      if expand("%:e") == 'h'
            call append(0, "#ifndef _".toupper(expand("%:t:r"))."_H_")
            call append(1, "#define _".toupper(expand("%:t:r"))."_H_")
            call append(2, "")
            call append(3, "")
            call append(4, "")
            call append(5, "#endif//_".toupper(expand("%:t:r"))."_H_")
            call append(6, "")
      endif
endfunc