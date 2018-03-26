#!/bin/bash

rm -f log_stderr executable 2> /dev/null
mkdir -p ./test

if [[ ! -f ./check ]]; then
    gcc check.c -o check -Wall --pedantic -std=c99
fi

echo "#!/bin/bash" > ./executable
echo "$@ \$@" >> ./executable
chmod 755 executable

A=0
B=0
C=0
START=$(date +%s)
for i in {00..99}; do
    echo "file$i" >> log_stderr
    L=$(timeout 25s ./executable < ./in/file$i | ./check ./in/file$i 2>> log_stderr | tee ./test/file$i | wc -l)
    CURRENT=$(date +%s)
    if (( CURRENT - START > 300 )); then
        echo "Time limit exceeded."
        break
    fi
    echo -n "."
    N=$(cat ./out/file$i)
    if (( L > 0 || N == 0 )); then
        A=$((A+1))
        M=$(cat ./test/file$i | sort -u | wc -l)
        echo -n $i ": gab[ " $N " ]  meu " $M
        if (( M == N )); then
            B=$((B+1))
            if (( L == N )); then
                C=$((C+1))
            fi
            echo "  OK"
        else
            echo "  Fail <-----"
        fi
    else
        echo $i ": gab[ " $N " ]  meu " $L" Fail? <-----"
    fi
done

CURRENT=$(date +%s)
MIN=$(((CURRENT-START)/60))
SEC=$(((CURRENT-START)%60))
if (( SEC < 10 )); then
    SEC="0$SEC"
fi
echo ""
echo "Tempo decorrido: 0${MIN}:${SEC}"
NA=$(echo "scale=2; $A*0.08" | bc)
NB=$(echo "scale=2; $B*0.04" | bc)
# desconta as entradas em que não há possibilidade de repetição:
NC=$(echo "scale=2; (($C-67) / 33.0) * 4" | bc)
TEST=$(echo "$NC < 0" | bc)
if [[ ! "$TEST" == "0" ]]; then
    NC="0.00"
fi
echo ""
echo "Nota do item (a): $NA de 8"
echo "Nota do item (b): $NB de 4"
echo "Nota do item (c): $NC de 4"
NTOTAL=$(echo "scale=2; $NA+$NB+$NC" | bc)
echo ""
echo "Nota do projeto: $NTOTAL de 10"
