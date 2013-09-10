#	a simple bash script for text processing (I was doing this in MAX but this is much easier to deal with) 
#	that takes a whole bunch of text, and saves each line as a separate text file, numbering each word form the original line
#	and placing it on its own line in the new file.  This script requires  that there is a file called master.txt in the pwd

if [ -a master.txt ] 				#check to see if master.txt exists
then
	mkdir -p lines_exported 			#make a directory for the exported lines
	counter=1 					#set a counter for the while loop						
	sed '/^$/d' master.txt > lines_stripped.txt	#sed is a handly little function that allows you to do all sorts of things; 
							#here I am using it to strip away blank lines
							#which I find using regex.  The stripped lines are saved to a new file, lines_stripped.txt	 

	length=$(wc -l < lines_stripped.txt)		#check for number of total lines in lines_stripped.txt  and set that to variable $length
	while [ $counter -le $length ]			#begin while loop
	do
		line=$(sed -n ${counter}p lines_stripped.txt)	#save each line individually to variable $line using sed
		counterB=1					#initialize another counter-this one is used to number each word within each line
		out=''						#initialize $out
		for word in $line 				#a handly little loop construction
		do
			out="$out$counterB, $word;\n"			#this might be a little confusing. I declare this varialbe beginning with $out, which 
									#allows me to basically add to whatever I had previously stored in the variable.
									#That way, I can write $out (which by the time it exits the loop contains every word
									#in the line) to a text file all at once

			(( counterB++ ))				#increment secondary counter
		done
		echo -e $out > lines_exported/$counter.txt	#save $out to a text file in the folder lines_exported
		echo "LINE NUMBER $counter"			#this isn't actually needed, but gives us some feedback in terminal and lets us know the
		echo -e $out					#the program is running correctlyt					
		(( counter++ ))					#increment $counter
	done
else
	echo "Please place file master.txt in the root diretory for processing!!"
fi	
