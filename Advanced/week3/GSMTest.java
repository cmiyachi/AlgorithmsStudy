
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Locale;
import java.util.StringTokenizer;

//import GSMTest.InputReader;
//import GSMTest.OutputWriter;


public class GSMTest {
	class ConvertVertexColorToSat {

	    int colorCount = 3;
	    int vertexCount ;
	    ArrayList<ArrayList<Integer>> clauses;
	    int variableCount;
	    Graph g;
	    Integer[][] variables; // 2d array in which i->vertex, j->color

	    ConvertVertexColorToSat(Graph g) {
	        this.g = g;
	        vertexCount = g.vertexCount;
	        variableCount = g.vertexCount * colorCount;
	        clauses = new ArrayList<>();
	        //vertex coloring with each vertex having 3 colors
	        variables = new Integer[g.vertexCount][colorCount];
	        initVariables();
	        computeSat();
	    }

	    /**
	     * Storing the value in (vertex, color) to output
	     */
	    private void initVariables(){
	        int counter = 1;
	        for (int vCount = 0; vCount < vertexCount; vCount++){
	            for (int cCount = 0; cCount < colorCount; cCount++){
	                variables[vCount][cCount] = counter++;
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
	     * vertex should be of some color
	     */
	    private void addVertexColorConstraint(){
	        for (int vertex=0; vertex < vertexCount; vertex++){
	            addExactlyOne(variables[vertex]);
	        }
	    }

	    /**
	     * add clause for following constraint
	     * no two edges belong to same color
	     */
	    private void addVertexEdgeConstraint(){
	        for (int i=0; i < g.edgeCount; i++){
	            Edge edge = g.edges[i];
	            int vertex1 = edge.from;
	            int vertex2 = edge.to;
	            for (int color = 0; color < colorCount; color++){
	                ArrayList<Integer> list = new ArrayList<>();
	                list.add(variables[vertex1][color] * -1);
	                list.add(variables[vertex2][color] * -1);
	                clauses.add(list);
	            }
	        }
	    }



	    private void computeSat(){
	        //add clause for every vertex in graph belonging to some color
	        addVertexColorConstraint();
	        //add clause for every edge in graph to satisfy constraint no two edges belong to same color
	        addVertexEdgeConstraint();
	    }
	}

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
	
	   private final InputReader reader;
	    private final OutputWriter writer;

	    public GSMTest(InputReader reader, OutputWriter writer) {
	        this.reader = reader;
	        this.writer = writer;
	    }

	    public static void main(String[] args) {
	        InputReader reader = new InputReader(System.in);
	        OutputWriter writer = new OutputWriter(System.out);
	        new GSMTest(reader, writer).run();
	        writer.writer.flush();
	    }

	    public void run() {
	        int n = reader.nextInt();
	        int m = reader.nextInt();
	        Graph g = new Graph(n, m);

	        for (int i = 0; i < m; ++i) {
	            g.addEdge(reader.nextInt()-1, reader.nextInt()-1);
	        }

	        ConvertVertexColorToSat sat = new ConvertVertexColorToSat(g);
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
