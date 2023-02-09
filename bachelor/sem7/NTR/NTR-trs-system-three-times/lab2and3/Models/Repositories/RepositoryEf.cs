using Microsoft.EntityFrameworkCore;
using System;
using System.Linq;
using System.Collections.Generic;

using lab2and3.Models.DomainModel;

namespace lab2and3.Models.Repositories
{
    public class RepositoryEf : IRepository
    {
        public User GetUser(string login)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                // var users = from us in ctx.Users where us.UserId == login select us;
                var users = ctx.Users.Where(ac => ac.Login == login);
                return users.Count() != 1 ? null : users.Single();
            }
        }

        public List<User> GetAllUsers()
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var users = ctx.Users;
                return users.ToList();
            }
        }

        public User CreateUser(string login)
        {

            using (var ctx = new TrsContext())
            {
                try
                {
                    _ensureDatabaseCreated(ctx);
                    var newUser = new User { UserId = Guid.NewGuid(), Login = login };
                    ctx.Users.Add(newUser);
                    ctx.SaveChanges();
                    return newUser;
                }
                catch (Exception)
                {
                    return null;
                }
            }

        }

        public Project GetProject(string projectName)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var projects = from pr in ctx.Projects where pr.Name == projectName select pr;
                return projects.Count() != 1 ? null : projects.Single();
            }
        }

        public List<Project> GetAllProjects()
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var users = ctx.Projects;
                return users.ToList();
            }
        }

        public List<Project> GetAllProjectsForOwner(string owner)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var users = from pr in ctx.Projects where pr.Owner == owner select pr;
                return users.ToList();
            }
        }

        public Project CreateProject(Project project)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                ctx.Projects.Add(project);
                ctx.SaveChanges();
                return project;
            }
        }

        public Project UpdateProject(Project project)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var existing = ctx.Projects.Filter(p => p.Name == project.Name).Single();
                existing.Budget = project.Budget;
                existing.IsActive = project.IsActive;
                existing.Users = project.Users;
                ctx.SaveChanges();
                return existing;
            }
        }

        public Activity GetActivity(string code)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var activities = from ac in ctx.Activities where ac.Code == code select ac;
                return activities.Count() != 1 ? null : activities.Single();
            }
        }

        public Activity CreateActivity(Activity activity)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                ctx.Activities.Add(activity);
                ctx.SaveChanges();
                return activity;
            }
        }

        public Activity UpdateActivity(Activity updated)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var existing = ctx.Activities.Find(updated.Id);
                ctx.Entry(existing).OriginalValues["RowVersion"] = updated.RowVersion;
                ctx.Entry(existing).CurrentValues.SetValues(updated);
                ctx.SaveChanges();
                return existing;
            }
        }

        public List<Activity> GetAllActivities()
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var activities = ctx.Activities;
                return activities.ToList();
            }
        }

        public List<Activity> GetActivitiesForUserForMonth(string executor, int year, int month)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                // bug workaround which doesn't allow comapring DateTime.Month in query because of nullability(?)
                var startOfMonth = new DateTime(year, month, 1);
                var endOfMonth = startOfMonth.AddMonths(1).AddSeconds(-1);
                var activities = ctx.Activities.Where(ac =>
                    ac.Executor == executor &&
                    ac.Date >= startOfMonth && ac.Date <= endOfMonth
                );
                return activities.ToList();
            }
        }

        public void DeleteActivity(string code, string executor)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var existing = ctx.Activities.Filter(ac => ac.Code == code && ac.Executor == executor).Single();
                ctx.Activities.Remove(existing);
                ctx.SaveChanges();
            }
        }

        public UsersMonth GetUsersMonth(string executor, int year, int month)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                var months = ctx.UsersMonths.Where(mt =>
                    mt.UserLogin == executor &&
                    mt.Year == year &&
                    mt.Month == month
                );
                return months.Count() != 1 ? null : months.Single();
            }
        }

        public UsersMonth AcceptMonthForUser(UsersMonth month)
        {
            using (var ctx = new TrsContext())
            {
                _ensureDatabaseCreated(ctx);
                ctx.UsersMonths.Add(month);
                ctx.SaveChanges();
                return month;
            }
        }

        private void _ensureDatabaseCreated(TrsContext ctx)
        {
            ctx.Database.EnsureCreated();
        }
    }
}