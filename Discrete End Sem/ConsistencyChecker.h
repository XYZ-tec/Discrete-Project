#pragma once
#ifndef CONSISTENCY_CHECKER_H
#define CONSISTENCY_CHECKER_H
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
using namespace std;
class ConsistencyChecker
{
private:
    int dfsDepth(const string& node,
        const map<string, vector<string>>& prerequisites,
        map<string, int>& memo,
        map<string, int>& visiting);
public:
    ConsistencyChecker();

    bool checkMissingPrerequisites(
        const map<string, vector<string>>& prerequisites,
        const map<string, set<string>>& studentCourses
    );

    bool checkCourseOverlaps(
        const map<string, pair<int, int>>& courseTimes,
        const set<string>& courses
    );

    bool checkStudentOverload(
        const map<string, int>& courseCredits,
        const map<string, set<string>>& studentCourses,
        int maxCredits
    );

    bool detectCircularPrerequisites(
        const map<string, vector<string>>& prerequisites
    );

    bool detectDuplicateCourseAssignments(
        const map<string, set<string>>& facultyCourses,
        const map<string, set<string>>& roomCourses
    );

    bool validateStudentScheduleConflicts(
        const map<string, pair<int, int>>& courseTimes,
        const map<string, set<string>>& studentCourses
    );

    bool checkFacultyCourseOverload(
        const map<string, set<string>>& facultyCourses,
        const map<string, int>& courseCredits,
        int maxCredits
    );

    bool checkRoomDoubleBooking(
        const map<string, pair<int, int>>& courseTimes,
        const map<string, string>& courseRoom
    );

    bool verifyRelationConsistency(
        const map<string, set<string>>& relation,
        const set<string>& codomain,
        bool& isFunction,
        bool& isInjective,
        bool& isSurjective
    );

    bool checkEquivalentCoursesConsistency(
        const vector< set<string> >& groups,
        const map<string, vector<string>>& prerequisites,
        const map<string, pair<int, int>>& courseTimes
    );

    set<string> detectUnreachableCourses(
        const map<string, vector<string>>& prerequisites
    );

    bool validateLogicRules(
        const vector< pair<string, string> >& rules,
        const set<string>& currentState
    );

    bool checkPrerequisiteDepthLimit(
        const map<string, vector<string>>& prerequisites,
        int limit
    );

    int countCycles(const map<string, vector<string>>& prerequisites);

};

#endif

