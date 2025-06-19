void switchTo(const string& target) {
    string targetHead = readBranchHead(target);
    if (targetHead != "null") {
        ofstream(CURRENT_BRANCH_FILE) << target;
        ifstream snapshot(SNAPSHOT_DIR + "/" + targetHead);
        string line;
        while (getline(snapshot, line)) {
            if (line.find(":") != string::npos && line.find("msg:") != 0 &&
                line.find("time:") != 0 && line.find("base:") != 0 && line.find("branch:") != 0) {
                size_t delim = line.find(":");
                string filename = line.substr(0, delim);
                string hash = line.substr(delim + 1);
                ifstream blob(BLOB_DIR + "/" + hash);
                ofstream outFile(filename);
                outFile << blob.rdbuf();
            }
        }
        cout << "Now on branch: " << target << endl;
        return;
    }
    if (fs::exists(SNAPSHOT_DIR + "/" + target)) {
        ifstream snapshot(SNAPSHOT_DIR + "/" + target);
        string line;
        while (getline(snapshot, line)) {
            if (line.find(":") != string::npos && line.find("msg:") != 0 &&
                line.find("time:") != 0 && line.find("base:") != 0 && line.find("branch:") != 0) {
                size_t delim = line.find(":");
                string filename = line.substr(0, delim);
                string hash = line.substr(delim + 1);
                ifstream blob(BLOB_DIR + "/" + hash);
                ofstream outFile(filename);
                outFile << blob.rdbuf();
            }
        }
        cout << "Checked out commit: " << target << endl;
    } else {
        cout << "Invalid branch or commit: " << target << endl;
    }
}
