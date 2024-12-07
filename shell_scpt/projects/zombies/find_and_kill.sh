#!/bin/bash


# Get the list of zombie processes
zombie_pids=$(ps aux | grep -w Z | aws '{print $2}')


# Iterate over the zombie processes
for zombie_pid in $zombie_pids; do
	
	# Get the parent PID of the zombie process
	parent_pid=$(ps o ppid= -p $zombie_pid)

	# terminate the zombie parent
	kill -1 $parent_pid

done

echo "Zombie process(es) have been removed."


