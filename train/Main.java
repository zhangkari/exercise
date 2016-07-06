public class Main {
	public static void main(String[] args) {

		int [][]data = {
			{
				0,   3,   10,  19
			},
			{
				100, 0,   2,   4
			},
			{
				9,   19,  0,   100
			},
			{
				4,   5,   9,   0
			}
		};

		Graph src = new Graph(data);
		Searchable s = new FloydSearch();
		Graph dst = s.search(src);
		if (null == dst) {
			System.out.println("search failed.\n");
			return;
		}

		int dist = dst.getShortestDistance(0, 3);
		System.out.println("<0, 3> = " + dist);
	}
}
