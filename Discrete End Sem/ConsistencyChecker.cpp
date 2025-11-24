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
        for (auto const& c : s.second)
            total += courseCredits.at(c);
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
        vector<string> trace;
        while (!st.empty())
        {
            string cur = st.top();
            if (state[cur] == 0)
            {
                state[cur] = 1;
                trace.push_back(cur);
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
    {
        for (auto const& c : f.second) count[c] += 1;
    }
    for (auto const& kv : count) if (kv.second > 1) return false;
    count.clear();
    for (auto const& r : roomCourses)
    {
        for (auto const& c : r.second) count[c] += 1;
    }
    for (auto const& kv : count) if (kv.second > 1) return false;
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
    for (auto const& cr : courseRoom) roomMap[cr.second].push_back(cr.first);
    for (auto const& r : roomMap)
    {
        const vector<string>& courses = r.second;
        for (size_t i = 0; i < courses.size(); ++i)
        {
            for (size_t j = i + 1; j < courses.size(); ++j)
            {
                pair<int, int> t1 = courseTimes.at(courses[i]);
                pair<int, int> t2 = courseTimes.at(courses[j]);
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
    for (auto const& kv : relation) if (kv.second.size() != 1) { isFunction = false; break; }
    map<string, int> valueCount;
    for (auto const& kv : relation)
    {
        for (auto const& v : kv.second) valueCount[v] += 1;
    }
    isInjective = true;
    for (auto const& kv : valueCount) if (kv.second > 1) { isInjective = false; break; }
    isSurjective = true;
    for (auto const& val : codomain) if (valueCount.find(val) == valueCount.end()) { isSurjective = false; break; }
    return isFunction && isInjective && isSurjective;
}

bool ConsistencyChecker::checkEquivalentCoursesConsistency(
    const vector< set<string> >& groups,
    const map<string, vector<string>>& prerequisites,
    const map<string, pair<int, int>>& courseTimes
)
{
    for (size_t g = 0; g < groups.size(); ++g)
    {
        const set<string>& group = groups[g];
        for (auto const& course : group)
        {
            if (prerequisites.count(course))
            {
                const vector<string>& req = prerequisites.at(course);
                for (size_t i = 0; i < req.size(); ++i)
                {
                    if (group.find(req[i]) != group.end()) return false;
                }
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
        const string& course = kv.first;
        if (!indeg.count(course)) indeg[course] = 0;
        const vector<string>& reqs = kv.second;
        for (size_t i = 0; i < reqs.size(); ++i)
        {
            const string& p = reqs[i];
            adj[p].push_back(course);
            if (!indeg.count(p)) indeg[p] = 0;
            indeg[course] += 1;
        }
    }
    queue<string> q;
    for (auto const& kv : indeg) if (kv.second == 0) q.push(kv.first);
    int processed = 0;
    set<string> all;
    for (auto const& kv : indeg) all.insert(kv.first);
    while (!q.empty())
    {
        string cur = q.front(); q.pop();
        processed++;
        if (adj.count(cur))
        {
            const vector<string>& nbrs = adj.at(cur);
            for (size_t i = 0; i < nbrs.size(); ++i)
            {
                indeg[nbrs[i]] -= 1;
                if (indeg[nbrs[i]] == 0) q.push(nbrs[i]);
            }
        }
    }
    set<string> unreachable;
    for (auto const& kv : indeg) if (kv.second != 0) unreachable.insert(kv.first);
    return unreachable;
}

bool ConsistencyChecker::validateLogicRules(
    const vector< pair<string, string> >& rules,
    const set<string>& currentState
)
{
    for (size_t i = 0; i < rules.size(); ++i)
    {
        const pair<string, string>& r = rules[i];
        if (currentState.find(r.first) != currentState.end())
        {
            if (currentState.find(r.second) == currentState.end()) return false;
        }
    }
    return true;
}

bool ConsistencyChecker::checkPrerequisiteDepthLimit(
    const map<string, vector<string>>& prerequisites,
    int limit
)
{
    map<string, int> memo;
    map<string, int> visiting;
    function<int(const string&)> dfs = [&](const string& node) -> int {
        if (memo.count(node)) return memo[node];
        if (visiting[node] == 1) return numeric_limits<int>::max() / 4;
        visiting[node] = 1;
        int best = 0;
        if (prerequisites.count(node))
        {
            const vector<string>& req = prerequisites.at(node);
            for (size_t i = 0; i < req.size(); ++i)
            {
                int d = dfs(req[i]);
                if (d > best) best = d;
            }
        }
        visiting[node] = 2;
        memo[node] = best + 1;
        return memo[node];
        };
    for (auto const& kv : prerequisites)
    {
        int depth = dfs(kv.first);
        if (depth > limit) return false;
    }
    return true;
}
