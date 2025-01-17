
class MyCircularDeque
{
private:
	int size;
	int *queue;
	int front;
	int rear;

public:
	MyCircularDeque(int k)
	{
		this->size = k + 1;
		queue = new int[size];
		front = 0;
		rear = 0;
	}

	bool insertFront(int value)
	{
		if (isFull())
		{
			return false;
		}
		else
		{
			queue[front] = value;
			front = front - 1;
			if (front < 0)
			{
				front = front + size;
			}
			return true;
		}
	}

	bool insertLast(int value)
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

	bool deleteFront()
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

	bool deleteLast()
	{
		if (isEmpty())
		{
			return false;
		}
		else
		{
			rear = rear - 1;
			if (rear < 0)
			{
				rear = rear + size;
			}
			return true;
		}
	}

	int getFront()
	{
		if (!isEmpty())
			return queue[(front + 1) % size];
		return -1;
	}

	int getRear()
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
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */