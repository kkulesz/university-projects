using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using System;
using System.Linq;

using lab1.Models.Repositories;
using lab1.Models.DomainModel;
using lab1.Models.ViewModel;

using lab1.Controllers.Common;

namespace lab1.Controllers
{
    public class ActivityController : Controller
    {
        public IActionResult MonthSummary(Nullable<DateTime> date)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            var fetchDate = date ?? DateTime.Today;
            var year = fetchDate.Year;
            var month = fetchDate.Month;

            var activitiesThisMonth = _repo.GetActivitiesForUserForMonth(executor, year, month);
            var usersMonth = _repo.GetUsersMonth(executor, year, month);
            var validUsersMonth = usersMonth ?? new UsersMonth(year, month, executor, frozen: false);

            var projectsThisMonth = activitiesThisMonth.ConvertAll(a => a.ProjectName).Distinct();
            var projectActivitiesList = new List<ProjectActivities>();
            foreach (var projectName in projectsThisMonth)
            {
                var activitiesForThisProject = activitiesThisMonth.Filter(a => a.ProjectName == projectName).ToList();
                var projectActivities = new ProjectActivities(projectName, activitiesForThisProject);
                projectActivitiesList.Add(projectActivities);
            }

            var monthSummary = new MonthSummary(projectActivitiesList, validUsersMonth);

            return View(monthSummary);
        }

        public IActionResult CreateActivityForm()
        {
            var projects = _repo.GetAllProjects();
            var activeProjectNames = projects.Filter(p => p.IsActive).ToList().ConvertAll(p => p.Name);
            return View(activeProjectNames);
        }

        public IActionResult CreateActivity(string code, string projectName, int budget, DateTime date, List<String> subactivities, string description)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();
            var activity = new Activity(code, projectName, executor, budget, acceptedBudget: null, date, subactivities, description, isActive: true);
            _repo.CreateActivity(activity);
            return _redirectToActivityView();
        }

        public IActionResult DeleteActivity(string code)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            _repo.DeleteActivity(code, executor);
            return _redirectToActivityView();
        }

        public IActionResult ShowActivity(string code)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            var activity = _repo.GetActivity(code);
            if (activity == null)
            {
                return _redirectToActivityView();
            }

            return View(activity);
        }

        public IActionResult UpdateActivityForm(string code)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            return View(_repo.GetActivity(code));
        }

        public IActionResult UpdateActivity(string code, string projectName, string executorName, int budget, int acceptedBudget, DateTime date, List<String> subactivities, string description, bool isActive)
        {
            var updated = new Activity(code, projectName, executorName, budget, acceptedBudget, date, subactivities, description, isActive);
            var result = _repo.UpdateActivity(updated);
            if (result == null)
                return _redirectToActivityView(); //TODO handle error
            return _redirectToActivityView();
        }

        public IActionResult AcceptMonth(DateTime date)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            var month = new UsersMonth(date.Year, date.Month, executor, frozen: true);
            var activitiesThisMonth = _repo.GetAllActivities()
                    .Filter(a => a.Date.Month == date.Month && a.Date.Year == date.Year)
                    .ToList()
                    .ConvertAll(a => a.SetInactive());
            _repo.AcceptMonthForUser(month);
            foreach (var act in activitiesThisMonth)
            {
                _repo.UpdateActivity(act);
            }

            return _redirectToActivityView();
        }

        private IActionResult _redirectToActivityView()
        {
            return RedirectToAction("MonthSummary");
        }

        private IActionResult _redirectToLogin()
        {
            return RedirectToAction("NotLoggedIn", "Auth");
        }

        private IRepository _repo = new RepositoryJson();
    }
}