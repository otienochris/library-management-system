for(size_t i = 16; i < 256; i++)
    {
        printf "\e[48;5;${i}m%03d" $i;
        printf '\e[0m';
        [ ! $((($i - 15) %6 )) -eq 0  ] && printf ' ' || printf '\n';
    }