class MyCircularQueue
{
private:
	int size;
	int *queue;
	int front;
	int rear;

public:
	MyCircularQueue(int k)
	{
		this->size = k + 1;
		queue = new int[size];
		front = 0;
		rear = 0;
	}

	bool enQueue(int value)
	{
		if (isFull())
		{
			return false;
		}
		else
		{
			rear = (rear + 1) % size;
			queue[rear] = value;
			return true;
		}
	}

	bool deQueue()
	{
		if (isEmpty())
		{
			return false;
		}
		else
		{
			front = (front + 1) % size;
			return true;
		}
	}

	int Front()
	{
		if (!isEmpty())
			return queue[(front + 1) % size];
		return -1;
	}

	int Rear()
	{
		if (!isEmpty())
			return queue[rear];
		return -1;
	}

	bool isEmpty()
	{
		if (front == rear)
			return true;
		return false;
	}

	bool isFull()
	{
		if (front == (rear + 1) % size)
			return true;
		return false;
	}
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */