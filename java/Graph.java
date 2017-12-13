import java.util.LinkedList;

public class Graph
{
    private Vertex[] vertex_array;
    private int num_vertices;

    public int getNum_vertices()
    {
        return num_vertices;
    }

    public Graph(int n_ver)
    {
        vertex_array = new Vertex[n_ver];
        num_vertices = n_ver;

        for (int i = 0; i < n_ver; ++i)
        {
            vertex_array[i] = new Vertex();
        }
    }

    public void graph_add_single_edge(int from, int to, long weight)
    {
        Vertex f = vertex_array[from - 1];
        Neighbor nforward = new Neighbor();
        nforward.setVertex_index(to - 1);
        nforward.setWeight(weight);
        nforward.next = null;
        if (f.neighbors == null) {
            f.neighbors = nforward;
        } else {
            nforward.next = f.neighbors;
            f.neighbors = nforward;
        }
    }

    void graph_add_edge(int from, int to, long weight)
    {
        graph_add_single_edge(from, to, weight);
        graph_add_single_edge(to, from, weight);
    }

    Neighbor graph_get_neighbors(int from)
    {
        Vertex f = vertex_array[from];
        return f.neighbors;
    }
}

class Neighbor
{
    private int vertex_index;
    private long weight;

    public int getVertex_index()
    {
        return vertex_index;
    }

    public void setVertex_index(int vertex_index)
    {
        this.vertex_index = vertex_index;
    }

    public long getWeight()
    {
        return weight;
    }

    public void setWeight(long weight)
    {
        this.weight = weight;
    }
    public Neighbor next;
}

class Vertex
{
    public Neighbor neighbors;
}
