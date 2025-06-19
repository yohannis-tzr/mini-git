void showLog() {
    string current = readBranchHead(getActiveBranch());
    while (current != "null") {
        ifstream snapIn(SNAPSHOT_DIR + "/" + current);
        string item;
        cout << "Commit: " << current << endl;
        while (getline(snapIn, item)) {
            if (item.rfind("msg:", 0) == 0  item.rfind("time:", 0) == 0  item.rfind("base:", 0) == 0)
                cout << item << endl;
        }
        cout << "-----------------------------" << endl;
        snapIn.clear();
        snapIn.seekg(0, ios::beg);
        while (getline(snapIn, item)) {
            if (item.rfind("base:", 0) == 0) {
                current = item.substr(6);
                break;
            }
        }
    }
}