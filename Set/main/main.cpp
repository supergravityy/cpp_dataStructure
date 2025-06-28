#include "../header/Set.h"
#include "../header/Libs.h"

void bonusTest();
void deMorganLaw();
void test_subsetCases();
void test_symmDiffCases();
void test_diffCases();
void test_intersectCases();
void test_unionCases();

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
    
    test_unionCases();
    test_intersectCases();
    test_diffCases();
    test_symmDiffCases();
    test_subsetCases();

    // 추가 수식검증란 (bonus)
    bonusTest();
    deMorganLaw();

    return 0;
}

void test_unionCases()
{
    cout << "====test_unionCases====" << endl << endl; 

    Set A, B, C, D, E;

    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);
    C.init(comparePerson, printPerson, destroyPerson, copyPerson);
    D.init(comparePerson, printPerson, destroyPerson, copyPerson);
    E.init(comparePerson, printPerson, destroyPerson, copyPerson);

    A.insert(new Person{ 1,"alpha"});
    A.insert(new Person{ 1,"beta"});
    A.insert(new Person{ 2, "gamma" });
    A.insert(new Person{ 3, "delta" });

    B.insert(new Person{ 5,"alpha" });
    B.insert(new Person{ 4,"theta" });

    // 1. 일반적인 경우

    cout << "1. general Case" << endl;
    Set* result1 = A | B;
    result1->printAll();
    delete result1;

    // 2. 동일집합인 경우
    cout << endl << "2. same set Case" << endl;
    C = A;
    Set* result2 = C | A;
    result2->printAll();
    delete result2;

    // 3. 공집합과의 합집합
    cout << endl << "3. one empty set Case" << endl;
    Set* result3 = D | A;
    result3->printAll();
    delete result3;

    // 4. 공집합끼리의 합집합
    cout << endl << "4. both empty set Case" << endl;
    Set* result4 = D | E;
    result4->printAll();
    delete result4;
}

void test_intersectCases()
{
    cout << endl << "====test_intersectCases====" << endl << endl;

    Set A, B, C, D, E;
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);
    C.init(comparePerson, printPerson, destroyPerson, copyPerson);
    D.init(comparePerson, printPerson, destroyPerson, copyPerson);
    E.init(comparePerson, printPerson, destroyPerson, copyPerson);

    A.insert(new Person{ 1, "alpha" });
    A.insert(new Person{ 1, "beta" });
    A.insert(new Person{ 2, "gamma" });
    A.insert(new Person{ 3, "delta" });

    B.insert(new Person{ 9, "alpha" });
    B.insert(new Person{ 8, "theta" });

    C.insert(new Person{ 10, "epsilon" });
    C.insert(new Person{ 11, "zeta" });

    // 1. 일반적인 경우 (alpha만 겹침)
    cout << "1. general Case (one element intersection)" << endl;
    Set* result1 = A & B;
    result1->printAll();
    delete result1;

    // 2. 겹치지 않는 경우
    cout << endl << "2. disjoint Case (no intersection)" << endl;
    Set* result2 = A & C;
    result2->printAll();
    delete result2;

    // 3. 동일한 집합
    cout << endl << "3. same set Case (A ∩ A)" << endl;
    Set* result3 = A & A;
    result3->printAll();
    delete result3;

    // 4. 한쪽이 공집합
    cout << endl << "4. one empty set Case" << endl;
    Set* result4 = A & D;
    result4->printAll();
    delete result4;

    // 5. 둘 다 공집합
    cout << endl << "5. both empty set Case" << endl;
    Set* result5 = D & E;
    result5->printAll();
    delete result5;
}

void test_diffCases()
{
    cout << endl << "====test_diffCases====" << endl << endl;

    Set A, B, C, D, E;
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);
    C.init(comparePerson, printPerson, destroyPerson, copyPerson);
    D.init(comparePerson, printPerson, destroyPerson, copyPerson);
    E.init(comparePerson, printPerson, destroyPerson, copyPerson);

    // A: alpha, beta, gamma, delta
    A.insert(new Person{ 1, "alpha" });
    A.insert(new Person{ 1, "beta" });
    A.insert(new Person{ 2, "gamma" });
    A.insert(new Person{ 3, "delta" });

    // B: alpha, delta
    B.insert(new Person{ 9, "alpha" });
    B.insert(new Person{ 9, "delta" });

    // C: beta, gamma (A의 부분집합)
    C.insert(new Person{ 4, "beta" });
    C.insert(new Person{ 5, "gamma" });

    // 1. 일반적인 경우 (alpha, delta 제거 → beta, gamma 남음)
    cout << "1. general Case" << endl;
    Set* result1 = A - B;
    result1->printAll();
    delete result1;

    // 2. 부분집합 제거 (A - C)
    cout << endl << "2. remove subset from A" << endl;
    Set* result2 = A - C;
    result2->printAll();
    delete result2;

    // 3. 동일한 집합 제거 (A - A → 0)
    cout << endl << "3. same set Case" << endl;
    Set* result3 = A - A;
    result3->printAll();
    delete result3;

    // 4. 공집합과의 차집합 (A - D = A)
    cout << endl << "4. subtract empty set from A " << endl;
    Set* result4 = A - D;
    result4->printAll();
    delete result4;

    // 5. 공집합에서 차집합 (D - A = 0)
    cout << endl << "5. empty set minus A " << endl;
    Set* result5 = D - A;
    result5->printAll();
    delete result5;
}

void test_symmDiffCases()
{
    cout << endl << "====test_symmDiffCases====" << endl << endl;

    Set A, B, C, D, E;
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);
    C.init(comparePerson, printPerson, destroyPerson, copyPerson);
    D.init(comparePerson, printPerson, destroyPerson, copyPerson);
    E.init(comparePerson, printPerson, destroyPerson, copyPerson);

    // A = {alpha, beta, gamma}
    A.insert(new Person{ 1, "alpha" });
    A.insert(new Person{ 2, "beta" });
    A.insert(new Person{ 3, "gamma" });

    // B = {gamma, delta, epsilon}
    B.insert(new Person{ 4, "gamma" });
    B.insert(new Person{ 5, "delta" });
    B.insert(new Person{ 6, "epsilon" });

    // C = {beta, gamma} → A의 부분집합
    C.insert(new Person{ 7, "beta" });
    C.insert(new Person{ 8, "gamma" });

    // D = A (동일 집합)
    D = A;

    // E = {} (공집합)

    // 1. 일반적인 경우: 일부 겹치고 일부 다름 → {alpha, beta, delta, epsilon}
    cout << "1. general Case (A ^ B)" << endl;
    Set* result1 = A ^ B;
    result1->printAll();
    delete result1;

    // 2. 부분집합 경우 (A ^ C) → A의 남는 원소 + C의 없는 원소
    cout << endl << "2. subset Case (A ^ C)" << endl;
    Set* result2 = A ^ C;
    result2->printAll();
    delete result2;

    // 3. 동일 집합 (A ^ A = 0)
    cout << endl << "3. same set Case (A ^ D)" << endl;
    Set* result3 = A ^ D;
    result3->printAll();
    delete result3;

    // 4. 완전한 독립 집합 (교집합 없음 → ∪ 결과와 동일)
    cout << endl << "4. disjoint Case (A ^ newSet)" << endl;
    Set F;
    F.init(comparePerson, printPerson, destroyPerson, copyPerson);
    F.insert(new Person{ 10, "lambda" });
    F.insert(new Person{ 11, "mu" });
    Set* result4 = A ^ F;
    result4->printAll();
    delete result4;

    // 5. 한 쪽이 공집합 (A ^ 0 = A)
    cout << endl << "5. one empty Case (A ^ 0)" << endl;
    Set* result5 = A ^ E;
    result5->printAll();
    delete result5;
}

void test_subsetCases()
{
    cout << endl << "====test_subsetCases====" << endl << endl;

    Set A, B, C, D, E;
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);
    C.init(comparePerson, printPerson, destroyPerson, copyPerson);
    D.init(comparePerson, printPerson, destroyPerson, copyPerson);
    E.init(comparePerson, printPerson, destroyPerson, copyPerson);

    // A = {alpha, beta}
    A.insert(new Person{ 1, "alpha" });
    A.insert(new Person{ 2, "beta" });

    // B = {alpha, beta, gamma}
    B.insert(new Person{ 3, "alpha" });
    B.insert(new Person{ 4, "beta" });
    B.insert(new Person{ 5, "gamma" });

    // C = {delta, epsilon} (A와 완전 독립)
    C.insert(new Person{ 6, "delta" });
    C.insert(new Person{ 7, "epsilon" });

    E.insert(new Person{ 7, "epsilon" });

    // D = A (동일 집합)

    // E = {} (공집합)

    // 1. A ⊂ B (진부분집합)
    cout << "1. A ⊂ B ?" << endl;
    cout << (A < B ? "true" : "false") << endl;

    // 2. A == D
    cout << endl << "2. A == D ?" << endl;
    D = A;
    cout << "A ⊆ D ? " << (A < D ? "true" : "false") << endl;
    cout << "A == D ? " << (A == D ? "true" : "false") << endl;

    // 3. A ⊂ C ? (독립 집합)
    cout << endl << "3. A ⊂ C ? (no common elements)" << endl;
    cout << (A < C ? "true" : "false") << endl;

    // 4. A ⊂ 0 (공집합이 포함해야 하는 경우 - false)
    cout << endl << "5. A ⊂ 0 ?" << endl;
    cout << (A < E ? "true" : "false") << endl;
}

void deMorganLaw()
{
    Set U, A, B;
    U.init(comparePerson, printPerson, destroyPerson, copyPerson);
    A.init(comparePerson, printPerson, destroyPerson, copyPerson);
    B.init(comparePerson, printPerson, destroyPerson, copyPerson);

    // 전체집합
    U.insert(new Person{ 1, "Alice" });
    U.insert(new Person{ 2, "Bob" });
    U.insert(new Person{ 3, "Charlie" });
    U.insert(new Person{ 4, "David" });
    U.insert(new Person{ 5, "Eve" });

    // A = {Alice, Bob}
    A.insert(new Person{ 1, "Alice" });
    A.insert(new Person{ 2, "Bob" });

    // B = {Charlie, David}
    B.insert(new Person{ 3, "Charlie" });
    B.insert(new Person{ 4, "David" });

    // (A ∪ B)'
    Set* unionAB = A | B;
    Set* lhs1 = U - *unionAB;

    // A' ∩ B'
    Set* notA = U - A;
    Set* notB = U - B;
    Set* rhs1 = *notA & *notB;

    cout << endl << "====demorgan law====" << endl;

    cout << "\n(1) (A ∪ B)' vs A' ∩ B'" << endl;
    cout << "LHS:" << endl; lhs1->printAll();
    cout << "RHS:" << endl; rhs1->printAll();
    cout << "Equal? " << (*lhs1 == *rhs1 ? "true" : "false") << endl;

    // (A ∩ B)'
    Set* intersectAB = A & B;
    Set* lhs2 = U - *intersectAB;

    // A' ∪ B'
    Set* rhs2 = *notA | *notB;

    cout << "\n(2) (A ∩ B)' vs A' ∪ B'" << endl;
    cout << "LHS:" << endl; lhs2->printAll();
    cout << "RHS:" << endl; rhs2->printAll();
    cout << "Equal? " << (*lhs2 == *rhs2 ? "true" : "false") << endl;

    // clean up
    delete unionAB; delete lhs1; delete rhs1;
    delete intersectAB; delete lhs2; delete rhs2;
    delete notA; delete notB;
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

    cout << endl << "====Complement Set====" << endl;

    // 여집합 A? = U - A
    Set* Ac = U - A;
    cout << "\nA? (Complement of A):" << endl;
    Ac->printAll();

    cout << endl << "====Bayes Theorem====" << endl;

    // P(A) = |A| / |U|
    double pA = (double)A.getSize() / U.getSize();
    double pB = (double)B.getSize() / U.getSize();

    
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