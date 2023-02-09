using System;
using System.IO;
using System.Text.Json;
using System.Collections.Generic;
using LanguageExt;
using System.Linq;

using lab1.Models.DomainModel;

namespace lab1.Models.Repositories
{
    public class RepositoryJson : IRepository
    {
        public RepositoryJson()
        {
            _initializeRepo();
        }

        public Option<User> GetUser(string login)
        {
            List<User> users = _getAllUsers();
            User user = users.Find(u => _stringEqualPredicate(u.Login, login));

            return user == null ? Option<User>.None : Option<User>.Some(user);
        }

        public List<User> GetAllUsers()
        {
            return _getAllUsers();
        }

        public Option<User> CreateUser(string login)
        {
            List<User> users = _getAllUsers();
            if (users.Exists(u => _stringEqualPredicate(u.Login, login)))
                return Option<User>.None;

            User newUser = new User(login);
            users.Add(newUser);
            string usersJson = _serializeJson(users);
            File.WriteAllText(_usersDataFile, usersJson);

            return Option<User>.Some(newUser);
        }

        public Project GetProject(string projectName)
        {
            List<Project> projects = _getAllProjects();
            Project project = projects.Find(p => _stringEqualPredicate(p.Name, projectName));

            // return project == null ? Option<Project>.None : Option<Project>.Some(project);
            return project;
        }

        public List<Project> GetAllProjects()
        {
            return _getAllProjects();
        }

        public List<Project> GetAllProjectsForOwner(string owner)
        {
            var all = _getAllProjects();
            return all.Filter(p => p.Owner == owner).ToList();
        }

        public Project CreateProject(Project project)
        {
            List<Project> projects = _getAllProjects();
            if (projects.Exists(p => _stringEqualPredicate(p.Name, project.Name)))
                return null;

            Option<User> ownerOpt = GetUser(project.Owner);
            if (ownerOpt.IsNone)
                return null;

            projects.Add(project);
            string projectsJson = _serializeJson(projects);
            File.WriteAllText(_projectsDataFile, projectsJson);

            return project;
        }

        public Project UpdateProject(Project project)
        {
            List<Project> projects = _getAllProjects();
            if (!projects.Exists(p => _stringEqualPredicate(p.Name, project.Name)))
                return null;

            Option<User> ownerOpt = GetUser(project.Owner);
            if (ownerOpt.IsNone)
                return null;

            projects.RemoveAll(p => _stringEqualPredicate(p.Name, project.Name));
            projects.Add(project);
            string projectsJson = _serializeJson(projects);
            File.WriteAllText(_projectsDataFile, projectsJson);

            return project;
        }

        public Activity GetActivity(string code)
        {
            var activities = _getAllActivities();
            return activities.Find(a => a.Code == code);
        }

        public Activity CreateActivity(Activity activity)
        {
            var executor = activity.ExecutorName;
            var date = activity.Date;
            var month = date.Month;
            var year = date.Year;

            var executorOpt = GetUser(activity.ExecutorName);
            if (executorOpt.IsNone)
                return null;

            var activitiesThisMonth = GetActivitiesForUserForMonth(executor, year, month);

            if (activitiesThisMonth.Exists(a => _stringEqualPredicate(a.Code, activity.Code)))
                return null;

            activitiesThisMonth.Add(activity);
            string activitiesJson = _serializeJson(activitiesThisMonth);
            var fileName = _prepareActivityFileName(executor, year, month);
            File.WriteAllText(fileName, activitiesJson);

            return activity;
        }

        public Activity UpdateActivity(Activity activity)
        {
            var executor = activity.ExecutorName;
            var date = activity.Date;
            var month = date.Month;
            var year = date.Year;

            var executorOpt = GetUser(activity.ExecutorName);
            if (executorOpt.IsNone)
                return null;

            var activitiesThisMonth = GetActivitiesForUserForMonth(executor, year, month);

            if (!activitiesThisMonth.Exists(a => _stringEqualPredicate(a.Code, activity.Code)))
                return null;

            activitiesThisMonth.RemoveAll(a => a.Code == activity.Code);
            activitiesThisMonth.Add(activity);
            string activitiesJson = _serializeJson(activitiesThisMonth);
            var fileName = _prepareActivityFileName(executor, year, month);
            File.WriteAllText(fileName, activitiesJson);
            return activity;
        }

        public List<Activity> GetAllActivities()
        {
            return _getAllActivities();
        }

        public List<Activity> GetActivitiesForUserForMonth(string executor, int year, int month)
        {
            var fileName = _prepareActivityFileName(executor, year, month);
            if (!File.Exists(fileName))
                return new List<Activity>();

            string activitiesJsonString = File.ReadAllText(fileName);

            return JsonSerializer.Deserialize<List<Activity>>(activitiesJsonString);
        }

        public void DeleteActivity(string code, string executor)
        {
            DirectoryInfo dinf = new DirectoryInfo(_activitiesDataDirectory);
            var allUsersFiles = dinf.GetFiles(executor + "*");
            foreach (var file in allUsersFiles)
            {
                var fileFullName = file.FullName;
                string activitiesJsonString = File.ReadAllText(fileFullName);
                var activities = JsonSerializer.Deserialize<List<Activity>>(activitiesJsonString);
                int removed = activities.RemoveAll(a => a.Code == code);
                if (removed > 0)
                {
                    if (activities.Length() > 0)
                    {
                        var jsonWithoutRemoved = _serializeJson(activities);
                        File.WriteAllText(fileFullName, jsonWithoutRemoved);
                    }
                    else
                        File.Delete(fileFullName);

                    return;
                }

            }
            throw new Exception();
        }

        public UsersMonth GetUsersMonth(string executor, int year, int month)
        {
            var months = _getAllUsersMonths();
            return months.Find(m => m.Year == year && m.Month == month && m.UsersLogin == executor);
        }

        public UsersMonth AcceptMonthForUser(UsersMonth month)
        {
            List<UsersMonth> months = _getAllUsersMonths();
            months.Add(month);
            string monthsJson = _serializeJson(months);
            File.WriteAllText(_monthsDataFile, monthsJson);

            return month;
        }

        private List<User> _getAllUsers()
        {
            string usersJsonString = File.ReadAllText(_usersDataFile);

            return JsonSerializer.Deserialize<List<User>>(usersJsonString);
        }

        private List<Project> _getAllProjects()
        {
            string projectsJsonString = File.ReadAllText(_projectsDataFile);

            return JsonSerializer.Deserialize<List<Project>>(projectsJsonString);
        }

        private List<Activity> _getActivitiesForUser(string login)
        {
            List<Activity> activites = new List<Activity>();
            DirectoryInfo dinf = new DirectoryInfo(_activitiesDataDirectory);
            var allUsersFiles = dinf.GetFiles(login + "*");
            foreach (var file in allUsersFiles)
            {
                string activitiesJsonString = File.ReadAllText(file.FullName);
                var newActivites = JsonSerializer.Deserialize<List<Activity>>(activitiesJsonString);
                activites.AddRange(newActivites);

            }
            return activites;
        }

        private List<Activity> _getAllActivities()
        {
            return _getActivitiesForUser(""); //if empty login is given, then all activities will be listed
        }

        private List<UsersMonth> _getAllUsersMonths()
        {
            string projectsJsonString = File.ReadAllText(_monthsDataFile);

            return JsonSerializer.Deserialize<List<UsersMonth>>(projectsJsonString);
        }

        private static void _initializeRepo()
        {
            if (!Directory.Exists(_dataDirectory))
            {
                Directory.CreateDirectory(_dataDirectory);
            }
            if (!File.Exists(_usersDataFile))
            {
                List<User> emptyUsersList = new List<User>();
                string emptyUsersListJson = _serializeJson(emptyUsersList);
                File.WriteAllText(_usersDataFile, emptyUsersListJson);
            }
            if (!File.Exists(_projectsDataFile))
            {
                List<Project> emptyProjectsList = new List<Project>();
                string emptyProjectsListJson = _serializeJson(emptyProjectsList);
                File.WriteAllText(_projectsDataFile, emptyProjectsListJson);
            }
            if (!Directory.Exists(_activitiesDataDirectory))
            {
                Directory.CreateDirectory(_activitiesDataDirectory);
            }
            if (!File.Exists(_monthsDataFile))
            {
                List<UsersMonth> emptyMonthsList = new List<UsersMonth>();
                string emptyMonthsListJson = _serializeJson(emptyMonthsList);
                File.WriteAllText(_monthsDataFile, emptyMonthsListJson);
            }
        }

        private bool _stringEqualPredicate(string first, string second)
        {
            return first == second;
        }

        private string _prepareActivityFileName(string executor, int year, int month)
        {
            var fileName = executor + "-" + year.ToString() + "-" + month.ToString() + ".json";
            return Path.Combine(_activitiesDataDirectory, fileName);
        }

        private static string _serializeJson<T>(T obj)
        {
            return JsonSerializer.Serialize(obj, _jsonOptions);
        }
        private static JsonSerializerOptions _jsonOptions = new JsonSerializerOptions { WriteIndented = true };


        private static string _dataDirectory = Path.Combine(Environment.CurrentDirectory, "Models", "data");
        private static string _usersDataFile = Path.Combine(_dataDirectory, "users.json");
        private static string _projectsDataFile = Path.Combine(_dataDirectory, "projects.json");
        private static string _activitiesDataDirectory = Path.Combine(_dataDirectory, "activities");
        private static string _monthsDataFile = Path.Combine(_dataDirectory, "months.json");
    }
}