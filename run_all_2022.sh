for i in $(seq -w 1 25) 
do 
    if test -f "./build/2022/$i/2022_day$i"; then
        echo ""
        echo "2022 Day $i"
        ./build/2022/$i/2022_day$i 2022/$i/input
        echo ""
        hyperfine --warmup=10 --runs 100 -N -u millisecond --style color "./build/2022/$i/2022_day$i 2022/$i/input"
    fi
done;
