# contents
- [head, tail](head,-tail)
- [zip](zip)


## head, tail
> read lines head or last 10 lines  
> head usage:  
- -c, --bytes=[-]K           
    - print the first K bytes of each file;  
    with the leading '-', print all but the last K bytes of each file.  
- -n, --lines=[-]K  
    - print the first K lines instead of the first 10;  
    with the leading '-', print all but the last K lines of each file

> tail usage: tail OPTION... FILE...
- -c, --bytes=K
    - output the last K bytes; 
    or use -c +K to output bytes starting with the Kth of each file
- -n, --lines=K
    - output the last K lines, instead of the last 10;
    or use -n +K to output starting with the Kth

## zip
> using zip to compress or uncompress a zip file  
> zip usage: zip -options -b path -t mmddyyyy -n suffixes zipfile list -xi list
- add or update file entry in zip file
    - -f freshen: only changed files  
    - -u update: only changed or new files  
    - -d delete entries in zipfile 
    - -m move into zipfile (delete OS files)
- compress levels
    - -num
    - -0 store only
    - -1 compress faster
    - -6 default
    - -9 compress better
- compress conditions
    - -n don't compress these suffixes
    - -x exclude the following names
    - -i include only the following names
- compress comments
    - -z add zipfile comment