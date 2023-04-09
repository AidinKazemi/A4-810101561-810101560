#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MONTH_DAYS = 30;

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
    int get_id() { return id; };
    int calculate_salary(int total_working_hour);
    int calculate_tax_amount(int total_working_hour);
    int calculate_bouns_amount(int total_working_hour);
    int calculate_total_earning(int total_working_hour);

private:
    int id;
    string name;
    int age;
    string level;
    Team *employee_team;
    Salary_config *employee_salary_config;
};

class Working_hour
{
public:
    int get_employee_id() { return employee_id; };
    int get_day() { return day; };
    int get_start() { return start; };
    int get_end() { return end; };
    int get_numeric_working_interval() { return end - start; };

private:
    int employee_id;
    int day;
    int start;
    int end;
};

class Team
{
public:
    int get_id() { return team_id; };
    int get_bouns() { return bouns; };
    int calculate_team_totalWH(vector<Working_hour> &whs);
    int calculate_team_average_totalWH(vector<Working_hour> &whs);

private:
    int team_id;
    int team_lead_id;
    vector<int> member_ids;
    int bouns;
    int bonus_min_working_hours;
    int bonus_working_hours_max_variance;
};

class Salary_config
{
public:
    string get_level() { return level; };
    int get_base_salary() { return base_salary; };
    int get_salary_per_hour() { return salary_per_hour; };
    int get_salary_per_extra_hour() { return salary_per_extra_hour; };
    int get_official_working_hours() { return official_working_hours; };
    int get_tax_percentage() { return tax_percentage; }

private:
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};

int Employee::calculate_salary(int total_working_hour)
{
    int salary;
    int base_salary = employee_salary_config->get_base_salary();
    int official_working_hours = employee_salary_config->get_official_working_hours();
    int salary_per_hour = employee_salary_config->get_salary_per_hour();
    int salary_per_extra_hour = employee_salary_config->get_salary_per_extra_hour();
    if (total_working_hour > official_working_hours)
        return official_working_hours * salary_per_hour + (total_working_hour - official_working_hours) * salary_per_extra_hour;
    else
    {
        salary = total_working_hour * salary_per_hour;
        if (salary > base_salary)
            return salary;
        else
            return base_salary;
    }
};
int Employee::calculate_tax_amount(int total_working_hour)
{
    return this->calculate_salary(total_working_hour) * this->employee_team->get_bouns() / 100;
};
int Employee::calculate_bouns_amount(int total_working_hour)
{
    return this->calculate_salary(total_working_hour) * this->employee_salary_config->get_tax_percentage() / 100;
};
int Employee::calculate_total_earning(int total_working_hour)
{
    return this->calculate_salary(total_working_hour) - this->calculate_tax_amount(total_working_hour) + calculate_bouns_amount(total_working_hour);
};
Employee *find_employee_by_id(vector<Employee> &employees, int id)
{
    for (Employee e : employees)
        if (e.get_id() == id)
            return &e;
}
Team *find_team_by_id(vector<Team> &teams, int id)
{
    for (Team t : teams)
        if (t.get_id() == id)
            return &t;
}
Salary_config *find_salaryconfig_by_level(vector<Salary_config> &salary_configs, string level)
{
    for (Salary_config s : salary_configs)
        if (s.get_level() == level)
            return &s;
}
vector<int> find_workinghours_by_employee_id_and_day(vector<Working_hour> &whs, int employee_id, int day)
{
    vector<int> v;
    for (int i = 0; i < whs.size(); i++)
        if ((whs[i].get_employee_id() == employee_id) && (whs[i].get_day() == day))
            v.push_back(i);
    return v;
}
int calculate_sum_of_WH_per_employee(vector<Working_hour> &whs, int employee_id)
{
    int sum = 0;
    for (Working_hour wh : whs)
        if (wh.get_employee_id() == employee_id)
            sum += wh.get_numeric_working_interval();
    return sum;
}
int calculate_sum_of_WH_per_day(vector<Working_hour> &whs, int day)
{
    int sum = 0;
    for (Working_hour wh : whs)
        if (wh.get_day() == day)
            sum += wh.get_numeric_working_interval();
    return sum;
}
int calculate_sum_of_WH_per_hour(vector<Working_hour> &whs, int start_of_period)
{
    int sum = 0;
    for (Working_hour wh : whs)
        if ((wh.get_start() <= start_of_period) && (wh.get_end() >= start_of_period + 1))
            sum++;
    return sum;
}
int calculate_absent_days_per_employee(vector<Working_hour> &whs, int employee_id)
{
    int present_days = 0;
    for (int d = 0; d < MONTH_DAYS; d++)
        if (find_workinghours_by_employee_id_and_day(whs, employee_id, d).size() > 0)
            present_days++;
    return MONTH_DAYS - present_days;
}
int Team::calculate_team_totalWH(vector<Working_hour> &whs)
{
    int sum = 0;
    for (int id : member_ids)
        sum += calculate_sum_of_WH_per_employee(whs, id);
    return sum;
}
int Team::calculate_team_average_totalWH(vector<Working_hour> &whs)
{
    return this->calculate_team_totalWH(whs) / member_ids.size();
}