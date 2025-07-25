﻿#include "../header/Graph.h" 
#pragma comment (lib,"lib/graph_debug.lib")

void undirectedTest(Graph& g);
void directedTest(Graph& g);

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
    Vertex* original = (Vertex*)data;
    return new Vertex{ original->id };
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

void printCnt(Graph& g)
{
    cout << "\n정점의 수 : " << g.get_vertexCnt() << endl;
    cout << "엣지의 수 : " << g.get_edgeCnt() << endl;
}

void printVerticesViaIterator(Graph& graph)
{
    int i = 0;
    for (const void* it = graph.begin(); it != nullptr; it = graph.next((void*)it))
    {
        const typAdjList* adjListNode = static_cast<const typAdjList*>(graph.data((void*)it));
        if (adjListNode)
        {
            cout << ", [Vertex] : ";
            printVertex(adjListNode->vertex);  // 사용자 정의 출력 함수
            i++;
        }
    }
    cout << ", cnt : " << i << endl;
}

int main() {
    Graph g;

    undirectedTest(g);
    directedTest(g);

    return 0;
}

void undirectedTest(Graph& g)
{
    cout << "======== 무방향그래프 ========" << endl << endl;
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
    g.insert_edge(v4, v1);

    cout << "\n[무방향 그래프] 초기 그래프 상태:\n";
    g.printGraph();
    printCnt(g);

    // 4. 존재하지 않는 노드에 연결시도
    Vertex* ghost = new Vertex{ 999 };
    if (!g.insert_edge(v1, ghost)) {
        cout << "\n[무방향 그래프] 존재하지 않는 정점과 엣지 연결 방지 확인됨\n";
    }
    delete ghost;

    // 5. 중복 엣지 삽입
    if (!g.insert_edge(v1, v2)) {
        cout << "\n[무방향 그래프] 중복 엣지 삽입 방지 확인됨 (v1 - v2)\n";
    }

    // 6. 직접 삭제 실패 테스트 (참조되고 있음)
    void* toRemove = v2;
    if (!g.remove_vertex(&toRemove)) {
        cout << "\n[무방향 그래프] 직접 삭제 실패 (v2): 참조되거나 엣지 존재\n";
    }

    // 7. safeRemove_vertex 성공 테스트
    void* safeRemove = v2;
    if (g.safeRemove_vertex(&safeRemove)) {
        cout << "\n[무방향 그래프] safeRemove_vertex 성공: v2 삭제됨\n";
        printCnt(g);
    }
    else {
        cout << "\n[무방향 그래프] safeRemove_vertex 실패\n";
    }

    // 8. 엣지 삭제 테스트
    void* rmv_srcEdge = v4, *rmv_destEdge = v1;
    if(g.remove_edge(&rmv_srcEdge, &rmv_destEdge)){
        cout << "\n[무방향 그래프] 엣지삭제 성공: " << ((Vertex*)rmv_srcEdge)->id << "-" << ((Vertex*)rmv_destEdge)->id << endl;
    }
    else {
        cout << "\n[무방향 그래프] 엣지삭제 실패\n";
    }

    // 최종 그래프 출력
    cout << "\n[무방향 그래프] 최종 그래프 상태:\n";
    g.printGraph();
    printCnt(g);

    cout << "\n[무방향 그래프] 반복자 테스트:\n";
    printVerticesViaIterator(g);
}

void directedTest(Graph& g)
{
    cout << endl << "======== 방향그래프 ========" << endl;
    // 1. 그래프 초기화 (방향 그래프)
    g.init(compareVertex, destroyVertex, printVertex, DIRECTED);

    // 2. 정점 생성 및 삽입
    Vertex* v1 = new Vertex{ 1 };
    Vertex* v2 = new Vertex{ 2 };
    Vertex* v3 = new Vertex{ 3 };
    Vertex* v4 = new Vertex{ 4 };
    Vertex* v5 = new Vertex{ 5 };
    Vertex* v6 = new Vertex{ 6 };
    Vertex* v7 = new Vertex{ 7 };
    Vertex* v8 = new Vertex{ 8 };

    g.insert_vertex(v1);
    g.insert_vertex(v2);
    g.insert_vertex(v3);
    g.insert_vertex(v4);
    g.insert_vertex(v5);
    g.insert_vertex(v6);
    g.insert_vertex(v7);
    g.insert_vertex(v8);

    // 3. 엣지 연결 (단방향)
    g.insert_edge(v1, v2);  // v1 → v2
    g.insert_edge(v1, v3);  // v1 → v3
    g.insert_edge(v2, v4);  // v2 → v4
    g.insert_edge(v3, v4);  // v3 → v4
    g.insert_edge(v4, v5);  // v4 → v5
    g.insert_edge(v5, v6);  // v5 → v6
    g.insert_edge(v6, v7);  // v6 → v7
    g.insert_edge(v7, v3);  // v7 → v3
    g.insert_edge(v4, v1);  // v4 → v1

    cout << "\n[방향 그래프] 초기 그래프 상태:\n";
    g.printGraph();
    printCnt(g);

    // 4. 존재하지 않는 노드에 엣지 연결 시도
    Vertex* ghost = new Vertex{ 999 };
    if (!g.insert_edge(v1, ghost)) {
        cout << "\n[방향 그래프] 존재하지 않는 정점과 엣지 연결 방지 확인됨\n";
    }
    delete ghost;

    // 5. 중복 엣지 삽입 방지 확인
    if (!g.insert_edge(v1, v2)) {
        cout << "\n[방향 그래프] 중복 엣지 삽입 방지 확인됨 (v1 → v2)\n";
    }

    // 6. safeRemove_vertex 테스트
    void* safeRemove = v8;
    if (g.safeRemove_vertex(&safeRemove)) {
        cout << "\n[방향 그래프] safeRemove_vertex 성공: v2 삭제됨\n";
        printCnt(g);
    }
    else {
        cout << "\n[방향 그래프] safeRemove_vertex 실패\n";
    }

    // 7. 엣지 삭제 테스트
    void* rmv_srcEdge = v4, * rmv_destEdge = v1;
    if (g.remove_edge(&rmv_srcEdge, &rmv_destEdge)) {
        cout << "\n[방향 그래프] 엣지삭제 성공: " << ((Vertex*)rmv_srcEdge)->id << "→" << ((Vertex*)rmv_destEdge)->id << endl;
    }
    else {
        cout << "\n[방향 그래프] 엣지삭제 실패\n";
    }

    // 7. 최종 상태 출력
    cout << "\n[방향 그래프] 최종 그래프 상태:\n";
    g.printGraph();
    printCnt(g);

    cout << "\n[방향 그래프] 반복자 테스트:\n";
    printVerticesViaIterator(g);
}