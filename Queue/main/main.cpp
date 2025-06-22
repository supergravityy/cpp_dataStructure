#include "../header/Queue.h"

typedef struct {
	int id;
	char name[32];
} UserData;

// For debugging
void printUser(const void* data) {
	const UserData* user = (const UserData*)data;
	cout << "[ID: " << user->id << ", Name: " << user->name << "]" << endl;
}

typCmpResult compareUser(const void* a, const void* b) {
	const UserData* u1 = (const UserData*)a;
	const UserData* u2 = (const UserData*)b;
	if (u1->id < u2->id) return LESS;
	if (u1->id > u2->id) return GREATER;
	return EQUAL;
}

void freeUser(void* data) {
	delete (UserData*)data;
}

int main() {
	cout << "===== Queue Test =====" << endl;

	Queue q;
	q.init(compareUser, printUser, freeUser);

	auto* u1 = new UserData{ 1, "Alpha" };
	auto* u2 = new UserData{ 2, "Beta" };
	auto* u3 = new UserData{ 3, "Gamma" };
	auto* u4 = new UserData{ 4, "Delta" };

	q.enqueue(u1);
	q.enqueue(u2);
	q.enqueue(u3);
	q.enqueue(u4);
	cout << "\nAfter enqueue 4 elements:" << endl;
	q.printAll();  // Expected: Alpha, Beta, Gamma

	// Peek
	cout << "\nPeek front: ";
	printUser(q.peek());

	// Dequeue 2 elements
	void* popped = nullptr;

	q.dequeue(&popped);
	cout << "\nDequeued 1st: ";
	printUser(popped);
	freeUser(popped);

	q.dequeue(&popped);
	cout << "Dequeued 2nd: ";
	printUser(popped);
	freeUser(popped);

	cout << "\nQueue after 2 dequeues:" << endl;
	q.printAll();  // Expected: Gamma

	// Destructor test
	cout << "\nEnd of main(): Queue will be destroyed." << endl;
	return 0;
}
