#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
    public:
        int getOrder();
        virtual int getMaximumDegree() = 0;
        virtual int getMinimumDegree() = 0;
        virtual int getVertexDegree(int vertex_id) = 0;

    protected:
        int order;

    private:
};

#endif // GRAPH_H
