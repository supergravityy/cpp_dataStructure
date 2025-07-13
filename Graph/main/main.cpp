#include "../header/Graph.h" // 너의 그래프 헤더 경로에 맞게 조정

using namespace std;

struct Vertex {
    int id;
};

void printVertex(const void* data) {
    const Vertex* v = (const Vertex*)data;
    printf("(%d)", v->id);
}

void destroyVertex(void* data) {
    delete (Vertex*)data;
}

void* copyVertex(void* data) {
    Vertex* orig = (Vertex*)data;
    return new Vertex{ orig->id };
}

typCmpResult compareVertex(const void* a, const void* b) {
    int idA = ((Vertex*)a)->id;
    int idB = ((Vertex*)b)->id;

    if (idA < idB) return LESS;
    if (idA > idB) return GREATER;
    return EQUAL;
}

void* getKey(void* data) {
    return &((Vertex*)data)->id;
}

int main() {
    Graph g;

    // 1. 그래프 초기화 (무방향)
    g.init(compareVertex, destroyVertex, printVertex, UNDIRECTED);

    // 2. 정점 생성 및 삽입
    Vertex* v1 = new Vertex{ 1 };
    Vertex* v2 = new Vertex{ 2 };
    Vertex* v3 = new Vertex{ 3 };
    Vertex* v4 = new Vertex{ 4 };

    g.insert_vertex(v1);
    g.insert_vertex(v2);
    g.insert_vertex(v3);
    g.insert_vertex(v4);

    // 3. 엣지 연결
    g.insert_edge(v1, v2);
    g.insert_edge(v1, v3);
    g.insert_edge(v2, v4);
    g.insert_edge(v3, v4);

    cout << "\n초기 그래프 상태:\n";
    cout << "정점의 수 : " << g.get_vertexCnt() << endl;
    cout << "엣지의 수 : " << g.get_edgeCnt() << endl;
    g.printGraph();

    // 4. 직접 삭제 실패 테스트 (참조되고 있음)
    void* toRemove = v2;
    if (!g.remove_vertex(&toRemove)) {
        cout << "\n직접 삭제 실패 (v2): 참조되거나 엣지 존재\n";
    }

    // 5. safeRemove_vertex 성공 테스트
    void* safeRemove = v2;
    if (g.safeRemove_vertex(&safeRemove)) {
        cout << "\nsafeRemove_vertex 성공: v2 삭제됨\n";
    }
    else {
        cout << "\nsafeRemove_vertex 실패\n";
    }
    
    // 6. 최종 그래프 출력
    cout << "\n최종 그래프 상태:\n";
    g.printGraph();
    cout << "정점의 수 : " << g.get_vertexCnt() << endl;
    cout << "엣지의 수 : " << g.get_edgeCnt() << endl;

    return 0;
}