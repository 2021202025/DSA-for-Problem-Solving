#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

// bool flag = false;

template <class T>
class deque
{
public:
	int frontPointer;
	int backPointer;
	int qsize;
	//Default set to 2
	int qcapacity = 2;

	T *storageBuffer;

public:
	deque()
	{
		qsize = 0;
		frontPointer = -1;
		backPointer = -1;
		storageBuffer = new T[qcapacity];
	}

	deque(int n, T x)
	{
		qsize = n;
		if (qsize > qcapacity)
			qcapacity = qsize;
		storageBuffer = new T[qcapacity];
		// T storageBuffer[size] = {x};
		for (int i = 0; i < n; i++)
		{
			storageBuffer[i] = x;
		}

		frontPointer = 0;
		backPointer = qsize - 1;
	}

	bool empty();
	bool full();
	void push_back(T x);
	void push_front(T x);
	void pop_front();
	void pop_back();
	T front();
	T back();
	int capacity();
	int size();
	void clear();
	void resize(int x, T d);
	T returnIndexElement(int idx);
	T operator[](int idx);
	void capHandler();
};

template <class T>
bool deque<T>::empty()
{
	if (frontPointer == -1 && backPointer == -1)
		return true;
	else
		return false;
}

template <class T>
T deque<T>::operator[](int idx)
{
	return returnIndexElement(idx);
}

template <class T>
bool deque<T>::full()
{
	if (qsize == qcapacity)
		return true;
	else
		return false;
}

template <class T>
int deque<T>::size()
{
	return qsize;
}

template <class T>
void deque<T>::clear()
{
	qsize = 0;
	frontPointer = -1;
	backPointer = -1;
	qcapacity = 2;
	storageBuffer = new T[qcapacity];
}

template <class T>
void deque<T>::resize(int x, T d)
{
	if (x < qsize)
	{
		int diff = qsize - x;
		for (int i = 0; i < diff; i++)
		{
			pop_back();
		}
		qsize = x;

		// if (qsize < (qcapacity / 2)) {
		// 	qcapacity = qcapacity / 2;
		// }
		// frontPointer = 0;
		// backPointer = qsize - 1;
	}
	else if (x > qsize)
	{
		int diff = x - qsize;
		for (int i = 0; i < diff; i++)
		{
			push_back(d);
		}
		qsize = x;
	}
	else
	{
		return;
	}
}

template <class T>
T deque<T>::returnIndexElement(int idx)
{
	// flag = false;
	if ((idx) < qsize and (idx) >= 0)
	{
		return storageBuffer[(frontPointer + idx) % qcapacity];
	}
	else
	{
		// flag = true;
		cout << "Out of Range" << endl;
		static T temp;
		return temp;
		// return -1;
	}
}

template <class T>
void deque<T>::capHandler()
{
	qcapacity = qcapacity * 2;
	T *temp = new T[qcapacity];

	int j = 0;
	int i = frontPointer;

	while (i != backPointer)
	{
		temp[j] = storageBuffer[i];
		i = (i + 1) % qsize;
		j++;
	}
	temp[j] = storageBuffer[i];

	frontPointer = 0;
	backPointer = qsize - 1;

	delete[] storageBuffer;
	storageBuffer = temp;
}

template <class T>
void deque<T>::push_back(T x)
{

	if (empty())
	{
		frontPointer = 0;
		backPointer = 0;
		storageBuffer[backPointer] = x;
		qsize++;
		return;
	}

	if (full())
	{
		capHandler();
	}

	// backPointer = (backPointer + 1) % qcapacity;
	// storageBuffer[backPointer] = x;
	// qsize++;

	auto temp = backPointer;
	temp = (temp + 1) % qcapacity;
	backPointer = temp;
	storageBuffer[backPointer] = x;
	qsize++;

	return;
}

template <class T>
void deque<T>::pop_back()
{
	if (empty())
	{
		cout << "Underflow" << endl;
		return;
	}

	if (frontPointer == backPointer)
	{
		qsize--;
		// cout << "HIII" << endl;
		frontPointer = -1;
		backPointer = -1;
		return;
	}

	qsize--;
	auto temp = backPointer;
	temp = (temp - 1 + qcapacity) % qcapacity;
	backPointer = temp;
	// backPointer = (backPointer - 1 + qcapacity) % qcapacity;
	// qsize--;
	return;
}

template <class T>
void deque<T>::push_front(T x)
{
	if (empty())
	{
		frontPointer = 0;
		backPointer = 0;
		storageBuffer[backPointer] = x;
		qsize++;
		return;
	}

	if (full())
	{
		capHandler();
	}

	// qsize++;
	// frontPointer = (frontPointer - 1 + qcapacity) % qcapacity;
	// storageBuffer[frontPointer] = x;

	auto temp = frontPointer;
	temp = (temp - 1 + qcapacity) % qcapacity;
	frontPointer = temp;
	storageBuffer[frontPointer] = x;
	qsize++;

	// frontPointer
	//     = (frontPointer - 1 + qcapacity) % qcapacity;
	// storageBuffer[frontPointer] = x;
	// qsize++;

	return;
}

template <class T>
void deque<T>::pop_front()
{
	if (empty())
	{
		cout << "Underflow" << endl;
		return;
	}

	if (frontPointer == backPointer)
	{
		qsize--;
		// cout << "HIII" << endl;
		frontPointer = -1;
		backPointer = -1;
		return;
	}

	qsize--;
	auto temp = frontPointer;
	temp = (temp + 1) % qcapacity;
	frontPointer = temp;
	return;
}

template <class T>
T deque<T>::front()
{
	// flag = false;
	if (!empty())
	{
		return storageBuffer[frontPointer];
	}
	else
	{
		cout << "Underflow" << endl;
		// flag = true;
		static T temp;
		return temp;
		// return -1;
	}
}

template <class T>
T deque<T>::back()
{
	if (!empty())
	{
		return storageBuffer[backPointer];
	}
	else
	{
		cout << "Underflow" << endl;
		// if ( typeid(T).name()) {
		// 	cout << "saffs" << endl;
		// }
		static T temp;
		return temp;
		// return -1;
	}
}

int main()
{
	// deque<float> q (5, 7);
	// cout << q.backPointer  << " " << q.qcapacity << endl;
	// for (int i = q.frontPointer; i <= q.backPointer; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }
	// cout << endl;
	// q.push_back(9);
	// q.pop_back();
	// q.push_back(4);
	// cout << q.front() << " " << q.back() << endl;
	// q.push_front(2);
	// q.push_front(9.4);
	// q.push_back(6.2);
	// q.pop_front();
	// cout << q.front() << " " << q.back() << endl;
	// q.push_front(3);
	// q.push_front(9.4);
	// q.pop_front();
	// q.pop_front();
	// for (int i = q.frontPointer; i <= q.backPointer; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }
	// cout << endl;

	// // q.push_front(11);
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// cout << q.front() << endl;
	// cout << q.back() << endl;
	// cout << q.size() << endl;

	// q.clear();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// cout << q.front() << endl;
	// cout << q.back() << endl;
	// cout << q.size() << endl;

	// cout << q.qcapacity << endl;

	// q.push_back(9);
	// q.push_back(4);

	// cout << q.qcapacity << endl;

	// q.push_back(9);
	// q.push_back(4);

	// cout << q.qcapacity << endl;

	// for (int i = q.frontPointer; i <= q.backPointer; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }
	// cout << endl;
	// cout << "----------------------------------------" << endl;

	// cout << q.qsize << endl;
	// q.resize(3, 5);

	// for (int i = q.frontPointer; i <= q.backPointer; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }
	// cout << endl;
	// cout << q.qsize << endl;

	// q.resize(10, 5);

	// for (int i = q.frontPointer; i <= q.backPointer; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }
	// cout << endl;
	// cout << q.qsize << endl;
	// cout << q.qcapacity << endl;
	// cout << q.returnIndexElement(10) << endl;
	// cout << q[10] << endl;

	// cout << "______________________________________________" << endl;

	// q.push_front(2);
	// for (int i = q.frontPointer; i <= q.backPointer; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }

	// deque<float> dq;
	// dq.push_back(6);
	// for (int i = dq.frontPointer; i <= dq.backPointer; i++) {
	// 	cout << dq.storageBuffer[i] << " ";
	// }
	// cout << endl;
	// cout << q.storageBuffer[5] << endl;

	// deque<string> q;
	// q.push_back("abc");
	// q.push_back("cde");
	// q.push_front("def");
	// // q.push_front(4);
	// // cout << q.back() << endl;
	// // cout << q.full() << endl;
	// q.pop_back();
	// q.push_front("ghi");
	// q.pop_front();
	// cout << q.front() << endl;
	// cout << q.front() << endl;
	// cout << q.size() << endl;
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.pop_back();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.pop_back();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.pop_back();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.pop_back();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.pop_back();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.pop_back();
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// cout << q.qsize << endl;
	// cout << q.back() << endl;
	// cout << q.empty() << endl;
	// cout << q.size() << endl;
	// q.clear();
	// cout << q.empty() << endl;
	// cout << q.size() << endl;
	// q.resize(10, 99);
	// cout << q.size() << endl;
	// // cout << q.qsize << endl;
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// cout << q.front() << endl;
	// cout << q.back() << endl;
	// q.push_front("jkl");
	// cout << q[0] << endl;
	// cout << q[1] << endl;
	// cout << q[2] << endl;
	// cout << q[3] << endl;
	// cout << q[10] << endl;
	// q.push_back(5);
	// cout << q.frontPointer << " " << q.backPointer << endl;
	// q.push_front(3);

	// cout << endl;
	// cout << q.front() << endl;
	// cout << q.storageBuffer[1] << endl;
	// cout << q[0] << endl;

	// for (int i = 0; i < q.qsize; i++) {
	// 	cout << q.storageBuffer[i] << " ";
	// }

	// deque<float> q;
	// cout << q.front() << endl;
	// cout << q.back() << endl;
	// q.push_back(10.8);
	// q.push_front(34.5);
	// q.push_back(5.4);
	// // q.pop_front();
	// q.push_back(10.8);
	// q.push_front(34.5);
	// q.push_back(5.4);
	// // q.pop_front();
	// // q.pop_front();
	// // q.pop_back();
	// // q.clear();
	// q.resize(15, 6);
	// cout << q.size() << endl;
	// cout << q.qcapacity << endl;
	// cout << q.front() << endl;
	// cout << q.back() << endl;
	// cout << q[1] << endl;
	// cout << q[2] << endl;
	// cout << q[3] << endl;
	// cout << q[4] << endl;
	// cout << q[5] << endl;
	// cout << q[6] << endl;
	// cout << q[7] << endl;
	// cout << q[8] << endl;
	// cout << q[9] << endl;

	// cout << q[-1] << endl;
	// cout << flag << endl;
	// if (flag) {
	// 	cout << -1 << endl;
	// 	flag = 0;
	// }
	// else {
	// 	cout << q[0] << endl;
	// }
	// cout << q[-5] << endl;
	// cout << q.empty() << endl;
	// cout << q[10] << endl;
	// q.pop_front();
	// cout << q.front() << endl;
	// cout << q.back() << endl;

	// cout << q.front() << endl;
	// cout << q.back() << endl;
	deque<string> q;
	// deque<int>
	cout << q.front() << endl;

	q.push_back("fjf");
	q.push_front("jf");

	cout << q[0] << endl;

	cout << q.empty() << endl;

	q.pop_front();
	cout << q.back() << endl;

	q.resize(0, "");
	cout << q.front() << endl;
	cout << q.back() << endl;

	cout << q.qcapacity << endl;
	cout << q.qsize << endl;
	q.push_back("chingam");
	q.clear();
	cout << q.front() << endl;
	cout << q.back() << endl;

	cout << q.size() << endl;

	return 0;
}