
Date: 08-12-2024
Topic: listing the 10 largest files in a directory
Ref_url: https://www.tomshardware.com/how-to/find-large-files-linux



## List file in descending order
ls -lS

## Identifying files larger than a specific size
find . -type f -size +100M

find ./test -type f -size +100M (checking other file paths)


## Searching the whole linnux system for large files
sudo find / -xdev -type f -size +100M

## Search linux system for files larger than 100M
sudo find / -type f -size +100M


#### Search for the top 10 largest files on a drive
sudo du -aBm / 2>/dev/null | sort -nr | head -n 10

### Code Explanation:

## du-aBM will search all files and directories, returning their
## size in megabyte

## / is the root directory

## 2>/dev/null will send any errors to /dev/null ensuring that no
## errors are printed to the screen.

## sort -nr will sort the output in reverse order

## head -n 10 will list the top 10 
