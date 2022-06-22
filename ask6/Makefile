
###################################################
#
# file: Makefile
#
# @Author:   Iacovos G. Kolokasis
# @Version:  10-02-2021
# @email:    kolokasis@csd.uoc.gr
#
# Makefile
#
####################################################


## Do not touch here
turnin: undoTurnin
	-git tag assignment6
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment4"; then \
		git tag -d assignment6 && git push origin :refs/tags/assignment6; \
		fi
makedata3:
	gcc src/createdata3.c -o data3.exe
	./data3.exe
	
makedata6:
	gcc src/createdata6.c -o data6.exe
	./data6.exe
	
makedata9:
	gcc src/createdata9.c -o data9.exe
	./data9.exe
	
makeall: makedata3 makedata6 makedata9

clean: 
	rm createdata3.txt
	rm createdata6.txt
	rm createdata9.txt
	rm data3.exe
	rm data6.exe
	rm data9.exe