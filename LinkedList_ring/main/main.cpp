#include "../header/cList.h"

typedef struct {
	int id;
	char name[32];
} UserData;

// Comparison function for UserData
typCmpResult cmpUser(const void* a, const void* b) {
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

// Memory cleanup function
void freeUser(void* data) {
	delete (UserData*)data;
}

int main() {
	cout << "===== 1. Constructor Test =====" << endl;
	cList my_cList;
	my_cList.init(cmpUser, printUser, freeUser);
	cout << ">> Circular list initialized." << endl;

	cout << "\n===== 2. Insertion Test =====" << endl;
	auto* u1 = new UserData{ 1, "Alice" };
	auto* u2 = new UserData{ 2, "Bob" };
	auto* u3 = new UserData{ 3, "Charlie" };
	auto* u4 = new UserData{ 4, "Daisy" };

	my_cList.push_front(u1);
	my_cList.push_front(u2);
	my_cList.push_front(u3);
	cout << ">> Performed push_front 3 times." << endl;
	my_cList.printAll();

	// Insert after a specific node
	void* node = my_cList.lookup_Node(u2);
	if (node != nullptr) {
		my_cList.insert_nextNode(node, u4);
		cout << ">> Inserted u4 after u2." << endl;
	}
	my_cList.printAll();

	cout << "\n===== 3. Deletion Test =====" << endl;
	void* deleted = nullptr;

	my_cList.pop_front(&deleted);
	freeUser(deleted);
	cout << ">> Performed pop_front once." << endl;
	my_cList.printAll();

	my_cList.pop_front(&deleted);
	freeUser(deleted);
	cout << ">> Performed pop_front twice." << endl;
	my_cList.printAll();

	// Delete node after u2 (which should be u4)
	node = my_cList.lookup_Node(u2);
	if (node != nullptr) {
		my_cList.remove_nextNode(node, &deleted);
		freeUser(deleted);
		cout << ">> Removed the node after u2 (expected u4)." << endl;
	}
	my_cList.printAll();

	cout << "\n===== 4. Destructor Test =====" << endl;
	cout << "The list will be automatically destroyed when it goes out of scope." << endl;

	return 0;
}
