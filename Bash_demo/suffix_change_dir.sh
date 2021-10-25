#!/bin/bash


if [ $# -ne 3 -a $# -ne 4 -a $# -ne 5 ]
then
    echo "parmetaer' number is wrong"
    echo "3 parmeters: ./savepth pameter1(readtxtpath) pameter2(savetxtpath) pameter3(suffixpath)"
    echo "4 or 5 pameters: ./savepath pameter1(readtxtpath) pameter2(savetxtpath) pameter3(sourcereplace) pameter4(dstreplace) pameter5(suffixpath), if not add suffixpath,don't input pameter5!"
    exit
fi
readtxtpath=$1


cat ${readtxtpath}|
while read line
do
    echo $line;
    if [ $# -eq 4 -o $# -eq 5 ]
    then
        savetxtpath=$2;
        sourcereplace=$3;
        dstreplace=$4;

        line=${line/$sourcereplace/$dstreplace};

        if [ $# -eq 5 ]
        then
            line=$5$line
        fi
        echo "write "${line}" into "${savetxtpath}
    elif [ $# -eq 3 ]
    then
        savetxtpath=$2;
        suffixpath=$3
        line=$3$line
        echo "write "${line}"into "${savetxtpath}

    fi
     echo $line >> ${savetxtpath};

done



