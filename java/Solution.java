import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

//http://eduinf.waw.pl/inf/alg/001_search/0138.php

/* Jeśli wagi krawędzi są nieujemne, to problem znalezienia ścieżki o najniższym koszcie dojścia elegancko rozwiązuje algorytm Dijkstry. Algorytm ten pozwala znaleźć koszty dojścia od wierzchołka startowego v do każdego innego wierzchołka w grafie (o ile istnieje odpowiednia ścieżka). Dodatkowo wyznacza on poszczególne ścieżki. Zasada pracy jest następująca:

 
Tworzymy dwa zbiory wierzchołków Q i S. Początkowo zbiór Q zawiera wszystkie wierzchołki grafu, a zbiór S jest pusty. Dla wszystkich wierzchołków u grafu za wyjątkiem startowego v ustawiamy koszt dojścia d(u) na nieskończoność. Koszt dojścia d(v) zerujemy. Dodatkowo ustawiamy poprzednik p(u) każdego wierzchołka u grafu na niezdefiniowany. Poprzedniki będą wyznaczały w kierunku odwrotnym najkrótsze ścieżki od wierzchołków u do wierzchołka startowego v. Teraz w pętli dopóki zbiór Q zawiera wierzchołki, wykonujemy następujące czynności:

    Wybieramy ze zbioru Q wierzchołek u o najmniejszym koszcie dojścia d(u).
    Wybrany wierzchołek u usuwamy ze zbioru Q i dodajemy do zbioru S.
    Dla każdego sąsiada w wierzchołka u, który jest wciąż w zbiorze Q, sprawdzamy, czy d(w) > d(u) + waga krawędzi u–w. Jeśli tak, to wyznaczamy nowy koszt dojścia do wierzchołka w jako: d(w) ← d(u) + waga krawędzi u–w. Następnie wierzchołek u czynimy poprzednikiem w: p(w) ← u. */



public class Solution
{
    public static final int TABLE_DEFAULT = 1000000;

    public static void main(String[] args)
    {        
        Scanner scan = new Scanner(System.in);
        int T = scan.nextInt();
        
        for(int iT = 0; iT < T; ++iT)
        {
            int n = scan.nextInt();
            int m = scan.nextInt();

            int [][] table = new int [n][n];

            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                {
                    table[j][i] = TABLE_DEFAULT;
                }


            for(int i = 0; i < m; ++i)
            {
                int x = scan.nextInt();
                int y = scan.nextInt();
                int r = scan.nextInt();

                x--;
                y--;

                if(table[x][y] > r)
                {
                    table[x][y] = r;
                    table[y][x] = r;
                }
            }

            int s = scan.nextInt();
            s--;
            
            //Algorithm
            //if given vertice is in S set; othervise it is in Q set
            boolean [] S = new boolean[n];
            int [] p = new int [n];
            int [] d = new int [n];
            
            for(int i = 0; i < n; ++i)
            {
                p[i] = -1;
                d[i] = Integer.MAX_VALUE;
            }
            
            d[s] = 0;
            
            for(int g = 0; g < n; ++g)
            {
                int minV = Integer.MAX_VALUE;
                int V = -1;
                
                for(int u = 0; u < n; ++u)
                {
                    if(d[u] < minV && !S[u]) //looking for the closest vertice in Q
                    {
                        minV = d[u];
                        V = u;
                    }
                }
                
                if(V == -1)
                    break;
                
                S[V] = true;
                
                //look for neighbours
                for(int i = 0; i < n; ++i)
                {
                    if(table[V][i] != TABLE_DEFAULT && i != V)
                    {
                        if(d[i] > d[V] + table[V][i])
                        {
                            d[i] = d[V] + table[V][i];
                            p[i] = V;
                        }
                    }
                }
            }
            
            for(int i = 0; i < n; ++i)
            {
                if(i != s)
                {
                    if(d[i] != Integer.MAX_VALUE)
                        System.out.print(d[i] + " ");
                    else
                        System.out.print(-1 + " ");
                }
            }
            System.out.print('\n');

            //Print graph
            /*for(int i = 0; i < n; ++i)
            {
                for(int j = 0; j < n; ++j)
                {
                    System.out.print(table[j][i] + " ");
                }
                System.out.print('\n');
            } */
        }
       scan.close();
    }
}
