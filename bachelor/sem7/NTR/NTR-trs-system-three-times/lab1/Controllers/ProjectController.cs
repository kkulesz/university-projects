using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using System.Collections.Generic;
using System;
using System.IO;
using System.Linq;

using lab1.Models.Repositories;
using lab1.Models.DomainModel;
using lab1.Models.ViewModel;

using lab1.Controllers.Common;

namespace lab1.Controllers
{
    public class ProjectController : Controller
    {
        public IActionResult ProjectSummaries()
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();

            var ownerProjects = _repo.GetAllProjectsForOwner(owner);
            var allActivities = _repo.GetAllActivities();

            var projectSummaries = new List<ProjectSummary>();
            foreach (var project in ownerProjects)
            {
                var projectSummary = _prepareProjectSummary(project, allActivities);
                projectSummaries.Add(projectSummary);
            }

            return View(projectSummaries);
        }

        public IActionResult ProjectSummaryForMonth(string projectName, DateTime date)
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();
            var year = date.Year;
            var month = date.Month;

            var ownerProjects = _repo.GetAllProjectsForOwner(owner);
            var allActivitiesThisMonth = _repo.GetAllActivities().Filter(a => a.Date.Month == month && a.Date.Year == year).ToList();
            var usersMonth = _repo.GetUsersMonth(owner, year, month) ?? new UsersMonth(year, month, owner, frozen: false);

            var wantedProject = ownerProjects.Find(p => p.Name == projectName);
            if (wantedProject == null)
                return _redirectToProjectView(); //TODO handle this

            var projectSummary = _prepareProjectSummary(wantedProject, allActivitiesThisMonth);
            var projectSummaryWithMonth = new ProjectSummaryWithMonth(projectSummary, usersMonth);
            return View(projectSummaryWithMonth);
        }

        public IActionResult SelectMonthAndProjectName()
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();
            var projects = _repo.GetAllProjectsForOwner(owner);

            return View(projects.ConvertAll(p => p.Name));
        }

        public IActionResult CreateProjectForm()
        {
            return View();
        }

        [HttpPost]
        public IActionResult CreateProject(string projectName, int budget, string subcategory1, string subcategory2)
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();

            var categories = new List<string> { subcategory1, subcategory2 }.Filter(c => c != null).ToList();
            var newProject = new Project(projectName, owner, budget, isActive: true, categories);
            _repo.CreateProject(newProject);

            return _redirectToProjectView();
        }

        public IActionResult MarkProjectNotActive(string projectName)
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();

            var inactive = _repo.GetProject(projectName).Inactive();
            _repo.UpdateProject(inactive);

            return _redirectToProjectView();
        }

        public IActionResult UpdateActivityAcceptedBudgetForm(string activityCode)
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();

            return View(_repo.GetActivity(activityCode));
        }

        public IActionResult UpdateActivityAcceptedBudget(string activityCode, int acceptedBudget)
        {
            string owner = this.HttpContext.Session.GetString(Constants.SessionKeyName);
            if (owner == null)
                return _redirectToLogin();
            var activity = _repo.GetActivity(activityCode);
            _repo.UpdateActivity(activity.SetAcceptedBudget(acceptedBudget));

            return _redirectToProjectView();
        }

        private ProjectSummary _prepareProjectSummary(Project project, List<Activity> activities)
        {
            var thisProjectActivities = activities.Filter(a => a.ProjectName == project.Name).ToList();
            var summedParticipantsBudget = thisProjectActivities.ConvertAll(a => _getParticipantBudget(a)).Sum();

            return new ProjectSummary(project.Name, project.IsActive, project.Budget, summedParticipantsBudget, thisProjectActivities);
        }

        private int _getParticipantBudget(Activity activity)
        {

            return activity.AcceptedBudget ?? activity.Budget;
        }

        private IActionResult _redirectToProjectView()
        {
            return RedirectToAction("ProjectSummaries");
        }

        private IActionResult _redirectToLogin()
        {
            return RedirectToAction("NotLoggedIn", "Auth");
        }
        private IRepository _repo = new RepositoryJson();
    }
}