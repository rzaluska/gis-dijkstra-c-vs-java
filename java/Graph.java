import java.util.ArrayList;

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

    public void graph_add_single_edge(int from, int to, int weight)
    {
        Vertex f = vertex_array[from - 1];
        Neighbor nforward = new Neighbor();
        nforward.setVertex_index(to - 1);
        nforward.setWeight(weight);
        f.addNeighbor(nforward);
    }

    void graph_add_edge(int from, int to, int weight)
    {
        graph_add_single_edge(from, to, weight);
        graph_add_single_edge(to, from, weight);
    }

    ArrayList<Neighbor> graph_get_neighbors(int from)
    {
        Vertex f = vertex_array[from];
        return f.getNeighbors();
    }
}

class Neighbor
{
    private int vertex_index;
    private int weight;

    public int getVertex_index()
    {
        return vertex_index;
    }

    public void setVertex_index(int vertex_index)
    {
        this.vertex_index = vertex_index;
    }

    public int getWeight()
    {
        return weight;
    }

    public void setWeight(int weight)
    {
        this.weight = weight;
    }
}

class Vertex
{
    private ArrayList<Neighbor> neighbors;

    public Vertex()
    {
        neighbors = new ArrayList<>();
    }

    public Neighbor getNeighbor(int index)
    {
        return neighbors.get(index);
    }

    public ArrayList<Neighbor> getNeighbors()
    {
        return neighbors;
    }

    void addNeighbor(Neighbor n)
    {
        neighbors.add(n);
    }

    public boolean isEmpty()
    {
        return neighbors.size() == 0;
    }
}
