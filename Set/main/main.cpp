#include "../header/Set.h"
#include "../header/Libs.h"

void bonusTest();

// Person 구조체 정의
typedef struct {
    int id;
    char name[32];
} Person;

// 비교 함수: name 기준
typCmpResult comparePerson(const void* a, const void* b) {
    const Person* pa = (const Person*)a;
    const Person* pb = (const Person*)b;

    int cmp = strcmp(pa->name, pb->name);

    if (cmp < 0) return LESS;
    else if (cmp > 0) return GREATER;
    else return EQUAL;
}

// 출력 함수
void printPerson(const void* data) {
    const Person* p = (const Person*)data;
    cout << "[ID: " << p->id << ", Name: " << p->name << "] " << endl;
}

// 해제 함수
void destroyPerson(void* data) {
    delete (Person*)data;
}

// 복사함수
void* copyPerson(void* src){
    Person* srcData = (Person*)src;
    Person* temp = new Person;
    
    temp->id = srcData->id;
    strcpy_s(temp->name, srcData->name);
    return (void*)temp;
}

int main() {
    Set A, B;
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);

    // A = {1, 2, 3}
    A.insert(new Person{ 1, "Alice" });
    A.insert(new Person{ 2, "Bob" });
    A.insert(new Person{ 3, "Charlie" });
    cout << "====== A elements ======" << endl;
    A.printAll();

    // B = {3, 4, 5}
    B.insert(new Person{ 3, "Charlie" });
    B.insert(new Person{ 4, "David" });
    B.insert(new Person{ 5, "Eve" });
    cout << endl << "====== B elements ======" << endl;
    B.printAll();

    // 합집합
    Set* U = A | B;
    cout << endl << "A ∪ B" << endl;
    if (U != nullptr) 
    { 
        U->printAll();
        // delete U; 
    }
    else 
        cout << "[Union Failed]" << endl;

    // 교집합
    Set* I = A & B;
    cout << endl << "A ∩ B" << endl;
    if (I != nullptr)
    {
        I->printAll();
        // delete I;
    }
    else 
        cout << "[Intersection Failed]" << endl;

    // 차집합 A - B
    Set* D = A - B;
    cout << endl << "A - B" << endl;
    if (D != nullptr)
    { 
        D->printAll(); 
        // delete D; 
    }
    else 
        cout << "[Difference Failed]" << endl;

    // 대칭 차집합
    Set* SD = A ^ B;
    cout << endl << "A △ B" << endl;
    if (SD != nullptr) 
    { 
        SD->printAll(); 
        // delete SD; 
    }
    else 
        cout << "[Symmetric Difference Failed]" << endl;

    // 비교 연산
    {
        Set sameSet1, sameSet2;
        sameSet1.init(comparePerson, printPerson, destroyPerson, copyPerson);
        sameSet2.init(comparePerson, printPerson, destroyPerson, copyPerson);
        sameSet1.insert(new Person{ 1, "alpha" });
        sameSet1.insert(new Person{ 1, "beta" });
        sameSet2.insert(new Person{ 2, "alpha" });
        sameSet2.insert(new Person{ 2, "beta" });

        cout << endl;
        cout << "sameSet1 == sameSet2 ? " << (sameSet1 == sameSet2 ? "true" : "false") << endl;
    }

    {
        Set subset1, subset2;
        subset1.init(comparePerson, printPerson, destroyPerson, copyPerson);
        subset2.init(comparePerson, printPerson, destroyPerson, copyPerson);
        subset1.insert(new Person{ 1, "alpha" });
        subset1.insert(new Person{ 1, "beta" });
        subset1.insert(new Person{ 1, "gamma" });
        subset2.insert(new Person{ 2, "alpha" });
        subset2.insert(new Person{ 2, "gamma" });

        cout << "subset1 ⊂ subset2 ? " << (subset1 < subset2 ? "true" : "false") << endl;
        cout << "subset1 ⊃ subset2 ? " << (subset1 > subset2 ? "true" : "false") << endl;
    }
    
    // 복사 대입은 사용하지 않고 명시적으로 copySet() 사용
    Set C;
    C.init(comparePerson, printPerson, destroyPerson, copyPerson);
    C = A;
    cout << endl << "C = A → C:" << endl;
    C.printAll();

    // 추가 수식검증란 (bonus)
    bonusTest();

    return 0;
}

void bonusTest()
{
    // 전체집합
    Set U;
    U.init(comparePerson, printPerson, destroyPerson, copyPerson);
    U.insert(new Person{ 1, "Alice" });
    U.insert(new Person{ 2, "Bob" });
    U.insert(new Person{ 3, "Charlie" });
    U.insert(new Person{ 4, "David" });
    U.insert(new Person{ 5, "Eve" });

    // 사건 A: Alice, Bob
    Set A;
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    A.insert(new Person{ 1, "Alice" });
    A.insert(new Person{ 2, "Bob" });

    // 사건 B: Bob, Charlie
    Set B;
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.insert(new Person{ 2, "Bob" });
    B.insert(new Person{ 3, "Charlie" });

    // 여집합 A? = U - A
    Set* Ac = U - A;
    cout << "\nA? (Complement of A):" << endl;
    Ac->printAll();

    // P(A) = |A| / |U|
    double pA = (double)A.getSize() / U.getSize();
    double pB = (double)B.getSize() / U.getSize();

    // 베이즈정리
    // A ∩ B
    Set* AandB = A & B;
    double pAandB = (double)AandB->getSize() / U.getSize();

    // P(A|B) = P(A ∩ B) / P(B)
    double pAgivenB = pB > 0 ? pAandB / pB : 0;

    // P(B|A) = P(A|B) * P(B) / P(A)
    double pBgivenA = (pA > 0) ? (pAgivenB * pB / pA) : 0;

    cout << fixed;
    cout.precision(4);
    cout << "\n[확률 계산]" << endl;
    cout << "P(A)        = " << pA << endl;
    cout << "P(B)        = " << pB << endl;
    cout << "P(A ∩ B)    = " << pAandB << endl;
    cout << "P(A | B)    = " << pAgivenB << endl;
    cout << "P(B | A)    = " << pBgivenA << "  ← 베이즈 정리 결과" << endl;

    // 정리
    delete Ac;
    delete AandB;
}