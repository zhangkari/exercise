
/**********************************************
 * file name:	Graph.java
 * description:
 * author:		kari.zhang
 *********************************************/

public class Graph {

    // limit mEdge is not too large
    private final static int MAX_VERTEX_CNT = 100;

    // limit the weight is not too large

    protected int[][] mEdgeInfo;

    public Graph(int[][] info) {
        setEdgeInfo(info);
    }

    /**
     * @param info must be a square matrix and must not be null
     */
    public void setEdgeInfo(int[][] info) {
        if (null != mEdgeInfo) {
            throw new IllegalArgumentException("edge info has already set");
        }

        if (!checkValidImpl(info)) {
            throw new IllegalArgumentException("argument is invalid");
        }

        mEdgeInfo = new int[info.length][info.length];
        for (int i = 0; i < info.length; i++) {
            mEdgeInfo[i] = new int[info.length];
            System.arraycopy(info[i], 0, mEdgeInfo[i], 0, info.length);
        }
    }

    protected boolean checkValidImpl(int[][] info) {
        if (null == info ||
                info.length < 1 ||
                info.length > MAX_VERTEX_CNT) {

            return false;
        }

        for (int i = 0; i < info.length; i++) {
            if (info[i] == null || info[i].length != info.length) {
                return false;
            }
        }

        return true;
    }

    public boolean checkValid() {
        return checkValidImpl(mEdgeInfo);
    }

    public void reset() {
        mEdgeInfo = null;
    }

    public int[][] getEdgeInfo() {
        return mEdgeInfo;
    }

    /**
     *
     * @param from
     * @param to
     * @return -1 means unreachable
     */
    public int getShortestDistance(int from, int to) {
        return mEdgeInfo[from][to];
    }

}
