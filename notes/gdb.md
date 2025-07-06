info gdb 					//Manual
info locals 				        //Vars in local scope
info variables				//Vars declared outside current scope
info functions				//Names and datatypes of all defined functions
info b 						//List all breakpoints
break funcName				//Set breakpoint at function funcName (short: b funcName)
break file::line			        //Set breakpoint at line in file
layout next					//Cycle through the layouts of gdb
p var 						//Print the value of variable var
p var = value 			        	//Force set value to a var
run 						        //Start the program
start 						//Synonymous to (b main && run). Puts temporary b at main
next 						//Execute the current line in source (short: n)
step 						//Step into function call at current line (short: s)
finish						//Finish the execution of current function (short: fin)
continue					//Resume execution (After a breakpoint) (short: c)
refresh 					        //Repaint the interface (To fix corrupted interface)
shell cmd 					//Run shell command cmd from gdb prompt
python gdb.execute(cmd)		//Run a gdb command cmd from python prompt
set print pretty on			//Enable pretty printing
							  (Put in ~/.gdbinit)