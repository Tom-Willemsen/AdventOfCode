for i in $(seq -w 1 25) 
do 
    if test -f "./build/2021/$i/day$i"; then
        echo ""
        echo "2021 Day $i"
        time ./build/2021/$i/day$i 2021/$i/input
    fi
done;