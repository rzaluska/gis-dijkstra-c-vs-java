import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Dijkstra
{
    public static void main(String[] args)
    {
        // Read graph data from stdin
        // Write result to stdout
        Timer timer = new Timer();
        try
        {
            System.setIn(new FileInputStream("test-cases/0.in.txt"));
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        Scanner sc = new Scanner(System.in);
        int num_test_cases = sc.nextInt();
        for (int i = 0; i < num_test_cases; i++)
        {
            int num_verticles = sc.nextInt();
            int num_edges = sc.nextInt();
            Graph g = new Graph(num_verticles);
            for (int j = 0; j < num_edges; j++)
            {
                int edge1 = sc.nextInt();
                int edge2 = sc.nextInt();
                int weight = sc.nextInt();
                g.graph_add_edge(edge1, edge2, weight);
            }
            int starting_verticle = sc.nextInt();
            timer.timer_start();
            int[] distance_table = dijkstra(g, starting_verticle - 1);
            timer.timer_stop();
            for (int j = 0; j < g.getNum_vertices(); j++)
            {
                if (i != starting_verticle - 1)
                {
                    if (i != g.getNum_vertices() - 1)
                    {
                        System.out.println(distance_table[j]);
                    } else
                    {
                        System.out.println(distance_table[j]);
                    }
                }
            }
            System.out.println("dijkstra full took: " + timer.timer_get_sec_delta() + " seconds, "
                    + timer.timer_get_usec_delta() + " us");
        }
    }

    private static int[] dijkstra(Graph g, int start)
    {
        int[] distance_table = new int[g.getNum_vertices()];
        PriorityQueue q = new PriorityQueue(g.getNum_vertices());

        distance_table[start] = 0;
        for (int i = 0; i < g.getNum_vertices(); ++i)
        {
            if (i != start)
            {
                distance_table[i] = Integer.MAX_VALUE;
            }
            q.priority_queue_add_with_priority(i, distance_table[i]);
        }

        while (!q.priority_queue_is_empty())
        {
            int min_vertex = q.priority_queue_extract_min();
            ArrayList<Neighbor> neighbors = g.graph_get_neighbors(min_vertex);
            for (int i = 0; i < neighbors.size(); ++i)
            {
                int alternative = distance_table[min_vertex] + neighbors.get(i).getWeight();
                if (alternative < distance_table[neighbors.get(i).getVertex_index()])
                {
                    distance_table[neighbors.get(i).getVertex_index()] = alternative;
                    q.priority_queue_decrease_priority(neighbors.get(i).getVertex_index(), alternative);
                }
            }
        }

        return distance_table;
    }
}