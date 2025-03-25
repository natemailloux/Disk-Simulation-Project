
# This Makefile is not intended to take advantage of separate compilation.
# It serves as a short-cut to command-line compilation

# Store this file in the project directory (DiskSim)

sim.x:
	g++ -std=c++17 CommonFiles/sim.cpp CommonFiles/Disk.cpp CommonFiles/EventNode.hpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp PickUp_Queue/PickUpQueue.cpp Look_Queue/LookQueue.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp CommonFiles/Request.cpp CLook_Queue/CLookQueue.cpp -o sim.x



clean:
	rm -f sim.x


