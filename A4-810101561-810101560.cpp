#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Employee;
class Working_hour;
class Team;
class Salary_config;

class Salary_calculator
{
private:
    vector<Employee> all_employees;
    vector<Team> all_teams;
    vector<Salary_config> all_salary_configs;
    vector<Working_hour> all_working_hours;
};

class Employee
{
private:
    long id;
    string name;
    int age;
    string level;
};

class Working_hour
{
private:
    long employee_id;
    int day;
    string working_interval;
};

class Team
{
private:
    int team_id;
    int team_lead_id;
    string member_ids;
    int bonus_min_working_hours;
    int bonus_working_hours_max_variance;
};

class Salary_config
{
private:
    string level;
    int base_salray;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};
