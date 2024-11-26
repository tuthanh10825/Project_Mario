#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	queue.push(command); 
}

Command CommandQueue::pop()
{
	Command front = queue.front(); 
	queue.pop(); 
	return front; 
}

bool CommandQueue::isEmpty() const
{
	return queue.empty();
}
