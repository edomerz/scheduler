scheduler

read: event loop

being - closly related actions and data

do: high level design: 
					1 - what is the being in the system.(מה היישוייות במערכת)
						(exmple: moduels, and the relations), 
						what are the actions, functions, its API of each being 
						what are there relations
					2 - what are the data structures that the models uses
					3 - what is the flow control of the scheduler?
					4 - API of scheduler
					
recievs the function, insert to priority queue accorfding to a condition to priority (like time of insert, or runinig time of each function)

finishes when the queue when empty

destroy

task arguments:
    -	function to run
    - 	data (the data the function uses)
    -	time interval for excution (seconds)
    	function running time is not included
    
    every func reutnrs status : success(finishe for now, its current time slut), end(finidhed completly), failure
    
	


