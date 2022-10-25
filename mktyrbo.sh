if [[ $1 == 'compile' ]]; then
    echo compiling tyrbo...
    make -f resources/mktyrbo.mk
    echo to run tyrbo: ./tyrbo
elif [[ $1 == 'clean' ]]; then
    echo cleaning intermediate and target files...
    make -f mktyrbo.mk clean
    echo done!
else
    echo Usage:
    echo ./mktyrbo.sh compile \# to compile tyrbo
    echo ./mktyrbo.sh clean \# to clean output files
fi
