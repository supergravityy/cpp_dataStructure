#include "../header/Stack.h"
#include "../header/List.h"
#pragma comment (lib,"lib/stack_debug.lib")

typedef struct {
	int id;
	char name[32];
} UserData;

// Comparison function for stack lookup (optional)
typCmpResult compareUser(const void* a, const void* b) {
	const UserData* u1 = (const UserData*)a;
	const UserData* u2 = (const UserData*)b;
	if (u1->id < u2->id) return LESS;
	if (u1->id > u2->id) return GREATER;
	return EQUAL;
}

// Print function
void printUser(const void* data) {
	const UserData* user = (const UserData*)data;
	cout << "[ID: " << user->id << ", Name: " << user->name << "]" << endl;
}

// Destructor
void freeUser(void* data) {
	delete (UserData*)data;
}

int main() {
	cout << "===== Stack Test =====" << endl;

	Stack myStack;
	myStack.init(compareUser, printUser, freeUser);

	// push 3 items
	auto* u1 = new UserData{ 1, "Alice" };
	auto* u2 = new UserData{ 2, "Bob" };
	auto* u3 = new UserData{ 3, "Charlie" };
	auto* u4 = new UserData{ 4, "Mike" };

	myStack.push(u1);
	myStack.push(u2);
	myStack.push(u3);
	myStack.push(u4);

	cout << "\nAfter pushing 4 elements:" << endl;
	myStack.printAll();  // Expected: Charlie, Bob, Alice, Mike

	// peek top element
	const void* top = myStack.peek();  // Change made to peek() suggested earlier
	if (top) {
		cout << "\npeek top element: ";
		printUser(top);
	}

	// pop two items
	void* popped = nullptr;
	myStack.pop(&popped);
	cout << "\npopped element 1: ";
	printUser(popped);
	freeUser(popped);

	myStack.pop(&popped);
	cout << "popped element 2: ";
	printUser(popped);
	freeUser(popped);

	// Final stack state
	cout << "\nRemaining element(s) in stack:" << endl;
	myStack.printAll();  // Expected: Alice, Mike

	// Destructor test (will be called automatically)
	cout << "\nEnd of main(): stack will be destroyed." << endl;

	return 0;
}