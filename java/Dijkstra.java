import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class Dijkstra
{
    public static class DijkstraResult {
        public long[] distance_table;
        public long[] prev_table;
    }

    public static void main(String[] args) throws Exception
    {
        // Read graph data from stdin
        // Write result to stdout
        Timer timer = new Timer();
        Timer all = new Timer();
        all.timer_start();
        /*
        try
        {
            //System.setIn(new FileInputStream("test-cases/0.in.txt"));
        } catch (FileNotFoundException e)
        {
            //e.printStackTrace();
        }
        */
        Scanner sc = new Scanner(System.in);
        int num_test_cases = sc.nextInt();
        for (int i = 0; i < num_test_cases; i++)
        {
            int num_verticles = sc.nextInt();
            int num_edges = sc.nextInt();
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
            timer.print(num_verticles, num_edges, 0);
            int starting_verticle = sc.nextInt();
            DijkstraResult result = dijkstra(g, starting_verticle - 1, num_verticles, num_edges);
            //timer.timer_start();
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
        }
    }

    static DijkstraResult dijkstra(Graph g, int start, int v, int e)
    {
        Timer timer = new Timer();
        timer.timer_start();
        long[] distance_table = new long[g.getNum_vertices()];
        long[] prev_table = new long[g.getNum_vertices()];
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
        init.print(v,e,1);

        Timer loop = new Timer();
        loop.timer_start();
        while (!q.priority_queue_is_empty())
        {
            int min_vertex = q.priority_queue_extract_min();
            Neighbor n = g.graph_get_neighbors(min_vertex);
            while (n != null) {
                long alternative = distance_table[min_vertex] + n.getWeight();
                if (alternative < distance_table[n.getVertex_index()])
                {
                    distance_table[n.getVertex_index()] = alternative;
                    prev_table[n.getVertex_index()] = min_vertex;
                    q.priority_queue_decrease_priority(n.getVertex_index(), alternative);
                }
                n = n.next;
            }
        }
        loop.timer_stop();
        loop.print(v,e,2);
        DijkstraResult result = new DijkstraResult();
        result.distance_table = distance_table;
        result.prev_table = prev_table;
        timer.timer_stop();
        timer.print(v,e,3);
        return result;
    }
}
