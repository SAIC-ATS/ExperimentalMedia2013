an ofXml-based index and search example for openFrameworks
====================================
---------------
![alt text] (Screenshot3.png "screenshot detail")

Intro
------
This example indexes an iTunes music library and makes it searchable by track, artist and album. A simple GUI allows users to input search terms and control search filters, then  displays the paged results.  I've included some screenshots below of what you can expect.  

The concepts deveoped in this example could be applied to any case in which a large, nested directory tree needs to be indexed and searched.  

Core openFrameworks concepts and methods covered include:
- `ofXml`
- `ofFile` and `ofDirectory`
- Simple example of using `Poco::RegularExpressions` 
- Use of custom base and extended classes

Design 
----------------
###Overview
I've designed this app with the aim of separating the GUI functionality from the index and search functionality.  That way, those who are more interested in getting familiar with  ofXml can study the `testApp.h` and `testAp.cpp` files without getting bogged down in the GUI implementation.  

That being said, I've done my best to write the code in an easy to read and well-organized fashion throughout, and to comment as much as possible.
###Index
The indexing is simple in principle: we recursively read through a root directory, pulling our artist and album names from the folder titles.  When we reach the album folders, we read each file in the directory, pulling in each filename.  All of that information gets added to an XML file that is saved in the bin/data folder.

(N.B. - this example assumes it will be directed to an iTunes library that has been [organized by iTunes](http://support.apple.com/kb/ht3847) - i.e., that the library is organized in this fashion: root->artist->album->track.  I've provided a sample iTunes library with the example (the .mp3 files aren't actually mp3's, so don't try to play them) for those who might not have their music organized in this way.)
###Search
The search is a little more complicated, but remains simple in principle.  We recursively descend into our musicLibrary.xml file, once for each search filter boolean (artist, album, track) that is true, adding the results to a new XML document.  Once we've gathered all of our results, we check for and remove duplicate results.
Keep in Touch!
---------------
Have questions or suggestions for improving the example?  Let me know!  I'm relatively new to openFrameworks, am sure there are many aspects of the example that could have been better designed, and would love to hear from you! 
- [@abrahamavnisan](http://github.com/abrahamavnisan) on git hub
- [@abrahamavnisan](http://forum.openframeworks.cc/users/abrahamavnisan/activity) on the openFrameworks forum

A Couple Screenshots
--------------------
![alt text] (Screenshot1.png "screenshot 1")
![alt text] (Screenshot2.png "screenshot 2")
