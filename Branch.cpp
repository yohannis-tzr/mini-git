void forkBranch(const string& newBranch) {
    // Check if branch already exists
    if (branchExists(newBranch)) {
        cout << "Branch already exists!" << endl;
        return;
    }

    string head = readBranchHead(getActiveBranch());
    ofstream out(BRANCHES_MAP, ios::app);
    out << newBranch << ":" << head << "\n";
    cout << "Branch created: " << newBranch << endl;
}

}
