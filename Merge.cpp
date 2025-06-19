void mergeBranch(const string& branchName) {
    string current = getActiveBranch();
    string currentHead = readBranchHead(current);
    string targetHead = readBranchHead(branchName);
    if (targetHead == "null") {
        cout << "No such branch or empty target." << endl;
        return;
    }
    ifstream tgtIn(SNAPSHOT_DIR + "/" + targetHead);
    unordered_map<string, string> mergeMap;
    string line;
    while (getline(tgtIn, line)) {
        if (line.find(":") != string::npos && line.find("msg:") != 0 &&
            line.find("time:") != 0 && line.find("base:") != 0 && line.find("branch:") != 0) {
            size_t delim = line.find(":");
            mergeMap[line.substr(0, delim)] = line.substr(delim + 1);
        }
    }
    ifstream curIn(SNAPSHOT_DIR + "/" + currentHead);
    while (getline(curIn, line)) {
        if (line.find(":") != string::npos && line.find("msg:") != 0 &&
            line.find("time:") != 0 && line.find("base:") != 0 && line.find("branch:") != 0) {
            size_t delim = line.find(":");
            string file = line.substr(0, delim);
            string hash = line.substr(delim + 1);
            if (mergeMap.find(file) != mergeMap.end() && mergeMap[file] != hash) {
                cout << "MERGE CONFLICT: " << file << endl;
            }
            mergeMap[file] = hash;
        }
    }
    ofstream newStage(STAGING_FILE);
    for (const auto& [file, hash] : mergeMap)
        newStage << file << ":" << hash << endl;
    stringstream commitMsg;
    commitMsg << "Merge from " << branchName;
    makeCommit(commitMsg.str());
}
