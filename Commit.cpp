void makeCommit(const string& note) {
    ifstream stageIn(STAGING_FILE);
    if (!stageIn) {
        cout << "Nothing to commit." << endl;
        return;
    }
    stringstream content;
    string item;
    while (getline(stageIn, item)) {
        content << item << endl;
    }
    string time = currentTimestamp();
    string branch = getActiveBranch();
    string parent = readBranchHead(branch);
    string meta = "msg: " + note + "\n" + "time: " + time + "base: " + parent + "\n" + "branch: " + branch + "\n";
    string hashVal = generateHash(meta + content.str());
    ofstream snapOut(SNAPSHOT_DIR + "/" + hashVal);
    snapOut << meta << content.str();
    updateHead(branch, hashVal);
    ofstream(STAGING_FILE); // clears stage
    cout << "Commit done. ID: " << hashVal << endl;
}