#include "ConsistencyChecker.h"
#include <stack>
#include <queue>
#include <limits>

ConsistencyChecker::ConsistencyChecker() {}

bool ConsistencyChecker::checkMissingPrerequisites(
    const map<string, vector<string>>& prerequisites,
    const map<string, set<string>>& studentCourses
)
{
    for (auto const& sc : studentCourses)
    {
        for (auto const& c : sc.second)
        {
            if (prerequisites.count(c))
            {
                const vector<string>& req = prerequisites.at(c);
                for (size_t i = 0; i < req.size(); ++i)
                {
                    if (sc.second.find(req[i]) == sc.second.end())
                        return false;
                }
            }
        }
    }
    return true;
}

bool ConsistencyChecker::checkCourseOverlaps(
    const map<string, pair<int, int>>& courseTimes,
    const set<string>& courses
)
{
    vector<string> v;
    for (auto const& c : courses) v.push_back(c);

    for (size_t i = 0; i < v.size(); ++i)
    {
        for (size_t j = i + 1; j < v.size(); ++j)
        {
            pair<int, int> t1 = courseTimes.at(v[i]);
            pair<int, int> t2 = courseTimes.at(v[j]);
            bool overlap = !(t1.second <= t2.first || t2.second <= t1.first);
            if (overlap) return false;
        }
    }
    return true;
}

bool ConsistencyChecker::checkStudentOverload(
    const map<string, int>& courseCredits,
    const map<string, set<string>>& studentCourses,
    int maxCredits
)
{
    for (auto const& s : studentCourses)
    {
        int total = 0;
        for (auto const& c : s.second) total += courseCredits.at(c);
        if (total > maxCredits) return false;
    }
    return true;
}

bool ConsistencyChecker::detectCircularPrerequisites(
    const map<string, vector<string>>& prerequisites
)
{
    map<string, int> state;
    for (auto const& p : prerequisites) state[p.first] = 0;

    for (auto const& p : prerequisites)
    {
        const string& node = p.first;
        if (state[node] != 0) continue;

        stack<string> st;
        st.push(node);

        while (!st.empty())
        {
            string cur = st.top();

            if (state[cur] == 0)
            {
                state[cur] = 1;
                if (prerequisites.count(cur))
                {
                    const vector<string>& nbrs = prerequisites.at(cur);
                    for (size_t i = 0; i < nbrs.size(); ++i)
                    {
                        const string& nb = nbrs[i];
                        if (!state.count(nb)) state[nb] = 0;
                        if (state[nb] == 1) return true;
                        if (state[nb] == 0) st.push(nb);
                    }
                }
            }
            else
            {
                st.pop();
                state[cur] = 2;
            }
        }
    }
    return false;
}

bool ConsistencyChecker::detectDuplicateCourseAssignments(
    const map<string, set<string>>& facultyCourses,
    const map<string, set<string>>& roomCourses
)
{
    map<string, int> count;

    for (auto const& f : facultyCourses)
        for (auto const& c : f.second) count[c]++;

    for (auto const& kv : count)
        if (kv.second > 1) return false;

    count.clear();

    for (auto const& r : roomCourses)
        for (auto const& c : r.second) count[c]++;

    for (auto const& kv : count)
        if (kv.second > 1) return false;

    return true;
}

bool ConsistencyChecker::validateStudentScheduleConflicts(
    const map<string, pair<int, int>>& courseTimes,
    const map<string, set<string>>& studentCourses
)
{
    for (auto const& s : studentCourses)
    {
        vector<string> v;
        for (auto const& c : s.second) v.push_back(c);

        for (size_t i = 0; i < v.size(); ++i)
        {
            for (size_t j = i + 1; j < v.size(); ++j)
            {
                pair<int, int> t1 = courseTimes.at(v[i]);
                pair<int, int> t2 = courseTimes.at(v[j]);
                bool overlap = !(t1.second <= t2.first || t2.second <= t1.first);
                if (overlap) return false;
            }
        }
    }
    return true;
}

bool ConsistencyChecker::checkFacultyCourseOverload(
    const map<string, set<string>>& facultyCourses,
    const map<string, int>& courseCredits,
    int maxCredits
)
{
    for (auto const& f : facultyCourses)
    {
        int total = 0;
        for (auto const& c : f.second) total += courseCredits.at(c);
        if (total > maxCredits) return false;
    }
    return true;
}

bool ConsistencyChecker::checkRoomDoubleBooking(
    const map<string, pair<int, int>>& courseTimes,
    const map<string, string>& courseRoom
)
{
    map<string, vector<string>> roomMap;

    for (auto const& cr : courseRoom)
        roomMap[cr.second].push_back(cr.first);

    for (auto const& r : roomMap)
    {
        const vector<string>& v = r.second;

        for (size_t i = 0; i < v.size(); ++i)
        {
            for (size_t j = i + 1; j < v.size(); ++j)
            {
                pair<int, int> t1 = courseTimes.at(v[i]);
                pair<int, int> t2 = courseTimes.at(v[j]);
                bool overlap = !(t1.second <= t2.first || t2.second <= t1.first);
                if (overlap) return false;
            }
        }
    }

    return true;
}

bool ConsistencyChecker::verifyRelationConsistency(
    const map<string, set<string>>& relation,
    const set<string>& codomain,
    bool& isFunction,
    bool& isInjective,
    bool& isSurjective
)
{
    isFunction = true;
    for (auto const& kv : relation)
        if (kv.second.size() != 1) { isFunction = false; break; }

    map<string, int> count;
    for (auto const& kv : relation)
        for (auto const& v : kv.second) count[v]++;

    isInjective = true;
    for (auto const& kv : count)
        if (kv.second > 1) { isInjective = false; break; }

    isSurjective = true;
    for (auto const& c : codomain)
        if (!count.count(c)) { isSurjective = false; break; }

    return isFunction && isInjective && isSurjective;
}

bool ConsistencyChecker::checkEquivalentCoursesConsistency(
    const vector< set<string> >& groups,
    const map<string, vector<string>>& prerequisites,
    const map<string, pair<int, int>>& courseTimes
)
{
    for (auto const& group : groups)
    {
        for (auto const& c : group)
        {
            if (prerequisites.count(c))
            {
                const vector<string>& req = prerequisites.at(c);
                for (auto const& r : req)
                    if (group.count(r)) return false;
            }
        }

        vector<string> v;
        for (auto const& c : group) v.push_back(c);

        for (size_t i = 0; i < v.size(); ++i)
        {
            for (size_t j = i + 1; j < v.size(); ++j)
            {
                pair<int, int> t1 = courseTimes.at(v[i]);
                pair<int, int> t2 = courseTimes.at(v[j]);
                bool overlap = !(t1.second <= t2.first || t2.second <= t1.first);
                if (overlap) return false;
            }
        }
    }
    return true;
}

set<string> ConsistencyChecker::detectUnreachableCourses(
    const map<string, vector<string>>& prerequisites
)
{
    map<string, vector<string>> adj;
    map<string, int> indeg;

    for (auto const& kv : prerequisites)
    {
        const string& c = kv.first;
        if (!indeg.count(c)) indeg[c] = 0;

        for (auto const& p : kv.second)
        {
            adj[p].push_back(c);
            if (!indeg.count(p)) indeg[p] = 0;
            indeg[c]++;
        }
    }

    queue<string> q;
    for (auto const& kv : indeg)
        if (kv.second == 0) q.push(kv.first);

    while (!q.empty())
    {
        string cur = q.front(); q.pop();

        if (adj.count(cur))
        {
            for (auto const& nxt : adj.at(cur))
            {
                indeg[nxt]--;
                if (indeg[nxt] == 0) q.push(nxt);
            }
        }
    }

    set<string> unreachable;
    for (auto const& kv : indeg)
        if (kv.second != 0) unreachable.insert(kv.first);

    return unreachable;
}

bool ConsistencyChecker::validateLogicRules(
    const vector< pair<string, string> >& rules,
    const set<string>& currentState
)
{
    for (auto const& r : rules)
    {
        if (currentState.count(r.first))
            if (!currentState.count(r.second))
                return false;
    }
    return true;
}

int ConsistencyChecker::dfsDepth(
    const string& node,
    const map<string, vector<string>>& prerequisites,
    map<string, int>& memo,
    map<string, int>& visiting
)
{
    if (memo.count(node)) return memo[node];
    if (visiting[node] == 1) return numeric_limits<int>::max() / 4;

    visiting[node] = 1;
    int best = 0;

    if (prerequisites.count(node))
    {
        const vector<string>& req = prerequisites.at(node);
        for (size_t i = 0; i < req.size(); ++i)
        {
            int d = dfsDepth(req[i], prerequisites, memo, visiting);
            if (d > best) best = d;
        }
    }

    visiting[node] = 2;
    memo[node] = best + 1;
    return memo[node];
}

bool ConsistencyChecker::checkPrerequisiteDepthLimit(
    const map<string, vector<string>>& prerequisites,
    int limit
)
{
    map<string, int> memo;
    map<string, int> visiting;

    for (auto const& kv : prerequisites)
    {
        int d = dfsDepth(kv.first, prerequisites, memo, visiting);
        if (d > limit) return false;
    }

    return true;
}

int ConsistencyChecker::countCycles(const map<string, vector<string>>& prerequisites)
{
    int cycleCount = 0;
    map<string, int> state;

    // Initialize
    for (map<string, vector<string>>::const_iterator it = prerequisites.begin();
        it != prerequisites.end(); ++it) {
        state[it->first] = 0;
    }

    // Simple DFS to detect cycles
    stack<string> st;

    for (map<string, vector<string>>::const_iterator it = prerequisites.begin();
        it != prerequisites.end(); ++it) {

        const string& startNode = it->first;

        if (state[startNode] != 0) continue;

        st.push(startNode);

        while (!st.empty()) {
            string cur = st.top();

            if (state[cur] == 0) {
                state[cur] = 1;

                if (prerequisites.count(cur)) {
                    const vector<string>& neighbors = prerequisites.at(cur);

                    for (size_t i = 0; i < neighbors.size(); i++) {
                        const string& neighbor = neighbors[i];

                        if (!state.count(neighbor)) {
                            state[neighbor] = 0;
                        }

                        if (state[neighbor] == 1) {
                            cycleCount++;
                        }

                        if (state[neighbor] == 0) {
                            st.push(neighbor);
                        }
                    }
                }
            }
            else {
                st.pop();
                state[cur] = 2;
            }
        }
    }

    return cycleCount;
}