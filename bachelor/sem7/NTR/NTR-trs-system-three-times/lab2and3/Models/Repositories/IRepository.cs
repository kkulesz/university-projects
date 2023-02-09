using System.Collections.Generic;

using lab2and3.Models.DomainModel;


namespace lab2and3.Models.Repositories
{
    interface IRepository
    {
        User GetUser(string login);
        List<User> GetAllUsers();
        User CreateUser(string login);
        Project GetProject(string projectName);
        List<Project> GetAllProjects();
        List<Project> GetAllProjectsForOwner(string owner);
        Project CreateProject(Project project);
        Project UpdateProject(Project project);
        Activity GetActivity(string code);
        Activity CreateActivity(Activity activity);
        Activity UpdateActivity(Activity activity);
        List<Activity> GetAllActivities();
        List<Activity> GetActivitiesForUserForMonth(string executor, int year, int month);
        void DeleteActivity(string code, string executor);
        UsersMonth GetUsersMonth(string executor, int year, int month);
        UsersMonth AcceptMonthForUser(UsersMonth month);
    }
}