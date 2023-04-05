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
public:
    int count_extra_working_hour();
    int count_salary();
    int a(int){return 0;};

private:
    long id;
    string name;
    int age;
    string level;
    vector<Working_hour *> employee_working_periods;
    Salary_config *employee_salary_config;
};

class Working_hour
{
public:
    int get_numeric_working_interval();

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
public:
    int get_official_working_hours() { return official_working_hours; };
    int get_salary_per_hour() { return salary_per_hour; };
    int get_salary_per_extra_hour() { return salary_per_extra_hour; };

private:
    string level;
    int base_salray;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};

int Working_hour::get_numeric_working_interval()
{
    int start, end;
    start = stoi(working_interval.substr(0, working_interval.find('-')));
    end = stoi(working_interval.substr(working_interval.find('-') + 1));
    return end - start;
};

int Employee::count_extra_working_hour()
{
    a(age);
    age = 4;
    int total_working_hours = 0;
    for (int i = 0; i < employee_working_periods.size(); i++)
        total_working_hours += employee_working_periods[i]->get_numeric_working_interval();
    int official_working_hours = employee_salary_config->get_official_working_hours();    
    return total_working_hours - official_working_hours;
}

int Employee::count_salary()
{
    int extra_working_hours = this->count_extra_working_hour();
    int official_working_hours = employee_salary_config->get_official_working_hours();
    int salary_per_hour = employee_salary_config->get_salary_per_hour();

    if (extra_working_hours > 0)
        return official_working_hours * salary_per_hour + extra_working_hours * salary_per_hour;
    else
        return (extra_working_hours + official_working_hours) * salary_per_hour;
};
