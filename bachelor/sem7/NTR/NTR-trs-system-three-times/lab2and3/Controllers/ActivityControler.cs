using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using Microsoft.EntityFrameworkCore;
using System;
using System.Linq;
using System.Collections.Generic;

using lab2and3.Models.Repositories;
using lab2and3.Models.DomainModel;
using lab2and3.Models.ViewModel;

using lab2and3.Controllers.Common;

namespace lab2and3.Controllers
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
            var validUsersMonth = usersMonth ?? new UsersMonth
            {
                UsersMonthId = Guid.NewGuid(),
                Year = year,
                Month = month,
                UserLogin = executor,
                Frozen = false
            };

            var projectsThisMonth = activitiesThisMonth.ConvertAll(a => a.Project).Distinct();
            var projectActivitiesList = new List<ProjectActivities>();
            foreach (var projectName in projectsThisMonth)
            {
                var activitiesForThisProject = activitiesThisMonth.Filter(a => a.Project == projectName).ToList();
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

        public IActionResult CreateActivity(string code, string projectName, int budget, DateTime date, string description)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();
            var activity = new Activity
            {
                Code = code,
                Project = projectName,
                Executor = executor,
                Budget = budget,
                AcceptedBudget = null,
                Date = date,
                Subactivities = null,
                Description = description,
                IsActive = true
            };
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
            var activity = _repo.GetActivity(code);
            return View(activity);
        }

        public IActionResult UpdateActivity(Activity updated)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            try
            {
                var result = _repo.UpdateActivity(updated);
                return _redirectToActivityView();
            }
            catch (DbUpdateConcurrencyException exc)
            {
                ModelState.Clear();
                var entry = exc.Entries.Single();
                var dbValues = _repo.GetActivity(updated.Code);
                if (dbValues == null)
                {
                    ModelState.AddModelError(string.Empty, "Unable to save changes. The Activity was deleted by another user.");
                }
                else
                {
                    var clValues = (Activity)entry.Entity;

                    if (dbValues.Budget != clValues.Budget)
                        ModelState.AddModelError("Budget", "Current value: " + dbValues.Budget);

                    if (dbValues.AcceptedBudget != clValues.AcceptedBudget)
                        ModelState.AddModelError("AcceptedBudget", "Current value: " + dbValues.AcceptedBudget);

                    if (dbValues.Date != clValues.Date)
                        ModelState.AddModelError("Date", "Current value: " + dbValues.Date);

                    if (dbValues.Description != clValues.Description)
                        ModelState.AddModelError("Description", "Current value: " + dbValues.Description);

                    ModelState.AddModelError(string.Empty, "The record you attempted to edit "
                                        + "was modified by another user after you got the original value. The "
                                        + "edit operation was canceled and the current values in the database "
                                        + "have been displayed. If you still want to edit this record, click "
                                        + "the Save button again. Otherwise click the Back to List hyperlink.");
                    updated.RowVersion = dbValues.RowVersion;
                }
            }
            catch (Exception)
            {
                ModelState.AddModelError("", "Unable to save changes. Try again, and if the problem persists, see your system administrator.");
            }

            // if we are there, it means there was an error during update, 
            // so we come back to update form instead of activity view

            // return RedirectToAction("UpdateActivityForm", new { code = code });
            return View("UpdateActivityForm", updated);
        }

        public IActionResult AcceptMonth(DateTime date)
        {
            string executor = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (executor == null)
                return _redirectToLogin();

            var month = new UsersMonth
            {
                UsersMonthId = Guid.NewGuid(),
                Year = date.Year,
                Month = date.Month,
                UserLogin = executor,
                Frozen = true
            };

            var activitiesThisMonth = _repo.GetAllActivities()
                    .Filter(a => a.Date.Month == date.Month && a.Date.Year == date.Year)
                    .ToList()
                    .ConvertAll(a => a.Inactive());
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

        private IRepository _repo = new RepositoryEf();
    }
}