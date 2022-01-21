#include <string>
#include "DAG.h"
#include "tests.h"

using namespace std;

void testGraph1()
{
    typedef Node<string> StringNode;
    typedef Edge<string> StringEdge;
    
    // Create nodes.
    StringNode& node1(* new StringNode(string("a")));
    StringNode& node2(* new StringNode(string("b")));
    StringNode& node3(* new StringNode(string("c")));
    
    // Create edges.
    vector<StringEdge> edges;
    edges.push_back(StringEdge(node1, node2));
    edges.push_back(StringEdge(node1, node3));

    // Create graph.
    DAG<string> stringDag(edges);
    if (stringDag.IsEmpty())
    {
        cout << "Test 1 - FAILED - Invalid DAG!" << endl;
    }
    else
    {
        cout << "Test 1 - PASSED" << endl;
    }

    // No need to explicitely delete nodes, as DAG has the ownership and will release them.
}

void testGraph2()
{
    typedef Node<int> IntNode;
    typedef Edge<int> IntEdge;
    
    // Create nodes.
    IntNode& node1(* new IntNode(-10));
    IntNode& node2(* new IntNode(-20));
    IntNode& node3(* new IntNode(-30));
    IntNode& node4(* new IntNode(-40));
    
    // Create edges.
    vector<IntEdge> edges;
    edges.push_back(IntEdge(node1, node2));
    edges.push_back(IntEdge(node2, node4));
    edges.push_back(IntEdge(node1, node3));
    edges.push_back(IntEdge(node3, node4));

    // Create graph.
    DAG<int> intDag(edges);
    if (intDag.IsEmpty())
    {
        cout << "Test 2 - FAILED - Invalid DAG!" << endl;
    }
    else
    {
        cout << "Test 2 - PASSED" << endl;
    }

    // No need to explicitely delete nodes, as DAG has the ownership and will release them.
}

void testGraph3()
{
    typedef Node<int> IntNode;
    typedef Edge<int> IntEdge;
    
    // Create nodes.
    IntNode& node1(* new IntNode(-10));
    
    // Create edges.
    vector<IntEdge> edges;
    edges.push_back(IntEdge(node1, node1));

    // Create graph.
    DAG<int> intDag(edges);
    if (intDag.IsEmpty())
    {
        cout << "Test 3 - PASSED" << endl;
    }
    else
    {
        cout << "Test 3 - FAILED - DAG should be invalid" << endl;
    }

    // No need to explicitely delete nodes, as DAG has the ownership and will release them.
}
