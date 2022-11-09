if [[ $1 == '' ]]; then
    echo compiling tyrbo...
    make -f resources/lib/mktyrbo.mk
    echo to run tyrbo: ./tyrbo
elif [[ $1 == 'clean' ]]; then
    echo cleaning intermediate and target files...
    rm resources/bin/*.o tyrbo
    echo done!
else
    echo Usage:
    echo ./mktyrbo.sh compile \# to compile tyrbo
    echo ./mktyrbo.sh clean \# to clean output files
fi
