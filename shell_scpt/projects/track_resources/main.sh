#!/bin/bash

##################################
# Date: 08-12-2024
# ref_url: https://medium.com/@anandhirematha/shell-scripts-of-real-time-5876ea2b9b1e
# Status: Untested (yet to test the code)
##################################


output_file="system_monitoring.txt"
threshold_cpu=80
threshold_memory=80
threshold_disk=80
recipient="my_email@gmail.com"

monitor_system() {
	timestamp=$(date "+%Y-%m-%d %H:%M:%S")

	# get CPU usage percentage
	cpu_usage=$(top -bn1 | awk '/^%Cpu/ {print $2}')

	# get memory usage percentage
	memory_usage=$(free | awk '/Mem:/{print $3/$2*100.0}')

	# get disk usage percentage
	disk_usage=$(df -h/ | awk '/\//{print $5}' | tr -d'%')

	# write output to file in table format
	echo -e "Timestamp\tCPU Usage (%)\tMemory Usage (%)\tDisk Usage (%)" >> "output_file"

	echo -e "$timestamp\t$cpu_usage\t\t$mem_usage\t\t$disk_usage" >> "output_file"

	# check if any threshold is exceeded and send alert email
	if (($(echo "$cpu_usage > $threshold_cpu" | bc -l) )) || (($(echo "$memory_usage > $threshold_mem" | bc -l) )) || (($(echo "$disk_usage > $threshold_disk" | bc -l) )); then
		send_alert_email
	fi	

}

send_alert_email() {
	subject="System monitoring alert"
	body="The system is experiencing high resource usage.\n\n Take appropriate action."

	echo -e "$body" | mail -s"$subject" "$recipient"
	echo "Alert email sent to $recipient"
}

# call the function
monitor_system

