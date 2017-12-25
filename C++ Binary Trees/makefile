treeLibrary:
	cl /c binary_tree.cpp
	lib binary_tree.obj
	
runTest:
	nmake treeLibrary
	cl /c test.cpp
	link binary_tree.lib test.obj
	@test
	
clean:
	del *.obj
	del *.exe
	del *.lib