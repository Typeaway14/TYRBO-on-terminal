if [[ $1 == 'compile' ]]; then
    echo compiling tyrbo...
    make -f mktyrbo.mk
    echo to run tyrbo: ./tyrbo
elif [[ $1 == 'clean' ]]; then
    echo cleaning intermediate and target files...
    make -f mktyrbo.mk clean
    echo done!
else
    echo ./make_tyrbo.sh usage:
    echo ./make_tyrbo.sh compile \# to compile tyrbo
    echo ./make_tyrbo.sh clean \# to clean output files
fi
