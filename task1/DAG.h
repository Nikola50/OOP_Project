#ifndef DAG_H
#define DAG_H

#include <memory>
#include <iostream>
#include <vector>
#include <set>

template <typename T>
class Node
{
public: 
    Node(T value) : m_value(value) {}
    ~Node()
    {
        // std::cout << "Destroying: " << m_value << std::endl;
    }

    void AddNextNode(Node<T>& nextNode)
    {
        m_nextNodes.push_back(&nextNode);
    }

    std::vector<Node<T>*>& NextNodes()
    {
        return m_nextNodes;
    }

private:
    T m_value;

    // Use raw pointers as IDs, given vectors can't hold references.
    // Both nodes and edges are ultimately managed and owned by DAG.
    std::vector<Node<T>*> m_nextNodes;
};


template <typename T>
class Edge
{
public: 
    Edge(Node<T>& start, Node<T>& end) : m_start(start), m_end(end) {}

    Node<T>& Start() {return m_start;}
    Node<T>& End() {return m_end;}

private:
    Node<T>& m_start;
    Node<T>& m_end;

};

template <typename T>
class DAG
{
public: 
    DAG(std::vector<Edge<T>> &edges)
    {
        // Use raw pointers as unique node IDs.
        std::set<Node<T>*> uniqueNodes;
        for (auto& edge : edges)
        {  
            // Add current edge to each start node.
            edge.Start().AddNextNode(edge.End());
            
            // Add start/end nodes if not already present.
            // Take full ownership of them in the process.
            if (uniqueNodes.insert(&edge.Start()).second)
            {
                m_nodes.push_back(move(std::unique_ptr<Node<T>>(&edge.Start())));
            }
            if (uniqueNodes.insert(&edge.End()).second)
            {
                m_nodes.push_back(move(std::unique_ptr<Node<T>>(&edge.End())));
            }
        }

        // Check if valid DAG.
        if (!IsAcyclic())
        {
            m_nodes.clear();
        }
    }

    bool IsEmpty()
    {
        return m_nodes.empty();
    }

    // Collect all per-node edges, into a list of edges for the overall graph.
    std::vector<Edge<T>> GetEdges()
    {
        std::vector<Edge<T>> edges;
        
        for (auto& node : m_nodes)
        {
            for (auto& nextNode : node.NextNodes())
            {
                edges.push_back(Edge<T>(node, nextNode));
            }
        }

        return edges;
    }
    
    bool RemoveNode(Node<T>& nodeToRemove)
    {
        // Remove incoming edges.
        for (auto& node : m_nodes)
        {
            auto& nextNodes = node.NextNodes();
            auto nextNodeIt = nextNodes.begin();
            while (nextNodeIt != nextNodes.end())
            {
                if (*nextNodeIt == &nodeToRemove)
                {
                    node.NextNodes().erase(nextNodeIt);
                    break;
                }

                nextNodeIt++;
            }
        }

        // Remove the node itself.
        auto nodeIt = m_nodes.begin();
        while (nodeIt != m_nodes.end())
        {
            if (*nodeIt == &nodeToRemove)
            {
                m_nodes.erase(nodeIt);
                break;
            }

            nodeIt++;
        }

        return true;
    }
    
    bool IsAcyclic()
    {
        for (auto& node : m_nodes)
        {
            std::set<Node<T>*> visited;
            if (!IterateDependents(*node, visited))
            {
                return false;
            }
        }
        
        return true;
    }

private:
    bool IterateDependents(Node<T>& currentNode, std::set<Node<T>*>& nodePath)
    {
        for (auto& nextNode : currentNode.NextNodes())
        {
            auto nextNodePath = nodePath;
            if (!nextNodePath.insert(nextNode).second)
            {
                // Found cycle, return false.
                return false;
            }

            return IterateDependents(*nextNode, nextNodePath);
        }

        return true;
    }

private:
    std::vector<std::unique_ptr<Node<T>>> m_nodes;
};


#endif