struct Set {
    Set *parent;
    int rank;
};
Set *CreateSet() {
    Set *s = new Set();
    s->parent = s;
    s->rank = 0;
    return s;
}
Set *GetSet(Set *set) {
    if (set->parent != set) {
        set->parent = GetSet(set->parent);
        return set->parent;
    } else {
        return set;
    }
}
bool SameSet(Set *set1, Set *set2) { return GetSet(set1) == GetSet(set2); }
void SetUnion(Set *set1, Set *set2) {
    Set *pset1 = GetSet(set1);
    Set *pset2 = GetSet(set2);
    if (pset1 != pset2) {
        if (pset1->rank > pset2->rank) {
            pset2->parent = pset1;
        } else if (pset1->rank < pset2->rank) {
            pset1->parent = pset2;
        } else {
            pset1->parent = pset2;
            pset2->rank++;
        }
    }
}