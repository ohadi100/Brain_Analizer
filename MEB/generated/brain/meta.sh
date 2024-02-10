# This "script" is sourced after content was mounted
# It usually contains some configuration data e.g. the size of the data partition

# Define the size of the data partition of a container. It is read-write mounted.
# The resulting size is smaller than given here, due to the use of ext4
DATASIZEMB=0
