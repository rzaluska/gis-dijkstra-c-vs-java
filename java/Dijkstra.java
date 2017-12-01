import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class Dijkstra
{
    public static class DijkstraResult {
        public int[] distance_table;
        public int[] prev_table;
    }

    public static void main(String[] args) throws Exception
    {
        // Read graph data from stdin
        // Write result to stdout
        Timer timer = new Timer();
        Timer all = new Timer();
        all.timer_start();
        try
        {
            System.setIn(new FileInputStream("test-cases/0.in.txt"));
        } catch (FileNotFoundException e)
        {
            //e.printStackTrace();
        }
        Scanner sc = new Scanner(System.in);
        int num_test_cases = sc.nextInt();
        for (int i = 0; i < num_test_cases; i++)
        {
            int num_verticles = sc.nextInt();
            int num_edges = sc.nextInt();
            System.out.printf("### graph with %d vertices and %d edges\n", num_verticles, num_edges);
            timer.timer_start();
            Graph g = new Graph(num_verticles);
            for (int j = 0; j < num_edges; j++)
            {
                int edge1 = sc.nextInt();
                int edge2 = sc.nextInt();
                int weight = sc.nextInt();
                g.graph_add_edge(edge1, edge2, weight);
            }
            timer.timer_stop();
            timer.print("# graph build took");
            int starting_verticle = sc.nextInt();
            timer.timer_start();
            DijkstraResult result = dijkstra(g, starting_verticle - 1);
            timer.timer_stop();
            timer.print("# dijkstra took");
            timer.timer_start();
            for (int j = 0; j < g.getNum_vertices(); j++)
            {
                if (j != starting_verticle - 1)
                {
                    if (j != g.getNum_vertices() - 1)
                    {
                        System.out.printf("%d ", result.distance_table[j]);
                    } else
                    {
                        System.out.printf("%d", result.distance_table[j]);
                    }
                }
            }
            System.out.println();
            for (int j = 0; j < g.getNum_vertices(); j++)
            {
                if (j != starting_verticle - 1)
                {
                    if (j != g.getNum_vertices() - 1)
                    {
                        System.out.printf("%d ", result.prev_table[j]);
                    } else
                    {
                        System.out.printf("%d", result.prev_table[j]);
                    }
                }
            }
            System.out.println();
            timer.timer_stop();
            timer.print("# print result took");
        }
        all.timer_stop();
        all.print("# execution took");
    }

    static DijkstraResult dijkstra(Graph g, int start)
    {
        Timer timer = new Timer();
        timer.timer_start();
        int[] distance_table = new int[g.getNum_vertices()];
        int[] prev_table = new int[g.getNum_vertices()];
        PriorityQueue q = new PriorityQueue(g.getNum_vertices());

        Timer init = new Timer();
        init.timer_start();
        distance_table[start] = 0;
        for (int i = 0; i < g.getNum_vertices(); ++i)
        {
            if (i != start)
            {
                distance_table[i] = Integer.MAX_VALUE;
                prev_table[i] = -1;
            }
            q.priority_queue_add_with_priority(i, distance_table[i]);
        }
        init.timer_stop();
        init.print("# dijkstra init");

        Timer loop = new Timer();
        loop.timer_start();
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
                    prev_table[neighbors.get(i).getVertex_index()] = min_vertex;
                    q.priority_queue_decrease_priority(neighbors.get(i).getVertex_index(), alternative);
                }
            }
        }
        loop.timer_stop();
        loop.print("# dijkstra loop");
        DijkstraResult result = new DijkstraResult();
        result.distance_table = distance_table;
        result.prev_table = prev_table;
        timer.timer_stop();
        timer.print("# dijkstra inside");
        return result;
    }
}
