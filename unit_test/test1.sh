#!/bin/sh
i=0
while (($i < 100))
do  
    printf "\x1b[32mPROGRAM:\x1b[34;1m\n"
        time ./client_unit_test

    if (($? == 1))
        then
            break
        fi
    i=$((i+1));
done
