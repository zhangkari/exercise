/**
 * Created by ws-kari on 16-7-6.
 */
public interface OnSearchListener {
    void onSearchStart();
    void onSearchProgress();
    void onSearchError(Error err);
    void onSearchComplete();
}
