


import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Locale;
import java.util.StringTokenizer;

/**
 * HamiltonianPathTest - client program to test reduction of  Hamiltonian Path  to SAT.
 */

public class CleaningApt {
	class Edge {
	    int from;
	    int to;

	    Edge(int from , int to){
	        this.from = from;
	        this.to = to;
	    }
	}
	
	class Graph {
	    int vertexCount;
	    int edgeCount;
	    Edge[] edges;
	    private int edgeCounter = 0;
	    boolean[][] isEdge;
	    ArrayList<Edge> nonEdges;


	    Graph(int vertexCount, int edgeCount){
	        this.vertexCount = vertexCount;
	        this.edgeCount = edgeCount;
	        edges = new Edge[edgeCount];
	        //computing nonEdges - used as a input for constraint in hamilPath SAT
	        isEdge = new boolean[vertexCount][vertexCount];
	        nonEdges = new ArrayList<>();
	    }

	    void addEdge(int from, int to){
	        Edge edge = new Edge(from, to);
	        edges[edgeCounter++] = edge;
	        isEdge[from][to] = true;
	        isEdge[to][from] = true;
	    }

	    /**
	     * computing nonEdges - used as a input for constraint in hamilPath SAT
	     */
	    void updateNonEdges(){
	        for (int i = 0; i < isEdge.length; i++){
	            for (int j = i+1; j < isEdge[0].length; j++){
	                if (!isEdge[i][j]){
	                    nonEdges.add(new Edge(i,j));
	                }
	            }
	        }
	    }

	}
	    
	class ConvertHamilPathToSat {

	    ArrayList<ArrayList<Integer>> clauses;
	    private int vertexCount;
	    private int positionCount;
	    int variableCount;
	    private Graph g;
	    Integer[][] variables; // 2d array in which i->vertex, j->position in hamilPath
	    ConvertHamilPathToSat(Graph g) {
	        this.g = g;
	        g.updateNonEdges();
	        //hamilPath with v vertices has v paths
	        variables = new Integer[g.vertexCount][g.vertexCount];
	        vertexCount = variables.length;
	        positionCount = variables[0].length;
	        variableCount = vertexCount * positionCount;
	        initVariables();
	        clauses = new ArrayList<>();
	        computeSat();
	    }

	    /**
	     * Storing the value in (vertex, pos) to output
	     */
	    private void initVariables(){
	        int counter = 1;
	        for (int vCount = 0; vCount < vertexCount; vCount++){
	            for (int pCount = 0; pCount < positionCount; pCount++){
	                variables[vCount][pCount] = counter++;
	            }
	        }
	    }

	    /**
	     * Routine to add clauses with the following constraint
	     * (only one value from the values array can be true)
	     *
	     * @param values
	     */
	    private void addExactlyOne(Integer[] values){
	        ArrayList<Integer> list = new ArrayList<>();
	        clauses.add(new ArrayList<Integer>(Arrays.asList(values)));
	        //negation of each combination of the variables (nchoose2)
	        for (int i=0; i < values.length ; i++){
	            for (int j=i+1; j < values.length; j++){
	                ArrayList<Integer> clause = new ArrayList<Integer>();
	                int firstNo = values[i];
	                int secondNo = values[j];
	                clause.add(firstNo*-1);
	                clause.add(secondNo*-1);
	                clauses.add(clause);
	            }
	        }
	    }


	    /**
	     * Add clause for the following constraint
	     * one vertex in each position in hamilPath
	     */
	    private void addVertexVisitConstraint(){

	        for (int vertex=0; vertex < vertexCount; vertex++){
	            Integer[] pos = new Integer[variables.length];
	            for (int position =0; position < positionCount; position++){
	                pos[position] = variables[position][vertex];
	            }
	            addExactlyOne(pos);
	        }
	    }

	    /**
	     * Add clause for the following constraint
	     * vertex should be visited only once in hamilPath
	     */
	    private void addVertexPositionConstraint(){
	        for (int vertex=0; vertex < vertexCount; vertex++){
	            addExactlyOne(variables[vertex]);
	        }
	    }

	    /**
	     * Add clause for the following constraint
	     * vertices not sharing an edge should not be part of successive positions in hamilPath
	     */
	    private void addVertexNonEdgeConstraint(){
	        for (int i=0; i < g.nonEdges.size(); i++){
	            Edge edge = g.nonEdges.get(i);
	            int vertex1 = edge.from;
	            int vertex2 = edge.to;
	            for (int pCount =0; pCount < positionCount-1; pCount++){
	                ArrayList<Integer> values = new ArrayList<>();
	                values.add((variables[vertex1][pCount] * -1));
	                values.add((variables[vertex2][pCount+1] * -1));
	                clauses.add(values);
	                values = new ArrayList<>();
	                values.add((variables[vertex1][pCount+1] * -1));
	                values.add((variables[vertex2][pCount] * -1));
	                clauses.add(values);
	            }

	        }
	    }


	    private void computeSat(){
	        //add clause for one vertex in each position in path
	        addVertexVisitConstraint();
	        //add clause for each vertex must be visited only once/ all vertices must be on path
	        addVertexPositionConstraint();
	        //add clause for every edge in graph to satisfy constraint of vertices not belonging to edge not part of successive positions
	        addVertexNonEdgeConstraint();
	    }
	}
	
    private final InputReader reader;
    private final OutputWriter writer;

    public CleaningApt(InputReader reader, OutputWriter writer) {
        this.reader = reader;
        this.writer = writer;
    }

    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        OutputWriter writer = new OutputWriter(System.out);
        new CleaningApt(reader, writer).run();
        writer.writer.flush();
    }

    public void run() {
        int n = reader.nextInt();
        int m = reader.nextInt();
        Graph g = new Graph(n, m);

        for (int i = 0; i < m; ++i) {
            g.addEdge(reader.nextInt()-1, reader.nextInt()-1);
        }

        ConvertHamilPathToSat sat = new ConvertHamilPathToSat(g);
        writer.printf("%d %d\n",sat.clauses.size(), sat.variableCount);
        for (int i=0; i < sat.clauses.size(); i++) {
            ArrayList<Integer> clause = sat.clauses.get(i);
            for (int j =0; j < clause.size(); j++) {
                writer.printf("%d ", clause.get(j));
            }
            writer.printf("%d\n",0);

        }
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    static class OutputWriter {
        public PrintWriter writer;

        OutputWriter(OutputStream stream) {
            writer = new PrintWriter(stream);
        }

        public void printf(String format, Object... args) {
            writer.print(String.format(Locale.ENGLISH, format, args));
        }
    }
}







