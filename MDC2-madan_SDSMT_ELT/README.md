This is a framework to use MDC2 LZAP output files in a compiled way.

Using the first time:

```bash
source setup.sh
source config.sh <some lzap file>
```

After, only setup.sh is necessary. 

There are two bases that can be adapted: 

1. baseloop.cpp
2. baseloopfilelist.cpp

The first takes one argument, which is a file path (wildcards work) to some lzap files to become part of the chain The second takes one argument, which is a file containing a list of file paths to be added to the chain. 

The Makefile will compile anything that ends in .cpp, so these two bases can be copied to other files. 


