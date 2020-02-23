# GenViewer
This tool allow you to visualize area of 2048x2048 from -1024 to 1024 on both axis.
We support generators from 1.7 to 1.14 included.
There is two way to use this tool, either by supplying a seed by argument or a list of seed inside the in.txt folder.
The default first argument is always the generator name.

Good ways to run this:

MapViewer.exe 1.12 1	-> produce in img/1.png an image for seed 1
MapViewer.exe 1.14		-> produce n images in img/ for all seeds in "in.txt"



To compile it you need libpng-dev
then do `cmake .`
then `make MapViewer`

