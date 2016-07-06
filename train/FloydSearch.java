
/***************************************
 * file name:   FloydSearch.java
 * description:
 * author:      kari.zhang
 **************************************/

public class FloydSearch implements Searchable {

    private int[][] mResultData;

    @Override
    public Graph search(Graph graph) {
        if (null == graph || !graph.checkValid()) {
            return null;
        }
        initResultData(graph);
        floydSearch();
        return new Graph(mResultData);
    }

    private void initResultData(final Graph graph) {
        int[][] data = graph.getEdgeInfo();
        mResultData = new int[data.length][data.length];
        for (int i = 0; i < data.length; i++) {
            mResultData[i] = new int[data.length];
            System.arraycopy(data[i], 0, mResultData[i], 0, data.length);
        }
    }

    private void floydSearch() {
        int N = mResultData.length;
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (mResultData[i][j] > mResultData[i][k] + mResultData[k][j]) {
                        mResultData[i][j] = mResultData[i][k] + mResultData[k][j];
                    }
                }
            }
        }
    }

}
