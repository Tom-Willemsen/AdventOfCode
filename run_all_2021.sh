BUILD_TYPE="$(grep -oE 'CMAKE_BUILD_TYPE:STRING=[a-zA-Z]+' build/CMakeCache.txt)"

if [ $BUILD_TYPE = "CMAKE_BUILD_TYPE:STRING=Release" ]
then
    HYPERFINE_RUN_ARGS="--warmup=10 --runs 100"
else
    HYPERFINE_RUN_ARGS="--warmup=1 --runs 3"
fi

for i in $(seq -w 1 25) 
do 
    if test -f "./build/2021/$i/day$i"; then
        echo ""
        echo "2021 Day $i"
        ./build/2021/$i/day$i 2021/$i/input
        echo ""
        hyperfine $HYPERFINE_RUN_ARGS -N -u millisecond --style basic "./build/2021/$i/day$i 2021/$i/input"
    fi
done;
